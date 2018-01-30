#include "hal_uart_ctrl.h"


UsuartTypedef uart[cfgUSUART_USFUL_NUM];   //总共定义了3个

static USUART_StatusTypeDef UART_WaitOnFlagUntilTimeout(uint8_t idx, uint32_t Flag, FlagStatus Status, uint32_t Tickstart, uint32_t Timeout);
static void usuart_defInit(uint8_t idx);
static void usuart_ctrlCfg(uint8_t idx);
static void usart_dma_tx_init(int idx);
static void usart_dma_rx_init(int idx);

void hal_usuart_init(void){
    usuart_defInit(USUART_IDX_DBG);                                                   //  调试串口
    usuart_defInit(USUART_IDX_LPLAM);                                                 //  左手臂步进电机串口
    usuart_defInit(USUART_IDX_RPLAM);                                                 //  右手臂步进电机串口
    usuart_defInit(USUART_IDX_RK);                                                    //  RK通信步进电机串口
    usuart_defInit(USUART_IDX_ARM);                                                   //  485通信
}

static void usuart_defInit(uint8_t idx){
    rcu_periph_clock_enable(RCU_AF);    
   switch(idx){
       case USUART_IDX_DBG:{
           rcu_periph_clock_enable(RCU_GPIOA);
           gpio_init(cfgUSART0_TX_PORT,GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,cfgUSART0_TX_PIN);
           gpio_init(cfgUSART0_RX_PORT,GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ,cfgUSART0_RX_PIN);   
           uart[USUART_IDX_DBG].param.periph=cfgUSART_DBG_PERIPTH;
           uart[USUART_IDX_DBG].param.clk=cfgUSART_DBG_CLK;
           uart[USUART_IDX_DBG].param.baudrate=115200U;
           uart[USUART_IDX_DBG].param.parity=USART_PM_NONE;
           uart[USUART_IDX_DBG].param.stblen=USART_STB_1BIT;
           uart[USUART_IDX_DBG].param.wlen=USART_WL_8BIT;
           uart[USUART_IDX_DBG].param.brDma=cfgUSART_DBG_RDMA;
           uart[USUART_IDX_DBG].param.bwDma=cfgUSART_DBG_WDMA;
           uart[USUART_IDX_DBG].param.gState=HAL_UART_STATE_READY;
           uart[USUART_IDX_DBG].param.irq=cfgUSART0_IRQ;
           uart[USUART_IDX_DBG].param.priority=cfgUSART0_PRIORITY;
           uart[USUART_IDX_DBG].param.subpriority=cfgUSART0_SUB_PRIORITY;
       }break;
       
       case USUART_IDX_LPLAM:{
           rcu_periph_clock_enable(RCU_GPIOA);
           gpio_init(cfgUSART1_TX_PORT,GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,cfgUSART2_TX_PIN);
           gpio_init(cfgUSART1_RX_PORT,GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ,cfgUSART2_RX_PIN);   
           uart[USUART_IDX_LPLAM].param.periph=cfgUSART_LPLAM_PERIPTH;
           uart[USUART_IDX_LPLAM].param.clk=cfgUSART_LPLAM_CLK;
           uart[USUART_IDX_LPLAM].param.baudrate=115200U;
           uart[USUART_IDX_LPLAM].param.parity=USART_PM_NONE;
           uart[USUART_IDX_LPLAM].param.stblen=USART_STB_1BIT;
           uart[USUART_IDX_LPLAM].param.wlen=USART_WL_8BIT;
           uart[USUART_IDX_LPLAM].param.brDma=cfgUSART_LPLAM_RDMA;
           uart[USUART_IDX_LPLAM].param.bwDma=cfgUSART_LPLAM_WDMA;
           uart[USUART_IDX_LPLAM].param.gState=HAL_UART_STATE_READY;
           uart[USUART_IDX_LPLAM].param.irq=cfgUSART1_IRQ;
           uart[USUART_IDX_LPLAM].param.priority=cfgUSART1_PRIORITY;
           uart[USUART_IDX_LPLAM].param.subpriority=cfgUSART1_SUB_PRIORITY;
       }break;
       
       case USUART_IDX_RPLAM:{
           rcu_periph_clock_enable(RCU_GPIOB);
           gpio_init(cfgUSART2_TX_PORT,GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,cfgUSART2_TX_PIN);
           gpio_init(cfgUSART2_RX_PORT,GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ,cfgUSART2_RX_PIN);       
           uart[USUART_IDX_RPLAM].param.periph=cfgUSART_RPLAM_PERIPTH;
           uart[USUART_IDX_RPLAM].param.clk=cfgUSART_RPLAM_CLK;
           uart[USUART_IDX_RPLAM].param.baudrate=115200U;
           uart[USUART_IDX_RPLAM].param.parity=USART_PM_NONE;
           uart[USUART_IDX_RPLAM].param.stblen=USART_STB_1BIT;
           uart[USUART_IDX_RPLAM].param.wlen=USART_WL_8BIT;
           uart[USUART_IDX_RPLAM].param.brDma=cfgUSART_RPLAM_RDMA;
           uart[USUART_IDX_RPLAM].param.bwDma=cfgUSART_RPLAM_WDMA;
           uart[USUART_IDX_RPLAM].param.gState=HAL_UART_STATE_READY;
           uart[USUART_IDX_RPLAM].param.irq=cfgUSART2_IRQ;
           uart[USUART_IDX_RPLAM].param.priority=cfgUSART2_PRIORITY;
           uart[USUART_IDX_RPLAM].param.subpriority=cfgUSART2_SUB_PRIORITY;
       }break;
      
       case USUART_IDX_RK:{
           rcu_periph_clock_enable(RCU_GPIOC);
           gpio_init(cfgUART3_TX_PORT,GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,cfgUART3_TX_PIN);
           gpio_init(cfgUART3_RX_PORT,GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ,cfgUART3_RX_PIN);      
           uart[USUART_IDX_RK].param.periph=cfgUSART_RK_PERIPTH;
           uart[USUART_IDX_RK].param.clk=cfgUSART_RK_CLK;
           uart[USUART_IDX_RK].param.baudrate=115200U;
           uart[USUART_IDX_RK].param.parity=USART_PM_NONE;
           uart[USUART_IDX_RK].param.stblen=USART_STB_1BIT;
           uart[USUART_IDX_RK].param.wlen=USART_WL_8BIT;
           uart[USUART_IDX_RK].param.brDma=cfgUSART_RK_RDMA;
           uart[USUART_IDX_RK].param.bwDma=cfgUSART_RK_WDMA;
           uart[USUART_IDX_RK].param.gState=HAL_UART_STATE_READY;
           uart[USUART_IDX_RK].param.irq=cfgUART3_IRQ;
           uart[USUART_IDX_RK].param.priority=cfgUSART3_PRIORITY;
           uart[USUART_IDX_RK].param.subpriority=cfgUSART3_SUB_PRIORITY;
       }break;
       
       case USUART_IDX_ARM:{  //暂时没用
           rcu_periph_clock_enable(RCU_GPIOC);
           rcu_periph_clock_enable(RCU_GPIOD);
           gpio_init(cfgUART4_TX_PORT,GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,cfgUART4_TX_PIN);
           gpio_init(cfgUART4_RX_PORT,GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ,cfgUART4_RX_PIN);    
           uart[USUART_IDX_ARM].param.periph=cfgUSART_ARM_PERIPTH;
           uart[USUART_IDX_ARM].param.clk=cfgUSART_ARM_CLK;
           uart[USUART_IDX_ARM].param.baudrate=115200U;
           uart[USUART_IDX_ARM].param.parity=USART_PM_NONE;
           uart[USUART_IDX_ARM].param.stblen=USART_STB_1BIT;
           uart[USUART_IDX_ARM].param.wlen=USART_WL_8BIT;
           uart[USUART_IDX_ARM].param.brDma=cfgUSART_ARM_RDMA;
           uart[USUART_IDX_ARM].param.bwDma=cfgUSART_ARM_WDMA;
           uart[USUART_IDX_ARM].param.gState=HAL_UART_STATE_READY;
           uart[USUART_IDX_ARM].param.irq=cfgUART4_IRQ;
           uart[USUART_IDX_ARM].param.priority=cfgUSART4_PRIORITY;
           uart[USUART_IDX_ARM].param.subpriority=cfgUSART4_SUB_PRIORITY;
          
       }break;
       default:{
       
       }break;
   }
   usuart_ctrlCfg(idx);
}


static void usuart_ctrlCfg(uint8_t idx){
    rcu_periph_clock_enable(uart[idx].param.clk);                       // 使能时钟 
    usart_deinit(uart[idx].param.periph);                                      // 先恢复然后再初始化
    usart_baudrate_set(uart[idx].param.periph,uart[idx].param.baudrate);       // 设置波特率
    usart_parity_config(uart[idx].param.periph,uart[idx].param.parity);        // 设置校验位
    usart_word_length_set(uart[idx].param.periph,uart[idx].param.wlen);        // 设置数据长度
    usart_stop_bit_set(uart[idx].param.periph,uart[idx].param.stblen);         // 设置停止位
    if(uart[idx].param.bwDma){
       usart_dma_tx_init(idx);
       usart_dma_transmit_config(uart[idx].param.periph,USART_DENT_ENABLE);    // 配置输出为DMA
    }else{
       usart_transmit_config(uart[idx].param.periph,USART_TRANSMIT_ENABLE);    // 使能数据发送
    }
    
    if(uart[idx].param.brDma){
       usart_dma_rx_init(idx);
       usart_dma_receive_config(uart[idx].param.periph,USART_DENR_ENABLE);     // 配置读数据为DMA
    }else{
       usart_receive_config(uart[idx].param.periph,USART_RECEIVE_ENABLE);     // 使能接收
    }
    usart_enable(uart[idx].param.periph);
    usart_interrupt_enable(uart[idx].param.periph,USART_INT_RBNE);             // 接收中断
    nvic_irq_enable(uart[idx].param.irq, uart[idx].param.priority, uart[idx].param.subpriority);  //抢占出问题了吗
}

/***********************************
 *      通道
 **********************************/
static void usart_dma_tx_init(int idx){//必须查看开发说明文档，串口对应DMA通道
      dma_parameter_struct param;
   switch(idx){
       case USUART_IDX_DBG:{   //调试用，不支持DMA
            // RX DMA0 CH4    TX  DMA0 CH3
           
       }
       case USUART_IDX_RPLAM:{
           // RX DMA0 CH2   TX DMA0 CH1
           
       }break;
       case USUART_IDX_LPLAM:{//串口1
           // RX DMA0 CH5   TX DMA0 CH6
           
          dma_deinit(DMA0,DMA_CH2);
       }break;
       
       case USUART_IDX_RK:{ //串口3
          // RX DMA1 CH2   TX DMA1 CH4
       }break;
       
       //不能用
       case USUART_IDX_ARM:{  //UART4不支持DMA
         // NOT SUPPORT
       }break;
       
       default:{
       
       }break;
   }

}



/***********************************
 *      通道
 **********************************/
static void usart_dma_rx_init(int idx){//必须查看开发说明文档，串口对应DMA通道
      dma_parameter_struct param;
   switch(idx){
       case USUART_IDX_DBG:{   //调试用，不支持DMA
            // RX DMA0 CH4
           
       }
       case USUART_IDX_RPLAM:{
           // RX DMA0 CH2
           
       }break;
       case USUART_IDX_LPLAM:{//串口1
           // RX DMA0 CH5
          dma_deinit(DMA0,DMA_CH2);
       }break;
       
       case USUART_IDX_RK:{ //串口3
          // RX DMA1 CH2
       }break;
       
       //不能用
       case USUART_IDX_ARM:{  //UART4不支持DMA
          // NOT SUPPORT
       }break;
       
       default:{
       
       }break;
   }

}


/****************************************
 *     串口数据发送封装
 ***************************************/
USUART_StatusTypeDef usuart_send(uint8_t idx,uint8_t* data,uint32_t length,uint32_t timeOut){// 开一个任务定时发送
    uint32_t tickStart;
    if(uart[idx].param.gState==HAL_UART_STATE_READY){//数据已经发送完了
      if((data==NULL) || (length==0U)){
        return USUART_ERROR;   //如果长度为0
      }
     __HAL_LOCK(&uart[idx].param);
        uart[idx].param.TxXferCount=length;
        uart[idx].param.TxXferSize=length;
        tickStart=HAL_GetTick();
        uart[idx].param.gState=HAL_UART_STATE_BUSY_TX;  //发送忙
        while(uart[idx].param.TxXferCount>0){
           uart[idx].param.TxXferCount--;
           if(UART_WaitOnFlagUntilTimeout(idx,USART_FLAG_TBE,RESET,tickStart,timeOut)!=USUART_OK){
               return USUART_TIMEOUT;
           }
            usart_data_transmit(uart[idx].param.periph,(*data++ & (uint8_t)0xFFU));
           if(UART_WaitOnFlagUntilTimeout(idx,USART_FLAG_TBE,RESET,tickStart,timeOut)!=USUART_OK){
             return USUART_TIMEOUT;
           }
        }        
     __HAL_UNLOCK(&uart[idx].param);  
      uart[idx].param.gState=HAL_UART_STATE_READY;        
     return USUART_OK;
    }else{
     return USUART_BUSY;
    }
}


USUART_StatusTypeDef usuart_dma_send(uint8_t idx,uint8_t* data,uint32_t length){
    return USUART_OK;
}




/*****************************
 *      等待超时
 ****************************/
USUART_StatusTypeDef UART_WaitOnFlagUntilTimeout(uint8_t idx, uint32_t Flag, FlagStatus Status, uint32_t Tickstart, uint32_t Timeout){
    while(usart_flag_get(uart[idx].param.periph,USART_FLAG_TBE)!=SET){  //数据还没有发送完毕
       if(Timeout!=HAL_MAX_DELAY){
          if((Timeout == 0U) || ((HAL_GetTick()-Tickstart) > Timeout))//如果是timeout延时时间是0或者已经超时了，则需要清空发送的buffer
          {
             usart_interrupt_flag_clear(uart[idx].param.periph,USART_INT_TBE|USART_INT_RBNE|USART_INT_PERR|USART_INT_ERR);//清空标志位
             uart[idx].param.gState= HAL_UART_STATE_READY;
             uart[idx].param.rxState= HAL_UART_STATE_READY;
             __HAL_UNLOCK(&uart[idx].param);   
             return USUART_TIMEOUT;
          }
       }
    }
    return USUART_OK;
}


void usuart_clear(uint8_t idx){
    uart[idx].rbuff.wptr=0;
    uart[idx].rbuff.rptr=0;
}

/******************************
 *     从buf中读取数据
 *****************************/
void usuart_read(uint8_t idx,uint8_t*data,uint8_t readLen,int wait){

}


/********************
 *  往buf中写入数据
 ********************/
int usuart_pushToBuf(uint8_t idx,uint8_t* data,uint32_t length){
   
    return 0;
}

/*******************
 *      读取数据
 ******************/
int usuart_pullFromBuf(uint8_t idx,uint8_t* data,uint32_t length){

   return 0;
}



void USART0_IRQHandler(void){
    uint8_t data;
    if(RESET != usart_flag_get(USART0, USART_FLAG_RBNE))
	 {
		data=(usart_data_receive(USART0) & 0xFF);
         
     } 
	 
	if(RESET != usart_flag_get(USART0, USART_FLAG_TBE))
	{

      //usart_data_transmit(USART0,data);	 
	}	
}



