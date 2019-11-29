
#include <EEPROM.h>
#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif
#define LED_PIN     11            //Digital pin which is connected to LED's DIN
#define NUM_LEDS    46            // Amount of leds connected

CRGB leds[NUM_LEDS];

#define BRIGHTNESS         50 // 0-255
#define FRAMES_PER_SECOND  120

String inputString = ""; //string for handling serial messages
String SerialMSG = "";
boolean stringComplete = false;
uint8_t currentPatternNumber;

uint8_t rainbowHue = 0;
uint8_t colorWheelHue = 0;

int  r = 255;
int g = 255;
int b = 255;
uint8_t brightness = BRIGHTNESS;



void setup() {
  delay(15);
  LEDS.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
  Serial.setTimeout(50);
  readMem();
  FastLED.setBrightness(brightness);
  CHSV hsv; //костыль
  CRGB rgb;
  rgb = hsv;
}

///////////////////////////////////////////////////EFFECTS LIST/////////////////////////////////////////////////////////////
typedef void (*PatternList[])();
PatternList patterns = {black, white, rainbow, solid, colorWheel, cylon};

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
    else if (SerialMSG.startsWith("SETBRIGHTNESS")) {
      SerialMSG.replace("SETBRIGHTNESS", "");
      brightness = SerialMSG.toInt();
      FastLED.setBrightness(brightness);
    }
    else if (SerialMSG.startsWith("?")) {
      if (SerialMSG.startsWith("?RGB")) {
        Serial.println(r + ',' + g + ','+ + b);
      }
      else if (SerialMSG.startsWith("?MODE")) {
        Serial.println(currentPatternNumber);
      }
    }
    else {
      currentPatternNumber = SerialMSG.toInt();
    }
  }
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);

  patterns[currentPatternNumber]();

  EVERY_N_MILLISECONDS(20) {
    rainbowHue++;
  }
  EVERY_N_MILLISECONDS(120) {
    colorWheelHue++;
  }
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
  EEPROM.put(16, brightness);
}

void readMem() {
  EEPROM.get(0, currentPatternNumber);
  EEPROM.get(10, r);
  EEPROM.get(12, g);
  EEPROM.get(14, b);
  EEPROM.get(16, brightness);
}

void nblendU8TowardU8( uint8_t& cur, const uint8_t target, uint8_t amount) {
  if (cur == target) return;

  if (cur < target) {
    uint8_t delta = target - cur;
    delta = scale8_video(delta, amount);
    cur += delta;
  } 
  else {
    uint8_t delta = cur - target;
    delta = scale8_video(delta, amount);
    cur -= delta;
  }
}
CRGB fadeTowardColor(CRGB& cur, const CRGB& target, uint8_t amount) {
  nblendU8TowardU8(cur.red, target.red, amount);
  nblendU8TowardU8(cur.green, target.green, amount);
  nblendU8TowardU8(cur.blue, target.blue, amount);
  return cur;
}
