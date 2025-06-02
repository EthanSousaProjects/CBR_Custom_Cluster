# RPM to PWM For CBR Dash Project

This testing script is used to produce a signal matching that of the RPM pulse that comes from the CBR when it is turned on. It is designed to run on an arduino nano but by changing the board target, the script should work on other boards.

Made in VS code Platform IO extension (see main README.md for usage information).

The signal gets outputted on pin 13 (D13)(Make sure to connect grounds).

To get this to work, compile and upload code to the nano/ board and connect a serial monitor as the signal does not start without it. The serial monitor tells you how to select an RPM value and when the signal is running and at what simulated RPM is. Use a keyboard only typing in numbers where relevenent and only charters when relevent.