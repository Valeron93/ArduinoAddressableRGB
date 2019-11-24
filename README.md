# ArduinoAddressableRGB

ArduinoAddressableRGB - is a sketch for Arduino/Genuino Development Board for controlling WS2812/WS2812B LED strips.

## Setting up and wiring 
* LED_PIN > LED strip's DIN
* +5V Power Supply > LED's +5V & Arduino's +5V
* GND Power Supply > LED's GND & Arduino's GND


## Implementing your own effects:
* Add method with your effect to 'Effects.ino' file.
* Modify pattern list this way:
```
PatternList patterns = {black, white, rainbow, solid};
```
to
```
PatternList patterns = {black, white, rainbow, solid, newEffect};
```
#


## Special Thanks
* [FastLED Library](https://github.com/FastLED/FastLED)
