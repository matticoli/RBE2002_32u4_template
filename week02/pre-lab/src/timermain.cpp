/*
 * Code for using TCC4 for precision PID timing.
 * You'll need to set TOP to set the interval
 * 
 * This code adds the ability to tune the gains and change the targets
 */

#include <Romi32U4.h>
#include "Timer.h"

const int led = 13;
typedef enum ledState {
  ON,
  OFF
} LEDState;

LEDState currentState;

void setup()
{
  pinMode(led, OUTPUT);
  currentState = OFF;
}

void loop() 
{
  static Timer tim(500);
  switch(currentState) {
    case ON:
      if (tim.isExpired()) {
        // Change led on state transition
        digitalWrite(led, LOW);
        tim.reset();
        currentState = OFF;
      }
      break;
    case OFF:
    default:
      if (tim.isExpired()) {
        // Change led on state transition
        digitalWrite(led, HIGH);
        tim.reset();
        currentState = ON;
      }
      break;
  }
}