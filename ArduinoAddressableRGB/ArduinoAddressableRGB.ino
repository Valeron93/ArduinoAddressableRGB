
#include <EEPROM.h>
#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define LED_PIN     11
#define VERSION     0.1
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    46
#define CHIPSET     WS2812
bool gReverseDirection = true;

CRGB leds[NUM_LEDS];

#define BRIGHTNESS         50 // 0-255
#define FRAMES_PER_SECOND  120

String inputString = ""; //string for handling serial messages
String SerialMSG = "";
boolean stringComplete = false;
uint8_t currentPatternNumber;
uint8_t gHue = 0;
int r = 255;
int g = 255;
int b = 255;

void setup() {
  delay(15);

  LEDS.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);

  FastLED.setBrightness(BRIGHTNESS);

  Serial.begin(9600);
  Serial.setTimeout(50);
  readMem();

  CHSV hsv; //костыль
  CRGB rgb;
  rgb = hsv;
}


typedef void (*PatternList[])();
PatternList patterns = {black, white, rainbow, solid};

void loop()
{
  if (stringComplete) {
    SerialMSG = inputString;
    inputString = "";
    stringComplete = false;
    if (SerialMSG.startsWith("SETRGB")) {
      SerialMSG.replace("SETRGB", ""); //clearing string from command
      char *temp = &SerialMSG[0u];
      sscanf(temp, "%d,%d,%d", &r, &g, &b); //parsing string
      temp = NULL; //unset temp char
      currentPatternNumber = 3;
    }
    else if (SerialMSG.startsWith("SAVE")) {
      Serial.println("Saved succesfully!");
      saveMem();
    }
    else if (SerialMSG.startsWith("?")) {
      if (SerialMSG.startsWith("?RGB")) {
        Serial.print(r);
        Serial.print(",");
        Serial.print(g);
        Serial.print(",");
        Serial.print(b);
        Serial.print("\n");
      }
      else if (SerialMSG.startsWith("?MODE")) {
        Serial.println(currentPatternNumber);
      }
    }
    else if (SerialMSG.startsWith("?VERSION")) {
      Serial.println(VERSION);
    }
    else {
      currentPatternNumber = SerialMSG.toInt();
    }
  }
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);

  patterns[currentPatternNumber]();

  EVERY_N_MILLISECONDS(20) {
    gHue++;  // slowly cycle the "base color" through the rainbow
  }
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  currentPatternNumber = (currentPatternNumber + 1) % ARRAY_SIZE(patterns);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void saveMem() {
  EEPROM.put(0, currentPatternNumber);
  EEPROM.put(10, r);
  EEPROM.put(12, g);
  EEPROM.put(14, b);
}

void readMem() {
  EEPROM.get(0, currentPatternNumber);
  EEPROM.get(10, r);
  EEPROM.get(12, g);
  EEPROM.get(14, b);
}


void rainbow() {
  fill_rainbow(leds, NUM_LEDS, gHue, 5);
}

void white()
{
  for ( int i = 0; i < NUM_LEDS; i++) {
    fadeTowardColor(leds[i], CRGB::White, 15);
  }
}

void black()
{
  for ( int i = 0; i < NUM_LEDS; i++) {
    fadeTowardColor(leds[i], CRGB::Black, 15);
  }
}
void solid() {
  CRGB color = CRGB(r, g, b);
  for ( int i = 0; i < NUM_LEDS; i++) {
    fadeTowardColor(leds[i], color, 15);
  }
}

void nblendU8TowardU8( uint8_t& cur, const uint8_t target, uint8_t amount)
{
  if ( cur == target) return;

  if ( cur < target ) {
    uint8_t delta = target - cur;
    delta = scale8_video( delta, amount);
    cur += delta;
  } else {
    uint8_t delta = cur - target;
    delta = scale8_video( delta, amount);
    cur -= delta;
  }
}
CRGB fadeTowardColor( CRGB& cur, const CRGB& target, uint8_t amount)
{
  nblendU8TowardU8( cur.red,   target.red,   amount);
  nblendU8TowardU8( cur.green, target.green, amount);
  nblendU8TowardU8( cur.blue,  target.blue,  amount);
  return cur;
}
