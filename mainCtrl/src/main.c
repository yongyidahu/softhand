/*!
    \file  main.c
    \brief enet demo 
*/

/*
    Copyright (C) 2017 GigaDevice

    2014-12-26, V1.0.0, demo for GD32F10x
    2017-06-30, V2.0.0, demo for GD32F10x
*/

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"
#include "semphr.h"
#include "croutine.h"

#include "gd32f10x.h"
#include "main.h"
#include "gd32f107c_eval.h"
#include "hal_timer_ctrl.h"
#include "hal_gpio_ctrl.h"
#include "hal_uart_ctrl.h"
#include "hal_rs485_ctrl.h"
#include "hal_pwm_ctrl.h"
#include "hal_it_ctrl.h"

#define INIT_TASK_PRIO   ( tskIDLE_PRIORITY + 1 )
#define LED_TASK_PRIO    ( tskIDLE_PRIORITY + 2 )


const char *pcTextForTask1 = "Task 1 is running\r\n";
const char *pcTextForTask2 = "Task 2 is running\t\n";

static void vTaskLED1(void *pvParameters);
static void vTaskLED2(void *pvParameters);

static TaskHandle_t xHandleTaskLED1=NULL;
static TaskHandle_t xHandleTaskLED2=NULL;
uint8_t debugData[16]={0xAA,0xBB,0xCC,0xDD,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
extern uint8_t bRecvFlg;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* The task function. */
void vTaskFunction( void *pvParameters );
// void LED1(void);
// void LED2(void);
/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    /* configure 4 bits pre-emption priority */
    nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
    SysTick_Config(1);
    hal_gpio_init();
    hal_timer_init();
    hal_usuart_init();//串口初始化
    hal_rs485_init();
    hal_pwm_init();
    rtos_timer_start(TIMER_ID_NOTIFY,1000,vTimerCallback);
    rtos_timer_start(TIMER_ID_SYSTEM_STICK,1,vTimerCallback);
    
	xTaskCreate(vTaskLED1, /*任务函数*/
	           "vTaskLED1",/*任务名称*/
	            512,       /*任务栈大小*/  
	            NULL,      /*任务参数*/ 
	            1,         /*任务优先级*/ 
	            &xHandleTaskLED1 /*任务句柄*/ 
	           );

	xTaskCreate(vTaskLED2, /*任务函数*/
	           "vTaskLED2",/*任务名称*/
	            512,       /*任务栈大小*/  
	            NULL,      /*任务参数*/ 
	            2,         /*任务优先级*/ 
	            &xHandleTaskLED2 /*任务句柄*/ 
	           );
			
  /* Start the scheduler so our tasks start executing. */
  vTaskStartScheduler();	

  /* Infinite loop */
  for( ;; );
}




static void vTaskLED1(void *pvParameters)
{
  while(1)
	{
        //gd_eval_led_toggle(LED3);
       // usuart_send(USUART_IDX_DBG,debugData,16,20);
       
       // rs485_get_id(1);
       // if(bRecvFlg==1){
       //     bRecvFlg=0;
            usuart_send(USUART_IDX_DBG,debugData,16,500);
      //  }
		vTaskDelay(1000);
  }
}

static void vTaskLED2(void *pvParameters)
{
  while(1)
  {
        gd_eval_led_toggle(LED4);
		vTaskDelay(10);
  }
}


void vTaskFunction( void *pvParameters )
{
    char *pcTaskName;

    /* The string to print out is passed in via the parameter.  Cast this to a
       character pointer. */
    pcTaskName = ( char * ) pvParameters;

    /* As per most tasks, this task is implemented in an infinite loop. */
    for( ;; )
    {
        taskENTER_CRITICAL();
        /* Print out the name of this task. */
        printf( "%s",pcTaskName );
        taskEXIT_CRITICAL();
        /* Delay for a period.  This time we use a call to vTaskDelay() which
           puts the task into the Blocked state until the delay period has expired.
           The delay period is specified in 'ticks'. */
        vTaskDelay( 1000 / portTICK_RATE_MS );
    }
}



/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(EVAL_COM1, (uint8_t) ch);
    while (RESET == usart_flag_get(EVAL_COM1, USART_FLAG_TBE));
    return ch;
}
