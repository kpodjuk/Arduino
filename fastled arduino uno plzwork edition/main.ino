#include <FastLED.h>


#define NUM_LEDS 150

#define DATA_PIN 6

// #define CLOCK_PIN 6

CRGB leds[NUM_LEDS];

void setup(){
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    pinMode(LED_BUILTIN, OUTPUT);
}


void loop(){
    leds[0] = CRGB::White;
    leds[2] = CRGB::White;
    leds[3] = CRGB::White;
    leds[4] = CRGB::White;
    leds[5] = CRGB::White;
    leds[6] = CRGB::White;
    FastLED.show();
    delay(30);


    // delay(500);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(500);
    // digitalWrite(LED_BUILTIN, LOW);

}


