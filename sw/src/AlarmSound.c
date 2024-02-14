#include "AlarmSound.h"


void ToggleBaseSound(void){
	GPIO_PORTD_DATA_R ^= 0x80;
}
