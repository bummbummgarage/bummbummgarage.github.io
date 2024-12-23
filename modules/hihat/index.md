---
layout: module
title: Hihat
description: Hihat module that I built for my modular synth drum machine project.
image: /modules/hihat/Bumm-Bumm-Garage-Hihat-Rev2.jpg
---

## Hihat

*September 2021*

![Bumm-Bumm-Garage-Hihat-Rev3](/modules/hihat/Bumm-Bumm-Garage-Hihat-Rev2.jpg)

I wanted a compact hihat module for my techno rack with a combined output for the closed and open hihat. I orientated myself mainly on the circuits of the 808. 

The development on the breadboard took relatively long, but was successful. Unfortunately the sound and the behavior on the first PCB prototype was not so satisfying. 

All in all, this was my most complex module up to that point. It will remain my nemesis.

## Details

**Panel and control board bottom:**

![Bumm-Bumm-Garage-Hihat-Rev3](/modules/hihat/Rev2/Bumm-Bumm-Garage-Hihat-Rev2-Panel-Control-Board.jpg)

**Main board top and bottom:**

![Bumm-Bumm-Garage-Hihat-Rev3](/modules/hihat/Rev2/Bumm-Bumm-Garage-Hihat-Rev2-Main-Board.jpg)

**Noise board top and bottom:**

![Bumm-Bumm-Garage-Hihat-Rev3](/modules/hihat/Rev2/Bumm-Bumm-Garage-Hihat-Rev2-Noise-Board.jpg)

## Features

* ✅ **Combined output** for the closed (CH) and open hihat (OH).
* ✅ **Kill switch**: CH overwrites the OH
* ✅ **Accent CV IN** with attenuation
* ✅ **Variable mix** of metallic crash and noise sound
* ✅ **Separate noise output** of metallic crash and noise sound
* ✅ **Envelopes output** of the CH and OH

## Ressources

**Revision 1 (breadboard prototype)**

- [Video snapshots from testing](https://www.youtube.com/watch?v=UXNZ4XKT65U)
- [Schematic (PDF)](/modules/hihat/Rev1/Bumm-Bumm-Garage-Hihat-Rev1-Schematic.pdf)

**Revision 2 (3 piece PCB)**

* [Schematic (PDF)](/modules/hihat/Rev2/Bumm-Bumm-Garage-Hihat-Rev2-Schematic.pdf)
* [Schematic, Panel, PCBs (EasyEDA)](/modules/hihat/Rev2/Bumm-Bumm-Garage-Hihat-Rev2-EasyEDA.zip)

**References**

* [Logic Noise: More CMOS Cowbell!](https://hackaday.com/2015/04/10/logic-noise-more-cmos-cowbell/)
* [TR-808 hihats project (PDF)](http://www.ericarcher.net/wp-content/uploads/2014/07/tr-808-hihat-diy-project-revised-dec-2009.pdf)
* [R-Envelope Generator](http://www.analog-synth.de/synths/mod2/trigdiv/trigdiv.htm)
* [Attack Release EG](http://www.synthdiy.com/show/?id=1134)

## Improvement Potential

**Revision 2**

* PCB: Thonkiconn footprint is twisted (I tweaked it for the first implementation).
* Soldered module: Noise regulator does not really work as intended: Cannot minimize as it should.
* Soldered module: Metallic sound doesn't sound as nice as in the breadboard prototypes.

