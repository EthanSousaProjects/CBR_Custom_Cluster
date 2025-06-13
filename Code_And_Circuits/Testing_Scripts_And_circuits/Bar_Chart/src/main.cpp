#include <Arduino.h>

int latchPin = 11;      // (11) ST_CP [RCK] on 74HC595
int clockPin = 10;      // (9) SH_CP [SCK] on 74HC595
int dataPin = 3;     // (12) DS [S1] on 74HC595

// Function to update an 8 LED bar chart attached to a 74HC595 shift register.
void update_bar_chart(int percentage_of_full,int latch_pin,int clock_pin,int data_pin);

void setup() {}

void loop() 
{
  for(int i = 0; i <= 100; i = i +10){
    update_bar_chart(i,latchPin,clockPin,dataPin);
    delay(1000);
  }
  update_bar_chart(0,latchPin,clockPin,dataPin);
}

void update_bar_chart(int percentage_of_full,int latch_pin,int clock_pin,int data_pin){
  // Setting up pins as output to set shift register.
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

  int amount_to_light = int((percentage_of_full * 8)/100); // Rounds down bar calculation due to int math

  // Now we know how many to update we have to update the byte that gets sent to the shift register.
  // giving decimal value here which converts to the correct binary representation (see HOW_TO_USE.md file for guidance)
  byte leds = int(1 << amount_to_light) - 1;
  /*
  The 1 << amount of light is a bit shift operation where the bit is shifted leftward in the byte.
  Has the same effect as doing 2 to the power of amount of light but works better due to data type issues.
  */

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
  delay(20); // Slight delay for everything to apply. If not has chance to break.
}
