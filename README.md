# ArduinoAddressableRGB

ArduinoAddressableRGB - is a sketch for Arduino/Genuino Development Board for controlling WS2812/WS2812B LED strips.

## Setting up and wiring 


## Serial Communication:
### Changing effects:


## Implementing your own effects:
* Add method with your effect to the end of code.
* Modify pattern list this way:
```
PatternList patterns = {black, white, rainbow, solid};
```
to
```
PatternList patterns = {black, white, rainbow, solid, yourEffectName};
```
#


## Special Thanks
* [FastLED Library](https://github.com/FastLED/FastLED)
* [bherrchen](https://github.com/bherrchen/WS2812-CaseLedstripControl) - for some good ideas
