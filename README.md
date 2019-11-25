<a href="arduino.cc"><img width=153 height=65 src="https://www.arduino.cc/en/uploads/Trademark/ArduinoCommunityLogo.png"></a>
# ArduinoAddressableRGB

ArduinoAddressableRGB - is a sketch for Arduino/Genuino Development Board for controlling WS2812/WS2812B LED strips.

## Warning
Don't connect an Arduino board to your PC without connecting powerful power supply to the strip. It will damage your Arduino board and motherboard! You can calculate power consumption: 60 mA per LED (max bright).


## Setting up and wiring 
* Arduino's Digital Pin (do not use RX and TX pins) -> LED strip's DIN
* +5V Power Supply -> LED's +5V & Arduino's +5V
* GND Power Supply -> LED's GND & Arduino's GND
* Change NUM_LEDS in sketch to amount of LEDs connected
* Change LED_PIN to pin where LED is connected



## Serial Commands:

* SETRGB<strong>r,g,b</strong> - Solid color in RGB
* 0 - Turn off
* 1 - White
* 2 - Rainbow
* 4 - Color Wheel

* SETBRIGHTNESS<strong>n</strong> (where n is amount 0-255) - change master brightness
* SAVE - save all settings to EEPROM
* ?MODE - print current pattern number
* ?RGB - print current color from EEPROM

## Implementing your own effects:
* Add method with your effect to 'Effects.ino' file.
* Modify pattern list this way:
```c++
PatternList patterns = {black, white, rainbow, solid, colorWheel};
```
to
```c++
PatternList patterns = {black, white, rainbow, solid, colorWheel, yourEffect};
```
#


## Special Thanks
* [FastLED Library](https://github.com/FastLED/FastLED)
* [kriegsman](https://github.com/kriegsman) - for his [fadeTowardColor.ino](https://gist.github.com/kriegsman/d0a5ed3c8f38c64adcb4837dafb6e690
