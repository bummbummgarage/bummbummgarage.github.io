# Sequencer II 0.1



## Solving Plan

| Question                                                  | Ansatz                                                       |
| --------------------------------------------------------- | ------------------------------------------------------------ |
| **Taugen die Features was?**                              | Kits zusammen bauen (mit Labels) und Feedback bekommen. Zum Selbstkostenpreis. |
| Taugt das DIY Kit etwas?                                  | Kit an die Leute bringen                                     |
| Taugt das Siebdruck etwas?                                | Siebdruck-Kit bestellen und ausprobieren                     |
| (Wie) kann ich das Gerät vermarkten (Preis, Kanäle, etc)? |                                                              |



## TODOs

* **Komponenten bestellen**
  * Nanos Every (inkl Headers)
  * Switches
  * Die richtigen LEDs
  * Noch etwas?
* **Frontend bestellen**
  * Checken ob die Platzierungen passen.
  * LEDs Löcher einen halben Millimeter mehr?
  * Angebot einholen bei 
* **User Manual schreiben**

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



## Other trigger / Gate sequencer kits

* https://www.robaux.io/swt16 
* https://www.robaux.io/swt16plus
* https://www.tindie.com/products/nbirch/polygons-kit-gate-sequencer-for-eurorack-12hp/
* https://division-6.com/products/dual-mini-sequencer/
* https://schneidersladen.de/en/robaux-ll8 (no kit)



