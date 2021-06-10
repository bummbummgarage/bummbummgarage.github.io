
const int notePotiPin = A0;
int notePotiVal = 0;
int note = 0; // 0 = C, 1 = Cis, 2 = D, …
const int noteLedPins[4] = { 9,10,11,12 }; // The LEDs for the binary display of the current note.


int octave = 0; // We'll have 4 octaves with the given 5 volts. 0 at system start. 
const int CVOutPin = 3;
float CVOut = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Initialize serial communication at 9600 bits per second.

  for( int l=0; l<4; l++ ) {
    pinMode(noteLedPins[l], OUTPUT);  // sets the pin as output
  }
  

}

void loop() {

  // Get the actual note.
  notePotiVal = ( analogRead(notePotiPin) ) * 3; // Times 3 to have no decimal numbers.

  if ( note != notePotiVal/256 ) {
    note = notePotiVal/256;
    Serial.print( "potiVal: ");
    Serial.println( notePotiVal / 3 );
    Serial.print( "note: ");
    Serial.println( note );
  }

  // Display the note on the binary display.
  displayBinary( note + 1 );
  // Output the CV.
  // analogWrite values go from 0 to 255.
  // 255/5 = 51
  float c = note * ( 51.0 / 12.0 );
  if ( CVOut != c ) {
    CVOut = c;
    Serial.print( "CVOut: " );
    Serial.println( CVOut );
  }
  
  analogWrite(CVOutPin, CVOut );
  
  
}


// As seen on http://www.multiwingspan.co.uk/arduino.php?page=led5
void displayBinary(byte numToShow)
{
  for (int i=0;i<4;i++)
  {
    if (bitRead(numToShow, i)==1)
    {
      digitalWrite(noteLedPins[i], HIGH);
    }
    else
    {
      digitalWrite(noteLedPins[i], LOW);
    }
  }

}
