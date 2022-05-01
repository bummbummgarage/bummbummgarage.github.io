
/*
  int incomingByte = 0;

  void setup() {

  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

  }

  void loop() {

  if (Serial.available() > 0) {

  incomingByte = Serial.read(); // read the incoming byte:

  Serial.print(" I received:");

  Serial.println(incomingByte);

  }

  }
*/



byte midi_start = 0xfa;
byte midi_stop = 0xfc;
byte midi_clock = 0xf8;
byte midi_continue = 0xfb;
int play_flag = 0;
byte data;

void setup() {
  Serial.begin(31250);
}

void loop() {
  if (Serial.available() > 0) {

    data = Serial.read();

    /*
    if (data == midi_start) {
      play_flag = 1;
    } else if (data == midi_continue) {
      play_flag = 1;
    } else if (data == midi_stop) {
      play_flag = 0;
    } else if ((data == midi_clock) && (play_flag == 1)) {
      Sync();
    }
    */
    
    if (data == midi_clock) {
      Serial.println("Clock tick");
    }
    

  }

}

// void Sync() {
  // do something for every MIDI Clock pulse when the sequencer is running
  // Serial.println("XXX");
// }







/*

  int incomingByte = 0;

  void setup() {

  Serial.begin(31250); // opens serial port, sets data rate to 9600 bps

  }

  void loop() {

  if (Serial.available() > 0) {

    incomingByte = Serial.read(); // read the incoming byte:

    Serial.print(" I received:");

    Serial.println(incomingByte);

  }

  }

*/
