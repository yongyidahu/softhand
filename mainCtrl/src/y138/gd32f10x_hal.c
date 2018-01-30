#include "gd32f10x_hal.h"

__IO uint32_t wtick;
void  HAL_IncTick(void){
    wtick++;
}
void HAL_Delay(__IO uint32_t Delay){
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = Delay;
  
  /* Add a period to guarantee minimum wait */
  if (wait < HAL_MAX_DELAY)
  {
     wait++;
  }
  while((HAL_GetTick() - tickstart) < wait)
  {
  }
}
uint32_t HAL_GetTick(void){

   return wtick;
}

