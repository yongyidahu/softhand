#ifndef __HAL_TIMER_CTRL_H_
#define __HAL_TIMER_CTRL_H_



#include "FreeRTOS.h"
#include "gd32f10x.h"
#include "gd32f107c_eval.h"
#include "stdio.h"
#include "timers.h"
#include "gd32f10x_hal.h"
#include "hal_gpio_ctrl.h"
#include "type.h"



typedef enum TIMER_ID_ENUM{
    TIMER_ID_NOTIFY,
    TIMER_ID_SYSTEM_STICK,
    TIMER_ID_NOP_2,
    TIMER_ID_NOP_3,
    TIMER_ID_NOP_4,
}TimerID_typedef_enum;


typedef struct TIMER_PARAM_STRUCT{
    char name[16];
    INT32U  id;
    INT32U  delay;
    TimerHandle_t timer;
}TimerCtrlTypedef;

#define cfgTimerNameNotify        ("Notify")
#define cfgTimerNameSystem        ("System")
#define cfgTimerNameNop2          ("Nop2")
#define cfgTimerNameNop3          ("Nop3")
#define cfgTimerNameNop4          ("Nop4")



#define cfgMaxTimerNum            (5)

//extern INT32U TIMER_ID_NOTIFY;
//extern TimerHandle_t notifyTimer;
void hal_timer_init(void);
bool rtos_timer_start(INT32U id,INT32U delay,TimerCallbackFunction_t callback);
void rtos_timer_stop(INT32U id);
void gd_timer_start(void);
void gd_timer_stop(void);



#endif


