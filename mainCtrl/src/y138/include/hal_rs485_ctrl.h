#ifndef __HAL_RS485_CTRL_H_
#define __HAL_RS485_CTRL_H_



#include "gd32f10x.h"
#include "hal_servo_cfg.h"
#include "hal_uart_ctrl.h"
#include <string.h>


#define cfgBUS_EN_PORT         (GPIOB)
#define cfgBUS_EN_PIN          (GPIO_PIN_3)





typedef enum SERVO_ACK_STATE_E{
    ACK_STATE_HEAD_1,
    ACK_STATE_HEAD_2,
    ACK_STATE_ID,
    ACK_STATE_LEN,
    ACK_STATE_CONTENT,
    ACK_STATE_ODD,
}ServoAckState_e;

typedef enum SERVO_BUS_IDX{
      BUS_ID_LARM_0,   // 左手臂  从上到下分别是00--05
      BUS_ID_LARM_1,
      BUS_ID_LARM_2,
      BUS_ID_LARM_3,
      BUS_ID_LARM_4,
      BUS_ID_LARM_5,
    
      BUS_ID_RARM_0,
      BUS_ID_RARM_1,
      BUS_ID_RARM_2,
      BUS_ID_RARM_3,
      BUS_ID_RARM_4,
      BUS_ID_RARM_5,
}BusServoIdx_e;


typedef struct{
   uint8_t bHeadRecv;  // 接收到数据头
   uint8_t bHead1Recv;
   uint8_t id; 
   uint8_t paramLen;   // 数据长度
   uint8_t len;        // 当前接收到的数据长度
   uint8_t odd;    
   uint16_t startPos;  // 起始指针
   uint16_t endPos;    // 结束位指针
   uint8_t  curPos;
   ServoAckState_e state; 
}ServoAck_t;


typedef struct{
    uint8_t  id;       // ID号
    uint8_t  bActive;  //  是否有效
    uint16_t maxPos;   // 0---4096   最大位置和最小位置
    uint16_t minPos;   // 0---4096   最大位置和最小位置
    uint16_t midPos;   // 中位调整
    uint16_t targetPos; // 目标位置
    uint16_t runTime;  // 运行时间
    uint16_t curPos;   // 当前位置
    uint16_t speed;    // 运行速度
    uint8_t  speedAdjust; // 速度调整
    uint8_t  regFlg;    // REG Write Flg
}BusServoState_t;


void hal_rs485_init(void);
int rs485_get_id(int id);



#endif


