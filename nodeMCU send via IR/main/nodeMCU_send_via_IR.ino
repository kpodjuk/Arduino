#include <Arduino.h>
#include "PinDefinitionsAndMore.h"
#include <IRremote.h>

#define DELAY 500

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK); // Specify send pin and enable feedback LED at default feedback LED pin

    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);
}



void loop() {

  // RED
  IrSender.sendNECRaw(0xF609FF00, 0);
//   digitalWrite(LED_BUILTIN, HIGH);
  delay(DELAY);

  // GREEN
  IrSender.sendNECRaw(0xF708FF00, 0);
//   digitalWrite(LED_BUILTIN, LOW);
  delay(DELAY);

  // BLUE
  IrSender.sendNECRaw(0xF50AFF00, 0);
//   digitalWrite(LED_BUILTIN, HIGH);
  delay(DELAY);

  // WHITE
  IrSender.sendNECRaw(0xF40BFF00, 0);
//   digitalWrite(LED_BUILTIN, LOW);
  delay(DELAY);



}
