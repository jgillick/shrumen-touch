# Touch Sensor Prototype

A simple touch controller for the shrumen lumen linear actuators which are programed with the Arduino libraries,
but not in the Arduino IDE.

Software:
---------
Setup an AVR environment on your computer: https://www.pololu.com/docs/0J36

Will also need Makefile support on your computer (often part of package called `build-essential`).

Parts:
------
  * 22nF capacitor
  * 1k resistor
  * 100 Ohm resistor
  * LED

Circuit:
-------
  * Pin D5 to PWM
  * Pin D6 to DIR
  * Pin D7 to an LED, with 100 Ohm resistor, to ground.
  * Pin A0 to one leg of the 22nf capacitor
  * Pin A1
    * to the other leg of the capacitor
    * to 1K resistor
    * from 1k resistor to touch sensor area.


Programming
-----------
  * Determine the chip on the arduino board you're programming, either atmega 328 or 168:
     * Set that to the 'MCU' variable in the Makefile (likely either atmega328p or atmega168p)
  * Determine the port your arduino is on (you can see this in the arduino IDE)
     * Set that to the 'DEVICE_PORT' variable in the Makefile
  * Run: `make program`