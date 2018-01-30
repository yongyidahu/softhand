#ifndef __HAL_SERVO_CFG_H_
#define __HAL_SERVO_CFG_H_


//define cfgSERVO_REG_ALL_PERMITE         //所有指令全部开放



#define cfgSERVO_REQ_HEAD_1          (0xff)   // 请求命令1
#define cfgSERVO_REQ_HEAD_2          (0xff)   // 请求命令2


#define cfgSERVO_ACK_HEAD_1          (0xff)   // 响应命令头
#define cfgSERVO_ACK_HEAD_2          (0xf5)   // 响应命令头2


#define cfgSERVO_VOL_MAX             (0x08)   // 电压上限是8V
#define cfgSERVO_VOL_MIN             (0x04)   // 电压下限
#define cfgSERVO_TEMP_MAX            (0x50)   // 最大温度上限


#define cfgSERVO_REQ_CMD_PING        (0x01)   // 查询工作状态
#define cfgSERVO_REQ_CMD_READ        (0x02)   // 查询控制表中的内容
#define cfgSERVO_REQ_CMD_WRITE       (0x03)   // 往控制表中写入内容
#define cfgSERVO_REQ_CMD_REG_WRITE   (0x04)   // 写寄存器
#define cfgSERVO_REQ_CMD_ACTION      (0x05)   // 在REG写入后调用ACTION功能
#define cfgSERVO_REQ_CMD_RESET       (0x06)   // 复位
#define cfgSERVO_REQ_CMD_SYNC_WRITE  (0x07)   // 同步写入



/**********************************
 *      寄存器地址
 *********************************/
 
 
#ifdef cfgSERVO_REG_ALL_PERMITE             // 不可以用的寄存器
     #define REG_FAC_YEAR          (0x00)   // 出厂   年
     #define REG_FAC_MONTH         (0x01)   // 出厂   月
     #define REG_FAC_DAY           (0x02)   // 出厂   日
     #define REG_VER_H             (0x03)   // 软件版本号(H)
     #define REG_VER_L             (0x04)   // 软件版本号(L)
     #define REG_BAUDRATE          (0x06)   // 波特率设置
     #define REG_NPOWER_H          (0x07)   // 开机次数H
     #define REG_NPOWER_L          (0x08)   // 开机次数L
     #define REG_TEMP_MAX          (0x0d)   // 最大温度上限(0x50)
     #define REG_VOL_MAX           (0x0e)   // 最大电压上限(0x08)
     #define REG_VOL_MIN           (0x0f)   // 电压下限
     #define REG_UNLOAD            (0x13)   // 卸载条件
     #define REG_LED0_ONOFF        (0x16)   // LED0控制开关
     #define REG_LED1_ONOFF        (0x17)   // LED1控制开关
     #define REG_LED2_ONOFF        (0x18)   // LED2控制开关
     #define REG_LED0_ON_TIME      (0x19)   // LED0点亮时间
     #define REG_LED1_ON_TIME      (0x1a)   // LED1点亮时间
     #define REG_LED2_ON_TIME      (0x1b)   // LED2点亮时间
     #define REG_MODE_ONOFF        (0x1c)   // 舵机电机切换模式
     #define REG_MOTOR_DIR         (0x1d)   // 电机模式方向切换
     #define REG_LED               (0x29)   // LED
     #define REG_CURRENT_H         (0x2e)   // 当前电流H
     #define REG_CURRENT_L         (0x2f)   // 当前电流L
     #define REG_LOCK_FLG          (0x30)   // LOCK标志
     #define REG_CURRENT_LOAD_H    (0x3c)   // 当前负载H
     #define REG_CURRENT_LOAD_L    (0x3d)   // 当前负载L
     #define REG_CURRENT_VOL       (0x3e)   // 当前电压
     #define REG_CURRENT_TEMP      (0x3f)   // 当前温度
     #define REG_SPEED_ADJ_H       (0x41)   // 速度调整H
     #define REG_SPEED_ADJ_L       (0x42)   // 速度调整L
#endif

#define REG_ID                (0x05)   // 设备ID号
#define REG_ANGLE_MIN_H       (0x09)   // 最小角度限制H
#define REG_ANGLE_MIN_L       (0x0a)   // 最小角度限制L
#define REG_ANGLE_MAX_H       (0x0b)   // 最大角度限制H
#define REG_ANGLE_MAX_L       (0x0c)   // 最大角度限制L
#define REG_TORQUE_MAX_H      (0x10)   // 最大扭矩H
#define REG_TORQUE_MAX_L      (0x11)   // 最大扭矩L
#define REG_SPEED             (0x12)   // 当前速度
#define REG_MID_POS_H         (0x14)   // 中位调整H
#define REG_MID_POS_L         (0x15)   // 中位调整L
#define REG_TORQUE_ONOFF      (0x28)   // 扭矩开关
#define REG_TARGET_POS_H      (0x2a)   // 目标位置H
#define REG_TARGET_POS_L      (0x2b)   // 目标位置L
#define REG_RUNTIME_H         (0x2c)   // 运行时间H
#define REG_RUNTIME_L         (0x2d)   // 运行时间L
#define REG_CURRENT_POS_H     (0x38)   // 当前位置H
#define REG_CURRENT_POS_L     (0x39)   // 当前位置L
#define REG_SPEED_H           (0x3a)   // 速度H
#define REG_SPEED_L           (0x3b)   // 速度L
#define REG_WRITE_FLG         (0x40)   // 写标志

#endif

