#include <Arduino.h>

#include <Stepper.h> // External Package needed for controller steppers easily.

Stepper gauge_stepper(600, 8, 4, 19, 13); // Defining step count and digitial pins used.

void setup() {
  // Setting RPM of motor test ideal speed here.
  gauge_stepper.setSpeed(19);
  // Note through testing rpm of 20 appears to be the max rpm that works well on the stepper.
  // Therefore all future usage will use an rpm of 19 to work quickly with a small ammount of head room for slight stepper differences
}

void loop() {
  // loop of moving the stepper consitantly.
  gauge_stepper.step(600);
  delay(1000);
  gauge_stepper.step(-600);
  delay(1000);
  gauge_stepper.step(300);
  delay(1000);
  gauge_stepper.step(-300);
  delay(1000);

}