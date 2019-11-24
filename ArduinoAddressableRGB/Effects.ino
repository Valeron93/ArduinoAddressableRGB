//Effects list
//Don't forget to add new void to pattern list
void rainbow() {
  fill_rainbow(leds, NUM_LEDS, gHue, 5);
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
