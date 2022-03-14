
const bool debug = false; // Enables the Serial print in several functions. Slows down the frontend.


// Fixated bottom and top end of the bpm scale for this clock.
// Music genre tempos: https://soundprogramming.net/synthesis/bpm-by-musical-genre/
const int lowestBpm = 0;
const int highestBpm = 200;

int maxBpm; // This can change on the run.
int minBpm; // This can change on the run.

const int bpmPotiPin = A0;
long bpm; // The global BPM storage.

const int minTrimpotPin = A1;
const int maxTrimpotPin = A2;

const int counterLEDPin = 11;

const int LEDPrimaryBright = 255;
const int LEDSecondaryBright = 10;


long lastBeat = 0; // Timestamp of the latest beat. Starts at zero.


const int triggerLength = 25; // In milliseconds.


const int bpmLEDPin = 10;



void setup() {

  if ( debug == true ) {
    Serial.begin(9600);
  }

  pinMode(bpmPotiPin, INPUT);
  pinMode(minTrimpotPin, INPUT);
  pinMode(maxTrimpotPin, INPUT);
  pinMode(counterLEDPin, OUTPUT);
  pinMode(bpmLEDPin, OUTPUT);

}

void loop() {

  /* --------------------------- 1. Get the BPM range --------------------------- */

  int mx = getMax();
  if ( mx != maxBpm ) {
    if ( debug == true ) {
      Serial.print("maxBpm: ");
      Serial.println(mx);
    }
    maxBpm = mx;
  }

  int mn = getMin();
  if ( mn != minBpm ) {
    if ( debug == true ) {
      Serial.print("minBpm: ");
      Serial.println(mn);
    }
    minBpm = mn;
  }

  /* ----------------------------- 2. Calculate BPM ----------------------------- */

  int b = getBpm();
  if ( b != bpm ) {
    if ( debug == true ) {
      Serial.print("BPM: ");
      Serial.println(b);
    }
    bpm = b;
    lastBeat = millis(); // Start cycles from the beginning.
  }

  /* ---------------------- 3. Calculate triggers per beat ---------------------- */

  // How many milliseconds has one beat cycle?
  long beatCycle = 60000 / bpm;

  // Has already enough time passed for the next beat?
  /*
    if( ( ( millis() - lastBeat ) % beatCycle ) == 0 ) {
      lastBeat = millis();
      if ( debug == true ) {
        Serial.print("lastBeat: ");
        Serial.println(lastBeat);
      }
    }
  */

  if ( ( millis() - beatCycle ) == lastBeat ) {
    lastBeat = millis();
    if ( debug == true ) {
      Serial.print("lastBeat: ");
      Serial.println(lastBeat);
    }
  }

  // Hier läuft etwas noch nicht rund. Mit den beiden Methoden oben fallen teilweise oder alle folgenden Schläge aus.


  /* ------------------------ 4. Output LEDS & triggers -------------------------- */

  // COUNTER LED
  // Light the counter LED a little on each second bpm (…2, …4, …6, …8).
  if ( bpm % 2 == 0 ) {
    analogWrite(counterLEDPin, LEDSecondaryBright);
    // Light the counter LED fully when the BPM is a multiple of ten (10, 20, 30, 40, …).
    if ( bpm % 10 == 0 ) {
      analogWrite(counterLEDPin, LEDPrimaryBright);
    }
  }
  else {
    analogWrite(counterLEDPin, 0);
  }

  // BPM LED
  if ( lastBeat - millis() < triggerLength ) {
    if ( debug == true ) {
      Serial.println("BEAT");
    }
    analogWrite(bpmLEDPin, LEDPrimaryBright);
  } else {
    analogWrite(bpmLEDPin, 0);
  }

}


// FUNCTIONS

// Calculate the maximum BPM.
int getMax() {
  int v = analogRead( maxTrimpotPin );
  int m = map( v, 0, 1023, lowestBpm, highestBpm );
  return m;
}

// Calculate the minimum BPM.
int getMin() {
  int v = analogRead( minTrimpotPin );
  int m = map( v, 0, 1023, lowestBpm, maxBpm );
  return m;
}

// Calculate the bpm based on the current settings.
int getBpm() {
  int v = analogRead( bpmPotiPin );
  int b = map( v, 0, 1023, minBpm, maxBpm );
  return b;
}
