
#include "FastLED.h"
CRGB led;
int fadeAmount = 5;  // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.
int brightness = 0; 

#define REDPIN   11
#define GREENPIN 9
#define BLUEPIN  10
#define DELAY 20


void showAnalogRGB( const CRGB& rgb)
{
  analogWrite(REDPIN,   rgb.r );
  analogWrite(GREENPIN, rgb.g );
  analogWrite(BLUEPIN,  rgb.b );
}




void setup()
{
  Serial.begin(115200);
    pinMode(REDPIN,   OUTPUT);
    pinMode(GREENPIN, OUTPUT);
    pinMode(BLUEPIN,  OUTPUT);

}

void loop()
{ 

   led.setRGB(255,255,255);  // Set Color HERE!!!
   led.fadeLightBy(brightness);
  showAnalogRGB(led);

  
  brightness = brightness + fadeAmount;
  // reverse the direction of the fading at the ends of the fade: 
  if(brightness == 0 || brightness == 255)
  {
    fadeAmount = -fadeAmount ; 
  }    
  delay(9);  // This delay sets speed of the fade. I usually do from 5-75 but you can always go higher.
}




