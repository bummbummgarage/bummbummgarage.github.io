# Power Supply

## Sicherungen

Basierend auf den Empfehlungen in https://www.reddit.com/r/askanelectrician/comments/ioqgi9/diy_power_supply_improvements/

### Sicherung für das Netzteil

* https://www.instructables.com/id/Eurorack-Modular-Synth-Base/ --> "Schurter 4304.6053"
* https://www.sps-forum.de/schaltschrankbau/90501-netzteil-wie-absichern.html --> "Man schaut ins Datenblatt/Handbuch des Netzteiles, da steht das drin ... also i.d.R sowas wie empfohlene / mindest / maximale Absicherung" --> Nix drin
* https://www.muffwiggler.com/forum/viewtopic.php?p=3079413#p3079413 --> "Only in deciding what type of fuse to use in the inlet. You need a **2A or 3A slow blow fuse** that can stand a higher current for a short time, i.e. it will warm up, but not melt."
* Leute fragen
  * ✅ https://www.muffwiggler.com/forum/viewtopic.php?f=17&t=235871&p=3328151&hilit=rt+65b#p3328151 --> Den mal fragen (Randy).
  * ✅ https://www.muffwiggler.com/forum/viewtopic.php?p=3328404#p3328404 --> der hat's auch.
  * ✅ https://www.muffwiggler.com/forum/viewtopic.php?p=3327413#p3327413 --> der hat's auch.

### Sicherungen für die Rails

## Howto

* MW RT-65B als Eurorack PSU
  * https://www.muffwiggler.com/forum/viewtopic.php?t=218742
  * https://www.reddit.com/r/synthdiy/comments/gj2qua/mean_well_rt65b_power_supply_for_a_eurorack_case/
  * https://www.youtube.com/watch?v=YGxOQuP4s1o&feature=youtu.be
* Verkabelung
  * Welche **Farben** für welche Kabel?: https://www.allaboutcircuits.com/textbook/reference/chpt-2/wiring-color-codes
    * Gelb-grün, blau, braun
* Kaltgerätebuchse verkabeln: http://bilder.hifi-forum.de/max/26833/schalter_235590.jpg

## Material

* Labor Bananenstecker Buchsen für vorne (4mm)
  * Rot (+12V): https://www.reichelt.de/bananenbuchse-4mm-vollisoliert-rot-bb-4-rt-bd-p184347.html
  * Schwarz (GND): https://www.reichelt.de/bananenbuchse-4mm-vollisoliert-schwarz-bb-4-sw-bd-p184348.html
  * Grün (-12V): https://www.reichelt.de/bananenbuchse-4mm-vollisoliert-gruen-bb-4-gn-p4895.html
* Bananenstecker mit Kabelklemmen (Cage Clamp)
  * Rot: https://www.reichelt.de/bananenstecker-4-mm-cage-clamp-rot-wago-215-212-p100779.html
  * Schwarz: https://www.reichelt.de/bananenstecker-4-mm-cage-clamp-schwarz-wago-215-311-p100780.html
  * Grün: https://www.reichelt.de/bananenstecker-4-mm-cage-clamp-gruen-wago-215-411-p100781.html
* Kupferlitze (stranded) für die Verteilung auf die Module dann
  * Rot: https://www.reichelt.de/kupferlitze-isoliert-10-m-1-x-0-14-mm-rot-litze-rt-p10297.html
  * Schwarz: https://www.reichelt.de/kupferlitze-isoliert-10-m-1-x-0-14-mm-schwarz-litze-sw-p10298.html
  * Grün: https://www.reichelt.de/kupferlitze-isoliert-10-m-1-x-0-14-mm-gruen-litze-gn-p10296.html
* Kaltgerätekabel: https://www.reichelt.de/netzkabel-schutzkontaktstecker-ger-1-5-m-schw-c13-nksk-150-sw-gg-p139464.html
* Kaltgerätestecker Buchse mit Schalter: https://www.reichelt.de/kaltgeraeteeinbaustecker-mit-schalter-10-a-4-8-mm-faston-rnd-465-00787-p254051.html
* Schaltnetzteil: https://www.reichelt.de/schaltnetzteil-geschlossen-65-w-5-12-12-v-5-2-8-0-5-a-mw-rt-65b-p147885.html
* Verteilerklemmen: Bei **Toom** kaufen (Wago)
* Kabel (für innen)
  * Kabelschuhe: https://**toom**.de/s/kabelschuhe
  * Flachsteckhülsen (inkl Schutzhüllen)
  * Kabel: Bei **toom** kaufen
* Case: Bei **Toom** kaufen, zweimal das grüne (Nutzmaße: 101x155x42) mit **Gewindestangen** und Spacern dann zusammen schrauben.

## Reddit Post

Hi guys, I built this Power Supply Unit (see pictures below) to run a bunch of synthesizer modules. It's based on a Meanwell RT-65B AC-DC power supply and it will use its +12V, -12V and GND which are available at the front via cable clamps in banana plugs. I built it by the recommendations found in https://www.muffwiggler.com/forum/viewtopic.php?p=3081619&sid=67d6d70b0a2a073c04ad6ded654066a2#p3081619 and added two LEDs at the front to indicate the power supply. So far everything runs as expected (I checked the voltage at the AC and DC connections) and there's no open fire :)

My **questions** are:

1. Is there something that I should **improve in terms of safety** (a.k.a. "how will it kill me")?
2. Can I add something to **prevent severe damage when I shorten the +12V/-12V/GND rails** at some point by mistake (always try to prevent this happening at all, but I guess it's likely) or shouldn't this be a problem?

I thank you in advance!

