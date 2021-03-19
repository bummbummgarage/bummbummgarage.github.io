Standalone VCO that I pulled together for my drum machine project.

FEATURES
✅ Square, triangle and sine wave
✅ Variable frequency range (30 Hz to 13 kHz)
✅ CV input with variable attenuation
✅ Variable DC

Swipe to see a demo, the schematic and stripboard layout.

Still being a newbie (especially to soldering), I went through the lowest lows making this work eventually. Learned a lot about testing and troubleshooting. So here are my careful…

ASSEMBLY NOTES

1. Assemble the *Power Supply* circuit.
2. Plug in **DC (max. 15 V)**.
3. Adjust the rails to a similar level (e.g. -12 V and +12 V) with a **multimeter**. This is necessary because the two diodes consume part of the negative voltage.
4. Assemble the *Input Adjust* and the *VCO* circuit.
5. Turn the *Tune Poti* (RV4) to full throttle.
6. Check the rails and adjust if needed.
7. Use the *Symmetry Trimmer* (RV5) to make the square wave symmetrical on the **oscilloscope**.
8. Assemble the *Waveshaper* circuit.
9. Check the rails and adjust if needed.
10. Make the triangle wave linger perfectly around 0V using the *Offset Trimmer* (RV6).
11. Use the *Sine Round Trimmer* (RV7) and *Sine Symmetry Trimmer* (RV8) to form a pretty sine wave.

NEXT STEPS

The only drop of bitterness is a slight whining that you can hear in the lower frequencies of the trangle and sine wave. There are good indications that this is related to the 555 timer in the power supply circuit. So one of the next things for me will be to build a stable external power supply unit (PSU) and have this VCO and the other modules powered with it.

#synthdiy #diysynth #sdiy #diymodularsynth #diysynthesizer #diyelectronics