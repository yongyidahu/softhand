#ifndef __USER_PUBLIC_H__
#define __USER_PUBLIC_H__


#include "gd32f10x.h"





typedef struct RK_CTRL_SERVO_PWM{
   uint8_t  idx;
   uint8_t  direction;
   uint8_t  mode;     // 控制模式
   uint8_t  bRecyle;  // 是否循环
   uint16_t angle;    // 需要控制的偏移角度
   uint16_t param;    // 根据控制模式来决定这个参数是速度还是时间
   uint16_t nop1;      // 预留
   uint16_t nop2;      // 预留
   uint16_t nop3;      // 预留
   uint16_t nop4;      // 预留
}RKPwmCtrl_t;   //RK端命令


/*************************
 *      485控制指令
 ************************/
typedef struct RK_CTRL_SERVO_RS485{
   uint32_t nop;



}RKRS485Ctrl_t;  //处理485消息的


/**************************
 *    I2C呼吸灯控制
 *************************/
typedef struct RK_CTRL_BLIGHT_I2C{//控制I2C指令
  uint32_t nop;


}RKLightCtrl_t;

/***************************
 *      touch 控制
 **************************/
typedef struct RK_CTRL_TOUCH{
   uint32_t nop;



}RKTouchCtrl_t;

typedef struct RK_CTRL_PLAM{
   uint32_t nop;


}RKPlamCtrl_t;


#endif


