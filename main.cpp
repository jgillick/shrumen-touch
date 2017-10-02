/*******************************************************************************
* A simple touch controller for the shrumen linear actuators.
*
* Parts:
* ------
*   > 22nF capacitor
*   > 1k resistor
*   > 100 Ohm resistor
*   > LED
*
* Circuit:
* -------
*   > Connect an LED, with 100 Ohm resistor, from D7 to ground.
*   > Pin A0 to one leg of the 22nf capacitor
*   > Pin A1
*     - to the other leg of the capacitor
*     - to 1K resistor
*     - from 1k resistor to touch sensor area.
*
*
* Sensor Circuit:
* ---------------
*      A0       A1
*      |        |
*      `---||---|
*         22nf  |
*               /
*               \
*               / 1K
*               \
*               |
*             (( ))  <- Touch sensor area
*
*
* Programming
* -----------
*   > Setup an AVR environment on your computer: https://www.pololu.com/docs/0J36
*   > Determine the chip you're programming, either atmega 328 or 168:
*      - Set that to the 'MCU' variable in the Makefile (likely either atmega328p or atmega168p)
*   > Determine the port your arduino is on (you can see this in the arduino IDE)
*      - Set that to the 'DEVICE_PORT' variable in the Makefile
*   > Run: make program
*
******************************************************************************/

#include <Arduino.h>
#include "touch.h"
#include "touch_control.h"

// SNS - A0
// SNSK - A1

/*----------------------------------------------------------------------------
                                Config
----------------------------------------------------------------------------*/

// Pins
#define PIN_PWM     5
#define PIN_DIR     6
#define PIN_STATUS  7

// Measure touch every x milliseconds
#define MEASUREMENT_PERIOD_MS 50

/*----------------------------------------------------------------------------
                                method prototypes
----------------------------------------------------------------------------*/
void setup();
void loop();

/*----------------------------------------------------------------------------
                                Program
----------------------------------------------------------------------------*/

// When we should measure the next touch
uint16_t time_to_measure_touch = 0u;


void setup() {
  // Setup touch sensors
  touch_init();

  // Pin setup
  pinMode(PIN_PWM, OUTPUT);
  pinMode(PIN_DIR, OUTPUT);
  pinMode(PIN_STATUS, OUTPUT);

  // enable interrupts
  sei();
}


void loop() {
  if (millis() >= time_to_measure_touch) {
    time_to_measure_touch += MEASUREMENT_PERIOD_MS;

    // Touch
    if (touch_measure(0, millis())) {
      // Extend
      // Analog 255
      // Digital LOW
      analogWrite(PIN_PWM, 255);
      digitalWrite(PIN_DIR, LOW);
      digitalWrite(PIN_STATUS, HIGH);
    }
    // No touch
    else {
      // Retract
      // Analog 255
      // Digital HIGH
      analogWrite(PIN_PWM, 255);
      digitalWrite(PIN_DIR, HIGH);
      digitalWrite(PIN_STATUS, LOW);
    }
  }
}
