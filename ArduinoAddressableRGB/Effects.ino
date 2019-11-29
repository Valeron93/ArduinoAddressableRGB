//Effects list
//Don't forget to add new void to pattern list
void rainbow() {
  fill_rainbow(leds, NUM_LEDS, rainbowHue, 5);
}

void white()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    fadeTowardColor(leds[i], CRGB::White, 15);
  }
}

void black()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    fadeTowardColor(leds[i], CRGB::Black, 15);
  }
}
void solid() {
  CRGB color = CRGB(r, g, b);
  for (int i = 0; i < NUM_LEDS; i++) {
    fadeTowardColor(leds[i], color, 15);
  }
}

void colorWheel() {
    for (int i = 0; i < NUM_LEDS; i++) {
    fadeTowardColor(leds[i], CHSV(colorWheelHue,255,255), 15);
  }
}

void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
 
  delay(ReturnDelay);
}

void cylon() {
  CylonBounce(r, g, b, 4, 10, 50);
}
