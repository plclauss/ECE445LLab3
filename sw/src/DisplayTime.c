#include "DisplayTime.h"


void DisplayTimeD(volatile uint16_t textColor, volatile uint8_t fifthSeconds, volatile uint8_t seconds, volatile uint8_t minutes, volatile uint8_t hours){
	char charConvert = 0;
	uint8_t hourReal = hours/5;
	if(fifthSeconds%5 == 0){
		Output_Clear();
		if(hourReal < 1){
			ST7735_DrawCharS(5, 50, '1' , textColor, textColor, 3);
			ST7735_DrawCharS(23, 50, '2' , textColor, textColor, 3);
		
		}
		else {
			charConvert = (hourReal/10) + '0';
			ST7735_DrawCharS(5, 50, charConvert , textColor, textColor, 3);
			charConvert = (hourReal%10) + '0';
			ST7735_DrawCharS(23, 50, charConvert , textColor, textColor, 3);
		}
	
		ST7735_DrawCharS(35, 50, ':' , textColor, textColor, 3);
		charConvert = (minutes/10) + '0';
		ST7735_DrawCharS(48, 50, charConvert , textColor, textColor, 3);
		charConvert = (minutes%10) + '0';
		ST7735_DrawCharS(66, 50, charConvert , textColor, textColor, 3);
	
		ST7735_DrawCharS(80, 58, ':' , textColor, textColor, 2);
		charConvert = (seconds/10) + '0';
		ST7735_DrawCharS(88, 57, charConvert , textColor, textColor, 2);
		charConvert = (seconds%10) + '0';
		ST7735_DrawCharS(100, 57, charConvert , textColor, textColor, 2);
	}
}


// Draws current time based on Time displayTime as an analog clock face.
// Inputs: 8-bit unsigned integer for seconds, for minutes, and for hours.
// Outputs: None* (Draws values on the LCD for an analog clock face).
#define PF2   (*((volatile uint32_t *)0x40025010)) // BLUE LED
void DisplayTimeA(const uint8_t fs, const uint8_t s, const uint8_t m, const uint8_t h) {
    // Can start by drawing the actual clock first, since it's independent of the
    // second, minute, and hour hands.
	if(fs%5 == 0){
		PF2 ^= 0x04;
    ST7735_FillScreen(ST7735_WHITE);
    BresenhamCircle(64, 80, 50);
    ST7735_DrawSmallCircle(62, 78, ST7735_BLACK);
    DrawNotches(50);
    // Draw actual hands.
    DrawHands(s, m, h);
		PF2 ^= 0x04;
	}
}

// ******************* NOTE *******************
// THIS ALGORITHIM IS UNIVERSAL; I'VE TAKEN IN-
// -SPIRATION FROM GEEKSFORGEEKS. THIS IS NOT 
// ORIGINAL CODE, BUT RATHER THE USAGE OF A C-
// -LEVER ALGORITHM.
// *******************************************
// Places the pixels where they need to be, based on center of circle, and 
// angles.
// SEE Display.c FOR EXPLANATION ON THIS ALGORITHM.
// Inputs: 
// Outputs: None* (Places 8 pixels based on inputs).
void DrawBresenhamCircle(const int16_t xCenter, const int16_t yCenter, const int16_t x, const int16_t y) {
    ST7735_DrawPixel(xCenter + x, yCenter + y, ST7735_BLACK);
    ST7735_DrawPixel(xCenter - x, yCenter + y, ST7735_BLACK);
    ST7735_DrawPixel(xCenter + x, yCenter - y, ST7735_BLACK);
    ST7735_DrawPixel(xCenter - x, yCenter - y, ST7735_BLACK);
    ST7735_DrawPixel(xCenter + y, yCenter + x, ST7735_BLACK);
    ST7735_DrawPixel(xCenter - y, yCenter + x, ST7735_BLACK);
    ST7735_DrawPixel(xCenter + y, yCenter - x, ST7735_BLACK);
    ST7735_DrawPixel(xCenter - y, yCenter - x, ST7735_BLACK);
}


// THIS ALGORITHIM IS UNIVERSAL; I'VE TAKEN IN-
// -SPIRATION FROM GEEKSFORGEEKS. THIS IS NOT 
// ORIGINAL CODE, BUT RATHER THE USAGE OF A C-
// -LEVER ALGORITHM.
// *******************************************
// Draws a circle using Bresenham's Algo.
// Inputs: x and y coordinates, dictating where the center of the circle will
// be drawn from; and the radius of the circle.
// Output: None* (Displays circle on LCD).
void BresenhamCircle(const int16_t xCenter, const int16_t yCenter, const int16_t radius) {
    // Center of circle at x = 64 and y = 80.
    int16_t x = 0;
    int16_t y = radius;
    int16_t d = 3 - 2 * radius;
    while(x <= y) {
        DrawBresenhamCircle(xCenter, yCenter, x, y);
        if (d <= 0) {
            x += 1;
            d = d + 4 * x + 6;
        }
        else {
            x += 1;
            y -= 1;
            d = d + 4 * (x - y) + 10;
        }
    }
}


// Draw seconds, minutes, and hour hands.
// Inputs: Current seconds, minutes, and hours.
// Outputs: None* (Draws on LCD).
void DrawHands(const uint8_t s, const uint8_t m, const uint8_t h) {
    double angle;
    int16_t x, y;
    
    // Seconds
    angle = (((double)(s * 360)) / (60.0));
    angle -= 90;
    if (angle > 360) {
        angle = 360 - angle;
    }
    angle = (((double)(angle * PI)) / (180.0));
    x = 65 + round(50 * cos(angle));
    y = 80 + round(50 * sin(angle));
    ST7735_Line(65, 80, x, y, ST7735_RED);
    //DrawHand(x, y, 0);
    
    // Minutes
    angle = (((double)(m * 360)) / 60.0);
    angle -= 90;
    if (angle > 360) {
        angle = 360 - angle;
    }
    angle = (((double)(angle * PI)) / (180.0));
    x = 65 + round(50 * cos(angle));
    y = 80 + round(50 * sin(angle));
    DrawHand(x, y, 1);
    
    // Hours
    angle = (((double)(h * 360)) / 60.0);
    angle -= 90;
    if (angle > 360) {
        angle = 360 - angle;
    }
    angle = (((double)(angle * PI)) / (180.0));
    x = 65 + round(50 * cos(angle));
    y = 80 + round(50 * sin(angle));
    DrawHand(x, y, 2);
}

		void DrawHand(int16_t x, int16_t y, const uint8_t color) {
    // Draws from center of clock, which is (65, 80).
    if (color == 0) {
        ST7735_Line(65, 80, x, y, ST7735_RED);
    }
    else if (color == 1) {
        ST7735_Line(65, 80, x, y, ST7735_BLACK);
    }
		else {
			ST7735_Line(65, 80, x, y, ST7735_BLUE);
		}
}
		
// Draws notches on analog clock face.
// Inputs: None
// Outputs: None* (Draws clock face notches, which are constant,
// independent of the current time.)
void DrawNotches(const uint8_t radius) {
	// Offset = 25 => Implies that we are 25 units away from the origin.
	// Also implies that we're 25 units away from edge of circle, since
	// radius is 50. (See invocation of Bresenham's Circle above).
	uint8_t offset = 25;
	double angleIncrement = 2 * PI / 12;
	for (int i = 0; i < 12; i += 1) {
		double angle = (i * angleIncrement);
		int xCoord = 64 + (offset * (int)cos(angle));
		int yCoord = 80 + (offset * (int)sin(angle));
		
		if (i == 0) {
			ST7735_Line(xCoord + (0.25 * offset), yCoord, xCoord + (offset - 5), yCoord, ST7735_BLACK);
			//ST7735_DrawCharS(xCoord + (1.125 * offset), yCoord - (0.14 * offset), '3', ST7735_BLACK, ST7735_WHITE, 2);
		}
		else if (i == 1) {
			ST7735_Line(xCoord + offset, yCoord + (0.625 * offset), xCoord + (1.5 * offset), yCoord + offset, ST7735_BLACK);
		}
		else if (i == 2) {
			ST7735_Line(xCoord + (0.625 * offset), yCoord + offset, xCoord + (0.875 * offset), yCoord + (1.55 * offset), ST7735_BLACK);
		}
		else if (i == 3) {
			ST7735_Line(xCoord, yCoord + (0.25 * offset), xCoord, yCoord + (offset - 5), ST7735_BLACK);
			//ST7735_DrawCharS(xCoord - (0.125 * offset), yCoord + (1.125 * offset), '6', ST7735_BLACK, ST7735_WHITE, 2);
		}
		else if (i == 4) {
			ST7735_Line(xCoord - offset, yCoord + (0.625 * offset), xCoord - (1.5 * offset), yCoord + offset, ST7735_BLACK);
		}
		else if (i == 5) {
			ST7735_Line(xCoord - (0.625 * offset), yCoord + offset, xCoord - (0.875 * offset), yCoord + (1.55 * offset), ST7735_BLACK);
		}
		else if (i == 6) {
			ST7735_Line(xCoord - (0.25 * offset), yCoord, xCoord - (offset - 5), yCoord, ST7735_BLACK);
			//ST7735_DrawCharS(xCoord - (1.45 * offset), yCoord - (0.14 * offset), '9', ST7735_BLACK, ST7735_WHITE, 2);
		}
		else if (i == 7) {
			ST7735_Line(xCoord - offset, yCoord - (0.625 * offset), xCoord - (1.5 * offset), yCoord - offset, ST7735_BLACK);
		}
		else if (i == 8) {
			ST7735_Line(xCoord - (0.625 * offset), yCoord - (1 * offset), xCoord - (0.875 * offset), yCoord - (1.55 * offset), ST7735_BLACK);
		}
		else if (i == 9) {
			ST7735_Line(xCoord, yCoord - (0.25 * offset), xCoord, yCoord - (offset - 5), ST7735_BLACK);
			//ST7735_DrawCharS(xCoord - (0.25 * offset), yCoord - (1.625 * offset), '1', ST7735_BLACK, ST7735_WHITE, 2);
			//ST7735_DrawCharS(xCoord, yCoord - (1.625 * offset), '2', ST7735_BLACK, ST7735_WHITE, 2);
		}
		else if (i == 10) {
			ST7735_Line(xCoord + (0.625 * offset), yCoord - offset, xCoord + (0.875 * offset), yCoord - (1.55 * offset), ST7735_BLACK);
		}
		else if (i == 11) {
			ST7735_Line(xCoord + offset, yCoord - (0.625 * offset), xCoord + (1.5 * offset), yCoord - offset, ST7735_BLACK);
		}
		else {
			;
		}
	}
}

uint16_t ChangeColor(volatile uint16_t curColor){
				while(getButton2()== 0){
					if(getButton1() == 1){
						if(curColor == ST7735_RED){
							curColor = ST7735_BLUE;
							DisplayTimeD(curColor, 0, 0, 0, 0);
							}
						else if(curColor == ST7735_BLUE){
							curColor = ST7735_GREEN;
							DisplayTimeD(curColor, 0, 0, 0, 0);
						}
						else if(curColor == ST7735_GREEN){
							curColor = ST7735_MAGENTA;
							DisplayTimeD(curColor, 0, 0, 0, 0);
						}
						else if(curColor == ST7735_MAGENTA){
							curColor = ST7735_CYAN;
							DisplayTimeD(curColor, 0, 0, 0, 0);
						}
						else if(curColor == ST7735_CYAN){
							curColor = ST7735_RED;
							DisplayTimeD(curColor, 0, 0, 0, 0);
						}
						DelayWait10ms(50);
				}
			}
				return curColor;
				DelayWait10ms(50);
		}

