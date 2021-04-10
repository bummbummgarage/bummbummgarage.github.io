# TODOs

* Auf alten Code migrieren
  * Code migrieren ohne Trig Ausgabe und ohne CV input
    * Track1 hinzügefen
      * Button
      * Code
  * Tracks: External CV Walkthrough.
* Was mit den ungenutzten pins beim Shifter?
* Zweiten ShiftRegister entfernen
* Wie geht es heller bzw konsistent in der Helligkeit?
* Matrix versorgung besser nicht über Arduino?
* Random Patterns :)





# Pins

| Pin  | Type      | Sequencer I 0.1       | NEW Sequencer II 0.1     |
| ---- | --------- | --------------------- | ------------------------ |
| A0   | Analog IN | tracksPushButtonPin   |                          |
| A1   | Analog IN | tracksPushButtonPin   |                          |
| A2   | Analog IN | tracksPushButtonPin   |                          |
| A3   | Analog IN | stepsCVInPin          |                          |
| A4   | Analog IN | stepsPushButtonPin    |                          |
| A5   | Analog IN | -                     |                          |
| A6   | Analog IN | -                     |                          |
| A7   | Analog IN | -                     |                          |
| TX   |           | -                     |                          |
| RX   |           | -                     |                          |
| 2    | Digital   | stepsJackDetectionPin |                          |
| 3    | PWM~      | -                     | Shift Register Cols SHCP |
| 4    | Digital   | -                     | Shift Register Cols STCP |
| 5    | PWM~      | -                     |                          |
| 6    | PWM~      | tracksOutputPin       |                          |
| 7    | Digital   | -                     | Shift Register Cols DS   |
| 8    | Digital   | -                     | Shift Register Rows SHCP |
| 9    | PWM~      | tracksOutputPin       |                          |
| 10   | PWM~      | tracksOutputPin       |                          |
| 11   | Digital   | -                     | Shift Register Rows STCP |
| 12   | Digital   | Adafruit_NeoPixel     | Shift Register Rows DS   |
|      |           |                       |                          |
|      |           |                       |                          |
|      |           |                       |                          |

