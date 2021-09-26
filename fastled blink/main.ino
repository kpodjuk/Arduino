#include "FastLED.h"
#include <time.h>
#include <stdlib.h>



#define NUM_LEDS 150
#define DELAY 150
#define DATA_PIN 4



CRGB leds[NUM_LEDS];

void setup() {

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 


}

// the loop function runs over and over again forever
void loop() {
    for(int i = 0;i<NUM_LEDS;i++){

    leds[i] = CRGB::White;
    FastLED.show();
    // Serial.print("loop executed xd\n");
    delay(DELAY);
    }

                      
}


// uint8_t randomColor(){
//     uint8_t randomColorPart = rand() % 255 + 0;

//     return randomColorPart;
// }

