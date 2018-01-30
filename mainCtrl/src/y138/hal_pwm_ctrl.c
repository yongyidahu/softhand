#include "hal_pwm_ctrl.h"

ServoCtrlTypedef servo[3];  //有两个舵机
static void servo_pwm_def(int idx);

static uint8_t timeTable[16]={0};   //速度等级控制  设置不同的PWM等级
static void servo_pwm_init(int idx);
static void servo_timer_init(int idx);
static void servo_write_pwm(int idx,uint16_t pwm);
static void servo_power_on(void);
static void servo_power_off(void);

void hal_pwm_init(void){
     rcu_periph_clock_enable(RCU_GPIOC);
     rcu_periph_clock_enable(RCU_GPIOB);
     rcu_periph_clock_enable(RCU_TIMER2);
     gpio_init(GPIOC,GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_1);
     servo_power_on();
     servo_pwm_def(SERVO_ID_LR);    // 初始化头部左右
     servo_pwm_def(SERVO_ID_UD);    // 初始化头部上下
     servo_pwm_def(SERVO_ID_EX);    // 初始化头部上下
     servo_timer_init(SERVO_ID_EX); // 只需要初始化一次
     servo_pwm_init(SERVO_ID_LR);   // 
     servo_pwm_init(SERVO_ID_UD);   //
     servo_pwm_init(SERVO_ID_EX);   //
}

void servo_power_on(void){
   gpio_bit_set(GPIOC,GPIO_PIN_1);

}

void servo_power_off(void){
   gpio_bit_reset(GPIOC,GPIO_PIN_1);
}

void servo_timer_init(int idx){
     timer_parameter_struct initpara;
     rcu_periph_clock_enable(RCU_TIMER2);
     timer_deinit(TIMER2);
     initpara.clockdivision=TIMER_CKDIV_DIV1;
     initpara.counterdirection= TIMER_COUNTER_UP;
     initpara.prescaler=108-1;  //  分频
     initpara.period=20000-1;     //  20ms 定时
     timer_init(TIMER2,&initpara);
}

/****************************
 *        PWM初始化
 ***************************/
void servo_pwm_init(int idx){
     timer_oc_parameter_struct ocPara;  // PWM输出
     ocPara.ocidlestate=TIMER_OC_IDLE_STATE_LOW;
     ocPara.ocpolarity=TIMER_OC_POLARITY_LOW;
     ocPara.outputstate=TIMER_CCX_ENABLE;
     timer_channel_output_config(servo[idx].defParam.periph,servo[idx].defParam.channel,&ocPara);  
     timer_channel_output_mode_config(servo[idx].defParam.periph,servo[idx].defParam.channel,TIMER_OC_MODE_PWM1);
     timer_auto_reload_shadow_enable(servo[idx].defParam.periph);
     timer_enable(servo[idx].defParam.periph);
     timer_channel_output_pulse_value_config(servo[idx].defParam.periph,servo[idx].defParam.channel,servo[idx].defParam.defPwm); 
}

void servo_write_pwm(int idx,uint16_t pwm){
     timer_channel_output_pulse_value_config(servo[idx].defParam.periph,servo[idx].defParam.channel,servo[idx].defParam.defPwm); 
}

/*************************
 *    上电设置PWM参数
 ************************/
void servo_pwm_def(int idx){
     switch(idx){
         case SERVO_ID_LR:{
             gpio_init(GPIOB,GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_0);
             servo[idx].defParam.maxHPwm=cfgSERVO_PWM_LR_HMAX;     // 硬件定义 最大 MAX
             servo[idx].defParam.minHPwm=cfgSERVO_PWM_LR_HMIN;     // 硬件定义 最小 MIN  
             servo[idx].defParam.maxSPwm=cfgSERVO_PWM_LR_SMAX;     // 软件定义 最大 MAX
             servo[idx].defParam.minSPwm=cfgSERVO_PWM_LR_SMIN;     // 软件定义 最小 MIN  
             servo[idx].defParam.defPwm=cfgSERVO_PWM_LR_DEF;       // 默认PWM
             servo[idx].defParam.step=cfgSERVO_PWM_LR_STEP;       // 每一步走的脉宽
             servo[idx].defParam.periph=TIMER2;
             servo[idx].defParam.angle=(float)cfgSERVO_ANGLE_LR_MAX/500;
             servo[idx].defParam.maxHAngle=cfgSERVO_ANGLE_LR_MAX;
             servo[idx].defParam.channel=TIMER_CH_2;
             servo[idx].pwm.currentStep=250;
         }break;
         case SERVO_ID_UD:{
             gpio_init(GPIOB,GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_1);
             servo[idx].defParam.maxHPwm=cfgSERVO_PWM_UD_HMAX;     // 硬件定义 最大 MAX
             servo[idx].defParam.minHPwm=cfgSERVO_PWM_UD_HMIN;     // 硬件定义 最小 MIN  
             servo[idx].defParam.maxSPwm=cfgSERVO_PWM_UD_SMAX;     // 软件定义 最大 MAX
             servo[idx].defParam.minSPwm=cfgSERVO_PWM_UD_SMIN;     // 软件定义 最小 MIN  
             servo[idx].defParam.defPwm=cfgSERVO_PWM_UD_DEF;       // 默认PWM
             servo[idx].defParam.step=cfgSERVO_PWM_UD_STEP;       // 每一步走的脉宽 
             servo[idx].defParam.periph=TIMER2;
             servo[idx].defParam.maxHAngle=cfgSERVO_ANGLE_UD_MAX;
             servo[idx].defParam.angle=(float)cfgSERVO_ANGLE_UD_MAX/500;
             servo[idx].defParam.channel=TIMER_CH_3;
             servo[idx].pwm.currentStep=250;
         }break;
         
         case SERVO_ID_EX:{
             gpio_init(GPIOB,GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);
             servo[idx].defParam.maxHPwm=cfgSERVO_PWM_EX_HMAX;     // 硬件定义 最大 MAX
             servo[idx].defParam.minHPwm=cfgSERVO_PWM_EX_HMIN;     // 硬件定义 最小 MIN  
             servo[idx].defParam.maxSPwm=cfgSERVO_PWM_EX_SMAX;     // 软件定义 最大 MAX
             servo[idx].defParam.minSPwm=cfgSERVO_PWM_EX_SMIN;     // 软件定义 最小 MIN  
             servo[idx].defParam.defPwm=cfgSERVO_PWM_EX_DEF;       // 默认PWM
             servo[idx].defParam.step=cfgSERVO_PWM_EX_STEP;        // 每一步走的脉宽 
             servo[idx].defParam.periph=TIMER2;
             servo[idx].defParam.maxHAngle=cfgSERVO_ANGLE_EX_MAX;
             servo[idx].defParam.angle=(float)cfgSERVO_ANGLE_EX_MAX/500;
             servo[idx].defParam.channel=TIMER_CH_1;               // 都需要相应的减去1
             servo[idx].pwm.currentStep=250;
         }break;
         default:{
         
         }break;
     }
}

static uint16_t servo_getPwmFromAngle(uint8_t idx, uint16_t angle){
     return (uint16_t)(500+angle*((float)(servo[idx].defParam.maxHPwm-servo[idx].defParam.minHPwm)/servo->defParam.maxHAngle));//将角度转化成PWM值
}




static uint16_t servo_getAngleFromPwm(){



}

void servo_pwm_start(int idx){
   if( servo[idx].state!=SERVO_STATE_RUN){
       servo[idx].state=SERVO_STATE_START;
   }
}

void servo_pwm_stop(int idx){
   servo[idx].state=SERVO_STATE_STOP;
}


void servo_pwm_notifyAngle(int idx,uint16_t step){
    uint16_t angle=step*servo[idx].defParam.maxHAngle/500;
    if(angle!=servo[idx].angle.current){
       servo[idx].angle.current=angle;
       servo[idx].angle.bchange=1;   // 更新数据
    }
}

void servo_pwm_writeTimeParam(int idx,RKPwmCtrl_t rkCmd){  //循环的时候根据时间和角度来计算速度 循环则根据这个速度进行控制
    uint16_t leftPwm=0,step=0;
    if(rkCmd.param==0){// 时间为0
       servo_pwm_stop(idx);   
       return;
   }
   servo[idx].pwm.bRecyle=rkCmd.bRecyle;  //是否来回循环
   servo[idx].pwm.direction=rkCmd.direction;
   if( servo[idx].pwm.direction==0){
       leftPwm=servo[idx].defParam.maxSPwm-servo[idx].pwm.currentPwm;
       if(leftPwm<=servo[idx].defParam.step){
         servo[idx].pwm.currentStep+=1; //又多走了一步
         servo[idx].pwm.currentPwm=servo[idx].pwm.targetPwm=servo[idx].defParam.maxSPwm;
         servo_write_pwm(idx,servo[idx].pwm.currentPwm);
         servo[idx].pwm.direction=1;
         if(!servo[idx].pwm.bRecyle){
            servo_pwm_stop(idx);              
            return;
         }
         servo_pwm_notifyAngle(idx,servo[idx].pwm.currentStep);
       }else{
         step=(servo[idx].pwm.targetPwm-servo[idx].pwm.currentPwm)/servo[idx].defParam.step;
         servo[idx].pwm.nStep=((servo[idx].pwm.targetPwm-servo[idx].pwm.currentPwm)%servo[idx].defParam.step==0)?step:step+1;
       }
   }else{
       leftPwm=servo[idx].pwm.currentPwm-servo[idx].defParam.minSPwm;
       if(leftPwm<=servo[idx].defParam.step){
         servo[idx].pwm.currentStep+=1; //又多走了一步
         servo[idx].pwm.currentPwm=servo[idx].pwm.targetPwm=servo[idx].defParam.minSPwm;
         servo_write_pwm(idx,servo[idx].pwm.currentPwm);
         servo[idx].pwm.direction=0;
         if(!servo[idx].pwm.bRecyle){
            servo_pwm_stop(idx);   
            return;
         }
       }else{
         step=(servo[idx].pwm.currentPwm-servo[idx].pwm.targetPwm)/servo[idx].defParam.step;
         servo[idx].pwm.nStep=((servo[idx].pwm.currentPwm-servo[idx].pwm.targetPwm)%servo[idx].defParam.step==0)?step:step+1; //需要走的总步数
       }
   }
     servo[idx].pwm.waitTime=(rkCmd.param/rkCmd.angle)*servo[idx].defParam.angle;//需要的延时时间
     servo[idx].pwm.waitTime=(servo[idx].pwm.waitTime==0)?timeTable[8]:servo[idx].pwm.waitTime;
     servo_pwm_start(idx);
}

void servo_pwm_writeSpeedParam(int idx,RKPwmCtrl_t rkCmd){
   uint16_t leftPwm=0,step=0;
    // 复位的时候是以速度进行控制
  if(rkCmd.param==0){// 时间为0
       return;
   }
  servo[idx].pwm.bRecyle=rkCmd.bRecyle;  //是否来回循环
  servo[idx].pwm.direction=rkCmd.direction;
 if( servo[idx].pwm.direction==0){
       leftPwm=servo[idx].defParam.maxSPwm-servo[idx].pwm.currentPwm;
       if(leftPwm<=servo[idx].defParam.step){
         servo[idx].pwm.currentStep+=1; //又多走了一步
         servo[idx].pwm.currentPwm=servo[idx].pwm.targetPwm=servo[idx].defParam.maxSPwm;
         servo_write_pwm(idx,servo[idx].pwm.currentPwm);
         servo[idx].pwm.direction=1;
         if(!servo[idx].pwm.bRecyle){
            servo_pwm_stop(idx);   
            return;
         }  
       }else{
         step=(servo[idx].pwm.targetPwm-servo[idx].pwm.currentPwm)/servo[idx].defParam.step;
         servo[idx].pwm.nStep=((servo[idx].pwm.targetPwm-servo[idx].pwm.currentPwm)%servo[idx].defParam.step==0)?step:step+1;
       }
   }else{
       leftPwm=servo[idx].pwm.currentPwm-servo[idx].defParam.minSPwm;
       if(leftPwm<=servo[idx].defParam.step){
         servo[idx].pwm.currentStep+=1; //又多走了一步
         servo[idx].pwm.currentPwm=servo[idx].pwm.targetPwm=servo[idx].defParam.minSPwm;
         servo_write_pwm(idx,servo[idx].pwm.currentPwm);
         servo[idx].pwm.direction=0;
         if(!servo[idx].pwm.bRecyle){
            servo_pwm_stop(idx);   
            return;
         }     
       }else{
         step=(servo[idx].pwm.currentPwm-servo[idx].pwm.targetPwm)/servo[idx].defParam.step;
         servo[idx].pwm.nStep=((servo[idx].pwm.currentPwm-servo[idx].pwm.targetPwm)%servo[idx].defParam.step==0)?step:step+1; //需要走的总步数
       }
   }   
}

void servo_pwm_writeResetParam(int idx,RKPwmCtrl_t rkCmd){
    // 复位的时候是以速度进行控制
    uint16_t leftPwm=0,step=0;
    servo[idx].pwm.targetPwm=1500;
    if(servo[idx].pwm.currentPwm>=1500){
       servo[idx].pwm.direction=1;
    }else{
       servo[idx].pwm.direction=0;
    }
    if(servo[idx].pwm.direction==0){
       leftPwm=1500-servo[idx].pwm.currentPwm;
       if(leftPwm<=servo[idx].defParam.step){
         servo[idx].pwm.currentStep+=1; //又多走了一步
         servo[idx].pwm.currentPwm=servo[idx].pwm.targetPwm=1500;
         servo_write_pwm(idx,servo[idx].pwm.currentPwm);
         servo[idx].pwm.direction=1;
       }else{
         step=(1500-servo[idx].pwm.currentPwm)/servo[idx].defParam.step;
         servo[idx].pwm.nStep=((1500-servo[idx].pwm.currentPwm)%servo[idx].defParam.step==0)?step:step+1;
       }
   }else{
       leftPwm=servo[idx].pwm.currentPwm-1500;
       if(leftPwm<=servo[idx].defParam.step){
         servo[idx].pwm.currentStep+=1; //又多走了一步
         servo[idx].pwm.currentPwm=servo[idx].pwm.targetPwm=1500;
         servo_write_pwm(idx,servo[idx].pwm.currentPwm);
         servo[idx].pwm.direction=0;
       }else{
         step=(servo[idx].pwm.currentPwm-1500)/servo[idx].defParam.step;
         servo[idx].pwm.nStep=((servo[idx].pwm.currentPwm-1500)%servo[idx].defParam.step==0)?step:step+1; //需要走的总步数
       }
   }   
   servo[idx].pwm.waitTime=timeTable[8];
}

/********************
 *    加速初始化
 *******************/
void servo_initAcc(){

}

/********************
 *     减速初始化
 ********************/
void servo_initDec(){

}


void servo_writeCtrl(int idx,RKPwmCtrl_t rkCmd){
     switch(rkCmd.mode){
         case SERVO_CTRL_WITH_TIME:{
           servo_pwm_writeTimeParam(idx,rkCmd);
         }break;
         
         case SERVO_CTRL_WITH_SPEED:{
           servo_pwm_writeSpeedParam(idx,rkCmd);  // 
         }break;
         
         case SERVO_CTRL_RESET:{
           servo_pwm_writeResetParam(idx,rkCmd);  // 直接复位
         }break;
         
         default:{
         
         }break;
     }
}

/**************************
 *   舵机通过时间控制
 *************************/
void servo_ctrl_withTime(int idx){
      uint16_t leftPwm=0;
     if(servo[idx].pwm.time>=servo[idx].pwm.waitTime){
        servo[idx].pwm.time=0;  //等待时间是0
        servo[idx].pwm.currentPwm=cfgSERVO_PWM_LR_HMIN+servo[idx].pwm.currentStep*servo[idx].defParam.step;// 默认
        if(servo[idx].pwm.direction==0){
          leftPwm=servo[idx].pwm.targetPwm-servo[idx].pwm.currentPwm;
          if(leftPwm<=servo[idx].defParam.step){//不足走一步的时候
             servo[idx].pwm.currentPwm=servo[idx].pwm.targetPwm;
             servo[idx].pwm.targetPwm=servo[idx].defParam.minSPwm;
             servo[idx].pwm.direction=1; 
          }else{
              servo_write_pwm(idx,servo[idx].pwm.currentPwm);     
              servo_pwm_stop(idx);  
              return;  
          }              
        }else{
          leftPwm=servo[idx].pwm.currentPwm-servo[idx].pwm.targetPwm;
          if(leftPwm<=servo[idx].defParam.step){//不足走一步的时候
             servo[idx].pwm.currentPwm=servo[idx].pwm.targetPwm;
             if(servo[idx].pwm.bRecyle==1){
                servo[idx].pwm.targetPwm=servo[idx].defParam.maxSPwm;
                servo[idx].pwm.direction=0;
             }else{
                servo_write_pwm(idx,servo[idx].pwm.currentPwm);     
                servo_pwm_stop(idx);  
                return;                 
             }        
          } 
        }     
        servo_write_pwm(idx,servo[idx].pwm.currentPwm);     
     }
}

/**************************
 *    舵机通过速度控制
 *************************/
void servo_ctrl_withSpeed(int idx){
     uint16_t leftPwm=0,currentPwm=0;
     if(servo[idx].pwm.time>=servo[idx].pwm.waitTime){
        servo[idx].pwm.time=0;  //等待时间是0
     }
}

void servo_runCtrl(int idx){
    switch(servo[idx].pwm.mode){
         case SERVO_CTRL_WITH_TIME:{
            servo_ctrl_withTime(idx);
         }break;
         
         case SERVO_CTRL_RESET:
         case SERVO_CTRL_WITH_SPEED:{
            servo_ctrl_withSpeed(idx);
         }break;
   
         default:{
         
         }break;
    }
}


/*************************
 *       更新状态
 ************************/
void servo_pwm_notifyCtrl(int idx){
    switch(servo[idx].state){
        case SERVO_STATE_IDLE:{
          
        }break;
        case SERVO_STATE_START:{
           servo[idx].pwm.time=0; 
           servo[idx].state=SERVO_STATE_RUN;
        }break;
       
        case SERVO_STATE_RUN:{
             servo_runCtrl(idx);
        }break;

        case SERVO_STATE_STOP:{
            servo[idx].pwm.time=0; 
            servo[idx].state=SERVO_STATE_IDLE;
        }break;            
       
        default:{
        
        }break;
    }
}

void servo_pwm_notifyMs(int idx){
    if(servo[idx].state==SERVO_STATE_RUN){   //每10ms转4us
       servo[idx].pwm.time++;  
    }
}














