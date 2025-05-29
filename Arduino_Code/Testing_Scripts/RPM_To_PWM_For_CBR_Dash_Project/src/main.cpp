#include <Arduino.h>

int rpm, on_time_mill, off_time_mill, on_time_micro, off_time_micro;
float hz, t;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  pinMode(13,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //TODO: Add in RPM changer.
  Serial.println("Running at 2000 RPM, press any key to stop/ change RPM");
  rpm = 13000;
  hz = rpm/60; //Freqency of pulse
  t = (1.0/hz) * 1000; // Wave time period in millisecounds
  // Signal is approximatly a 6.67% duty cycle pwm signal so setting that up and running it.
  on_time_mill = int(t * 0.0667);
  on_time_micro = int(((t*0.0667)- on_time_mill)* 1000);
  off_time_mill = int(t - float(on_time_mill));
  off_time_micro = int((t*1000) - (on_time_mill*1000) - on_time_micro - (off_time_mill*1000));
  // Some rounding errors will occur above due to rounding of ints and floats but should be close enough.
  while (!Serial.available()) { // While loop waiting for a keyboard press, Runs signal until told to stop
    digitalWrite(13,HIGH);
    delay(on_time_mill);
    delayMicroseconds(on_time_micro);
    digitalWrite(13,LOW);
    delay(off_time_mill);
    delayMicroseconds(off_time_micro);
  }
  Serial.read();
}