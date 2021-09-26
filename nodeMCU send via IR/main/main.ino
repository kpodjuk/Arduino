#include <IRremote.h>

IRsend irsend;

#define DELAY 500

void setup()
{
  Serial.begin(115200);
  // irsend.blink13(true);
  Serial.println("Ready to go!");
}

void loop()
{

  // RED
  irsend.sendNECRaw(0xF609FF00, 4);
  delay(DELAY);
  // GREEN
  irsend.sendNECRaw(0xF708FF00, 4);
  delay(DELAY);
  // BLUE
  irsend.sendNECRaw(0xF50AFF00, 4);
  delay(DELAY);
  // WHITE
  irsend.sendNECRaw(0xF40BFF00, 4);
  delay(DELAY);


}