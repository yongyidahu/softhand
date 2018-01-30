#ifndef __HAL_PWM_CTRL_H__
#define __HAL_PWM_CTRL_H__


#include "gd32f10x.h"
#include "public.h"


#define cfgSERVO_MAX_WAIT          (50)   // 最长等待时间
#define cfgSERVO_NOTIFY_TIME       (10)   // 每10ms更新一次数据  

#define cfgSERVO_PWM_LR_HMAX       (2500)
#define cfgSERVO_PWM_LR_HMIN       (500)
#define cfgSERVO_ANGLE_LR_MAX      (180)
#define cfgSERVO_PWM_LR_SMAX       (2500)
#define cfgSERVO_PWM_LR_SMIN       (500)
#define cfgSERVO_PWM_LR_DEF        (1500)
#define cfgSERVO_PWM_LR_STEP       (4)    //每4us算一步


#define cfgSERVO_PWM_UD_HMAX       (2500)    // 软件 
#define cfgSERVO_PWM_UD_DEF        (1500)    // 默认的PWM值
#define cfgSERVO_PWM_UD_SMAX       (2500)
#define cfgSERVO_PWM_UD_SMIN       (500)
#define cfgSERVO_PWM_UD_HMIN       (500)
#define cfgSERVO_PWM_UD_STEP       (4)
#define cfgSERVO_ANGLE_UD_MAX      (180)


#define cfgSERVO_PWM_EX_HMAX       (2500)    // 软件 
#define cfgSERVO_PWM_EX_DEF        (1500)    // 默认的PWM值
#define cfgSERVO_PWM_EX_SMAX       (2500)
#define cfgSERVO_PWM_EX_SMIN       (500)
#define cfgSERVO_PWM_EX_HMIN       (500)
#define cfgSERVO_PWM_EX_STEP       (4)
#define cfgSERVO_ANGLE_EX_MAX      (180)

typedef enum SERVO_PWM_IDX_ENUM{
    SERVO_ID_LR,
    SERVO_ID_UD,
    SERVO_ID_EX,
}ServoPwmIdx_e;

/****************************
 *        控制方式
 ****************************/
typedef enum SERVO_CTRL_MODE{
   SERVO_CTRL_STOP=0x00,
   SERVO_CTRL_WITH_TIME,     /***控制不考虑时间***/
   SERVO_CTRL_WITH_SPEED,         /***控制不考虑速度***/
   SERVO_CTRL_RESET,         /*******复位********/
}ServoCtrlMode_e;


typedef enum SERVO_CTRL_STATE{
    SERVO_STATE_IDLE,
    SERVO_STATE_START,
    SERVO_STATE_RUN,
    SERVO_STATE_STOP,
}ServoState_e;


typedef struct SERVO_PWM_DEF_STRUCT{
    uint16_t defPwm;     // 默认的PWM值
    uint16_t maxHPwm;     // 硬件定义的最大PWM值
    uint16_t minHPwm;     // 硬件定义最小PWM
    uint16_t maxSPwm;     // 软件定义最大PWM
    uint16_t minSPwm;     // 软件定义最小PWM
    uint16_t maxWait;     // 每一步最长等待时间
    uint16_t step;        // 每一步走的Step距离
    uint32_t periph;      // 接口
    uint16_t channel;     // 通道号
    uint16_t maxHAngle;
    float   angle;
}ServoDef_t;


typedef struct SERVO_PWM_PARAM_STRUCT{
    uint16_t nTotoal;     // 需要走走的总步数
    uint16_t nStep;       // 当前走的步数
    uint16_t currentStep; //
    uint16_t currentPwm;
    uint16_t targetPwm;   // 目标 PWM值  //只有当需要跑到1500的时候需要用到
    uint16_t waitTime;    // 等待时间    
    uint16_t time;        // 时间计数
    uint8_t  mode;        // 控制模式
    uint8_t bRecyle;      // 是否进行循环 
    uint8_t direction;
}ServoPwmCtrl_t;

typedef struct SERVO_ANGLE_PARAM_STRUCT{
   uint16_t offset;
   uint8_t direction;
   uint8_t bchange;  //有更新
   uint16_t current;
   uint16_t target;
}ServoAngleCtrl_t;



typedef struct SERVO_PWM_CTRL_STRUCT{
    ServoAngleCtrl_t angle;
    ServoPwmCtrl_t pwm;    // 步数控制
    ServoDef_t defParam;         // 默认参数 
    ServoState_e state;       // 控制状态
}ServoCtrlTypedef;


void hal_pwm_init(void);
void servo_writeCtrl(int idx,RKPwmCtrl_t rkCmd);


#endif


