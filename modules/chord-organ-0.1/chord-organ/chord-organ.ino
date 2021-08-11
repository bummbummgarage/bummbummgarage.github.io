
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
  

    CHORD ORGAN
    This is the code for an Eurorack synth module.
    It's built and tested on an Arduino Nano.
    
    Find out more on: http://bummbummgarage.github.io/
    
    ---------------------------------------------------------------------- */

/* ##########################################################################
   PRESETUP
   ##########################################################################
*/
const bool debug = false; // Enables the Serial print in several functions. Just for debugging, sound won't work properly when set on.

// Arduino synth library, see https://github.com/dzlonline/the_synth
#include <synth.h>
synth chord; // Initialzing the synth.

// Inputs 
const int rootCVIn = A0;

// Potis
const int wavePotiPin = A4;
const int rootPotiPin = A5;
const int shapePotiPin = A6;

// Waveforms
const int waveCount = 5;
const int voiceWaves[waveCount] = { SINE, TRIANGLE, SQUARE, SAW, NOISE };
int voiceWave; // The current wave. Will be intially set in the loop.

// Tune (root note)
int root; // This is the base note of the chord defined in semitones (36-84, C-2 to C+2). Will be set in the loop.
// Low and high define the range.
const int lowestRoot = 36;
const int highestRoot = 84;
int rootDelta; // This is the number of semitones to be added via the CV IN.
int tune; // The resulting tune for the chord (the base note).

// Chord shapes
const int voiceCount = 4;
const int shapeCount = 13;
const int chordShapes[shapeCount][voiceCount] = {
  { 0, 4, 7, 12 }, // Major
  { 0, 3, 7, 12 }, // Minor
  { 0, 4, 7, 11 }, // Major 7th
  { 0, 3, 7, 10 }, // Minor 7th
  { 0, 5, 7, 11 }, // Suspended 4th
  { 0, 7, 12, 0 }, // Power 5th
  { 0, 5, 12, 0 }, // Power 4th
  { 0, 4, 7, 8 }, // Major 6th
  { 0, 3, 7, 8 }, // Minor 6th
  { 0, 3, 6, 0 }, // Diminished
  { 0, 4, 8, 0 }, // Augmented
  { 0, 0, 0, 0 }, // Root
  { -24, -12, 0, 0 } // Sub Octave
};
int chordShape; // The global variable for the current chord shape. Will be set in the loop.

// Misc
const int voiceEnv = 0; // Not needed, we just play the chord along.
const int voiceLength = 0; // Not needed, we just play the chord along.
const int voiceMod = 64; // 64 means no modulation, which is fine, not needed.

/* ##########################################################################
   SETUP
   ##########################################################################
*/

void setup()
{

  if ( debug == true ) {
    Serial.begin(9600); // Initialize serial communication at 9600 bits per second.
  }

  chord.begin(); // Start it up

}

/* ##########################################################################
   LOOP
   ##########################################################################
*/

void loop()
{

  // Set the wave of the voices.
  setWave();
  
  // Set the tune.
  setTune();

  // Set the shape of the chord.
  setShape();

  // Prepare the chord.
  setupChord();

  // Play the chord
  for (int v = 0; v < voiceCount; v++) {
    chord.trigger(v);
  }

}

/* ##########################################################################
   FUNCTIONS
   ##########################################################################
*/

// Set the waveform.
void setWave() {
  int v = analogRead(wavePotiPin);
  int w = ( v * waveCount ) / 1024;
  if ( millis() < 10 || voiceWave != w ) { // Act after booting and when the value has changed.
    voiceWave = w;
    if ( debug == true ) {
      Serial.print("Wave (poti value): ");
      Serial.print(voiceWave);
      Serial.print(" (");
      Serial.print(v);
      Serial.println(")");
    }
  }
}

// Set the tune (resulting root note) from the poti and the CV In.
void setTune() {

  // 1. Get the root poti value.
  int v = analogRead(rootPotiPin); // The poti value
  int r = map(v, 0, 1023, lowestRoot, highestRoot);
  if ( millis() < 10 || root != r ) { // Act after booting and when the value has changed.
    root = r;
    if ( debug == true ) {
      Serial.print("Root (poti value): ");
      Serial.print(root);
      Serial.print(" (");
      Serial.print(v);
      Serial.println(")");
    }
  }

  // 2. Get the CV In value.
  int c = analogRead(rootCVIn);
  float unitsPerSemitone = 1024 / 4.9 / 12; // 17,4149659864
  int d = c / unitsPerSemitone; // Root is defined by the number of semitones.
  if ( millis() < 10 || rootDelta != d ) { // Act after booting and when the value has changed.
    rootDelta = d;
    if ( debug == true ) {
      Serial.print("Root delta (CV IN value): ");
      Serial.print(rootDelta);
        Serial.print(" (");
        Serial.print(c);
        Serial.println(")");
    }
  }

  // 3. Calculate the resulting tune.
  int t = root + rootDelta;
  if ( millis() < 10 || tune != t ) { // Act after booting and when the value has changed.
    tune = t;
    if ( debug == true ) {
      Serial.print("Tune (root + delta): ");
      Serial.print(tune);
      Serial.print(" (");
      Serial.print(root);
      Serial.print(" + ");
      Serial.print(rootDelta);
      Serial.println(")");
    }
  }
  
}

// Set the shape of the chord.
void setShape() {
  int v = analogRead(shapePotiPin);
  int s = ( v * shapeCount ) / 1024;
  if ( millis() < 10 || chordShape != s ) { // Act after booting and when the value has changed.
    chordShape = s;
    if ( debug == true ) {
      Serial.print("Chord shape (poti value): ");
      Serial.print(chordShape);
      Serial.print(" (");
      Serial.print(v);
      Serial.println(")");
    }
  }
}

// Setting up the voices for the chord.
void setupChord() {
  for (int v = 0; v < voiceCount; v++) {
    int baseNote = tune + chordShapes[ chordShape ][ v ];
    chord.setupVoice( v, voiceWaves[voiceWave], baseNote, voiceEnv, voiceLength, voiceMod );
  }
}
