
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 12
#define NUMPIXELS 32

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500

const int pixelBrightness = 255;

const int lightsPixels[8][4] = {
  { 0, 1, 2, 3 },
  { 4, 5, 6, 7 },
  { 8, 9, 10, 11 },
  { 12, 13, 14, 15 },
  { 16, 17, 18, 19 },
  { 20, 21, 22, 23 },
  { 24, 25, 26, 27},
  { 28, 29, 30, 31}
};
const int lightsRGB[8][3] = {
  { 255, 0, 0},
  { 255, 0, 255 },
  { 255, 0, 0 },
  { 255, 0, 255 },
  { 255, 0, 0 },
  { 0, 0, 255},
  { 255, 0, 0 },
  { 255, 0, 0 }
};
const int lightsDurations[8] {
  5000,
  55000,
  34000,
  21000,
  8000,
  13000,
  89000,
  11000
};


/*
  const int lightAPixels = { 0, 8, 16, 24 };
  const int lightAColor ="" ;
*/

void setup() {

  Serial.begin(9600); // Initialize serial communication at 9600 bits per second.

  // Adafruit Pixels
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pixels.setBrightness(pixelBrightness);

}

void loop() {

  pixels.clear(); // All pixels off at the beginning of the loop.

    // Walking through the lights (rows).
    for (int r = 0; r <= 7; r++) {

      // Walking through the particular pixels.
      for (int p = 0; p <= 3; p++) {

        // Getting the brightness.
        float values[3];
        int modulo ;
        if ( millis() < lightsDurations[r] ) {
          modulo = millis();
        } else {
          modulo = millis() % lightsDurations[r];
        }

        // Arduino LED Breathing with Gauss bells: https://makersportal.com/blog/2020/3/27/simple-breathing-led-in-arduino
        float gamma = 0.16; // affects the width of peak (more or less darkness), don't change much for an effect.
        float beta = 0.5; // shifts the gaussian to be symmetric

        // Walking through the RGB channels.
        for (int c = 0; c <= 2; c++) {

          values[c] = (float)lightsRGB[r][c] * ( exp( -( pow( ( ( (float)modulo / (float)lightsDurations[r] ) - beta ) / gamma, 2.0 ) ) / 2.0 ) );

        }

        pixels.setPixelColor( lightsPixels[r][p] , pixels.Color( values[0] , values[1] , values[2] ));

      }

    }

  pixels.show();

}
