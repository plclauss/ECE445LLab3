#ifndef _DISPLAYTIME_
#define _DISPLAYTIME_

#include <stdint.h>
#include "./inc/ST7735.h"
#include "./src/button.h"
#include "./src/Time.h"
#include <math.h>

#define PI 3.14159265

void DisplayTimeD(volatile uint16_t textColor, volatile uint8_t fifthSeconds, volatile uint8_t seconds, volatile uint8_t minutes, volatile uint8_t hours);

void DisplayTimeA(const uint8_t fs, const uint8_t s, const uint8_t m, const uint8_t h);

void DrawBresenhamCircle(const int16_t xCenter, const int16_t yCenter, const int16_t x, const int16_t y);
	
void BresenhamCircle(const int16_t xCenter, const int16_t yCenter, const int16_t radius);

void DrawHands(const uint8_t s, const uint8_t m, const uint8_t h);

void DrawHand(int16_t x, int16_t y, const uint8_t color);

void DrawNotches(const uint8_t radius);

uint16_t ChangeColor(volatile uint16_t curColor);
	
#endif