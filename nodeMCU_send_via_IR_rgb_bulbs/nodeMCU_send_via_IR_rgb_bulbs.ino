#include <Arduino.h>

#include <IRremote.h>

#define DELAY 500
#define IR_SEND_PIN 14

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK); // Specify send pin and enable feedback LED at default feedback LED pin

    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);
}

void loop()
{

    for (int i = 1; i <= 24; i++)
    {
        sendButtonPressToLightbulb(i);
        Serial.printf("Sending button number: %i\n", i);
        delay(DELAY);
    }
}

void sendButtonPressToLightbulb(int button)
{
    switch (button)
    {
    case 1: // brightness up
        IrSender.sendNECRaw(0xFA05FF00, 0);
        break;
    case 2: // brightness down
        IrSender.sendNECRaw(0xFB04FF00, 0);
        break;
    case 3: // off
        IrSender.sendNECRaw(0xF906FF00, 0);
        break;
    case 4: // on
        IrSender.sendNECRaw(0xF807FF00, 0);
        break;
    case 5: // red
        IrSender.sendNECRaw(0xF609FF00, 0);
        break;
    case 6: // green
        IrSender.sendNECRaw(0xF708FF00, 0);
        break;
    case 7: // blue
        IrSender.sendNECRaw(0xF50AFF00, 0);
        break;
    case 8: // white
        IrSender.sendNECRaw(0xF40BFF00, 0);
        break;
    case 9: // slightly lighter red
        IrSender.sendNECRaw(0xF20DFF00, 0);
        break;
    case 10: // slightly lighter green
        IrSender.sendNECRaw(0xF30CFF00, 0);
        break;
    case 11: // slightly lighter blue
        IrSender.sendNECRaw(0xF10EFF00, 0);
        break;
    case 12: // flash
        IrSender.sendNECRaw(0xF00FFF00, 0);
        break;
    case 13: // orange
        IrSender.sendNECRaw(0xF20DFF00, 0);
        break;
    case 14: // turquoise
        IrSender.sendNECRaw(0xF30CFF00, 0);
        break;
    case 15: // purple
        IrSender.sendNECRaw(0xF10EFF00, 0);
        break;
    case 16: // strobe
        IrSender.sendNECRaw(0xF00FFF00, 0);
        break;
    case 17: // slightly lighter orange
        IrSender.sendNECRaw(0xE619FF00, 0);
        break;
    case 18: // navy
        IrSender.sendNECRaw(0xE718FF00, 0);
        break;
    case 19: // pink
        IrSender.sendNECRaw(0xE51AFF00, 0);
        break;
    case 20: // fade
        IrSender.sendNECRaw(0xE41BFF00, 0);
        break;
    case 21: // yellow
        IrSender.sendNECRaw(0xEE11FF00, 0);
        break;
    case 22: // darker navy
        IrSender.sendNECRaw(0xEF10FF00, 0);
        break;
    case 23: // rose
        IrSender.sendNECRaw(0xED12FF00, 0);
        break;
    case 24: // smooth
        IrSender.sendNECRaw(0xEC13FF00, 0);
        break;
    }
}