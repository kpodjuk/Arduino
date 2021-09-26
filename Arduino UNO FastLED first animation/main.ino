#include "FastLED.h"
#include <time.h>
#include <stdlib.h>



#define NUM_LEDS 150
#define DELAY 150
#define DATA_PIN 5

CRGB leds[NUM_LEDS];

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  FastLED.addLeds<WS2813, 5, GRB>(leds, NUM_LEDS); 
//   srand(time(NULL));
    Serial.begin(9600); // open the serial port at 9600 bps:
    Serial.print("Hello world\n");
    delay(1000);
}

// the loop function runs over and over again forever
void loop() {
    // for(int i = 0;i<NUM_LEDS;i++){
	// // leds[i] = CRGB::Blue; FastLED.show(); delay(DELAY);
    // // leds[i].red = randomColor();
    // // leds[i].green = randomColor();
    // // leds[i].blue = randomColor();    
    // leds[i] = CRGB::White;
    // Serial.print("Hello world xd\n");
    // FastLED.show();
    // delay(DELAY);
    // }


    for(int i = 0; i <NUM_LEDS; i++){
        leds[i] =  CRGB::Blue;
    }

                      
}


// uint8_t randomColor(){
//     uint8_t randomColorPart = rand() % 255 + 0;

//     return randomColorPart;
// }

