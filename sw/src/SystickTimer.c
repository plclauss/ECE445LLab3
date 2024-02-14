#include "SystickTimer.h"


//Initializes the Systick timer
//Follows procedures dictated by the TM4C123GXL Data sheet
//Inputs: None
//Outputs: None
void SysTick_Init(void);


//ISR triggered by the count flag of SysTick
//Count Flag is set when the SysTick counts down from 
//Set value to zero.
//Inputs: None
//Outputs: None
void SysTick_Handler(void);



void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = 0x00f42400 - 1;  	// maximum reload value
  NVIC_ST_CURRENT_R = 0;                // any write to current clears it
                                        // enable SysTick with core clock
  
	NVIC_ST_CTRL_R = 0x00000007; 					// enables core clock with interrupts
}

void SysTick_Handler(void){
		DT.fifthSeconds += 1;
	
	if(DT.fifthSeconds >= 5){
		
		DT.seconds += 1;
		DT.fifthSeconds = 0;
		
		if(DT.seconds >= 60){
		
			DT.minutes += 1;
			DT.seconds = 0;
		
			if(DT.minutes >= 60){
				DT.hours += 5;
				DT.minutes = 0;
			
				if(DT.hours >= 55){
					
					DT.hours = 0;
				}
			}
		}
	}
}	
