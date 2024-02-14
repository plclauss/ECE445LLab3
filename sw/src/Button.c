#include "button.h"

void	pinInit(void){
	SYSCTL_RCGCGPIO_R	|=	0x08;	
	
	while((SYSCTL_PRGPIO_R&0x08)	==	0){};
		
	GPIO_PORTD_LOCK_R	=	0x4C4F434B;
	GPIO_PORTD_CR_R = 0x8C;
	GPIO_PORTD_AMSEL_R	=	0x00;
	GPIO_PORTD_PCTL_R	=	0x00000000;
	GPIO_PORTD_DIR_R	=	0x80;
	GPIO_PORTD_AFSEL_R	=	0x00;	
	GPIO_PORTD_DEN_R	=	0x8C;
		
}

uint8_t Butt1Press(void){
	return (GPIO_PORTD_DATA_R & 0x04) != 0;
}

uint8_t Butt2Press(void){
	
	return (GPIO_PORTD_DATA_R & 0x08) != 0;
	
}