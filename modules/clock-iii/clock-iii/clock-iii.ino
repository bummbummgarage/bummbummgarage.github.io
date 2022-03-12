// Fixated bottom and top end of the bpm scale for this clock.
// Music genre tempos: https://soundprogramming.net/synthesis/bpm-by-musical-genre/
const int lowestBpm = 0;
const int highestBpm = 200;

int maxBpm; // This can change on the run.
int minBpm; // This can change on the run.

const int bpmPotiPin = A0;
int bpm; // The global BPM storage.

const int minTrimpotPin = A1;
const int maxTrimpotPin = A2;

const int counterLEDPin = 11;

const int LEDPrimaryBright = 150;
const int LEDSecondaryBright = 10;


void setup() {

  Serial.begin(9600);

  pinMode(bpmPotiPin, INPUT);
  pinMode(minTrimpotPin, INPUT);
  pinMode(maxTrimpotPin, INPUT);
  pinMode(counterLEDPin,OUTPUT);

}

void loop() {

  /* --------------------------- 1. Get the BPM range --------------------------- */

  int mx = getMax();
  if ( mx != maxBpm ) {
    Serial.print("maxBpm: ");
    Serial.println(mx);
    maxBpm = mx;
  }
  
  int mn = getMin();
  if ( mn != minBpm ) {
    Serial.print("minBpm: ");
    Serial.println(mn);
    minBpm = mn;
  }

  /* ----------------------------- 2. Calculate BPM ----------------------------- */

  int b = getBpm();
  if ( b != bpm ) {
    Serial.print("BPM: ");
    Serial.println(b);
    bpm = b;   
  }

  /* ---------------------- 3. Calculate triggers per beat ---------------------- */


  /* ------------------------ 4. Output LEDS & triggers -------------------------- */

  // COUNTER LED
  // Light the counter LED a little on each second bpm (…2, …4, …6, …8).
  if ( bpm % 2 == 0 ) {
    analogWrite(counterLEDPin,LEDSecondaryBright);
    // Light the counter LED fully when the BPM is a multiple of ten (10, 20, 30, 40, …).
    if ( bpm % 10 == 0 ) {
      analogWrite(counterLEDPin,LEDPrimaryBright);
    }
  }
  else {
    analogWrite(counterLEDPin,0); 
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
