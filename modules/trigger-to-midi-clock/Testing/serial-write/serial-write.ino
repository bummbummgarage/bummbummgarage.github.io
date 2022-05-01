
/*
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.write(45); // send a byte with the value 45

  // int bytesSent = Serial.write("hello");  //send the string "hello" and return the length of the string.
}
*/


void setup() {
 // Serial.begin(31250);
  Serial.begin(9600);
}

void loop() {
  Serial.write(0xf8); // send a byte with the value 45
  delay(100);
}
