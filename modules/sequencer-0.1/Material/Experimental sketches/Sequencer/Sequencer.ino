/*
   General variables.
*/
// Global timestamp stored with millis()
// https://www.arduino.cc/reference/en/language/functions/time/millis/
unsigned long timestamp;

// Indicator for the bpm (defined by the interval between the steps).
// Zero means it's off, not running.
int interval;

// The number of taps (for setting the speed) and the temporary interval.
int taps;
int tapsStart;
int tapsEnd;

// Number of total steps.
const int steps = 4;

// The current step that we're in.
int step;
// The timestamp of the latest step start.
long stepLog;

// The blinking time.
int blink = 100;


/*
   The push button for step control (pBS).
*/
// Assigned to pin 2.
int pBS = 2;
// The latest state of the step push button.
int pBSLast;
// The timestamp of the latest state change.
long pBSLog;

/*
   Illuminating everything
*/
// Pin assignments.
int LED[4] = {6, 5, 4, 3};

/*
   SETUP
   The setup routine runs once when you press reset.
*/
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Make the push buttons pins an input:
  pinMode(pBS, INPUT);

  // declare LED pins to be outputs.
  pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT);
  pinMode(LED[2], OUTPUT);
  pinMode(LED[3], OUTPUT);

  // Speed is zero, sequencer not running.
  interval = 0;

  // We start at step 1;
  step = 1;

  // Zero taps at the beginning.
  taps = 0;

  // Blink at start.
  LEDsBlink();
  delay(blink);
  LEDsBlink();

}


/*
   LOOP
   The loop routine runs over and over again forever:
*/
void loop() {


  /*
     Running through the steps.
  */
  // If the interval is set, run through the steps.
  if ( interval != 0 ) {

    // When the latest step start farther in the past than an interval, …
    if ( millis() > (stepLog + interval) )
    {
      // Turn off the LEDs.
      LEDsOff();

      // Turn on the current LEDs
      LEDOn(LED[step - 1]);

      Serial.print("Step ");
      Serial.println(step);
      // … increase the steps and set the stepLog to current time.
      increaseSteps();
      stepLog = millis();
    }

  }


  /*
      Push button "Steps" listeners and actions.
  */
  // When the state of the steps push button changed.
  int pBSNow = digitalRead(pBS);
  if ( pBSNow != pBSLast ) {

    Serial.print("Steps push button has been");

    // The button is being pushed.
    if ( pBSNow == 1 ) {
      Serial.println(" pushed.");
      delay(50); // Delay a little bit to avoid bouncing

      // If the sequencer is running…
      // … reset it to step 1.
      if ( interval != 0) {
        step = 1;
        stepLog = 0;
      }

      // If the sequencer is not running…
      // … listen to the taps (to set the interval).
      if ( interval == 0) {

        taps++;

        for (int i = 0; i < taps; i++) {
          LEDOn(LED[i]);
        }

        switch (taps) {
          case 1:
            tapsStart = millis();
            Serial.print( "Tap 1: " );
            Serial.println( tapsStart );
            break;
          case 2:
            Serial.print( "Tap 2: " );
            Serial.println( millis() );
            break;
          case 3:
            Serial.print( "Tap 3: " );
            Serial.println( millis() );
            break;
          case 4:
            tapsEnd = millis();
            Serial.print( "Tap 4: " );
            Serial.println( tapsEnd );
            taps = 0;
            int c = ( tapsEnd - tapsStart ) / 3;
            delay(c);
            interval = c;
            Serial.print( "Intervall: " );
            Serial.println( interval );
            break;
        }

      }

    }

    // The button has been released.
    if ( pBSNow == 0 ) {
      Serial.println(" released.");
      delay(50); // Delay a little bit to avoid bouncing
    }

    // Log the timestamp of the change.
    pBSLog = millis();

    // Set the new push button state.
    pBSLast = pBSNow;

  }
  // When steps push button has been pushed for more than a second.
  if ( ( pBSNow == 1 ) && ( millis() > (pBSLog + 2000) ) && ( interval != 0 ) ) {

    Serial.println("Stop it and reset.");

    LEDsBlink();
    delay(blink);
    LEDsBlink();

    interval = 0;
    step = 1;

  }


}


/*
   Functions
*/
// Increase the steps
void increaseSteps() {

  if ( step < steps ) {
    step++;
  } else {
    step = 1;
  }

}

// Light one specific LED.
void LEDOn(int LED) {
  digitalWrite(LED, HIGH);
}
// Turn on all LEDs.
void LEDsOn() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(LED[i], HIGH);
  }
}
// Turn off all LEDs.
void LEDsOff() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(LED[i], LOW);
  }
}
void LEDsBlink() {
  LEDsOn();
  delay(blink);
  LEDsOff();
}
