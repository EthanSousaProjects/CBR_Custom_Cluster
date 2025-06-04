#include <Arduino.h>

// External packages to setup a serial interface with the GPS module and parse the data from it.
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

static const int rx_pin = 9, tx_pin = 8;
// Note with above rx pin on arduino connects to tx pin on gps module and vis versa. Could use other pins.
static const uint32_t gps_baud = 9600;
// Baud rate of my module is 9600 some modules maybe different so change as appropriate.

TinyGPSPlus gps_parser; // Object that parses GPS string.

SoftwareSerial gps_serial(rx_pin,tx_pin); // Setup for software serial interface.

void setup() {
  Serial.begin(9600); // For USB communication
  gps_serial.begin(gps_baud); // Starting serial for gps.
}

void loop() {

  if (gps_serial.available() > 0){ // See if gps serial connection has data.

    //Serial.write(gps_serial.read()); // testing line to see raw gps serial data.
    
    gps_parser.encode(gps_serial.read()); // Translate the data
    if (gps_parser.satellites.isUpdated()){
    // Print the data to the serial monitor over the USB serial connection.
      Serial.print("Sat Count = ");
      Serial.println(gps_parser.satellites.value());
      Serial.print("Latitude = ");
      Serial.println(gps_parser.location.lat(),6);
      Serial.print("Logitude = ");
      Serial.println(gps_parser.location.lng(),6);
      Serial.print("Speed in Kph = ");
      Serial.println(gps_parser.speed.kmph());
      // More outputs can be found here: https://arduiniana.org/libraries/tinygpsplus/
    }
  }
}