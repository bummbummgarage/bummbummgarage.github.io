
/* --------------------------------------------------------------------------

    $$$$$$$\  $$\   $$\ $$\      $$\ $$\      $$\               
    $$  __$$\ $$ |  $$ |$$$\    $$$ |$$$\    $$$ |              
    $$ |  $$ |$$ |  $$ |$$$$\  $$$$ |$$$$\  $$$$ |              
    $$$$$$$\ |$$ |  $$ |$$\$$\$$ $$ |$$\$$\$$ $$ |              
    $$  __$$\ $$ |  $$ |$$ \$$$  $$ |$$ \$$$  $$ |              
    $$ |  $$ |$$ |  $$ |$$ |\$  /$$ |$$ |\$  /$$ |              
    $$$$$$$  |\$$$$$$  |$$ | \_/ $$ |$$ | \_/ $$ |              
    \_______/  \______/ \__|     \__|\__|     \__|                    
                                                                
    $$$$$$$\  $$\   $$\ $$\      $$\ $$\      $$\               
    $$  __$$\ $$ |  $$ |$$$\    $$$ |$$$\    $$$ |              
    $$ |  $$ |$$ |  $$ |$$$$\  $$$$ |$$$$\  $$$$ |              
    $$$$$$$\ |$$ |  $$ |$$\$$\$$ $$ |$$\$$\$$ $$ |              
    $$  __$$\ $$ |  $$ |$$ \$$$  $$ |$$ \$$$  $$ |              
    $$ |  $$ |$$ |  $$ |$$ |\$  /$$ |$$ |\$  /$$ |              
    $$$$$$$  |\$$$$$$  |$$ | \_/ $$ |$$ | \_/ $$ |              
    \_______/  \______/ \__|     \__|\__|     \__|                      
                                                                
     $$$$$$\   $$$$$$\  $$$$$$$\   $$$$$$\   $$$$$$\  $$$$$$$$\ 
    $$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ $$  _____|
    $$ /  \__|$$ /  $$ |$$ |  $$ |$$ /  $$ |$$ /  \__|$$ |      
    $$ |$$$$\ $$$$$$$$ |$$$$$$$  |$$$$$$$$ |$$ |$$$$\ $$$$$\    
    $$ |\_$$ |$$  __$$ |$$  __$$< $$  __$$ |$$ |\_$$ |$$  __|   
    $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |      
    \$$$$$$  |$$ |  $$ |$$ |  $$ |$$ |  $$ |\$$$$$$  |$$$$$$$$\ 
     \______/ \__|  \__|\__|  \__|\__|  \__| \______/ \________|
  

    SEQUENCER II – GATES & TRIGGERS
    This is the code for an Eurorack synth module.
    It's built and tested on an Arduino Nano Every.
    
    Find out more on: http://bummbummgarage.github.io/
    
    ---------------------------------------------------------------------- */


/* ##########################################################################
   PRESETUP
   ##########################################################################
*/

// General
const bool debug = false; // Enables the Serial print in several functions. Slows down the frontend.
const int pushButtonDelay = 50; // The time a button will be muted after last change.
const int longPress = 2000; // The time to trigger secondary actions on buttons.

// Steps
const int stepsCount = 8; // Overall number of steps.
int stepsMode; // 0 = voltage controlled, 1 = internally clocked, 2 = recording clock.
long stepsModeChangeLog; // Timestamp log of the latest steps mode change.
int stepsPosition = 0; // The current position of the steps. 0 means no step active, starts with 1.
int stepsInterval = 0; // Defines the speed of the internal clock. 0 means clock is not running.
long stepsChangeLog; // Timestamp log of the latest steps position change.
const char stepsPushButtonPin = A3; // Steps push button pin assignment.
int stepsPushButton; // 0 or 1.
long stepsPushButtonChangeLog; // The timestamp of the last change of this button.
int tapCount = 0; // The counter when tapping in the speed.
long tapStart; // Timestamp of tapping in.
long tapEnd; // Timestamp of tapping out.
const char stepsJackDetectionPin = 4; // The pin of the detection for the external CV jack.
const char stepsCVInPin = A7; // The pin of the external CV jack to clock the sequencer.
int stepsCVIn; // The control voltage state from an external source in the jack, 0 or 1.

// Tracks
const int tracksCount = 3; // The number of tracks.
int tracksMode[tracksCount]; // 0 = record and play, 1 = pattern select.
long tracksModeChangeLog[tracksCount]; // Timestamp log of the latest tracks mode change.
bool tracksPattern[tracksCount][stepsCount]; // Holds the logical pattern of each track.
long tracksPatternChangeLog[tracksCount]; // Timestamp of last pattern change per track.
const char tracksPushButtonPin[tracksCount] = { A2, A1, A0 }; // Tracks push button pin assignments (1-3).
int tracksPushButton[tracksCount]; // The state of the tracks push buttons, 0 or 1.
long tracksPushButtonChangeLog[tracksCount]; // Timestamp of the latest change to the track pattern.
const int tracksOutputPin[tracksCount] = { 5, 9, 10 }; // Tracks output pin assignments (1-3).
const int tracksPatternCount = 10; // The number of predefined patterns.
const bool tracksPredefinedPattern[tracksPatternCount][stepsCount] = { // Predefined patterns for the tracks.
  { 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 0, 0 },
  { 1, 1, 1, 1, 0, 0, 0, 0 },
  { 1, 1, 0, 0, 0, 0, 0, 0 },
  { 1, 0, 1, 0, 1, 0, 1, 0 },
  { 0, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 1, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 1, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 1 }
};
int tracksPatternPreview[tracksCount]; // Which pattern is previewed (select mode) per track.

// Sequence Modes
int sequenceMode; // 0 = chronologically, 1 = limited to the bottom and top hit on the tracks, 2 = random.
int bottomHit = 0; // The hit over all tracks with the smallest step number.
int topHit = 0; // The hit over all tracks with the highest step number.

// Display
#include <ShiftRegister74HC595.h> // ShiftRegister74HC595 Library, Docs: https://timodenk.com/blog/shift-register-arduino-library/

const int ledMatrixRowsShiftRegisters = 1; // Number of shift registers attached in series.
const int ledMatrixRowsDataPin = 6; // DS
const int ledMatrixRowsLatchPin = 7; // STCP
const int ledMatrixRowsClockPin = 8; // SHCP
ShiftRegister74HC595<ledMatrixRowsShiftRegisters> ledMatrixRows(ledMatrixRowsDataPin, ledMatrixRowsClockPin, ledMatrixRowsLatchPin);

const int ledMatrixColsPins [ ( tracksCount + 1 ) ] = { 2, 3, 11, 12 }; // The pins to control the LED matrix columns (right to left, 1-4).

const int flashTime = 300; // How many milliseconds a flash lasts.
const int slowPulseTime = 1000; // How long one slow pulse cycle lasts.

// Output
const int triggerTime = 10; // The time of a trigger pulse generated by the internal clock in milliseconds.

/* ##########################################################################
   SETUP
   ##########################################################################
*/

void setup() {

  if ( debug == true ) {
    Serial.begin(9600); // Initialize serial communication at 9600 bits per second.
  }

  // STEPS
  pinMode(stepsCVInPin, INPUT); // Makes steps CV IN jack an input.
  pinMode(stepsPushButtonPin, INPUT); // Makes steps push button an input.

  // TRACKS
  for (int t = 0; t < tracksCount; t++) {
    pinMode(tracksPushButtonPin[t], INPUT); // Makes tracks push buttons inputs.
    pinMode(tracksOutputPin[t], OUTPUT); // Tracks outputs.
    setTracksMode(t, 0); // Set all tracks to mode 0;
  }

  // LED MATRIX
  // Rows
  pinMode(ledMatrixRowsDataPin, OUTPUT); // Tracks outputs.
  pinMode(ledMatrixRowsLatchPin, OUTPUT); // Tracks outputs.
  pinMode(ledMatrixRowsLatchPin, OUTPUT); // Tracks outputs.
  // Columns
  for (int c = 0; c < ( tracksCount + 1 ); c++) {
    pinMode(ledMatrixColsPins[c], OUTPUT);
  }

  setSequenceMode(0); // The the mode initally.

}

/* ##########################################################################
   LOOP
   ##########################################################################
*/
void loop() {

  /* ------------------------------------------------------------------------
    INPUTS & STATES
    -------------------------------------------------------------------------
  */

  // STEPS ------------------------------------------------------------------

  // CV jack
  bool stepsJackConnection = checkStepsJackConnection(); // Depending on a cable plugged in (1) or not (0).

  // Push button.
  bool s = checkPushButton( stepsPushButtonPin, stepsPushButton, stepsPushButtonChangeLog ); // 0 or 1.
  bool stepsPushButtonChanged = false;
  if ( s != stepsPushButton ) {
    stepsPushButtonChanged = true;
    stepsPushButtonChangeLog = millis();
    if ( debug == true ) {
      Serial.print("stepsPushButton: ");
      Serial.println(s);
    }
    stepsPushButton = s;
  }

  // Clock Modes

  // CLOCK MODE 0: "EXTERNALLY CLOCKED" mode
  if ( stepsJackConnection == true ) { // CV plugged in.

    // Set the mode.
    int m = 0;
    if ( stepsMode != m ) {
      setStepsMode(m);
      setStepsInterval(0); // Unset the interval, we don't need it  here.
    }

    // Scenario 1: CV is on the move --> we'll update the steps.
    updateSteps();

    // Scenario 2: Pushing the button --> resets steps.
    if ( stepsPushButtonChanged == true && stepsPushButton == 1 ) {
      if ( sequenceMode == 1 ) { // Steps are limited.
          setStepsPosition( bottomHit );
      } else {
        setStepsPosition(1);
      }
    }

  }

  // CLOCK MODE 1: "INTERNALLY CLOCKED" mode
  if ( stepsJackConnection == false && stepsInterval != 0 ) { // No CV plugged in and the interval for the internal clock is set.

    // Set the mode.
    int m = 1;
    if ( stepsMode != m ) {
      setStepsMode(m);
    }

    // Scenario 1: New interval after last step --> move on step further.
    if ( millis() - stepsChangeLog > stepsInterval ) {
      changeStepsPosition();
    }

    // Scenario 2: Pushing the button --> resets steps.
    if ( stepsPushButtonChanged == true && stepsPushButton == 1 ) {
      if ( sequenceMode == 1 ) { // Steps are limited.
          setStepsPosition( bottomHit );
      } else {
        setStepsPosition(1);
      }
    }

    // Scenario 3: Holding the button for longer --> Clears interval (which leads to "recording clock" mode).
    if ( stepsPushButton == 1 && ( millis() - stepsPushButtonChangeLog > longPress ) ) {
      setStepsInterval(0);
    }

  }

  // CLOCK MODE 2: "TAPPING SPEED" mode
  if ( stepsJackConnection == false && stepsInterval == 0 ) { // No CV in and no interval set.

    // Set the mode.
    int m = 2;
    if ( stepsMode != m ) {
      setStepsMode(m);
    }

    // Set steps position to 0;
    stepsPosition = 0;

    // Scenario 1: Tapping through to set the clock's speed --> Sets interval and resets steps.
    bool isTap = false;
    if ( stepsPushButton == 1 && stepsPushButtonChanged == true ) {
      isTap = true;
    }

    // Set the interval by tapping through.
    stepsTapping( isTap );

  }

  // TRACKS -----------------------------------------------------------------

  bool tracksPushButtonChanged[tracksCount];
  for (int t = 0; t < tracksCount; t++) { // Walk through all tracks.

    // Push button.
    bool b = checkPushButton( tracksPushButtonPin[t], tracksPushButton[t], tracksPushButtonChangeLog[t] ); // 0 or 1.
    tracksPushButtonChanged[t] = false;
    if ( b != tracksPushButton[t] ) { // The state has changed.
      tracksPushButtonChanged[t] = true;
      tracksPushButtonChangeLog[t] = millis();
      if ( debug == true ) {
        Serial.print("tracksPushButton[");
        Serial.print(t);
        Serial.print("]: ");
        Serial.println(b);
      }
      tracksPushButton[t] = b;
    }

    // Modes

    // TRACK MODE 0: "RECORD & PLAY"
    if ( tracksMode[t] == 0 ) {

      // Scenario 1: Tracks button pushed once --> Set and unset the tracks steps for the current step position.
      if ( tracksPushButton[t] == true && tracksPushButtonChangeLog[t] > tracksPatternChangeLog[t] && stepsPosition > 0 && !stepsPushButton ) {
        bool s;
        if ( tracksPattern[ t ][ ( stepsPosition - 1 ) ] == true ) { // Flip the state.
          s = false;
        } else {
          s = true;
        }
        setTracksPattern( t, ( stepsPosition - 1 ), s);
        logOuterHits();
      }

      // Scenario 2: Tracks button pressed long --> Switch to track mode 1 (pattern select).
      if ( tracksPushButton[t] == true && ( millis() > tracksPushButtonChangeLog[t] + longPress )  && !stepsPushButton ) {
        setTracksMode(t, 1);
      }

    }

    // TRACK MODE 1: "PATTERN SELECT"
    if ( tracksMode[t] == 1 ) {

      // Scenario 1: Just entered the mode --> Apply first pattern.
      if ( tracksModeChangeLog[t] > tracksPatternChangeLog[t] ) {
        tracksPatternPreview[t] = 0;
        applyTracksPattern(t, tracksPatternPreview[t]);
      }

      // Scenario 2: Tracks button pushed once --> Walk through (increase pattern view number).
      if ( tracksPushButtonChanged[t] == true && tracksPushButton[t] == true && tracksPushButtonChangeLog[t] > tracksPatternChangeLog[t]  && !stepsPushButton  ) {
        increaseTracksPreviewPattern(t);
        applyTracksPattern(t, tracksPatternPreview[t]);
      }

      // Scenario 2: Tracks button unpressed for a while --> Switch to mode 0.
      if ( millis() > ( tracksPatternChangeLog[t] + ( longPress ) ) ) {
        setTracksMode(t, 0);
        logOuterHits();
      }

    }

  }  

  // SEQUENCE MODES --------------------------------------------------------------

  for (int t = 0; t < tracksCount; t++) { // Walk through all tracks buttons.
    if( stepsPushButton && tracksPushButton[t] && tracksPushButtonChanged[t] ) {
      setSequenceMode(t);
    }
  }


  /* ------------------------------------------------------------------------
     DISPLAY & OUTPUT
     ------------------------------------------------------------------------
  */

  // STEPS

  for (int p = 0; p < stepsCount; p++) { // Walking through all the pixels of the steps.

    // ALL MODES: A new mode just got entered --> flash.
    if ( millis() - stepsModeChangeLog < flashTime ) {

      // Lightning the row LEDs designated to the steps in the matrix:
      clearLEDMatrix(); // Turn off all LEDs
      ledMatrixRows.setAllHigh(); // Put voltage on all rows. This is brighter than setting single LEDs.
      ledMatrixColSet(0, LOW); // Place ground on the column of the step LEDs.

    }

    // MODE 0: Walk through the steps and light the corresponding pixel.
    if ( stepsMode == 0 ) {
      if ( ( millis() > stepsModeChangeLog + flashTime ) ) { // Initial mode flash is done.

        clearLEDMatrix(); // Turn off all LEDs
        
        if ( p == stepsPosition - 1 ) {

          // Lightning the particular step LED in the matrix:
          ledMatrixRows.set(p, HIGH); // Put voltage on the rows of this step.
          ledMatrixColSet(0, LOW); // Place ground on the column of the step LEDs.

        }
      }
    }

    // MODE 1: Walk through the steps and light the corresponding pixel.
    if ( stepsMode == 1 ) { // Shine brighter when there is acutally current floating out.
      if ( ( millis() > stepsModeChangeLog + flashTime ) ) { // Initial mode flash is done.
        if ( p == stepsPosition - 1 ) {

          // Lightning the particular step LED in the matrix:
          clearLEDMatrix(); // Turn off all LEDs
          ledMatrixRows.set(p, HIGH); // Put voltage on the rows of this step.
          ledMatrixColSet(0, LOW); // Place ground on the column of the step LEDs.

        }
      }
    }

    // MODE 2: Pulsate or indicate the tap count.
    if ( stepsMode == 2 ) {

      // Scenario 1: Not tapped yet, already blinked yet --> pulsate.
      if ( tapCount == 0 && ( millis() > stepsModeChangeLog + flashTime ) ) {

        // Lightning the step LEDs in the matrix:
        int ledState = pulsateColor( stepsModeChangeLog, HIGH, LOW ); // Calculating the state (on or off).
        clearLEDMatrix(); // Turn off all LEDs
        ledMatrixRows.set(p, ledState); // Put voltage on the rows of this step.
        ledMatrixColSet(0, LOW); // Place ground on the column of the step LEDs.

      }

      // Scenario 2: Tapping in --> indicate the progress (4 * 2 lights).
      if ( tapCount != 0 ) {
        int t; // Top end of the illumination.
        switch (tapCount) {
          case 1:
            t = 1;
            break;
          case 2:
            t = 3;
            break;
          case 3:
            t = 5;
            break;
          case 4:
            t = 7;
            break;
        }
        if ( p <= t ) {

          // Lightning the particular step LED in the matrix:
          clearLEDMatrix(); // Turn off all LEDs
          ledMatrixRows.set(p, HIGH); // Put voltage on the rows of this step.
          ledMatrixColSet(0, LOW); // Place ground on the column of the step LEDs.

        }

      }

    }

  }


  // TRACKS

  for (int t = 0; t < tracksCount; t++) { // Walk through all tracks.

    for (int p = ( ( t + 1 ) * stepsCount ) ; p < ( ( t + 2 ) * stepsCount ); p++) { // Walk through all pixels of the current track.

      if ( millis() < flashTime ) { // Flash all LEDs when Arduino has booted.

        // Lightning the row LEDs designated to this track in the matrix:
        clearLEDMatrix(); // Turn off all LEDs
        ledMatrixRows.setAllHigh(); // Put voltage on all rows. This is brighter than setting single LEDs.
        ledMatrixColSet( ( t + 1 ) , LOW); // Place ground on the column of the step LEDs.

      } else {

        int s = p - ( ( t + 1 ) * stepsCount ); // The actual relative step insight of the current track.

        if ( tracksPattern[t][s] == true ) {

          // INTERLUDE: Update step status here (in case of rapidly changed external CV).
          if ( stepsMode == 0 ) {
            updateSteps();
          }

          // TRACK MODE 0: Illuminate all the active steps.
          if ( tracksMode[t] == 0 ) {

            // DISPLAY
            clearLEDMatrix(); // Turn off all LEDs
            ledMatrixRows.set( s , HIGH); // Put voltage on the row of this step.
            ledMatrixColSet( ( t + 1 ) , LOW); // Put ground on the column of this track.
        
            // OUTPUT some CV when here's a hit.
            if ( tracksPattern[t][ ( stepsPosition - 1 ) ] == true ) { // For the particular step.
        
              digitalWrite(tracksOutputPin[t], LOW); // Reset output.
        
              // Steps mode 0: High when CV in, but at least for the trigger time.
              if ( stepsMode == 0 && ( stepsCVIn == 1 || ( millis() < ( stepsChangeLog + triggerTime ) ) ) ) {
                digitalWrite(tracksOutputPin[t], HIGH);
              }
              // Steps mode 1: High in the trigger time.
              if ( stepsMode == 1 && ( millis() < ( stepsChangeLog + triggerTime ) ) ) {
                digitalWrite(tracksOutputPin[t], HIGH);
              }
        
            }

          }

          // TRACK MODE 1: Pattern select --> Blink the steps of the currently viewed predefined pattern.
          if ( tracksMode[t] == 1 ) {
            
            // Lightning the track LEDs of the pattern in the matrix:
            int ledState = pulsateColor( tracksPatternChangeLog[t], HIGH, LOW ); // Calculating the state (on or off).
            clearLEDMatrix(); // Turn off all LEDs
            ledMatrixRows.set( s , ledState); // Put voltage on the rows of this step.
            ledMatrixColSet( ( t + 1 ) , LOW); // Place ground on the column of the step LEDs.

          }

        }

      }

    }

  }

}


/* ##########################################################################
   FUNCTIONS
   ##########################################################################
*/

// GENERAL

// Check the state of a certain push button.
bool checkPushButton( int pin, bool currentState, long changeLog ) { // If HIGH or LOW.
  int r;
  // Is the last change older than a delay time?
  if ( millis() > changeLog + pushButtonDelay ) {
    r = digitalRead(pin);
  } else { // If not return old button state.
    r = currentState;
  }
  return r;
}

// DISPLAY

// Pulsate – Returns a value for a certain time since start.
int pulsateColor( long start, int on, int off ) {
  int r;
  // What's the fraction of pulses since initiated?
  double m = 0;
  if ( millis() > slowPulseTime ) {
    m = ( millis() - start ) % slowPulseTime; // Modulo
  } else {
    m = millis(); // Just for the first glimpses after booting.
  }
  double f = m / (double)(slowPulseTime); // Factor
  if ( f < 0.5 ) {
    r = on;
  } else {
    r = off;
  }    
  return r;
}

// Clear LED matrix
void clearLEDMatrix() {
  ledMatrixRows.setAllLow();
  ledMatrixColsSetAllHigh();
}

// Set the states of the columns in the LED matrix.
void ledMatrixColSet (int column, int state) {
  digitalWrite( ledMatrixColsPins[column], state); // Reset output.
}

// Set all columns to HIGH (which turns the LEDs off).
void ledMatrixColsSetAllHigh() {
  for (int c = 0; c < ( tracksCount + 1 ); c++) { // Walk through the columns (tracks + steps).
    ledMatrixColSet (c, HIGH);
  }
}


// STEPS

bool checkStepsJackConnection() {
  int r = digitalRead(stepsJackDetectionPin);
  return r;
}

void updateSteps() {
    // CV goes HIGH --> move on step further.
    // Check the CV.
    bool c = checkStepsCVIn(); // 0 or 1.
    if ( c != stepsCVIn ) {
      if ( debug == true ) {
        Serial.print("stepsCVIn: ");
        Serial.println(c);
      }
      if (c == 1) {
        changeStepsPosition();
      }
      stepsCVIn = c;
    }  
}

bool checkStepsCVIn() {
  int r = digitalRead(stepsCVInPin);
  return r;
}

// Set the steps position
void setStepsPosition(int s) {
  stepsPosition = s;
  logStepsChange(stepsPosition);
}

// Move the step position forward.
void changeStepsPosition() {
  if( sequenceMode == 0 ) { // Chronologically from start to end.
    if ( stepsPosition < stepsCount ) {
      stepsPosition++;
    } else {
      stepsPosition = 1;
    }
  }
  if( sequenceMode == 1 ) { // Chronologically limited by the bottom and top hit.
    if ( stepsPosition < topHit ) {
      stepsPosition++;
    } else {
      stepsPosition = bottomHit;
    }
  }
  if( sequenceMode == 2 ) { // Random.
    stepsPosition = random(1, stepsCount+1);
  }
  logStepsChange(stepsPosition);
}

// Log the steps change.
void logStepsChange(int p) {
  stepsChangeLog = millis();
  if ( debug == true ) {
    Serial.print("stepsPosition: ");
    Serial.print(p);
    Serial.print(" at ");
    Serial.println(stepsChangeLog);
  }
}

void setStepsInterval(int interval) {
  stepsInterval = interval;
  if ( debug == true ) {
    Serial.print("stepsInterval: ");
    Serial.println(stepsInterval);
  }
}

void setStepsMode(int mode) {
  stepsMode = mode;
  stepsModeChangeLog = millis();
  if ( debug == true ) {
    Serial.print("stepsMode: ");
    Serial.print(mode);
    Serial.print(" – ");
    Serial.println(stepsModeChangeLog);
  }
}

// Tapping through to set the interval.
void stepsTapping(bool isTap) {
  if ( isTap == true ) {
    tapCount++;
    if ( debug == true ) {
      Serial.print("tapCount: ");
      Serial.println(tapCount);
    }
    if ( tapCount == 1 ) {
      tapStart = millis();
    }
    if ( tapCount == 4 ) {
      tapEnd = millis();
    }
  }
  if ( tapEnd > tapStart && tapCount >= 4 ) { // Enough tapping, now wait another interval and then start clocking.
    int i = ( tapEnd - tapStart ) / 3;
    if ( millis() >= tapEnd + i ) {
      setStepsInterval(i);
      stepsPosition = 0;
      tapCount = 0;
    }
  }
}


// TRACKS

void setTracksMode(int track, int mode) {
  tracksMode[track] = mode;
  tracksModeChangeLog[track] = millis();
  if ( debug == true ) {
    Serial.print("tracksMode[");
    Serial.print(track);
    Serial.print("]: ");
    Serial.print(mode);
    Serial.print(" – ");
    Serial.println(tracksModeChangeLog[track]);
  }
}

// Set the pattern for a track.
void setTracksPattern( int track, int step, bool state ) {
  tracksPattern[ track ][ step ] = state;
  tracksPatternChangeLog[track] = millis();
  if ( debug == true ) {
    Serial.print("tracksPattern[");
    Serial.print(track);
    Serial.print("][");
    Serial.print(step);
    Serial.print("]: ");
    Serial.print(state);
    Serial.print(" at ");
    Serial.println(millis());
  }
}

void applyTracksPattern(int track, int pattern) {
  tracksPatternPreview[track] = pattern;
  if ( debug == true ) {
    Serial.print("tracksPatternPreview[");
    Serial.print(track);
    Serial.print("]: ");
    Serial.println(pattern);
  }
  for (int s = 0; s < stepsCount; s++) { // Walk through the steps.
    setTracksPattern( track, s, tracksPredefinedPattern[pattern][s] );
  }
}

// Icreases or resets the integer of the currently viewed pattern.
void increaseTracksPreviewPattern(int track) {
  if ( tracksPatternPreview[track] < ( tracksPatternCount - 1 ) ) {
    tracksPatternPreview[track]++;
  } else {
    tracksPatternPreview[track] = 0;
  }
}

// SEQUENCE MODES

void setSequenceMode(int mode) {
  sequenceMode = mode;
  if ( debug == true ) {
    Serial.print("sequenceMode: ");
    Serial.println(mode);
  }
}

void logOuterHits() { // Logs the bottom and top step that has a hit on a track.
  int top = 0;
  int bottom = stepsCount;
  for (int t = 0; t < tracksCount; t++) { // Walk through all tracks.
    for (int s = 0; s < stepsCount; s++) { // Walk through all steps.
      if ( tracksPattern[t][s] ) {
        if ( s < bottom ) {
          bottom = s;
        }
        if ( s > top ) {
          top = s;
        }
      } 
    }
  }
  bottomHit = bottom + 1;
  topHit = top + 1;
  if ( debug == true ) {
    Serial.print("bottomHit: ");
    Serial.print(bottomHit);
    Serial.print(", topHit: ");
    Serial.println(topHit);
  }
}
