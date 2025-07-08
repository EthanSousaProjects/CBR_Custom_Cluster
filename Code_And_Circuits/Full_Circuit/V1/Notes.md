# Notes following the V1 design

- Through testing the following pin config is needed for the stepper to operate correctly `Stepper gauge_stepper(600, 2, 3, 5, 4);`

- Display works as expected using the testing code found in the test script folder. Makes a nice white colour with all the resistors.

- All power lines are working as expected getting all voltage levels i would expect

- Intesting note when powered on all lights sometimes pop on.


## Improvements for V2 design

- Make a smaller diameter.

- Consider a module based setup instead of using the nano for packaging reasons. (ESP32-S3 based) is more advanced and will need to worry about usb port but would help slim down packaging and may make more pins avaliable for usage.

- Consider the use of multiple PCBs

- Adjust capacitors to use standard values i have by putting them in parallel if needed as some values i do not have.

- Reconsider the power supplies, smaller?, Can i power nano with just 3.3V eliminatig need for 9V one, etc.

- Move all the components (caps, resistors, chips, etc) that do not have to be on the top layer to the bottom layer.

- Move all the traces to the bottom layer/ as many as possible.

- Try to implement the logging controller with GPS, SD card, etc

- Reconsider pinouts to work a bit better for the stepper driver to keep all pins on the same layer.

- Consider an SMD mounting for anything that is currently through hole. eg. steppper driver, nano, 

- Change 10 uF caps to electrolitic or decrease to be an SMD version (eg. 0.1 uF) 0.1uF for noise filtering and elecolitic to hold charge for componentes suddenly drawing it. Reconfigure it to work a bit better and ceramic caps do not reach high values.

- Add in underlights for RPM gauge/ speedo gauge that I forgot about. Make through hole 5mm ones or consider using standard W5W lights by putting holes in PCB at certain spots. Or consider using SMD mounting leds for smaller packaging.

- Reconsider mounting hole locations to be more evenly distrabuted.

- Reconsider some footprints that can be a socket instead of component directly soldered on.

- Implement diodes just maybe reconsider smd vs through hole

- re implement caps

- reconsider how display resistors are implemented as if want other colour than white really hard to desolder smd bits could make solder pad which could be good.

- Reconsider how to display speed can it work on the LCD as the alphanumeric takes up a bit too much space in current design. Testing required.

- Change the pins around after the logic level shifter to the stepper driver to keep all traces on the same layer and adjust pin config in code to suit.

## Extra notes on improvements and what to tackel.