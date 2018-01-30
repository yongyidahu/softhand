#include "hal_rs485_ctrl.h"


uint16_t cmdLen=0;
uint8_t  cmdLine[64];
uint8_t  recvLine[64];
uint8_t bRecvFlg=0;
void rs485_write_cmd(int id,uint8_t cmd,uint8_t* data,uint16_t length);
static void rs485_add_head(void);
static void rs485_add_cmd(uint8_t id,uint8_t cmd);
static void rs485_add_param(uint8_t subCmd,int param);
uint8_t rs485_checkodd(uint8_t* data,int length);
static void rs485_cmdLine_len(void);
static void rs485_recv_enable(void);
static void rs485_recv_disable(void);
static void delayUs(uint16_t us);

uint8_t recvData=0;
ServoAck_t ack;
/*************************
 *     用于控制舵机
 ************************/

void hal_rs485_init(void){
    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_init(cfgBUS_EN_PORT,GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,cfgBUS_EN_PIN);
    rs485_recv_enable();
    ack.state=ACK_STATE_HEAD_1;
}

void hal_rs485_ctrl(void){
      
}



void rs485_recv_enable(void){
   gpio_bit_reset(cfgBUS_EN_PORT,cfgBUS_EN_PIN); //根据规格书显示，

}


void rs485_recv_disable(void){
    gpio_bit_set(cfgBUS_EN_PORT,cfgBUS_EN_PIN); 
}


int rs485_get_id(int id){
     if(id>12){
      //查询错误，返回-1
       return -1;
     }
     rs485_add_head();
     rs485_add_cmd(id+1,cfgSERVO_REQ_CMD_READ);
     rs485_add_param(REG_ID,0x01);
     rs485_cmdLine_len();
     cmdLine[cmdLen]=rs485_checkodd(cmdLine,cmdLen);
     rs485_recv_disable();
     delayUs(3);
     usuart_send(USUART_IDX_ARM,cmdLine,cmdLen,10);  //发送数据
     delayUs(5);    // 适当延时，否则有可能出错
     rs485_recv_enable();
     return 0;     
}

int rs485_ping_state(int id){
    if(id>12){
      //查询错误，返回-1
       return -1;
     }
     rs485_add_head();
     rs485_add_cmd(id+1,cfgSERVO_REQ_CMD_PING);
     rs485_cmdLine_len();
     cmdLine[cmdLen]=rs485_checkodd(cmdLine,cmdLen);
     rs485_recv_disable();
     delayUs(3);
     usuart_send(USUART_IDX_ARM,cmdLine,cmdLen,10);  //发送数据
     delayUs(5);   // 适当延时，否则有可能出错
     rs485_recv_enable();
     return 0; 
}

/**********************
 *    重新编写ID
 **********************/
void rs485_write_id(int id){
  
}

/***********************
 *  上电查询工作状态
 **********************/
void rs485_query_state(int idx){
    
}


/***********************
 *    恢复出厂设置
 **********************/
void rs485_resetdef(void){


}

/*********************
 *  添加命令行头部
 ********************/
static void rs485_add_head(){
    memset(cmdLine,0,sizeof(cmdLine));
    cmdLine[0]=cfgSERVO_REQ_HEAD_1;
    cmdLine[1]=cfgSERVO_REQ_HEAD_2;
    cmdLen=2;
}

void rs485_add_cmd(uint8_t id,uint8_t cmd){
    cmdLine[cmdLen]=id;
    cmdLine[cmdLen+1]=0;   //先将长度设置为0后续根据数据长度来再次做出更新
    cmdLine[cmdLen+2]=cmd;
    cmdLen+=3;
}

void rs485_add_param(uint8_t subCmd,int param){ // param可以是设置的数据也可以代表读取的长度
    cmdLine[cmdLen]=subCmd;
    if(param!=-1){
      cmdLine[cmdLen+1]=(uint8_t)param;
      cmdLen+=2;
    }else{
      cmdLen+=1;
    }
}

/**********************
 *     进行数据校验
 *********************/
uint8_t rs485_checkodd(uint8_t* data,int length){
    long sum=0;
    int i=0;
    for(i=2;i<length;i++){
       sum+=data[i];
    }
    sum=~sum;
    cmdLen+=1;
    
    return (uint8_t)(sum&0xff);
}

/**********************
 *     设置命令行长度
 **********************/
void rs485_cmdLine_len(void){
     cmdLine[3]=cmdLen-3;   //先将长度设置为0后续根据数据长度来再次做出更新
}




/**********************
 *     延时函数
 *********************/
static void delayUs(uint16_t us){
    uint16_t i=0;
    for(i=0;i<us*108;i++);
}

/*************************************
 *          解析反馈数据
 ************************************/
static void rs485_parseRecv(uint8_t data){
    recvLine[ack.curPos]=data;
    switch(ack.state){
        case ACK_STATE_HEAD_1:{
           if(data==0xff){
             ack.state=ACK_STATE_HEAD_2;
             ack.bHead1Recv=1;
           }
            ack.startPos=0;
            ack.curPos=0;
        }break;
        
        case ACK_STATE_HEAD_2:{
          if(data==0xf5){
            if(ack.bHead1Recv==1){
               ack.bHeadRecv=1;
               ack.bHead1Recv=0;
               ack.state=ACK_STATE_ID;
            }else{
              ack.state=ACK_STATE_HEAD_1;
            }
          }else{
            ack.state=ACK_STATE_HEAD_1;
          }
        }break;
        
        case ACK_STATE_ID:{
            ack.id=data;
            ack.state=ACK_STATE_LEN;
        }break;
        
        case ACK_STATE_LEN:{
            ack.paramLen=data;
            ack.state=ACK_STATE_CONTENT;
            ack.len=0;
        }break;
        
        case ACK_STATE_CONTENT:{
            ack.len++;
            if(ack.len==ack.paramLen-1){
               ack.state=ACK_STATE_ODD;
            }
        }break;
        
        case ACK_STATE_ODD:{
           ack.state=ACK_STATE_HEAD_1;
           ack.odd= rs485_checkodd(recvLine,ack.curPos-1);
           if(data==ack.odd){
            //接收到正确数据
            bRecvFlg=1;
           }
           ack.len=ack.curPos;
           ack.bHead1Recv=0;
        }break;
       
        default:{
        
        }break;
    }
    ack.curPos= (ack.curPos+1)%64;
}

void UART4_IRQHandler(void){
     if(RESET != usart_flag_get(UART4, USART_FLAG_RBNE))
	 {
	   recvData= usart_data_receive(UART4);
       rs485_parseRecv(recvData);
     } 
}




