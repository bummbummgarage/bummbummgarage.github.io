/* --------------------------------------------------------------------------

    $$$$$$$\  $$\   $$\ $$\      $$\ $$\      $$\               
    $$  __$$\ $$ |  $$ |$$$\    $$$ |$$$\    $$$ |              
    $$ |  $$ |$$ |  $$ |$$$$\  $$$$ |$$$$\  $$$$ |              
    $$$$$$$\ |$$ |  $$ |$$\$$\$$ $$ |$$\$$\$$ $$ |              
    $$  __$$\ $$ |  $$ |$$ \$$$  $$ |$$ \$$$  $$ |              
    $$ |  $$ |$$ |  $$ |$$ |\$  /$$ |$$ |\$  /$$ |              
    $$$$$$$  |\$$$$$$  |$$ | \_/ $$ |$$ | \_/ $$ |              
    \_______/  \______/ \__|     \__|\__|     \__|                    
                                                                
    $$$$$$$\  $$\   $$\ $$\      $$\ $$\      $$\               
    $$  __$$\ $$ |  $$ |$$$\    $$$ |$$$\    $$$ |              
    $$ |  $$ |$$ |  $$ |$$$$\  $$$$ |$$$$\  $$$$ |              
    $$$$$$$\ |$$ |  $$ |$$\$$\$$ $$ |$$\$$\$$ $$ |              
    $$  __$$\ $$ |  $$ |$$ \$$$  $$ |$$ \$$$  $$ |              
    $$ |  $$ |$$ |  $$ |$$ |\$  /$$ |$$ |\$  /$$ |              
    $$$$$$$  |\$$$$$$  |$$ | \_/ $$ |$$ | \_/ $$ |              
    \_______/  \______/ \__|     \__|\__|     \__|                      
                                                                
     $$$$$$\   $$$$$$\  $$$$$$$\   $$$$$$\   $$$$$$\  $$$$$$$$\ 
    $$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ $$  _____|
    $$ /  \__|$$ /  $$ |$$ |  $$ |$$ /  $$ |$$ /  \__|$$ |      
    $$ |$$$$\ $$$$$$$$ |$$$$$$$  |$$$$$$$$ |$$ |$$$$\ $$$$$\    
    $$ |\_$$ |$$  __$$ |$$  __$$< $$  __$$ |$$ |\_$$ |$$  __|   
    $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |      
    \$$$$$$  |$$ |  $$ |$$ |  $$ |$$ |  $$ |\$$$$$$  |$$$$$$$$\ 
     \______/ \__|  \__|\__|  \__|\__|  \__| \______/ \________|
  
    VIDEO CLIP GENERATOR
    Based on Processing (https://processing.org/)
    
    Find out more about my project on: http://www.bummbummgarage.com/
    
    License: Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
    --> https://creativecommons.org/licenses/by-sa/4.0/
    
---------------------------------------------------------------------- */
    

import processing.sound.*;
SoundFile track;
FFT fft; // Docs: https://processing.org/reference/libraries/sound/FFT.html
int bands = 8; // Define how many FFT bands to use (this needs to be a power of two)
float[] spectrum = new float[bands];
BeatDetector beatDetector; // Docs: https://github.com/processing/processing-sound/blob/master/examples/Analysis/BeatDetection/BeatDetection.pde

int bpm = 110; // The BPM of the song.
int bpmResolution = 4; // The possible images (changes) per beat.
boolean isBeat = false;

boolean recording = false; // Record clip, docs: https://www.youtube.com/watch?v=G2hI9XL6oyk

void setup() {
  
  size(720, 720);
  background(0);
  
  // Set the frame rate.
  int fr = ( bpm / 60 ) * bpmResolution;
  frameRate(fr);
  print("frameRate: " + fr + "\n");
  
  // Play the track.
  track = new SoundFile(this, "track.aif");
  track.play();
  
  // FFT
  fft = new FFT(this, bands);
  fft.input(track);
  
  // Beat Detection
  beatDetector = new BeatDetector(this);
  beatDetector.input(track);
  
  // Basic line setup.
  strokeCap(SQUARE); 
   
}

void draw() {
  
  clear();
  
  if (beatDetector.isBeat()) {
    
    isBeat = true;
    
    // The random background.
    int r = (int) random(0, 3);
    int alpha = 170;
    switch(r) {
      case 0: // Green.
        fill( 36, 146, 15, alpha );
        break;
      case 1: // Red.
        fill( 241, 63, 87, alpha ); // Line color.
        break;
      case 2: // Yellow.
        fill( 255, 246, 190, alpha ); // Line color.
        break;
    }
    strokeWeight( 0 );
    rect(0, 0, width, height); // Colored flash.
    
  } else {
    
    isBeat = false;
  }
  
  fft.analyze(spectrum);

  for(int i = 0; i < bands; i++){
    
    // See the spectrum numbers to get an idea:
    // print("spectrum["+i+"]: " + spectrum[i] + "\n");
    
    int alphaFactor = 15; // Play around.
    
    int alpha = (int) ( 255 * spectrum[i] * alphaFactor );
    
    if(isBeat) {
      alpha = 255; // Set opacity to full, because the background is colored as well.
    }
    
    if( spectrum[i] > 0.005 ){ // Threshold, play around.
      drawRandomLine( (i*i), alpha );
      // drawRandomLine( (int) (i/spectrum[i]), alpha ); // Nice alternative!
    }
    
  }
  
  if (recording) {
    saveFrame("output/clip_####.png");
  }
  
}


// Bumm Bumm Colors:
// Greeen: #24920f, rgb(36, 146, 15)
// Red: #f13f57, rgb(241, 63, 87)
// Yellow: #fff6be, rgb(255, 246, 190)

void drawRandomLine(int sw, int alpha) {
    strokeWeight( sw );
    
    // The random color of the stroke.
    int r = (int) random(0, 3);
    switch(r) {
      case 0: // Green.
        stroke( 36, 146, 15, alpha );
        break;
      case 1: // Red.
        stroke( 241, 63, 87, alpha ); // Line color.
        break;
      case 2: // Yellow.
        stroke( 255, 246, 190, alpha ); // Line color.
        break;
    }
    
    line( (int) random(0, width) , (int) random(0, height) , (int) random(0, width) , (int) random(0, height) );
}
