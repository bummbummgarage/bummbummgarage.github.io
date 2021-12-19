

int triggerInLEDPin = 13;

long triggerInHigh; // Timestamp of the latest high.
long triggerInLow; // Timestamp of the latest low.

long cycleStart = 0; // Timestamp of when the last cycle began.
int cycleTime = 0;


int triggerOutLEDPin = 12;

int quantity = 3;

int triggerLength = 10; // In milliseconds.


void setup() {
  
  Serial.begin(9600);

  // Pin settings
  pinMode(triggerInLEDPin, OUTPUT);
  pinMode(triggerOutLEDPin, OUTPUT);

}

void loop() {

  int slices[quantity] = {}; // The time slices for the distributed hits.

  // ------------------------ TRIGGER IN ------------------------
  // Get the trigger IN state and the cycle time.
  if ( getTriggerIn() ) {

    // Light up the input LED.
    digitalWrite(triggerInLEDPin, HIGH);

    // Is it the beginning of a new cycle?
    if ( triggerInLow > triggerInHigh ) { // Yes

      Serial.println("Cycle starts");

      // Time to log the latest cycle time.
      cycleTime = millis() - cycleStart;

      // Log the new cycle start timestamp.
      cycleStart = millis();

    }
    
    triggerInHigh = millis();

  } else {

    // Mute the input LED.
    digitalWrite(triggerInLEDPin, LOW);

    triggerInLow = millis();

  }


  // ------------------------ SLICE THE CYCLE ------------------------
  // Calculate the time slices for the triggers OUT.

  if ( cycleTime != 0 ) {

    for (int i=0; i <= quantity; i++){
      
      if(i == 0) {
        slices[i] = cycleTime / quantity;
      } else {
        slices[i] = ( cycleTime / quantity ) + slices[i-1] ;
      }
    }

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
    for (int i = 0; i < quantity; i++) {

      int triggerStart = cycleStart + slices[i];
      int triggerEnd = triggerStart + triggerLength;

      if( millis() >= triggerStart && millis() < triggerEnd ) {

        digitalWrite(triggerOutLEDPin, HIGH);

      } else {

        digitalWrite(triggerOutLEDPin, LOW);

      }

    }

  }

}



// Read the trigger and set the global variable.
boolean getTriggerIn(){
  boolean t = LOW;
  int length = 10; // milliseconds
  int frequency = 1; // 120 BPM
  int cycle = 1000 / frequency;

  // One beat has a cycle of 500ms = 10ms (HIGH) + 490ms (LOW);
  for (int i = 0; i <= length; i++) {
    if ( ( millis() - i ) % cycle == 0 ) {
      t = HIGH;
    }
  }

  return t;
}
