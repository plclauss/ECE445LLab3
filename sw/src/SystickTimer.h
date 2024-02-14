#ifndef _SYSTICKTIMERH_
#define _SYSTICKTIMERH_

#include "../inc/tm4c123gh6pm.h"
#include "Time.h"


void SysTick_Init(void);

void SysTick_Handler(void);


#endif