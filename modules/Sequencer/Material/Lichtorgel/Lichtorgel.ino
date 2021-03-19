



int ledPinA = 11;
int timeA = 5000;
int ledPinB = 10;
int timeB = 55000;
int ledPinC = 9;
int timeC = 34000;
int ledPinD = 6;
int timeD = 21000;
int ledPinE = 5;
int timeE = 8000;
int ledPinF = 3;
int timeF = 13000;

void setup() {
  pinMode(ledPinA,OUTPUT);
  pinMode(ledPinB,OUTPUT);
  pinMode(ledPinC,OUTPUT);
  pinMode(ledPinD,OUTPUT);
  pinMode(ledPinE,OUTPUT);
  pinMode(ledPinF,OUTPUT);
  Serial.begin(9600) ;  // setup the serial for debugging 
}

void loop(){

  lightLED ( ledPinA, timeA );
  lightLED ( ledPinB, timeB );
  lightLED ( ledPinC, timeC );
  lightLED ( ledPinD, timeD );
  lightLED ( ledPinE, timeE );
  lightLED ( ledPinF, timeF );
  

  /*

  float value;

  int modulo ;

  if( millis() < timeA ) {

    modulo = millis();
    
  } else {

    modulo = millis() % timeA;
    
  }
  
  Serial.println( modulo );

  // Arduino LED Breathing with Gauss bells: https://makersportal.com/blog/2020/3/27/simple-breathing-led-in-arduino
  float gamma = 0.11; // affects the width of peak (more or less darkness), don't change much for an effect.
  float beta = 0.5; // shifts the gaussian to be symmetric

  value = 255.0 * ( exp( -( pow( ( ( (float)modulo / (float)timeA ) - beta ) / gamma, 2.0 ) ) / 2.0 ) );
  
  Serial.println( value );

  analogWrite(ledPinA, value);
  */
  

  /*
  int result = millis() % 50000;
  Serial.println( result );

  int LEDValue = ( result * 255 ) / 50000;

  analogWrite(ledPinA, LEDValue);
  */
  
}



float lightLED ( int ledPin, int duration ) {

  float value;

  int modulo ;

  if( millis() < duration ) {

    modulo = millis();
    
  } else {

    modulo = millis() % duration;
    
  }
  
  // Serial.println( modulo );

  // Arduino LED Breathing with Gauss bells: https://makersportal.com/blog/2020/3/27/simple-breathing-led-in-arduino
  float gamma = 0.11; // affects the width of peak (more or less darkness), don't change much for an effect.
  float beta = 0.5; // shifts the gaussian to be symmetric

  value = 255.0 * ( exp( -( pow( ( ( (float)modulo / (float)duration ) - beta ) / gamma, 2.0 ) ) / 2.0 ) );
  
  // Serial.println( value );

  analogWrite(ledPin, value);
  
}


/*
int ledPinA = 11;
int ledPinB = 10;
int ledPinC = 9;
int ledPinD = 6;
// int ledPinE = 5;
// int ledPinF = 3;

int timeA = 3000;
int timeB = 3000;
int timeC = 3000;

void setup() {
  pinMode(ledPinA,OUTPUT);
  pinMode(ledPinB,OUTPUT);
  pinMode(ledPinC,OUTPUT);
  pinMode(ledPinD,OUTPUT);
}

void loop(){
  fadeOn(timeA,5,ledPinA);
  fadeOff(timeA,5,ledPinA);
  fadeOn(timeB,5,ledPinB);
  fadeOff(timeB,5,ledPinB);
  fadeOn(timeB,5,ledPinB);
  fadeOff(timeB,5,ledPinB);
}

void fadeOn(unsigned int time,int increament, int ledPin){
  for (byte value = 0 ; value < 255; value+=increament){
    analogWrite(ledPin, value);
    delay(time/(255/5));
  }
}

void fadeOff(unsigned int time,int decreament, int ledPin){
  for (byte value = 255; value >0; value-=decreament){
    analogWrite(ledPin, value);
    delay(time/(255/5));
  }
}
*/




/*

// 14CORE Pulsing / Breating LED Sketch

int LEDPin = 11; 

float sinVal;
int ledVal;

void setup() {
pinMode(LEDPin, OUTPUT);
}

void loop() {
for (int x=0; x<180; x++) {

// convert degrees to radians then obtain the sin value then obtain sin value

sinVal = (sin(x*(3.1412/180)));

int ledVal = int(sinVal*255);
analogWrite(LEDPin, ledVal);
delay(25); // Delay 2 seconds 

  }
}

*/





/*
int LEDsUpperEnd = 13;
int LEDsLowerEnd = 10;

void setup() {

  for (int i = LEDsLowerEnd; i <= LEDsUpperEnd; i++) {
    pinMode(i, OUTPUT) ; // setup all of the neccesary LED pins
  }
  // Serial.begin(9600) ;  // setup the serial for debugging 
}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(13, HIGH);

  int randomNum = random(LEDsLowerEnd, LEDsUpperEnd); // pick random light to turn on. 
  digitalWrite(randomNum, HIGH) ; // turn on the randomly chosen light 
  
  int randomTime = random(500, 3000); // pick a random amount of time to wait, the lowest being the minimum and the highest being the maxium
  delay(randomTime) ;  //wait the random time 

  digitalWrite(randomNum, LOW) ; // turn off the light 
  
}
*/
