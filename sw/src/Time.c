#include "Time.h"

Time DT = {0, 0, 0, 0};

uint16_t setupTime(void) {
    // Make screen black.
		uint16_t StartColor = 0x001F;
    Output_Clear();
	
		// Display base clock.
		DisplayTimeD(StartColor, 0, 0, 0, 0);
    
    // Create a variable to prevent critical sections.
    // It's likely this is unnecessary, since SysTick isn't
    // running, but it's better to play it safe.
    Time tempTime;
		StartColor = ChangeColor(StartColor);

  // Loop to setup hours until button is pressed.
  // Since we want the clock to display what the user
  // is pressing, we'll be calling display functions from
  // Display.h in between buttton presses.
  while (getButton2() == 0) {
        // Wait for button press, accounting for bounce.
        // Update hours.
		if(getButton1() == 1){
        if (DT.hours == 55) { DT.hours = 0; }
        else { DT.hours += 5; }
				tempTime = DT;
        DisplayTimeD(StartColor, tempTime.fifthSeconds, tempTime.seconds, tempTime.minutes, tempTime.hours);
      }
        // Display digital.
				DelayWait10ms(30);
  }
	
	DelayWait10ms(100);

  // We do a similar thing as above, but with seconds.
  while(getButton2() == 0) {
        // Wait for button press, accounting for bounce.
        // Update minutes.
		if(getButton1() == 1){
				DT.minutes += 1;
        if (DT.minutes == 60) { DT.minutes = 0; }
        tempTime = DT;
        DisplayTimeD(StartColor, tempTime.fifthSeconds, tempTime.seconds, tempTime.minutes, tempTime.hours);
			}
		DelayWait10ms(30);
  }
	return StartColor;
}

void DelayWait10ms(uint32_t n) {
    uint32_t volatile time;
    while (n){
        time = 727240 * 2 / 91;  // 10msec
        while (time){
            --time;
        }
        --n;
    }
}

void Pause(void) {
    while (getButton1() == 0) {
        DelayWait10ms(10);
    }
    while (getButton1() == 1) {
        DelayWait10ms(10);
    }
}

uint16_t setAlarm(volatile uint16_t textColor, Time* alarmTime){
	
    // Make screen black.
    Output_Clear();
	
		// Create a variable to prevent critical sections.
    // It's likely this is unnecessary, since SysTick isn't
    // running, but it's better to play it safe.
    Time tempTime;
	
		// Display Last shown clock 
		alarmTime->fifthSeconds = 0;
		alarmTime->seconds = 0;
		alarmTime->minutes = 0;
		alarmTime->hours = 0;
		tempTime = *alarmTime;
    DisplayTimeD(textColor, tempTime.fifthSeconds, tempTime.seconds, tempTime.minutes, tempTime.hours);
		textColor = ChangeColor(textColor);

  // Loop to setup hours until button is pressed.
  // Since we want the clock to display what the user
  // is pressing, we'll be calling display functions from
  // Display.h in between buttton presses.
		DelayWait10ms(50);
  while (getButton2() == 0) {
        // Wait for button press, accounting for bounce.
				uint8_t confirmPress;
       // while(getButton1() == 1) {
       //     DelayWait10ms(10);
       // }
       // while(getButton1() == 0) {
       //     DelayWait10ms(10);
       // }
				
        if(getButton1() == 1){
        // Update hours.
        if (alarmTime->hours == 55) { alarmTime->hours = 0; }
        else { alarmTime->hours += 5; }
				// Display digital.
        tempTime = *alarmTime;
        DisplayTimeD(textColor, tempTime.fifthSeconds, tempTime.seconds, tempTime.minutes, tempTime.hours);
				DelayWait10ms(30);
        }
       
  }
	
	DelayWait10ms(100);

  // We do a similar thing as above, but with seconds.
  while(getButton2() == 0) {
        // Wait for button press, accounting for bounce.
        //while(getButton1() == 1) {
        //    DelayWait10ms(10);
        //}
        //while(getButton1() == 0) {
        //    DelayWait10ms(10);
        //}
        
			if(getButton1() == 1){
        // Update minutes.
				alarmTime->minutes += 1;
        if (alarmTime->minutes == 60) { alarmTime->minutes = 0; }
				// Display digital.
        tempTime = *alarmTime;
        DisplayTimeD(textColor, tempTime.fifthSeconds, tempTime.seconds, tempTime.minutes, tempTime.hours);
				DelayWait10ms(30);
			}
        

  }
	return textColor;
}
	
	
