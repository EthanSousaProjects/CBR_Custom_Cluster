#include <Arduino.h>

int wheel_pulses_per_rotation = 6, rpm = 0, speed = 0, pin_rpm = 21, pin_speed = 21, measurement_time_length = 300;
float wheel_circumfrance = 10; // In meters

// Function call for getting RPM pin_rpm = pin to measure from, measurement_time_length = sampling time length in ms.
int measure_rpm(int pin_rpm);
// Function call for getting speed pin_speed = pin to measure from, measurement_time_length = sampling time length in ms.
int measure_speed(int pin_speed, int measurement_time_length);

void setup() {
  Serial.begin(9600); // Start serial monitor
}

void loop() {
  speed = measure_speed(pin_speed, measurement_time_length);
  rpm = measure_rpm(pin_rpm);

  Serial.print("Current Speed: ");
  Serial.println(speed);
  Serial.print("Current RPM: ");
  Serial.println(rpm);
  delay(1000); // wait 1 secound between outputting data to serial monitor for readability Actual dash should just output ASAP.
}


int measure_rpm(int pin_rpm) {
  pinMode(pin_rpm,INPUT);
  int rpm;
  unsigned long time_hi = pulseIn(pin_rpm,HIGH,60000); // Trying to get length of time that data pin input is high.
  //Time out of 100ms as if no high signal in 100ms then rpm will be set to 0. Lowest reasonable rpm i want to see is 1000rpm.
  if (time_hi == 0){
    // No high signal detected during 100ms time frame therefore rpm = 0.
    return(0);
  }
  else{
    unsigned long time_low = pulseIn(pin_rpm,LOW,125000);
     // Convert total signal time to rpm 1/signal time for frequency = rotations per secound, 1000000 to convert from micro sec to secounds 6 at beginning for 60 sec in 1 min.
    rpm = int(float(60000000)/float(time_hi+time_low));
    if (rpm >= 13500){
      return(0);
    }
    else{
      return(rpm);
    }
  }
}


int measure_speed(int pin_speed, int measurement_time_length) {
  pinMode(pin_speed,INPUT);
  boolean went_high = false;
  unsigned long ms_start = millis(), ms_end = ms_start + ((unsigned long)measurement_time_length);
  int pulse_count = 0;
  while(millis() <= ms_end){
    if(digitalRead(pin_speed) == HIGH && went_high == false){ // Counting pulses when signal rises to HIGH
      ++pulse_count;
      went_high = true;
    }
    else if(went_high == true && digitalRead(pin_speed) ==LOW){ // Resetting when signal goes back to LOW
      went_high = false;
    }
  }
  Serial.println(pulse_count);
  //TODO: fix math here for speed calc based on inputs is just rpm one for now.
  //TODO: Make speed pulse count like rpm count and tune values
  return(int((float(pulse_count)/ float(measurement_time_length)) * 60000)); // First bit gets pulses per secound then * 60000 to get pulses per minute = rpm and for conversion of ms to s.
}