#include <Arduino.h>

int wheel_pulses_per_rot = 6, rpm = 0, speed = 0, pin_rpm = 21, pin_speed = 21;
float wheel_circumfrance = 1; // In meters

// Note wheel specs are just examples not the actual CBR values.

// Function call for getting RPM pin_rpm = pin to measure from
int measure_rpm(int pin_rpm);
// Function call for getting speed pin_speed = pin to measure from, returns in m/s
int measure_speed(int pin_speed, float wheel_circumfrance, int wheel_pulses_per_rot);

void setup() {
  Serial.begin(9600); // Start serial monitor
}

void loop() {
  speed = measure_speed(pin_speed,wheel_circumfrance,wheel_pulses_per_rot);
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
  unsigned long time_hi = pulseIn(pin_rpm,HIGH,65000); // Trying to get length of time that data pin input is high.
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


int measure_speed(int pin_speed, float wheel_circumfrance, int wheel_pulses_per_rot) {
  pinMode(pin_speed,INPUT);
  int speed;
  //Tune things on a real case as creating test case is nearly impossible for my application.
  unsigned long time_hi = pulseIn(pin_rpm,HIGH,65000); // Trying to get length of time that data pin input is high.
  //Time out of 100ms as if no high signal in 100ms then rpm will be set to 0. Lowest reasonable rpm i want to see is 1000rpm.
  if (time_hi == 0){
    // No high signal detected during 100ms time frame therefore rpm = 0.
    return(0);
  }
  else{
    unsigned long time_low = pulseIn(pin_rpm,LOW,125000);

    if (pulseIn == 0){
      return (0);
    }
    else{
      return(int((wheel_circumfrance/float(wheel_pulses_per_rot))/(float(time_hi+time_low)/float(1000000))));
      // doing distance over time.
    }
  }
}