# Pulse Counter for Speed and RPM measurments

This testing script and circuit is used to test a pulse reading/ measuring script. This can then be used to translate the electrical pulses from the speed sensor and/or RPM pulses into speed or RPM data to be displayed on the dash. It is based on using an arduino nano running the RPM_TO_PWM script that is part of the `Testing_Scripts_And_Circuits` folder of this project and using a DOIT ESP32 devkit V1 to figure out the rpm/ count the pulses coming from the nano. Both scripts should work on any other microcontroller using the arduino framework.

It can be noted that the pulses per secound for the RPM pulsing is equal to the Rotations Per Secound (RPS) therefore multiplying by 60 gives the RPM value. This is an output of this script.
Speed is a bit more complicated and depends on how the pulses are spread apart around the circumfrance of the wheel and in turn the wheel diameter. Eg if the wheel circumfrance is 4 meters and there are 4 pulses per wheel rotation. 1 pulse would mean you have traveled 1 meter. If that happened over a 1 secound time period then you would be moving at 1 meter per secound.

It is important to note that the arduino works on 5V and the DOIT esp32 works on 3.3 volts thus a voltage divider was required for my use case. If alternative boards are used please make sure the voltage pulse measured is close to/ is the working voltage of micro controllers. Sending a 5V pulse to a 3.3V device may break the 3.3V device and sending a 3.3V pulse to a 5V device may just not recognise the signal as high.

There is a scematic and test PCB made in KICAD in the folder `Circuit_GPS` of how everything should be connected together. If you are not using the same boards as me, please adjust the voltage divider (resistors) to something more appropriate. Please also connect the grounds of the micro controllers together so that there is a common ground reference point/ plane.

Once everything is connected, start both boards up having a serial monitor attached to each. On the nano you will have to type a RPM value to start the pulsing and on the measurment side you should see RPM and speed values. Verify they are as you expect by making some hand calculation based on your input parameters.

TODO: draw out circuit

TODO: Write thanks to instructable guy https://www.instructables.com/Use-Arduino-to-Display-Engine-RPM/