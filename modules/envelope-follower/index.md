# Envelope Follower

## TODOs

* Alles bestellen



## Rev 1 

**Feedback**:

* https://modwiggler.com/forum/viewtopic.php?f=17&t=256361&p=3657389
* https://www.reddit.com/r/synthdiy/comments/rbitj4/simple_envelope_follower_circuit/



## Improvement Potential

* Ideal rectifier einbauen: https://www.reddit.com/r/synthdiy/comments/rbitj4/simple_envelope_follower_circuit/hntzjwl/?context=3



## References

Peak Detection: https://www.youtube.com/watch?v=jllsqRWhjGM





## Use Cases And Tests

* 👍🏻✅ **Sidechain compressor mit Kick und Chords** – https://www.youtube.com/watch?v=lGtKlH0UeuA --> um den Drop richtig wirken zu lassen. Volume und Filter Side Chain.
* 👍🏻✅ **Sidechain from Kick on Clapping Noise (Hihats) controlling volume** – https://youtu.be/ld04GHoWDUk?t=74
* 👍🏻 🟧Mit einem **Envelope über einem Bass** mischen, der über die Kick geht. Den dann in den VCA packen --> Kann es leider noch nicht zusammenmischen. Brauch den neuen Mixer :)
* 👍🏻✅ **Bass Riff from Drum Envelope** – https://www.youtube.com/watch?v=aByLEB_AZaE (Hälfte) mit Hihats bestimmt witzig.
* 👍🏻 **Envelope from Drum Loop Modulating Pitch** – https://www.youtube.com/watch?v=XZxf5caWySw – Interessant, um die Response zu testen (Auflösung).
* 👍🏻 Envelope **Modulating Filter on Drum Loop**: https://www.youtube.com/watch?v=ld04GHoWDUk
* 👍🏻 **Guitar in controlling VCA with sequenced melody**: https://youtu.be/ld04GHoWDUk?t=150







## Post Text

Prototype of an envelope follower that I built for my DIY modular synth techno rack. My main stakes in this module are being able to side chain and create duckings on voices when the kick hits #technotechno

Swipe to see some video demos, the schematic and the panel design that I have in mind. 

What I did in the videos:

1. Muting noisy claps when the kick hits (kick's envelope on VCF).
2. Muting chords when the kick hits (kick's envelope on VCF).
3. Muting hihats when the kick hits (kick's envelope in VCA).
4. Creating bass line from drum pattern (mixed drums' envelope in VCA).

Disclaimer: The attack isn't a real attack from my perspective. Meaning it does not delay the time when the signal peak is reached. It rather smooths the entire signal like an attenuator. I decided to call it "Attack" anyways since I'll use it mainly to reduce natural pops at the beginning of an envelope. Any loss in amplitude coming from this can be compensated with the gain :)

Next steps will be designing the PCBs and the final panel design.

[#synthdiy](https://www.instagram.com/explore/tags/synthdiy/) [#diysynth](https://www.instagram.com/explore/tags/diysynth/) [#sdiy](https://www.instagram.com/explore/tags/sdiy/) [#diymodularsynth](https://www.instagram.com/explore/tags/diymodularsynth/) [#diysynthesizer](https://www.instagram.com/explore/tags/diysynthesizer/) [#diyelectronics](https://www.instagram.com/explore/tags/diyelectronics/)

----



[Simple Envelope Follower Circuit](https://www.reddit.com/r/synthdiy/comments/rbitj4/simple_envelope_follower_circuit/)



