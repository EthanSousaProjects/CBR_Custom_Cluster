#include <Arduino.h>
#include <SPI.h> //Needed to have hardware SPI utilized.
#include <U8g2lib.h> // Library required for easy graphics management on the display.

#include "graphics.h"

//#include "private.h" // Graphics not uploaded to git repo but used in my script.

/* Creating the U8g2 constructor display class (the class call basically).
U8G2 = Start for the library.
ST7565 = The controller that is part of the display.
NHD = New haven displays.
C12832 = Defining the display it's self (the size mainly).
1,2,F drawing mode definition 1 and 2 is page based which will require a loop. F is full page buffer uses more ram than 1 and 2 but faster F is used for now.
4W_HW_SPI = 4 Wire hardware SPI mode.
Bracket Parameters:
- U8G2_R2 = defines the picture rotation, in this case 180 degree rotation, landscape as was upside down at first.
- 9 = chip select pin
- 12 = dc pin, register select pin, A0
- 10 = Reset pin
Hardware SPI was used as it will work faster than software SPI based methods in the library. Pins 13 (SPI clock pin (SPI_SCK))
and 11 (SPI data pin (COPI(MOSI))) do not need to be specified as they are the hardware SPI pins of the arduino nano esp32.
*/
U8G2_ST7565_NHD_C12832_F_4W_HW_SPI u8g2(U8G2_R2,9,12,10);


int delay_time = 5000; // Delay time between screens to make it easier to read

void setup() {
  Serial.begin(9600); //Initializing USB serial communication.
  /*
  Initializing the display
  Note due to using Pin 12 the MISO pin
  Slight initialisation changes had to be made using
  PinMode and digitalWrite
  to allow u8g2 library to work correctly with the display
  normally only the u8g2.begin() line is necessary.
  */
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);
  u8g2.begin();
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);

}

void loop() {
  // Going through each graphic type in turn to see what they all look like.
  // Basic Hello world to see initialization
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(0,20,"Hello World!");
  u8g2.sendBuffer();
  delay(delay_time);

  //30 segment size test Bold font for kph
  u8g2.clearBuffer();
  u8g2.drawXBM(0,0,128,32,high30seg);
  u8g2.setFont(u8g2_font_t0_30b_mr);
  u8g2.drawStr(75,20,"kph");
  u8g2.sendBuffer();
  delay(delay_time);

  //30 segment size test nonbold font for kph
  u8g2.clearBuffer();
  u8g2.drawXBM(0,0,128,32,high30seg);
  u8g2.setFont(u8g2_font_t0_30_mr);
  u8g2.drawStr(75,20,"kph");
  u8g2.sendBuffer();
  delay(delay_time);

  //32 segment size test with trip and odometer
  u8g2.clearBuffer();
  u8g2.drawXBM(0,0,128,32,high32seg);
  u8g2.setFont(u8g2_font_VCR_OSD_mr);
  u8g2.drawStr(75,18,"kph");
  u8g2.sendBuffer();
  delay(delay_time);

  // Font based speed representation
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_inr33_mn);
  u8g2.drawStr(0,32," 42");
  u8g2.setFont(u8g2_font_t0_30_mr);
  u8g2.drawStr(80,20,"kph");
  u8g2.setFont(u8g2_font_5x7_mr);
  u8g2.drawStr(79,32,"A1000000.0");
  u8g2.sendBuffer();
  delay(delay_time);

  //RPM version a/1 test (Same)
  u8g2.clearBuffer();
  u8g2.drawXBM(0,0,128,32,rpm_a);
  u8g2.sendBuffer();
  delay(delay_time);

  //RPM version b/2 test (Ramping)
  u8g2.clearBuffer();
  u8g2.drawXBM(0,0,128,32,rpm_b);
  u8g2.sendBuffer();
  delay(delay_time);

  //Coolant and fuel version a/1 test (Ramping)
  u8g2.clearBuffer();
  u8g2.drawXBM(0,0,128,32,cool_fuel_a);
  u8g2.sendBuffer();
  delay(delay_time);

  //Coolant and fuel version b/2 test (Same)
  u8g2.clearBuffer();
  u8g2.drawXBM(0,0,128,32,cool_fuel_b);
  u8g2.sendBuffer();
  delay(delay_time); 

  /*
  * The following is used in my script but due to licencing the graphics cannot be uploaded to git
  * Commented out for git upload but used in my script. 
  

  //Private_a
  u8g2.clearBuffer();
  u8g2.drawXBM(0,0,128,32,private_a);
  u8g2.sendBuffer();
  delay(delay_time); 

  //Private_b
  u8g2.clearBuffer();
  u8g2.drawXBM(0,0,128,32,private_b);
  u8g2.sendBuffer();
  delay(delay_time);

  //Private_c
  u8g2.clearBuffer();
  u8g2.drawXBM(0,0,128,32,private_c);
  u8g2.sendBuffer();
  delay(delay_time);

  //Private_d
  u8g2.clearBuffer();
  u8g2.drawXBM(0,0,128,32,private_d);
  u8g2.sendBuffer();
  delay(delay_time);

  //Private_e
  u8g2.clearBuffer();
  u8g2.drawXBM(0,0,128,32,private_e);
  u8g2.sendBuffer();
  delay(delay_time);

  //Private_f
  u8g2.clearBuffer();
  u8g2.drawXBM(0,0,128,32,private_f);
  u8g2.sendBuffer();
  delay(delay_time);

  //Private_g
  u8g2.clearBuffer();
  u8g2.drawXBM(0,0,128,32,private_g);
  u8g2.sendBuffer();
  delay(delay_time);
  End of private section*/
}