#ifndef __HAL_UART_CTRL_H_
#define __HAL_UART_CTRL_H_

#include "gd32f10x.h"
#include "gd32f107c_eval.h"
#include "stdio.h"
#include "gd32f10x_hal.h"
#include "gd32f10x_hal_def.h"

#define UART_CNT(head, tail, size) (((head) - (tail)) & ((size)-1))
#define UART_SPACE(head, tail, size) UART_CNT((tail), ((head)+1), (size))



#define cfgUSUART_USFUL_NUM     (5)
#define cfgUSUART_RBUF_LEN      (512) 
#define cfgUSUART_WBUF_LEN      (256)

#define CFG_ON                   (1)
#define CFG_OFF                  (0)

/*************************
 *     串口1管脚定义
 ************************/
#define cfgUSART0_TX_PORT           (GPIOA)
#define cfgUSART0_TX_PIN            (GPIO_PIN_9)

#define cfgUSART0_RX_PORT           (GPIOA)
#define cfgUSART0_RX_PIN            (GPIO_PIN_10)

#define cfgUSART0_IRQ               (USART0_IRQn)
#define cfgUSART0_PRIORITY          (0)
#define cfgUSART0_SUB_PRIORITY      (0)

/*************************
 *     串口2管脚定义
 ************************/
#define cfgUSART1_TX_PORT           (GPIOA)
#define cfgUSART1_TX_PIN            (GPIO_PIN_2)
#define cfgUSART1_RX_PORT           (GPIOA)
#define cfgUSART1_RX_PIN            (GPIO_PIN_3)
#define cfgUSART1_IRQ               (USART1_IRQn)
#define cfgUSART1_PRIORITY          (0)
#define cfgUSART1_SUB_PRIORITY      (0)

/*************************
 *     串口3管脚定义
 ************************/
#define cfgUSART2_TX_PORT           (GPIOB)
#define cfgUSART2_TX_PIN            (GPIO_PIN_10)

#define cfgUSART2_RX_PORT           (GPIOB)
#define cfgUSART2_RX_PIN            (GPIO_PIN_11)
#define cfgUSART2_PRIORITY          (0)
#define cfgUSART2_SUB_PRIORITY      (0)

#define cfgUSART2_IRQ               (USART2_IRQn)
/*************************
 *     串口4管脚定义
 ************************/
#define cfgUART3_TX_PORT           (GPIOC)
#define cfgUART3_TX_PIN            (GPIO_PIN_10)

#define cfgUART3_RX_PORT           (GPIOC)
#define cfgUART3_RX_PIN            (GPIO_PIN_11)
#define cfgUSART3_PRIORITY          (0)
#define cfgUSART3_SUB_PRIORITY      (0)

#define cfgUART3_IRQ               (UART3_IRQn)
/*************************
 *     串口5管脚定义
 ************************/
#define cfgUART4_TX_PORT           (GPIOC)
#define cfgUART4_TX_PIN            (GPIO_PIN_12)

#define cfgUART4_RX_PORT           (GPIOD)
#define cfgUART4_RX_PIN            (GPIO_PIN_2)

#define cfgUART4_IRQ               (UART4_IRQn)
#define cfgUSART4_PRIORITY          (0)
#define cfgUSART4_SUB_PRIORITY      (0)

// 调试串口接口参数定义
#define cfgUSART_DBG_PERIPTH     (USART0)
#define cfgUSART_DBG_CLK         (RCU_USART0)
#define cfgUSART_DBG_RDMA        (CFG_OFF)
#define cfgUSART_DBG_WDMA        (CFG_OFF)


// 左机械臂串口参数定义
#define cfgUSART_LPLAM_PERIPTH    (USART1)
#define cfgUSART_LPLAM_CLK        (RCU_USART1)
#define cfgUSART_LPLAM_RDMA       (CFG_OFF)           //   接收DMA
#define cfgUSART_LPLAM_WDMA       (CFG_OFF)           //   发送DMA



// 右机械臂串口参数定义
#define cfgUSART_RPLAM_PERIPTH    (USART2)
#define cfgUSART_RPLAM_CLK        (RCU_USART2)
#define cfgUSART_RPLAM_RDMA       (CFG_OFF)           //   接收DMA
#define cfgUSART_RPLAM_WDMA       (CFG_OFF)           //   发送DMA


//通信串口参数定义
#define cfgUSART_RK_PERIPTH      (UART3)
#define cfgUSART_RK_CLK          (RCU_UART3)
#define cfgUSART_RK_RDMA         (CFG_OFF)           //   接收DMA
#define cfgUSART_RK_WDMA         (CFG_OFF)           //   发送DMA  

//通信串口参数定义
#define cfgUSART_ARM_PERIPTH      (UART4)
#define cfgUSART_ARM_CLK          (RCU_UART4)
#define cfgUSART_ARM_BAUDRATE     (115200U)
#define cfgUSART_ARM_RDMA         (CFG_OFF)           //   接收DMA
#define cfgUSART_ARM_WDMA         (CFG_OFF)           //   发送DMA  


typedef enum
{
  HAL_UART_STATE_RESET             = 0x00U,   /*!< Peripheral is not initialized
                                                   Value is allowed for gState and RxState */
  HAL_UART_STATE_READY             = 0x20U,   /*!< Peripheral Initialized and ready for use
                                                   Value is allowed for gState and RxState */
  HAL_UART_STATE_BUSY              = 0x24U,   /*!< an internal process is ongoing 
                                                   Value is allowed for gState only */
  HAL_UART_STATE_BUSY_TX           = 0x21U,   /*!< Data Transmission process is ongoing
                                                   Value is allowed for gState only */
  HAL_UART_STATE_BUSY_RX           = 0x22U,   /*!< Data Reception process is ongoing
                                                   Value is allowed for RxState only */
  HAL_UART_STATE_BUSY_TX_RX        = 0x23U,   /*!< Data Transmission and Reception process is ongoing
                                                   Not to be used for neither gState nor RxState.
                                                   Value is result of combination (Or) between gState and RxState values */
  HAL_UART_STATE_TIMEOUT           = 0xA0U,   /*!< Timeout state
                                                   Value is allowed for gState only */
  HAL_UART_STATE_ERROR             = 0xE0U    /*!< Error
                                                   Value is allowed for gState only */
}HAL_UART_StateTypeDef;



typedef enum USUART_IDX_ENUM{
    USUART_IDX_DBG=0x00,    // 用于调试用
    USUART_IDX_LPLAM,   // 左臂
    USUART_IDX_RPLAM,   // 右臂
    USUART_IDX_RK,     // 与RK通信串口
    USUART_IDX_ARM,
}UsuartIdx_e;

/***********************
 *    读写的BUF长度
 **********************/
typedef struct USUART_BUF_TYPEDEF{
     uint8_t rxBuf[cfgUSUART_RBUF_LEN];   //  读BUF
     uint32_t wptr;        //  写地址
     uint32_t rptr;        //  读地址
}UsuartBufTypedef;


/**************************
 *     用于定义串口模式
 *************************/
typedef struct USUART_PARAM_TYPEDEF{
    uint32_t periph;  // 串口定义
    rcu_periph_enum clk;
    uint32_t baudrate;      // 波特率
    uint32_t parity;        // 校验方式
    uint32_t wlen;          // 数据长度 
    uint32_t stblen;        // 停止位长度
    uint8_t  brDma;         // 读数据采用DMA
    uint8_t  bwDma;         // 写数据采用DMA
    uint32_t TxXferSize;
    uint32_t TxXferCount;
    uint32_t ErrorCode;
    uint32_t RxXferSize;
    uint32_t RxXferCount;
    uint8_t* wxBuf;         //  读BUF
    uint32_t priority;       // 设置优先级
    uint32_t subpriority;       // 设置优先级
    uint8_t irq;            // 启动串口中断
    USUART_LockTypeDef Lock;// 锁标志
    __IO HAL_UART_StateTypeDef gState;
    __IO HAL_UART_StateTypeDef rxState;
}UsuartParamTypedef;


/*************************
 *     定义串口参数 包括配置参数 读写BUF
 ************************/
typedef struct USUART_TYPEDEF{
    UsuartParamTypedef param;    // 串口参数
    UsuartBufTypedef   rbuff;     // 读写串口BUF
}UsuartTypedef;

USUART_StatusTypeDef usuart_send(uint8_t idx,uint8_t* data,uint32_t length,uint32_t timeOut);
void usuart_clear(uint8_t idx);
void hal_usuart_init(void);
int rs485_ping_state(int id);
extern UsuartTypedef uart[cfgUSUART_USFUL_NUM];   //总共定义了3个

#endif

