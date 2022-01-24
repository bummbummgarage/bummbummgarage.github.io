
// General
const bool debug = true; // Enables the Serial print in several functions. Slows down the frontend.


int triggerInLEDPin = 2;

long triggerInHigh; // Timestamp of the latest trigger high.
long triggerInLow; // Timestamp of the latest trigger low.

long cycleStart = 0; // Timestamp of when the last cycle began.
int cycleTime = 0; // The absolute time span one cycle has in the given settings.

int quantity = 4; // The amount of triggers per cycle.

float distribution = 1; // 1 is equally distributed.

int triggerOutLEDPin = 3;
const int triggerLength = 25; // In milliseconds.

void setup() {

  if ( debug == true ) {
    Serial.begin(9600); // Initialize serial communication at 9600 bits per second.
  }

  // Pin settings
  pinMode(triggerInLEDPin, OUTPUT);
  pinMode(triggerOutLEDPin, OUTPUT);

}

void loop() {

  // ------------------------ TRIGGER IN ------------------------
  // Get the trigger IN state and the cycle time.
  if ( getTriggerIn() ) {

    // Light up the input LED.
    digitalWrite(triggerInLEDPin, HIGH);

    // Is it the beginning of a new cycle?
    if ( triggerInLow > triggerInHigh ) { // Yes

      // Log the latest cycle time.
      cycleTime = millis() - cycleStart;

      // Log the new cycle start timestamp.
      cycleStart = millis();

      // Debug: Log the settings on cycle start.
      if ( debug == true ) {
        Serial.print("cycleStart: ");
        Serial.println(cycleStart);
        Serial.print("cycleTime: ");
        Serial.println(cycleTime);
      }

    }

    // Log the timestamp of this trigger high.
    triggerInHigh = millis();

  } else {

    // Mute the input LED.
    digitalWrite(triggerInLEDPin, LOW);

    // Log the timestamp of this trigger low.
    triggerInLow = millis();

  }


  // ------------------------ SLICE THE CYCLE ------------------------
  // Calculate the time slices for the triggers OUT.
  // This happens all the time because the settings can change anytime.

  int slices[quantity] = {}; // The time slices for the distributed hits.
  
  if ( debug == true && getTriggerIn() ) {
    Serial.print("slices: ");
  }        
  
  for(int i = 0; i < quantity; i++ ) {

    if (i==0) {

      slices[i] = (int) ( distribution * ( cycleTime / quantity ) );

    } else {

      slices[i] = (int) ( distribution * ( ( cycleTime - slices[i-1] ) / ( quantity - i ) ) + slices[i-1] );

    }
    
    if ( debug == true && getTriggerIn() ) {
      Serial.print( slices[i] );
      Serial.print(" ");
    }

  }
    
  if ( debug == true && getTriggerIn() ) {
    Serial.println("");
  }


  // ------------------------ TRIGGER OUT ------------------------
  // Set the trigger OUT state.

  if ( cycleTime != 0 ) {

    // Trigger at the beginning of each cycle.
    if ( millis() < ( cycleStart + triggerLength ) ) {
      digitalWrite(triggerOutLEDPin, HIGH);

    } else {
      digitalWrite(triggerOutLEDPin, LOW);
    }

    // Triggers for the slices.
    for (int i = 0; i < ( quantity - 1 ); i++) {

      // Trigger output when we're in the right time window.
      if( millis() >= ( cycleStart + slices[i] ) && millis() < ( cycleStart + slices[i] + triggerLength ) ) {

        digitalWrite(triggerOutLEDPin, HIGH);
        /*
        Serial.print(i);
        Serial.print(": ");
        Serial.print(millis());
        Serial.println("-");
        */

      } else {

        digitalWrite(triggerOutLEDPin, LOW);

      }

    }

  }

}


// Read the trigger and set the global variable.
boolean getTriggerIn(){
  boolean t = LOW;
  int frequency = 1; // 120 BPM
  int cycle = 1000 / frequency;

  // One beat has a cycle of 500ms = 10ms (HIGH) + 490ms (LOW);
  for (int i = 0; i <= triggerLength; i++) {
    if ( ( millis() - i ) % cycle == 0 ) {
      t = HIGH;
    }
  }

  return t;
}
