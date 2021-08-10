
const bool debug = false; // Enables the Serial print in several functions. Sound won't work properly when true.
const int pushButtonDelay = 50; // The time a button will be muted after last change.


// Arduino synth library modulation example

//Hardware connections:

//                    +10µF
//PIN 11 ---[ 1k ]--+---||--->> Audio out
//                  |
//                 === 10nF
//                  |
//                 GND

// DZL 2014
// HTTP://dzlsevilgeniuslair.blogspot.dk
// HTTP://illutron.dk

#include <synth.h>

synth chord; // Initialzing the synth.

const int wavePotiPin = A5;
const int rootPotiPin = A6;
const int shapePotiPin = A7;

int root = 69; // This is the base note of the chord (36-84, C-2 to C+2). "A" by default, will be updated in the loop.
// Low and high define the range.
const int lowestRoot = 36;
const int highestRoot = 84;

const int waveCount = 5;
const int voiceWaves[waveCount] = { SINE, TRIANGLE, SQUARE, SAW, NOISE };
int voiceWave = 0; // Start with a sine.

const int voiceEnv = 0; // Not needed, we just play the chord along.
const int voiceLength = 0; // Not needed, we just play the chord along.
const int voiceMod = 64; // 64 means no modulation, which is fine, not needed.

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

int chordShape = 5;


void setup()
{

  if ( debug == true ) {
    Serial.begin(9600); // Initialize serial communication at 9600 bits per second.
  }

  chord.begin();  // Start it up

}

void loop()
{

  // Set the root note.
  setRoot();

  // Set the wave of the voices.
  setWave();

  // Set the shape of the chord.
  setShape();

  // Prepare the chord.
  setupChord();

  // Play the chord
  for (int v = 0; v < voiceCount; v++) {
    chord.trigger(v);
  }

}


// Setting up the voices for the chord.
void setupChord() {

  for (int v = 0; v < voiceCount; v++) {
    int tune = root + chordShapes[ chordShape ][ v ];
    chord.setupVoice( v, voiceWaves[voiceWave], tune, voiceEnv, voiceLength, voiceMod );
  }

}


// Set the root note from the poti and the CV In.
void setRoot() {
  root = readRootPoti();
}


// Get the value from the root poti.
// Return something between 0 and 127.
int readRootPoti() {
  int v = analogRead(rootPotiPin); // The poti value
  int t = map(v, 0, 1023, lowestRoot, highestRoot);
  if ( debug == true ) {
    Serial.print("rootPotiVal (tune): ");
    Serial.print(v);
    Serial.print(" (");
    Serial.print(t);
    Serial.println(")");
  }
  return t;
}


// Set the shape of the chord.
void setShape() {
  chordShape = readShapePoti();
}

// Read the shape poti.
int readShapePoti() {
  int v = analogRead(shapePotiPin);
  int s = ( v * shapeCount ) / 1024;
  if ( debug == true ) {
    Serial.print("shapePotiVal (shape): ");
    Serial.print(v);
    Serial.print(" (");
    Serial.print(s);
    Serial.println(")");
  }
  return s;
}

void setWave() {
  voiceWave = readWavePoti();
}

// Read the waveform poti.
int readWavePoti() {
  int v = analogRead(wavePotiPin);
  int w = ( v * waveCount ) / 1024;
  if ( debug == true ) {
    Serial.print("wavePotiVal: ");
    Serial.println(w);
  }
  return w;
}
