#ifndef __HAL_GPIO_CTRL_H_
#define __HAL_GPIO_CTRL_H_


#include "gd32f10x.h"
#include "gd32f107c_eval.h"
#include "stdio.h"
#include <string.h>

#define cfgRCU_GPIO_A           (RCU_GPIOA)
#define cfgRCU_GPIO_B           (RCU_GPIOB)
#define cfgRCU_GPIO_C           (RCU_GPIOC)
#define cfgRCU_GPIO_D           (RCU_GPIOD)


#define LED_ON                  (1)
#define LED_OFF                 (0)
#define cfgLED_TOG_TIME         (500)




#define cfgLED_GPIO_PORT           (GPIOB) 
#define cfgLED_GPIO_PIN            (GPIO_PIN_7)

#define cfgHEAD_EX_PORT            (GPIOB)    // PWM
#define cfgHEAD_EX_PIN             (GPIO_PIN_7)

#define cfgHEAD_LR_PORT            (GPIOB)    // PWM
#define cfgHEAD_LR_PIN             (GPIO_PIN_0)

#define cfgHEAD_UD_PORT            (GPIOB)    // PWM
#define cfgHEAD_UD_PIN             (GPIO_PIN_1)


#define cfgSERVO_POWER_PORT        (GPIOC)
#define cfgSERVO_POWER_PIN         (GPIO_PIN_1)

#define cfgLARAM_POWER_PORT        (GPIOC)
#define cfgLARAM_POWER_PIN         (GPIO_PIN_2)

#define cfgRARAM_POWER_PORT        (GPIOC)
#define cfgRARAM_POWER_PIN         (GPIO_PIN_3)


#define cfgLED_CON_EN_PORT         (GPIOC)
#define cfgLED_CON_EN_PIN          (GPIO_PIN_6)




typedef struct  LED_STATE_TOG{
    int togTime;
    int state;
}LEDCtrl_typedef;



void hal_gpio_init(void);
void led_on_off(void);
void led_off(void);
void led_on(void);

#endif
