# TODOs

* Bestellen
  * Nanos Every (inkl Headers)
  * Switches
  * Richtige LEDs
  * Noch etwas?
* Frontend bestellen (LEDs Löcher einen halben Millimeter mehr?)
* Random Patterns mit rein programmieren :)
* Code: Ungenutzte Pins internal pull-up und testen.
* Gibt es weitere Fav Zener Dioiden neben der benutzten 1N4733A?
* Macht der Nano die Minus Volte auch mit, wenn alles zusammen gebaut.
* Detection Pin als Input deklarieren?



## Notes

* Build Doc mit langen LEDs, siehe auch Opening phrases: http://transientmodules.com/wp-content/uploads/2021/01/7J_BUILD_DOC.pdf



## Fragen

| Frage                                                        | Antwort                                                      |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| Trigger mit Oscilloscope testen                              | 4 V circa.                                                   |
| Funktioneren die Output Jacks auch geerdet, wenn nicht angeschlossen? | Ja, alles gut --> Erden am Switch Pin                        |
| 74… decoupl Caps,                                            | Ja, 100nF siehe Datasheet                                    |
| Was ist nun mit Minus Voltage am Input? Hält die Diode das ab --> ggf mal ohne Pin Anschluss messen. | Maximum Volt ist 5.X. Mit Minus sind es -0.7 --> können die schadhaft sein? **Der Uno hats überlebt mit -12V am Input** |
| Glättens Caps für Arduino?                                   | https://forum.arduino.cc/t/decoupling-capacitors/136084/3 --> Ja, 100nF |
| Power Supply Decoupl Caps?                                   | Ja, viele Infos, Muster scheinen 10uF zu sein. Rein damit.   |
| Arduino ungenutzte Pins an GND oÄ?                           | enable the internal pull-up, https://forums.adafruit.com/viewtopic.php?f=25&t=20742#p108290 |



