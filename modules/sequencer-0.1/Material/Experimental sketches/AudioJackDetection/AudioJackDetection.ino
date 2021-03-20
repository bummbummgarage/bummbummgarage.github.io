

int jackDetectionPin = 2;
int CVInPin = 4;
bool jack;
bool CVIn;

int CVOutPin = 7;


void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  pinMode(jackDetectionPin, INPUT);
  pinMode(CVInPin, INPUT);
  pinMode(CVOutPin, OUTPUT);

}

void loop() {

  if( CVIn == true ) {
    digitalWrite(CVOutPin, HIGH);
  } else {
    digitalWrite(CVOutPin, LOW);
  }

  bool j = checkJack();
  if ( j != jack ) {
    Serial.print( "Jack: " );
    Serial.println( j );
    delay(50);
    jack = j;
  }

  bool c = checkCVIn();
  if ( c != CVIn ) {
    Serial.print( "CV: " );
    Serial.println( c );
    CVIn = c;
  }

}


bool checkJack() { // If HIGH or LOW.
  int r = digitalRead(jackDetectionPin);
  return r;
}

bool checkCVIn() { // If HIGH or LOW.
  int r = digitalRead(CVInPin);
  return r;
}
