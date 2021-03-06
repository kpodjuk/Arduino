#include <FastLED.h>

// Example showing how to use FastLED color functions
// even when you're NOT using a "pixel-addressible" smart LED strip.
//
// This example is designed to control an "analog" RGB LED strip
// (or a single RGB LED) being driven by Arduino PWM output pins.
// So this code never calls FastLED.addLEDs() or FastLED.show().
//
// This example illustrates one way you can use just the portions 
// of FastLED that you need.  In this case, this code uses just the
// fast HSV color conversion code.
// 
// In this example, the RGB values are output on three separate
// 'analog' PWM pins, one for red, one for green, and one for blue.
 
#define REDPIN   11
#define GREENPIN 9
#define BLUEPIN  10
#define DELAY 10

// showAnalogRGB: this is like FastLED.show(), but outputs on 
// analog PWM output pins instead of sending data to an intelligent,
// pixel-addressable LED strip.
// 
// This function takes the incoming RGB values and outputs the values
// on three analog PWM output pins to the r, g, and b values respectively.
void showAnalogRGB( const CRGB& rgb)
{
  analogWrite(REDPIN,   rgb.r );
  analogWrite(GREENPIN, rgb.g );
  analogWrite(BLUEPIN,  rgb.b );
}



// colorBars: flashes Red, then Green, then Blue, then Black.
// Helpful for diagnosing if you've mis-wired which is which.
void colorBars()
{
  showAnalogRGB( CRGB::Red );   
  delay(DELAY);
  showAnalogRGB( CRGB::Green ); 
  delay(DELAY);
  showAnalogRGB( CRGB::Blue );  
  delay(DELAY);
  showAnalogRGB( CRGB::Black ); 
  delay(DELAY);
}

void loop() 
{
  static uint8_t hue;
  hue = hue + 1;
  Serial.println(hue);
  // Use FastLED automatic HSV->RGB conversion
  showAnalogRGB( CHSV( hue, 255, 255) );
  
  delay(DELAY);
}


void setup() {
  Serial.begin(115200);
  pinMode(REDPIN,   OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN,  OUTPUT);

  // Flash the "hello" color sequence: R, G, B, black.
  colorBars();
}

