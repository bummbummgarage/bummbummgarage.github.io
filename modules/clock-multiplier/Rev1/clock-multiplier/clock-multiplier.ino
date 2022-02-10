
/* ##########################################################################
   PRESETUP
   ##########################################################################
*/

// General
const bool debug = false; // Enables the Serial print in several functions. Slows down the frontend.
const bool internalClock = false; // Refuses the triggers and starts the internal clock. Meant for developing / debugging.
const int internalClockBpm = 70; // The speed for the internal clock.
const int pushButtonDelay = 50; // The time the button will be insensitive after last change.


// Trigger IN
int triggerInPin = A5;
int triggerInLEDPin = 3;

long triggerInHigh; // Timestamp of the latest trigger high.
long triggerInLow; // Timestamp of the latest trigger low.


// Cycles
long cycleStart = 0; // Timestamp of when the last cycle began.
int cycleTime = 0; // The absolute time span one cycle has in the given settings.


// Quantity
const int quantityPotiPin = A3;
const int quantityCVPin = A4;
const int maxQuantity = 8; // The maximum amount of possible triggers out per cycle.
int currentQuantity; // The current amount of triggers per cycle.


// Distribution
const int distributionPotiPin = A2;
const int maxDistribution = 11; // The amount of different distribution patterns.
int currentDistribution;


// Mute
const int mutePin = 2;
int mutePinState; // 0 or 1.
long mutePinChangelog; // The timestamp of the last change on this button.
bool mute = false; // The global mute state.


// Trigger OUT
int triggerOutLEDPin = 5;
int triggerOutLedMuted = 5; // The amount of brightness when muted.
const int triggerLength = 25; // In milliseconds.
int triggerOut = LOW;



/* ##########################################################################
   SETUP
   ##########################################################################
*/

void setup() {

  if ( debug == true ) {
    Serial.begin(9600); // Initialize serial communication at 9600 bits per second.
  }

  // Pin settings
  pinMode(triggerInPin, INPUT);
  pinMode(triggerInLEDPin, OUTPUT);
  pinMode(quantityPotiPin, INPUT);
  pinMode(quantityCVPin, INPUT);
  pinMode(distributionPotiPin, INPUT);
  pinMode(mutePin, INPUT);
  pinMode(triggerOutLEDPin, OUTPUT);

}


/* ##########################################################################
   LOOP
   ##########################################################################
*/

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

  // ------------------------ QUANTITY ------------------------
  int q = getQuantity();
  if( currentQuantity != q ) {
    currentQuantity = q;
    digitalWrite(triggerInLEDPin, HIGH); // A little flash to indicate the change.
    if ( debug == true ) {
      Serial.print("currentQuantity: ");
      Serial.println(currentQuantity);

      int cvQuantity = analogRead(quantityCVPin);
      Serial.println(cvQuantity);
      
    }
  }


  // ------------------------ DISTRIBUTION ------------------------
  int d = getDistribution();
  if( currentDistribution != d ) {
    currentDistribution = d;
    digitalWrite(triggerInLEDPin, HIGH); // A little flash to indicate the change.
    if ( debug == true ) {
      Serial.print("currentDistribution: ");
      Serial.println(currentDistribution);
    }
  }


  // ------------------------ MUTE ------------------------
  // Checking and setting the status of mute or unmuted.
  bool p;
  p = digitalRead(mutePin); // Read the pin.
  if ( ( p != mutePinState ) && ( millis() > ( mutePinChangelog + pushButtonDelay ) ) ) { // Did the pin recently change?
    mutePinState = p;
    mutePinChangelog = millis();
    if (p == 1) { // The button is pushed.
      // toggle the global mute state.
      if(mute) {
        mute = false;
        if(debug) {
          Serial.println("Unmute");
        }
      } else {
        mute = true;
        if(debug) {
          Serial.println("Mute");
        }
      }
      digitalWrite(triggerInLEDPin, HIGH); // A little flash to indicate the change.
    }
  }
  

  // ------------------------ TRIGGER OUT ------------------------
  // 1. Calculate the time slices for the triggers OUT.
  // This happens all the time because the settings can change anytime.
  // We will calculate the exact timestamps when the single hits should follow based on the current settings.
  // And then act on'em, meaning LED and the trigger.

  for(int i = 0; i < currentQuantity; i++ ) {

    // 1. Calculate the decimals from 0 to 1 for our hit quantity.
    double d = (double) i*1/currentQuantity;

    // 2. Calculate the resulting factor depending on the set ease function.
    // Based on: https://easings.net/
    double f;

    switch (currentDistribution) {
      case 1:
        f = d * d * d * d * d; // easeInQuint
        break;
      case 2:
        f = d * d * d * d; // easeInQuart
        break;
      case 3:
        f = d * d * d; // easeInCubic
        break;
      case 4:
        f = d * d; // easeInQuad
        break;
      case 5:
        f = 1 - cos((d * PI) / 2); // easeInSine
        break;
      case 6:
        f = d; // Linear
        break;
      case 7:
        f = sin((d * PI) / 2); // easeOutSine
        break;
      case 8:
        f = 1 - (1 - d) * (1 - d); // easeOutQuad
        break;
      case 9:
        f = 1 - pow(1 - d, 3); // easeOutCubic
        break;
      case 10:
        f = 1 - pow(1 - d, 4); // easeOutQuart
        break;
      case 11:
        f = 1 - pow(1 - d, 5); // easeOutQuint
        break;
      default:
        f = d; // Linear
        break;
    }                         

    // 3. Calculate the resulting absolute timestamp.
    long t = (long) cycleStart + ( cycleTime * f );

    // 4. Check if we're in the time span to trigger and blink.
    if ( ( millis() >= t ) && ( millis() < ( t + triggerLength ) ) ) {
      if(!mute) {
        triggerOut = 255;
      } else {
        triggerOut = triggerOutLedMuted;
      }
      i = currentQuantity; // If so, stop the right away to keep the trigger HIGH.
    } else {
      triggerOut = 0;
    }
    
  }

  // Flash the output LED.
  analogWrite( triggerOutLEDPin, triggerOut );

}



/* ##########################################################################
   FUNCTIONS
   ##########################################################################
*/

// Read the trigger and set the global variable.
boolean getTriggerIn(){
  boolean t = LOW;

  if ( !internalClock ) {
    
    t = digitalRead(triggerInPin);
    
  } else {
    
    int cycle = 1000 / ( internalClockBpm / 60 );
    for (int i = 0; i <= triggerLength; i++) { // Run the clock.
      if ( ( millis() - i ) % cycle == 0 ) {
        t = HIGH;
      }
    }
    
  }

  return t;
}


// Read the CV inputs for the quantity.
int getQuantity() {
    int basicQuantity = analogRead(quantityPotiPin); // The basic quantity given by the poti
    int cvQuantity = analogRead(quantityCVPin); // The quantity given by the control voltage IN.
    // Map both values summed up.
    int q = map( ( basicQuantity + cvQuantity ), 0, 1024, 1, ( maxQuantity + 1 ) );
    // Return the value with the defined maximum.
    int r;
    if( q > maxQuantity ) {
      r = maxQuantity;
    } else {
      r = q;
    }
    return r;
}

// Read the CV input (poti) for the distribution.
int getDistribution() {
    int d;
    d = map( analogRead(distributionPotiPin), 0, 1023, 1, ( maxDistribution + 1 ) );
    return d;
}
