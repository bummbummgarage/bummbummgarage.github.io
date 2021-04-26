int latchPin = 7;  // RCLK (Register Clock / Latch) Pin des 74HC595 ist verbunden mit dem digitalen Pin 5
int clockPin = 8; // SRCLK (Shit Register Clock) Pin des 74HC595 ist verbunden mit dem digitalen Pin 6
int dataPin = 6;  // SER (Serial input) Pin des 74HC595 ist verbunden mit dem digitalen Pin 4

byte leds = 0;    // Hier speichern wir den Zustand der acht LEDs

void setup() 
{
  // Alle Pins für den 74HC595 des Arduino auf OUTPUT (=Ausgang) setzen
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

  // Rows
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  
}

void loop() 
{

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

/*
digitalWrite(clockPin, LOW); // 11 at shift register
digitalWrite(latchPin, LOW); // 12 at shift register
digitalWrite(dataPin, HIGH); // 14 at shift register
*/

  
    bitSet(leds, 1);    // an der Position i in der Variable leds das Bit auf 1 setzen
    updateShiftRegister();

  
  leds = 0; // Alle LEDs ausschalten
  
  updateShiftRegister();
  delay(500);
  
  for (int i = 0; i < 8; i++) // Eine LED nach der anderen einschalten
  {
    bitSet(leds, i);    // an der Position i in der Variable leds das Bit auf 1 setzen
    updateShiftRegister();
    delay(500);
  }


}

/*
 * updateShiftRegister() - Diese Funktion setzt den latchPin auf LOW und ruft dann die Arduino-Funktion "shiftOut" auf, um den Inhalt der Variablen "leds" im Schieberegister zu verschieben, bevor der latchPin wieder auf HIGH gesetzt wird.
 */
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
