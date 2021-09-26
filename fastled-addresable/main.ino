#include  "FastLED.h"
#define NUM_LEDS 150
CRGB leds[NUM_LEDS];
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  FastLED.addLeds<NEOPIXEL, 19>(leds, NUM_LEDS); 
}

// the loop function runs over and over again forever
void loop() {
    for(int i = 0;i<NUM_LEDS;i++){
	leds[i] = CRGB::White; FastLED.show(); delay(10);
	leds[i] = CRGB::Black; FastLED.show(); delay(10);        
    }

                      
}

