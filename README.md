<a href="arduino.cc"><img width=153 height=65 src="https://www.arduino.cc/en/uploads/Trademark/ArduinoCommunityLogo.png"></a>
# ArduinoAddressableRGB

ArduinoAddressableRGB - is a sketch for Arduino/Genuino Development Board for controlling WS2812/WS2812B LED strips.

## Setting up and wiring 
* LED_PIN > LED strip's DIN
* +5V Power Supply > LED's +5V & Arduino's +5V
* GND Power Supply > LED's GND & Arduino's GND



## Serial Commands:

* SETRGB<strong>r,g,b</strong> - Solid color in RGB
* 0 - Turn off
* 1 - White
* 2 - Rainbow

* SETBRIGHTNESS<strong>n</strong> (where n is amount 0-255) - change master brightness
* SAVE - save all settings to EEPROM
* ?MODE - print current pattern number
* ?RGB - print current color from EEPROM

## Implementing your own effects:
* Add method with your effect to 'Effects.ino' file.
* Modify pattern list this way:
```c++
PatternList patterns = {black, white, rainbow, solid};
```
to
```c++
PatternList patterns = {black, white, rainbow, solid, newEffect};
```
#


## Special Thanks
* [FastLED Library](https://github.com/FastLED/FastLED)
