#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define LEDPIN    6
#define SIGNALPIN A2
#define NUMPIXELS 8*8

Adafruit_NeoPixel pixels(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 20

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
}

byte frame_heart[64] = {
  0,0,1,0,0,1,0,0,
  0,1,1,1,1,1,1,0,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,0,
  0,0,1,1,1,1,1,0,
  0,0,0,1,1,1,0,0,
  0,0,0,1,1,0,0,0,
};

byte frame1[64] = {
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
};

byte frame2[64] = {
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,1,1,1,1,0,0,
  1,1,0,0,0,0,1,1,
  1,1,0,0,0,0,1,1,
  0,0,1,1,1,1,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
};

byte frame3[64] = {
  0,0,0,0,0,0,0,0,
  0,0,1,1,1,1,0,0,
  0,1,0,0,0,0,1,0,
  1,1,0,0,0,0,1,1,
  1,1,0,0,0,0,1,1,
  0,1,0,0,0,0,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,0,0,0,0,0,
};

byte frame4[64] = {
  0,0,0,1,1,0,0,0,
  0,0,1,0,0,1,0,0,
  0,1,0,0,0,0,1,0,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  0,1,0,0,0,0,1,0,
  0,0,1,0,0,1,0,0,
  0,0,0,1,1,0,0,0,
};

void loop() {
  pixels.clear();

  int s = analogRead(SIGNALPIN);
  byte (*frame)[64];

  if (s<400) {
    frame = &frame1;
  } else if (s<600) {
    frame = &frame2;
  } else if (s<800) {
    frame = &frame3;
  } else {
    frame = &frame4;
  }

  for(int i=0; i<NUMPIXELS; i++) {
    if ((*frame)[i] == 1) {
      pixels.setPixelColor(i, pixels.Color(138, 43, 226));
    } else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
  }
  pixels.show();
  delay(DELAYVAL);
}
