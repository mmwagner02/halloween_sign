#include <FastLED.h>

const int DATA_PIN = 2;
const CRGB ORANGE = CRGB(237,109,0);
const CRGB OFF = CRGB(0,0,0);

void empty(CRGB* wire, int count) {
  for (int i = 0; i < count; i++) {
    wire[i] = OFF;
  }
}
void fill(CRGB* wire, int count)  {
  for (int i = 0; i < count; i++) {
    wire[i] = ORANGE;
  }
}

void fillClockwise(CRGB* wire, int step, int size) {
    if (step > size) return;
    wire[step] = ORANGE;
}
void fillFromTop(CRGB* wire, int step, int size) {
  if (step > size) return;
  if (step % 2) wire[step/2] = ORANGE;
  else wire[size-((step-1)/2)] = ORANGE;
}
void snakeClockwise(CRGB* wire, int step, int size) {
  if (step > size) return;
  if (step >= 10) wire[step - 10] = OFF;
  wire[step] = ORANGE;
}

typedef void(*fillerFunc)(CRGB*, int, int);
fillerFunc fillers[] = {&fillFromTop, &fillClockwise, &snakeClockwise};
const int numFillers = 3;

CRGB ALL_LEDS[240];
CRGB *B = ALL_LEDS;
CRGB *FIRST_O = ALL_LEDS + 120;
CRGB *SECOND_O = ALL_LEDS + 180;

void setup() {
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(ALL_LEDS, 240);
    pinMode(LED_BUILTIN, OUTPUT);
}
void loop() {
  empty(ALL_LEDS,240);
  fillerFunc filler = fillers[random(numFillers)];
  for (int step = 0; step < 60; step++) {
    filler(B,        step*2,   120);
    filler(B,        step*2+1, 120);
    filler(FIRST_O,  step, 60);
    filler(SECOND_O, step, 60);
    FastLED.show();
    delay(50);
  }
  fill (ALL_LEDS,240);FastLED.show();delay(500);
  empty(ALL_LEDS,240);FastLED.show();delay(100);
  fill (ALL_LEDS,240);FastLED.show();delay(500);
  delay(500);
}
