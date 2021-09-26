#include <Arduino.h>
#line 1 "c:\\Users\\kamil\\Documents\\Arduino\\addressable-ambibox-node-via-wifi\\addresable-amilight.ino"
#include "FastLED.h"

#define NUM_LEDS 59
#define DATA_PIN 5
#define serialRate 38400

static const uint8_t prefix[] = {'A', 'd', 'a'};

// Define the array of leds
CRGB leds[NUM_LEDS];

#line 12 "c:\\Users\\kamil\\Documents\\Arduino\\addressable-ambibox-node-via-wifi\\addresable-amilight.ino"
void setup();
#line 36 "c:\\Users\\kamil\\Documents\\Arduino\\addressable-ambibox-node-via-wifi\\addresable-amilight.ino"
void loop();
#line 12 "c:\\Users\\kamil\\Documents\\Arduino\\addressable-ambibox-node-via-wifi\\addresable-amilight.ino"
void setup() { 
  FastLED.addLeds<WS2813, DATA_PIN, GRB>(leds, NUM_LEDS); 

            // // set darkroom mode at setup (small light at edges of desk)
            // leds[0].setRGB( 186, 0, 0);
            // leds[58].setRGB( 186, 0, 0);

            leds[0].red = 0xFF;
            leds[1].red =0xFF;
            leds[2].red =0xFF;
            leds[3].red =0xFF;
            leds[4].red =0xFF;

            FastLED.show();

      Serial.begin(serialRate);
      Serial.print("Ada\n");
      // leds[0] = 0xFF0000;

      // leds[60] = 0xFF0000;
      //       FastLED.show();

}

void loop() { 



      for(int i = 0; i < sizeof(prefix); ++i){
            while (!Serial.available());
            if(prefix[i] != Serial.read()) 
            return;
      }
      while(Serial.available() < 3);
      int highByte = Serial.read();
      int lowByte  = Serial.read();
      int checksum = Serial.read();
      if (checksum != (highByte ^ lowByte ^ 0x55)){
            return;}

      uint16_t ledCount = ((highByte & 0x00FF) << 8 | (lowByte & 0x00FF) ) + 1;
      if (ledCount > NUM_LEDS){
            ledCount = NUM_LEDS;
            }
            

            // READ FROM SERIAL 
      for (int i = 0; i < ledCount; i++){
            while(Serial.available() < 3){

            leds[i].r = Serial.read();
            Serial.print("R:%i", leds[i].r);
            leds[i].g = Serial.read();
            Serial.print("G:%i", leds[i].g);

            leds[i].b = Serial.read();}
            Serial.print("B:%i", leds[i].b);
}

}



