#include <Arduino.h> // Needing for platformio

// Reguired I2C library and control library for display
#include <Wire.h>
#include <SparkFun_Alphanumeric_Display.h> // Library avaliable athttp://librarymanager/All#SparkFun_Qwiic_Alphanumeric_Display by SparkFun
// Library can also be found in the arduino librarys https://docs.arduino.cc/libraries/sparkfun-qwiic-alphanumeric-display-arduino-library/

HT16K33 display; // Setting up class for the display

String value;
int value_length_addition;

void setup()
{
  Serial.begin(9600);
  Serial.println("SparkFun Qwiic Alphanumeric - Example 1: Print String");

  Wire.begin(); //Join I2C bus

  if (display.begin() == false)
  {
    Serial.println("Device did not acknowledge! Freezing.");
    while (1);
  }
  Serial.println("Display acknowledged.");
  display.setBrightness(15);
  display.print("\t\t\t\t"); // Turn on all segments on display.
  display.updateDisplay();
  delay(1000);
}

void loop()
{
  // Avaliable functions can be found at: https://learn.sparkfun.com/tutorials/sparkfun-qwiic-alphanumeric-display-hookup-guide/all

  // Loop will cycle between 0 and 100 km then miles with a slight delay to see how fast we can update the display and how it all looks
  // Miles is M in 4th position and Kilometers is K.
  for(int i = 0; i <=100; i++){
    // Displaying numbers from 0 to 100.
    display.clear(); // Clear contents of display
    value = String(i);
    value_length_addition = 3 - int(value.length());
    for(unsigned int j = value_length_addition; j < 3;j++){
      display.printChar(value.charAt(j-value_length_addition),j);
    }
    display.printChar('k',3);
    display.updateDisplay();
    delay(200);

  }
  for(int i = 0; i <=100; i++){
    // Displaying numbers from 0 to 100.
    display.clear(); // Clear contents of display
    value = String(i);
    value_length_addition = 3 - int(value.length());
    for(unsigned int j = value_length_addition; j < 3;j++){
      display.printChar(value.charAt(j-value_length_addition),j);
    }
    display.printChar('m',3);
    display.updateDisplay();
    delay(200);

  }

}