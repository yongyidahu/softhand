#ifndef __GD32F10X_HAL_H_
#define __GD32F10X_HAL_H_


#ifdef __cplusplus
 extern "C" {
#endif

#include "gd32f10x.h"
#include "gd32f107c_eval.h"
#include "stdio.h"
#include "gd32f10x_hal_def.h"
     
void              HAL_IncTick(void);
void              HAL_Delay(__IO uint32_t Delay);
uint32_t          HAL_GetTick(void);
     
#ifdef __cplusplus
}
#endif
#endif

