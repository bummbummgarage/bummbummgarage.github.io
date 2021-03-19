

/* ##########################################################################
   PRESETUP
   ##########################################################################
*/

const int steps = 4; // Number of total steps.
bool externalClock; // The current state of the external clock (high or low).
bool clock; // The internal clock.
long upLog; // Logs when the clock goes up. Needed on internal clocking to move on.
int step; // The current step that we're in.
int interval; // Indicator for the speed. 0 means it's off, not running.
int LEDSteps[4] = {6, 5, 4, 3}; // LED pin assignments for the steps illumination.



class Steps {
  
}



/* ##########################################################################
   SETUP
   ##########################################################################
*/

void setup() {

  Serial.begin(9600); // Initialize serial communication at 9600 bits per second:

  externalClock = 0;
  interval = 500;
  setClock(0);

  // Declare LED pins to be outputs.
  for (int i = 0; i < steps; i++) {
    pinMode( LEDSteps[i] , OUTPUT );
  }

}


/* ##########################################################################
   LOOP
   ##########################################################################
*/

void loop() {

  /* ------------------------------------------------------------------------
     INPUTS
     ------------------------------------------------------------------------
  */


  /* ------------------------------------------------------------------------
     STATE MANAGEMENT
     ------------------------------------------------------------------------
  */

  if ( externalClock == 1 ) { // The external clock is connected and running.

    interval = 0; // Set the interval to 0, because the external clock has highest prio.

    if ( clock == 0 ) { // The internal clock was down, meaning there's an upwards transitions.

      setClock(1); // Set the internal clock to 1, since this is the acutal state.
      logUp( millis() ); // Log the timestamp of the upwards transition.
      increaseSteps(); // Increase the current step.

    }
  }

  if ( externalClock == 0 ) { // The external clock is in the down phase OR none connected.

    if ( interval != 0 ) { // There is an interval set, meaning no external clock running.

      if ( millis() - upLog > interval ) { // The event of the latest up is longer ago than the interval, meaning we have an up.

        setClock(1); // Set the internal clock to 1, since this is the acutal state.
        logUp( millis() ); // Log the timestamp of the upwards transition.
        increaseSteps(); // Increase the current step.

      } else {

        setClock(0); // Set the internal clock to 0, since this is the acutal state.

      }

      if ( interval == 0 ) { // There is no interval set.

        setClock(0); // Set the internal clock to 0, since this is the acutal state.

      }

    }

  }


  /* ------------------------------------------------------------------------
     DISPLAY
     ------------------------------------------------------------------------
  */
  
  // Light the steps.
  



}



/* ##########################################################################
   FUNCTIONS
   ##########################################################################
*/

// Set the internal clock.
void setClock(int state) {
  clock = state;
}

// Increase the steps and start all over when the end is reached.
void increaseSteps() {
  if ( step < steps ) {
    step++;
  } else {
    step = 1;
  }
  Serial.print("Step: ");
  Serial.println(step);
}

// Log the up transition of the clock.
void logUp( long timestamp ) {
  upLog = timestamp;
  Serial.print("High on: ");
  Serial.println(timestamp);
}

// Light one specific Step LED.
void LEDOn(int LED) {
  digitalWrite(LED, HIGH);
}
// Turn off all Step LEDs.
void LEDsOff() {
  for (int i = 0; i < steps; i++) {
    digitalWrite(LEDSteps[i], LOW);
  }
}
