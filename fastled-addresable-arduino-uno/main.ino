#include  "FastLED.h"
#include <time.h>
#include <stdlib.h>



#define NUM_LEDS 150
#define DELAY 20
CRGB leds[NUM_LEDS];
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  FastLED.addLeds<NEOPIXEL, 16>(leds, NUM_LEDS); 
  srand(time(NULL));
    Serial.begin(115200); // open the serial port at 9600 bps:
    Serial.print("Hello world xd\n");
}

// the loop function runs over and over again forever
void loop() {
    for(int i = 0;i<NUM_LEDS;i++){
	// leds[i] = CRGB::Blue; FastLED.show(); delay(DELAY);
    leds[i].red = randomColor();
    leds[i].green = randomColor();
    leds[i].blue = randomColor();    
    // leds[i].red = 255;
    // leds[i].green = 255;
    // leds[i].blue = 255;
    FastLED.show();
    delay(DELAY);
    // leds[i] = CRGB::Gray; 
	// leds[i] = CRGB::Black; FastLED.show(); delay(DELAY); //black        
    }
        for(int i = 0;i<NUM_LEDS;i++){
            leds[i] = CRGB::Black;
        }
    // for(int i = NUM_LEDS; i<NUM_LEDS;i++){
	// leds[i] = CRGB::Blue; FastLED.show(); delay(DELAY);
	// // leds[i] = CRGB::Black; FastLED.show(); delay(DELAY);        //black
    // }
                      
}


uint8_t randomColor(){
    uint8_t randomColorPart = rand() % 255 + 0;
    // uint8_t randomG = rand() % 255 + 0;
    // uint8_t randomB = rand() % 255 + 0;
    // Serial.println("chuj");
    return randomColorPart;
}


// void setColor(uint8_t r,uint8_t g, uint8_t b){

// }