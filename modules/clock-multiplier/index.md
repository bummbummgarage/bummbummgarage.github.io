---
layout: module
title: Clock Multiplier
image: /modules/clock-multiplier/Rev1/Bumm-Bumm-Garage-Clock-Multiplier-Rev1-Breadboard.jpg
Description: Clock multiplier that I built for my techno rack to play non-linear accented triplets, quintuplets or septuplets.
---

# Clock Multiplier

![](Rev1/Bumm-Bumm-Garage-Clock-Multiplier-Rev1-Breadboard.jpg)

I've heard, especially with Lady Starlight, that techno tracks get more interesting when the bassline hits in triplets (3 beats), quintuplets (5 beats) or septuplets (7 beats). In contrast, the songs from my techno rack have always been relatively linear in this respect. That's why I build this Clock Multiplier. The main inspiration is Befaco's Burst, from which I took the terminology for quantity and distribution.

In the first step I implement the idea with an Arduino as a prototype, so I can quickly test the handling and features on the rack.

As a follow-up version, I'm building it around an ATMega, i.e. without a pre-built Arduino, making it much cheaper and space-saving.

## Features

* ✅ **Variable quantity** of beats (1–8)
* ✅ **Variable beat distribution** (11 gradations)
* ✅ **Quantity CV** input with attenuation
* ✅ **Muting button** for the output triggers
* ✅ **Overvoltage protection** on both inputs

## Specifications

**Parameters (quantity and distribution):**

![](Bumm-Bumm-Garage-Clock-Multiplier-Parameters.png)

## Resources

**Revision 1 (Arduino on breadboard)**

* [Video snapshots from testing](https://www.youtube.com/watch?v=SXv_L24jIZk)
* [Schematics (PDF)](Rev1/Bumm-Bumm-Garage-Clock-Multiplier-Rev1-Schematic.pdf)
* [Arduino Sketch (Code)](https://github.com/bummbummgarage/bummbummgarage.github.io/blob/main/modules/clock-multiplier/Rev1/clock-multiplier/clock-multiplier.ino)
* Showcase and feedback on [Instagram](https://www.instagram.com/p/CZ1NLhLM4i7/) and [Reddit](https://www.reddit.com/r/synthdiy/comments/spvbwu/clock_multiplier_with_variable_trigger/)
* Improvement potential: Opamp buffer at the output and an ATMega 329 instead of an Arduino.

<!--

## Testing / Use cases

* from 1khz to 9khz? -> https://www.reddit.com/r/synthdiy/comments/spvbwu/comment/hwhrxm8/?utm_source=share&utm_medium=web2x&context=3 und Rückmeldung geben.

  

## TODOs

* PCB und Panel setzen
  * Beschriftung, Logos etc.
  * Panel setzen
  * Übereinander legen
* Schematic auf Git sichern
* Kram bestellen
* Reverse Polarity Protection testen, Hardcore Test.
* Use Cases finden
  * Fünftel Bass line über einen Takt
* (Startup Sequence einbauen -> Morse Code)
* Lösen: LEDs leuchten, wenn kein Trigger IN kommt. Soll nicht.

### Features:

* Offene Schnittstelle am Modul, wenn man es hacken möchte für eigene Programme.
* Mute

### ATMega Standalone

* Build an Arduino:
  * https://www.instructables.com/Build-an-Arduino/
  * https://www.instructables.com/Build-Your-Own-Arduino/
  * https://duckduckgo.com/?q=build+an+arduino&ia=web
* Arduino Uno to ATmega328 - Shrinking your Arduino Projects: https://www.youtube.com/watch?v=Sww1mek5rHU

## Resources

* **Wolles How-To**  (https://wolles-elektronikkiste.de/atmega328p-standalone-betreiben#Anker3, shorted, and done with AVR Pocket Programmer and an ATMega328P-PU):
  * Choose "Tools > Board > Arduino Uno"
  * Choose "Tools > Programmer > USBtinyISP"
  * Click "Tools > Programmer > Burn Bootloader"
  * Upload sketch via "Sketch > Upload Using Programmer"
* **ATMega Digital and Analog Pins**: https://www.componentsinfo.com/atmega328p-pinout-configuration-datasheet/
* **Overvoltage Protection:**
  * https://forum.arduino.cc/t/12v-to-arduino-pin-zener-diode/529876/2#msg3759664

## Fragen

* Wie bekomme ich den ISP Programmer drauf (dann mit Strom oder ohne)?
  * ISP and power supply
* Welche Decoupling Caps für den ATMega mit dem uA7805?

-->
