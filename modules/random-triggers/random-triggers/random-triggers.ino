

// General
const bool debug = false; // Enables the Serial print in several functions. Slows down the frontend.
const bool internalClock = false; // Refuses the triggers and starts the internal clock. Meant for developing / debugging.
const int internalClockBpm = 480; // The speed for the internal clock.


// Trigger IN
bool triggerIn = false; // Indicator that the current HIGH state has already been detected.
int triggerInLEDPin = 3;
int triggerInPin = A5;


// PATTERN
int patternLength;
int patternDensity;
const int densityPotiPin = A3;
const int lengthPotiPin = A2;
String pattern; // The current pattern stored in zeros (0 = no trigger) and ones (1 = trigger).
long calculation; // Timestamp of the latest calculation.
int calcIndication = 200; // Time in milliseconds that the LEDs are lid to indicate the recent calculation.


// Trigger OUT
int patternPosition = 1; // Starts at 1 and ends at patternLength.
const int triggerLength = 25; // In milliseconds.
const int triggerOutLEDPin = 5;
long triggerOutHigh; // Timestamp of the latest trigger out.
int triggerOutPin = 6;




/* ##########################################################################
   SETUP
   ##########################################################################
*/

void setup() {

  if ( debug == true ) {
    Serial.begin(9600); // Initialize serial communication at 9600 bits per second.
  }

  // Pin settings
  pinMode(triggerInLEDPin, OUTPUT);
  pinMode(triggerInPin, INPUT);
  pinMode(densityPotiPin, INPUT);
  pinMode(triggerOutLEDPin, OUTPUT);
  pinMode(triggerOutPin, OUTPUT);

  // Ensuring non-repeating randomness in random().
  // See https://www.arduino.cc/reference/en/language/functions/random-numbers/randomseed/
  randomSeed(analogRead(0));

}



/* ##########################################################################
   LOOP
   ##########################################################################
*/

void loop() {
  

  // --------------------- CALCULATE PATTERN --------------------

  int l = getLength(); // The length of the pattern.
  int d = getDensity(); // The density of the pattern.
  bool c = false; // Indicator to re-calculate.

  // Did the pattern config change?
  // Length
  if ( l != patternLength ) {
      
    if ( debug == true ) {
      Serial.print("Pattern length: ");
      Serial.println(l);
    }

    // Set the new length globally.
    patternLength = l;

    // Ping the calculation.
    c = true;
    
  }

  // Density
  if ( d != patternDensity ) {
      
    if ( debug == true ) {
      Serial.print("Pattern density: ");
      Serial.print(d);
      Serial.println(" %");
    }

    // Set the new density globally.
    patternDensity = d;

    // Ping the calculation.
    c = true;
    
  }

  // Re-calculate pattern and reset position if needed 
  if ( c == true ) {

    String p = calculatePattern( patternLength , patternDensity );

    // Set the global pattern accordingly.
    pattern = p;

    // Store the timestamp of the calculation.
    calculation = millis();
      
    if ( debug == true ) {
      Serial.print("Pattern: ");
      Serial.println(p);
    }

    // Reset global pattern position.
    patternPosition = 1;
    
  }

  // Light both LEDs when the pattern has been calculated.
  if ( millis() <= ( calculation + calcIndication ) ) {

    digitalWrite(triggerInLEDPin, HIGH);
    digitalWrite(triggerOutLEDPin, HIGH);
      
  }


  // ------------------------ MATCH TRIGGERS ------------------------
  if ( getTriggerIn() ) {

    // Light up the trigger in LED.
    digitalWrite(triggerInLEDPin, HIGH);

    // Is this truely the beginning of this trigger high?
    if ( !triggerIn ) { // Check against the latest stored state.
      
      // Log the current trigger in high phase.
      triggerIn = true;
      
      if ( debug == true ) {
        Serial.println("Trigger IN");
      }
      
      // Do we have a trigger on the current pattern position?
      if ( pattern.substring( ( patternPosition - 1 ) ).startsWith( "1" ) ) { // YES!
  
        // Log the trigger out.
        triggerOutHigh = millis();
        
        if ( debug == true ) {
          Serial.print("patternPosition: ");
          Serial.println(patternPosition);
          Serial.println("Trigger OUT");
        }
        
      }
    
      // Advance pattern position.
      if ( patternPosition < patternLength ) {
        patternPosition++;
      } else {
        patternPosition = 1;
      }
      
    }
    
  } else {

      // Mute the trigger in LED (if there is no calc. to be indicated).
      if ( millis() > ( calculation + ( triggerLength * 4 ) ) ) {
        digitalWrite(triggerInLEDPin, LOW);
      }
    
      // Log the current trigger in low phase.
      triggerIn = false;
    
  }


  // ----------------------- SEND TRIGGERS ------------------------

  // Send the trigger out and light the LED as long it's time.
  if ( millis() <= ( triggerOutHigh + triggerLength ) ) {
    
    digitalWrite(triggerOutLEDPin, HIGH);
    digitalWrite(triggerOutPin, HIGH);
    
  } else {

    // Mute the light (when no calc. is to be indicated).
    if ( millis() > ( calculation + calcIndication ) ) {
      digitalWrite(triggerOutLEDPin, LOW);
      digitalWrite(triggerOutPin, LOW);
    } 
    
  }

}



/* ##########################################################################
   FUNCTIONS
   ##########################################################################
*/

// Read the trigger.
boolean getTriggerIn(){
  boolean t = LOW;
  if ( !internalClock ) { // the external clock
    t = digitalRead(triggerInPin);
  } else { // the internal clock (when developing or debugging).
    int cycle = 1000 / ( internalClockBpm / 60 );
    for (int i = 0; i <= triggerLength; i++) { // Run the clock.
      if ( ( millis() - i ) % cycle == 0 ) {
        t = HIGH;
      }
    }
  }
  return t;
}


// Read the poti and return the trigger pattern length.
int getLength(){

  // Get the density as a number between 1 and 4.
  int v  = map( analogRead(lengthPotiPin), 0, 1024, 1, 6 );

  int l;
  
  switch (v) {
    case 1:
      l = 8;
      break;
    case 2:
      l = 16;
      break;
    case 3:
      l = 32;
      break;
    case 4:
      l = 64;
      break;
    case 5:
      l = 128;
      break;
    case 6:
      l = 128;
      break;
  }
  
  return l;
}


// Read the poti and return the trigger pattern density.
int getDensity() {

  // Get the density as a number between 0 and 100.
  int d  = map( analogRead(densityPotiPin), 0, 1024, 0, 100 );
  
  return d;
}


// Calculate the pattern based on the current config.
String calculatePattern( int l , int d ){

  String p; // The pattern to be stored.

  // Iteratively create the pattern.
  for (int i = 0; i < l; i++) {
  
    // Random binary with propability
    // As seen on: https://forum.arduino.cc/t/increasing-probability-with-a-number/358459/6
    if ( random( 100 ) < d ) {
      
      // will be executed d % of time
      p = p + "1";
      
    } else {
      
      // will be executed in ( 100 – d ) % of the time
      p = p + "0";
      
    }

  }
  
  return p;
}
