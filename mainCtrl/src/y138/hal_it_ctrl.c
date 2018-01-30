#include "hal_it_ctrl.h"


//处理各种中断消息
uint8_t rxbuffer;


//void USART0_IRQHandler(void){
//   
//    if(RESET != usart_flag_get(USART0, USART_FLAG_RBNE))
//	 {
//		rxbuffer=(usart_data_receive(USART0) & 0xFF);
//         
//     } 
//	 
//	if(RESET != usart_flag_get(USART0, USART_FLAG_TBE))
//	{

//      usart_data_transmit(USART0,rxbuffer);	 
//	}	
//}

void USART1_IRQHandler(void){
    
    if(RESET != usart_flag_get(USART1, USART_FLAG_RBNE))
	 {
		rxbuffer=(usart_data_receive(USART1) & 0xFF);
     } 
	 
	if(RESET != usart_flag_get(USART1, USART_FLAG_TBE))
	 {
				 
	 }
}


void USART2_IRQHandler(void){
    
    if(RESET != usart_flag_get(USART2, USART_FLAG_RBNE))
	 {
		rxbuffer=(usart_data_receive(USART2) & 0xFF);
     } 
	 
	if(RESET != usart_flag_get(USART2, USART_FLAG_TBE))
	{
				 
	}
}

void UART3_IRQHandler(void){
     
    if(RESET != usart_flag_get(UART3, USART_FLAG_RBNE))
	 {
		rxbuffer=(usart_data_receive(UART3) & 0xFF);
     } 
	 
	if(RESET != usart_flag_get(UART3, USART_FLAG_TBE))
	{

	}
}


 void vTimerCallback(xTimerHandle pxTimer){
    INT32U ulTimerID;
    configASSERT(pxTimer);
    ulTimerID = (uint32_t)pvTimerGetTimerID(pxTimer);
    if(ulTimerID==(INT32U)TIMER_ID_SYSTEM_STICK){//作为提醒的任务
       HAL_IncTick();
       led_on_off();
    }else if(ulTimerID==(INT32U)TIMER_ID_NOTIFY){

    }
}
 


