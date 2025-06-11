#include <Arduino.h>

int rpm, on_time_mill, off_time_mill, on_time_micro, off_time_micro;
float hz, t;
char input_rpm[5] = {'0','0','0','0','0'};

char input_digit();

void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  pinMode(13,OUTPUT);
  
}

void loop() {

  // RPM changer here.
  Serial.println("Please input a digit for the 10000 positon");
  input_rpm[0] = input_digit();
  Serial.println("Please input a digit for the 1000 positon");
  input_rpm[1] = input_digit();
  Serial.println("Please input a digit for the 100 positon");
  input_rpm[2] = input_digit();
  Serial.println("Please input a digit for the 10 positon");
  input_rpm[3] = input_digit();
  Serial.println("Please input a digit for the 1 positon");
  input_rpm[4] = input_digit();


  // Producing signal based on RPM input.
  rpm = atoi(input_rpm);
  if (rpm == 0){ // error check as 0 RPM could break stuff so just set to 1 if found to be that.
    rpm = 1;
  }
  Serial.println("Running at " + String(rpm) + " RPM, press any key to stop/ change RPM");
  hz = rpm/60; //Freqency of pulse
  t = (1.0/hz) * 1000; // Wave time period in millisecounds
  // Signal is approximatly a 6.67% duty cycle pwm signal so setting that up and running it.
  on_time_mill = int(t * 0.0667);
  on_time_micro = int(((t*0.0667)- on_time_mill)* 1000);
  off_time_mill = int(t - float(on_time_mill) - (float(on_time_micro)/1000));
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


// Function which makes sure a digit is inputed into the serial terminal.
char input_digit(){
  char input;
  boolean is_digit = false;
  Serial.println("Please type digit you want:");
  while (is_digit == false){
    while (!Serial.available()) {};
    input = Serial.read();
    if (isdigit(input)){
      is_digit = true;
    }
    else{
      Serial.println("Not a digit please type digit:");
    }
  }
  return(input);
}