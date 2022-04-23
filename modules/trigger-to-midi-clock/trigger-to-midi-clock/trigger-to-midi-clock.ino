
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
  
    TRIGGER TO MIDI CLOCK (Rev1)
    This is the code for an Eurorack synth module.
    It's built and tested on an Arduino Uno.

    Crucial parts of the code are taken gratefully from:
    "Arduino MIDI clock with tap tempo" by DieterVDW
    via https://github.com/DieterVDW/arduino-midi-clock

    Creative Commons yeah! License: CC BY-NC 4.0

    REFERENCES:
    - https://diymidicontroller.com/arduino-midi-clock-tutorial/ (concept basics)
    - https://www.instructables.com/Send-and-Receive-MIDI-with-Arduino/ (concept basics)
    - https://forum.arduino.cc/t/understanding-midi-clock-with-arduino/377317/2 (concept basics)
    - https://www.recordingblogs.com/wiki/midi-clock-message (concept basics)
    - https://www.recordingblogs.com/wiki/midi-system-realtime-messages (concept basics)
    
    ---------------------------------------------------------------------- */
    

/* ##########################################################################
   PRESETUP
   ##########################################################################
*/

#include <TimerOne.h>

// General
const bool debug = false; // Enables the Serial print in several functions. MIDI will not work (different baud rates).
const int pushButtonDelay = 50; // The time the button will be insensitive after last change.


// Trigger IN
const int triggerInPin = A5;
const int triggerInLEDPin = 3;
long triggerInHigh; // Timestamp of the latest trigger high.
long triggerInLow; // Timestamp of the latest trigger low.

// Cycles & intervals
long cycleStart = 0; // Timestamp of when the last cycle began (in microseconds).
long cycleTime = 0; // The absolute time span one cycle has in the given settings (in microseconds).
long intervalMicroSeconds;

// MIDI Clock OUT
#define MIDI_TIMING_CLOCK 0xF8
const int midiClockOutLEDPin = 5;

// Stop & start
const int stopButtonPin = 7;
int stopButtonState; // 0 or 1.
long stopButtonChangelog; // The timestamp of the last change on this button.
bool stopped = false; // The global stop state.


void setup() {

  if ( debug == true ) {
    Serial.begin(9600); // Initialize serial communication at 9600 bits per second.
  } else {
    // Set MIDI baud rate:
    Serial.begin(31250); // https://www.midi.org/midi-articles/arduino-midi-output-basics
  }

  // Pin settings
  pinMode(triggerInPin, INPUT);
  pinMode(triggerInLEDPin, OUTPUT);
  pinMode(midiClockOutLEDPin, OUTPUT);
  pinMode(stopButtonPin, INPUT);

  // Timer Setup
  // Docs: https://playground.arduino.cc/Code/Timer1/
  Timer1.initialize(); // No period specified, 1 second by default.
  Timer1.attachInterrupt(sendClockPulse);

  
}



void loop() {


  // Get the trigger IN state and the cycle time.
  if ( getTriggerIn() ) {

    // ------------------------ STOP & START ------------------------
    // Checking and setting the status of stop and start.
    bool s;
    s = digitalRead(stopButtonPin); // Read the button pin.
    
    if ( ( s != stopButtonState ) && ( millis() > ( stopButtonChangelog + pushButtonDelay ) ) ) { // Did the pin recently change?
      
      stopButtonState = s;
      
      stopButtonChangelog = millis();
  
      if (s == 1 && !stopped ) { // The button is pushed and the clock is globally running.
        stopped = 1; // Set globally to stopped.
        if ( debug == false ) {
          Serial.write(0xfc); // Send the MIDI stop message.
        } else {
          Serial.println("Stop");
        }
      }
  
      if (s == 0 && stopped ) { // The button is released and the clock is globally stopped.
        stopped = 0; // Set globally to start (!stopped).
        if ( debug == false ) {
          Serial.write(0xfa); // Send the MIDI start message.
        } else {
          Serial.println("Start");
        }
      }
      
    }

    // ------------------------- LEDS -------------------------
    // Light up the input LED.
    digitalWrite(triggerInLEDPin, HIGH);
    
    // Light the MIDI clock out LED, when it's running.
    if ( !stopped ) {
      digitalWrite(midiClockOutLEDPin, HIGH);
    }


    // ------------------ CYCLES & INTERVALS ------------------
    // Is it the beginning of a new cycle?
    if ( triggerInLow > triggerInHigh ) { // Yes

      // Log the latest cycle time.
      cycleTime = micros() - cycleStart;

      // Log the new cycle start timestamp.
      cycleStart = micros();

      // Debug: Log the settings on cycle start.
      if ( debug == true ) {
        Serial.print("cycleStart: ");
        Serial.println(cycleStart);
        Serial.print("cycleTime: ");
        Serial.println(cycleTime);
      }

      // Update timer period.
      intervalMicroSeconds = (long) cycleTime / 24;
      if ( debug == true ) {
        Serial.print("intervalMicroSeconds: ");
        Serial.println(intervalMicroSeconds);
      }
      Timer1.setPeriod(intervalMicroSeconds);

    }

    // Log the timestamp of this trigger high.
    triggerInHigh = micros();

  } else {

    // Mute the input LED.
    digitalWrite(triggerInLEDPin, LOW);
    
    // Mute the MIDI clock out LED if the clock is running.
    if ( !stopped ) {
      digitalWrite(midiClockOutLEDPin, LOW);
    }

    // Log the timestamp of this trigger low.
    triggerInLow = micros();

  }

}



/* ##########################################################################
   FUNCTIONS
   ##########################################################################
*/

// Read the trigger.
boolean getTriggerIn(){
  boolean t = LOW;
  t = digitalRead(triggerInPin);
  return t;
}

void sendClockPulse() {
  if ( debug == false ) {
    // Write the timing clock byte
    Serial.write(MIDI_TIMING_CLOCK);
  }
}
