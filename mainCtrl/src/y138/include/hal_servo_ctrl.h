#ifndef __HAL_SERVO_CTRL_H_
#define __HAL_SERVO_CTRL_H_


#include "gd32f10x.h"
#include "hal_servo_cfg.h"
#include "hal_rs485_ctrl.h"
#include "hal_pwm_ctrl.h"




/**********************
 *      响应错误码
 *********************/
typedef enum SERVO_ACK_ERRORCODE{
   SERVO_OK,            // 状态OK
   SERVO_OVER_LOAD,     // 过载
   SERVO_OVER_TMP,      // 温度过高
   SERVO_OVER_VOLTAGE,  // 过压
}AckErrCode_e;


typedef enum SERVO_TYPE_CODE{
   SERVO_TYPE_RS485,
   SERVO_TYPE_PWM,
}ServoType_e;

//以角速度进行转还是以时间等角度进行偏移 




#endif

