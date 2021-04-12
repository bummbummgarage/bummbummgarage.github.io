# TODOs

* Schematic bauen.
* Frontend gestalten und bestellen.
* PCB bauen und bestellen.
* Was ist nun mit Minus Voltage am Input? Hält die Diode das ab --> ggf mal ohne Pin Anschluss messen.
* Random Patterns mit rein programmieren :)
* Gibt es weitere Fav Zener Dioiden neben der benutzten 1N4733A?



## Fragen

| Frage                                                        | Antwort                               |
| ------------------------------------------------------------ | ------------------------------------- |
| Trigger mit Oscilloscope testen                              | 4 V circa.                            |
| Funktioneren die Output Jacks auch geerdet, wenn nicht angeschlossen? | Ja, alles gut --> Erden am Switch Pin |
|                                                              |                                       |



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
| 3    | PWM~      | -                     | Matrix Cols: Track 3     |
| 4    | Digital   | -                     | Matrix Cols: Track 2     |
| 5    | PWM~      | -                     | Matrix Cols: Track 1     |
| 6    | PWM~      | tracksOutputPin       |                          |
| 7    | Digital   | -                     | Matrix Cols: Steps       |
| 8    | Digital   | -                     | Shift Register Rows SHCP |
| 9    | PWM~      | tracksOutputPin       |                          |
| 10   | PWM~      | tracksOutputPin       |                          |
| 11   | Digital   | -                     | Shift Register Rows STCP |
| 12   | Digital   | Adafruit_NeoPixel     | Shift Register Rows DS   |
|      |           |                       |                          |
|      |           |                       |                          |
|      |           |                       |                          |

