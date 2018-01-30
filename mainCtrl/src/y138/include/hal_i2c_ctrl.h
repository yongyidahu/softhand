#ifndef __HAL_I2C_CTRL_H_
#define __HAL_I2C_CTRL_H_

#include "gd32f10x.h"
#include "gd32f107c_eval.h"
#include "stdio.h"
#include "gd32f10x_hal.h"
#include "gd32f10x_hal_def.h"


#define cfgI2C_LIGHT_NUM        (3)

#define ACK                     (0xff)
#define NACK                    (0xf5)
#define cfgSYS_FREQ             (108)//108m

/************************************
 *         呼吸灯
 ************************************/
#define cfgLBLIGHT_RST_PORT         (GPIOA)
#define cfgLBLIGHT_RST_PIN          (GPIO_PIN_4)
#define cfgLBLIGHT_SCL_PORT         (GPIOA)
#define cfgLBLIGHT_SCL_PIN          (GPIO_PIN_5)
#define cfgLBLIGHT_SDA_PORT         (GPIOA)
#define cfgLBLIGHT_SDA_PIN          (GPIO_PIN_6)


#define cfgRBLIGHT_RST_PORT         (GPIOA)
#define cfgRBLIGHT_RST_PIN          (GPIO_PIN_7)
#define cfgRBLIGHT_SCL_PORT         (GPIOC)
#define cfgRBLIGHT_SCL_PIN          (GPIO_PIN_4)
#define cfgRBLIGHT_SDA_PORT         (GPIOC)
#define cfgRBLIGHT_SDA_PIN          (GPIO_PIN_5)

#define cfgFBLIGHT_RST_PORT         (GPIOB)
#define cfgFBLIGHT_RST_PIN          (GPIO_PIN_12)
#define cfgFBLIGHT_SCL_PORT         (GPIOB)
#define cfgFBLIGHT_SCL_PIN          (GPIO_PIN_13)
#define cfgFBLIGHT_SDA_PORT         (GPIOB)
#define cfgFBLIGHT_SDA_PIN          (GPIO_PIN_14)


typedef enum I2C_SEL_ENUM{
    I2C_BLIGHT_LEFT,       //  左侧 呼吸灯
    I2C_BLIGHT_RIGHT,      //  右侧 呼吸灯
    I2C_BLIGHT_FRONT,      //  前方 呼吸灯
}I2cSel_e;

typedef struct I2C_CTRL_PARAM{  
    uint32_t sclPort;   // SCL接口
    uint32_t sclPin;

    uint32_t sdaPort;  // SDA接口
    uint32_t sdaPin;

    uint32_t rstPort; // RST接口
    uint32_t rstPin;
}I2cCtrl_typedef;

typedef struct I2C_TYPEDEF{
    I2cSel_e idx;
    I2cCtrl_typedef gpio;
}I2CTypedef;


void hal_i2c_init(int idx);

void i2c_sda_set(int idx);
void i2c_sda_clr(int idx);

void i2c_scl_set(int idx);
void i2c_scl_clr(int idx);


void i2c_start(int idx);
void i2c_stop(int idx);
uint8_t i2c_write_data(int idx,uint8_t val);
uint8_t i2c_read_data(int idx);
uint8_t i2c_wait_ack(int idx);
void i2c_delay(uint16_t us);    // 不能进入调度
void i2c_hw_reset(int idx);

#endif


