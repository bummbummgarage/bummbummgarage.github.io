
// ShiftRegister74HC595 Library
// Docs: https://timodenk.com/blog/shift-register-arduino-library/
#include <ShiftRegister74HC595.h>

/*
  const int numberOfShiftRegisters = 1; // number of shift registers attached in series
  int serialDataPin = 12; // DS
  int latchPin = 11; // STCP
  int clockPin = 8; // SHCP
  ShiftRegister74HC595<numberOfShiftRegisters> sr(serialDataPin, clockPin, latchPin);
*/

const int ledMatrixRowsShiftRegisters = 1; // number of shift registers attached in series
const int ledMatrixRowsDataPin = 12; // DS
const int ledMatrixRowsLatchPin = 11; // STCP
const int ledMatrixRowsClockPin = 8; // SHCP
ShiftRegister74HC595<ledMatrixRowsShiftRegisters> ledMatrixRows(ledMatrixRowsDataPin, ledMatrixRowsClockPin, ledMatrixRowsLatchPin);


const int ledMatrixColsShiftRegisters = 1; // number of shift registers attached in series
int ledMatrixColsDataPin = 7; // DS
int ledMatrixColsLatchPin = 4; // STCP
int ledMatrixColsClockPin = 3; // SHCP
ShiftRegister74HC595<ledMatrixColsShiftRegisters> ledMatrixCols(ledMatrixColsDataPin, ledMatrixColsClockPin, ledMatrixColsLatchPin);



void setup() {
  // put your setup code here, to run once:

  
}

void loop() {

uint8_t pinValues[2];

  ledMatrixRows.setAllLow();
  ledMatrixCols.setAllHigh();

  ledMatrixRows.set(0, HIGH);
  ledMatrixCols.set(0, LOW);

  ledMatrixRows.setAllLow();
  ledMatrixCols.setAllHigh();

  ledMatrixRows.set(1, HIGH);
  ledMatrixCols.set(1, LOW);

  ledMatrixRows.setAllLow();
  ledMatrixCols.setAllHigh();

  ledMatrixRows.set(2, HIGH);
  ledMatrixCols.set(2, LOW);

  ledMatrixRows.setAllLow();
  ledMatrixCols.setAllHigh();

  ledMatrixRows.set(3, HIGH);
  ledMatrixCols.set(3, LOW);

  ledMatrixRows.setAllLow();
  ledMatrixCols.setAllHigh();

  ledMatrixRows.set(1, HIGH);
  ledMatrixCols.set(0, LOW);

  ledMatrixRows.setAllLow();
  ledMatrixCols.setAllHigh();

  ledMatrixRows.set(2, HIGH);
  ledMatrixCols.set(0, LOW);

  ledMatrixRows.setAllLow();
  ledMatrixCols.setAllHigh();

  ledMatrixRows.set(3, HIGH);
  ledMatrixCols.set(0, LOW);

  ledMatrixRows.setAllLow();
  ledMatrixCols.setAllHigh();

  ledMatrixRows.set(4, HIGH);
  ledMatrixCols.set(0, LOW);

  ledMatrixRows.setAllLow();
  ledMatrixCols.setAllHigh();

  ledMatrixRows.set(5, HIGH);
  ledMatrixCols.set(0, LOW);

  ledMatrixRows.setAllLow();
  ledMatrixCols.setAllHigh();

  ledMatrixRows.set(6, HIGH);
  ledMatrixCols.set(0, LOW);

  ledMatrixRows.setAllLow();
  ledMatrixCols.setAllHigh();

  ledMatrixRows.set(7, HIGH);
  ledMatrixCols.set(0, LOW);

  ledMatrixRows.setAllLow();
  ledMatrixCols.setAllHigh();


  /*
  pinValues[0] = { B00000001 };
  ledMatrixRows.setAll(pinValues);

  pinValues[1] = { B11111110 };
  ledMatrixCols.setAll(pinValues);

  
  pinValues[0] = { B00000010 };
  ledMatrixRows.setAll(pinValues);

  pinValues[1] = { B11111101 };
  ledMatrixCols.setAll(pinValues);
  */


}
