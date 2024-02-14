#ifndef _TIMEH_
#define _TIMEH_

#include <stdint.h>
#include "./inc/ST7735.h"
#include "DisplayTime.h"
#include "button.h"
#include "./inc/Timer5A.h"

#define PF0   (*((volatile uint32_t *)0x40025004)) // Left Button
#define PF4   (*((volatile uint32_t *)0x40025040)) // Right Button

typedef struct Time {
	volatile uint8_t fifthSeconds;
	volatile uint8_t seconds;
	volatile uint8_t minutes;
	volatile uint8_t hours;
}Time;

extern Time DT;

uint16_t setupTime (void);
void DelayWait10ms(uint32_t n);

uint16_t setAlarm(volatile uint16_t textColor, Time* alarmTime);

void Pause(void);

#endif