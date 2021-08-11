---
layout: module
title: Case II 0.1
---

<!-- image: modules/case-ii-0.1/Bumm-Bumm-Garage-Case-II-0.1-01.jpg
description: 19 inch Eurorack case that I built for my modular synth drum machine project. -->

# Chord Organ

*Version 0.1 from August 2021*

<!-- BILD --> 

Prototype for a polyphonic synth lead. I build it while having some slack time, waiting for new DIY kits for my techno rack project. I got inspired by the [Chord Organ from Music Thing Modular](https://musicthing.co.uk/pages/chord.html). 

## Features

* ✅ 4 simultaneous voices (polyphony)
* ✅ 5 different waveforms: sine, triangle, square, saw, tuned noise
* ✅ 13 different chord shapes
* ✅ 48 semitones (from C-2 to C+2)
* ✅ CV IN for the root note of the chord

## Details

It is based on an Arduino Nano. Luckily I found the library [the_synth](https://github.com/dzlonline/the_synth). That made the implementation with some additional circuitry a relatively easy task.

![chord-shapes](chord-shapes.png)

The logic and design of the chord shapes are taken from the [Music Thing Modular's approach](https://youtu.be/btCs3EEpJm0?t=104). They can be edited in the sketch file.

## Links

<!-- Video Demo
Schematic (PDF)
Arduino Sketch (Code)-->

* Arduino Sketch (Code)



**TODO:**

* Die Akkorde noch mal überprüfen. Wie im Original und richtig?
* Amp hinten hin.



----



* Das Original:
  * Demo: https://www.youtube.com/watch?v=btCs3EEpJm0
  * Artikel: https://medium.com/music-thing-modular-notes/chord-organ-the-easiest-way-to-get-simple-chords-from-a-modular-synth-2f48684fdb9a
  * Repo: https://github.com/TomWhitwell/Chord-Organ/blob/master/Chord-Organ/README.md
  * https://www.thonk.co.uk/shop/chordorgan/



Radio Music Project Page: https://github.com/TomWhitwell/RadioMusic/wiki



Waves auf Arduino:

* Wavetables:
  * https://www.instructables.com/Turn-your-Arduino-into-a-4-voice-wavetable-synth-w/ and https://github.com/dzlonline/the_synth
    * Erklärung dafür: https://www.youtube.com/watch?v=9OtRh3_pn68
* Emulate:
  * Inder: https://www.youtube.com/watch?v=RpNqkMF8vHM
  * Der Deutsche: https://create.arduino.cc/projecthub/michalin70/arduino-as-waveform-synthesizer-for-music-2aa48f - Geht auf Nano Every?
  * https://www.instructables.com/Arduino-Waveform-Generator-1/
  * Lib: https://github.com/hoilett/Waveforms
  * Built in: https://www.arduino.cc/reference/de/language/functions/advanced-io/tone/ Nur auf einem PIN möglich

