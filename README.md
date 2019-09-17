For hooking up the led display, visit the following 

https://learn.adafruit.com/16x32-rgb-display-with-raspberry-pi-part-2?view=all

https://learn.adafruit.com/connecting-a-16x32-rgb-led-matrix-panel-to-a-raspberry-pi?view=all

Once the new cc file is added to the examples folder, To compile the program, type this into the command line:

gcc -Wall -o rgbledcountdown rgbledcountdown.cc -lwiringPi -lled-matrix

To run the program, type the following into the command line:

sudo ./rgbledcountown --led-no-hardware-pulse
