#ifndef __HAL_BREATH_LIGHT_H_
#define __HAL_BREATH_LIGHT_H_



#include "gd32f10x.h"
#include "hal_i2c_ctrl.h"


#define cfgREG_IN_STATUS_P0      (0x00)   // 读取P0口电平       读
#define cfgREG_IN_STATUS_P1      (0x01)   // 读取P1口电平       读
#define cfgREG_OUT_STATUS_P0     (0x02)   // 读取P0口输出状态   读写
#define cfgREG_OUT_STATUS_P1     (0x03)   // 读取P1口输出状态   读写
#define cfgREG_CFG_PORT_P0      (0x04)   // 配置P0输入输出     读写
#define cfgREG_CFG_PORT_P1      (0x05)   // 配置P0输入输出     读写
#define cfgREG_IT_EN_P0         (0x06)   // 中断使能P0         读写
#define cfgREG_IT_EN_P1         (0x07)   // 中断使能P1         读写
#define cfgREG_READ_ID          (0x10)   // 读取ID号           读
#define cfgREG_CTRL             (0x11)   // 全局控制寄存器     读写
#define cfgREG_CFG_LED_MODE0    (0x12)   // P0_0~7工作模式切换 读
#define cfgREG_CFG_LED_MODE1    (0x13)   // P1_0~7工作模式切换 读
#define cfgREG_LED_P1_0         (0x20)   // LED P1_0电流控制   写
#define cfgREG_LED_P1_1         (0x21)   // LED P1_1电流控制   写
#define cfgREG_LED_P1_2         (0x22)   // LED P1_2电流控制   写
#define cfgREG_LED_P1_3         (0x23)   // LED P1_3电流控制   写
#define cfgREG_LED_P0_0         (0x24)   // LED P0_0电流控制   写
#define cfgREG_LED_P0_1         (0x25)   // LED P0_1电流控制   写
#define cfgREG_LED_P0_2         (0x26)   // LED P0_2电流控制   写
#define cfgREG_LED_P0_3         (0x27)   // LED P0_3电流控制   写
#define cfgREG_LED_P0_4         (0x28)   // LED P0_4电流控制   写
#define cfgREG_LED_P0_5         (0x29)   // LED P0_5电流控制   写
#define cfgREG_LED_P0_6         (0x2a)   // LED P0_6电流控制   写
#define cfgREG_LED_P0_7         (0x2b)   // LED P0_7电流控制   写
#define cfgREG_LED_P1_4         (0x2c)   // LED P1_4电流控制   写
#define cfgREG_LED_P1_5         (0x2d)   // LED P1_5电流控制   写
#define cfgREG_LED_P1_6         (0x2e)   // LED P1_6电流控制   写
#define cfgREG_LED_P1_7         (0x2f)   // LED P1_7电流控制   写

#endif
