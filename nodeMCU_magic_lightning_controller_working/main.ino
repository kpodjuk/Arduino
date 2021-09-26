
#include <Arduino.h>

#define IR_RECEIVE_PIN 16 // D0

#include <IRremote.h>

void setup()
{
    Serial.begin(115200);
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    /*
     * Start the receiver, enable feedback LED and take LED feedback pin from the internal boards definition
     */
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);

    Serial.print(F("Ready to receive IR signals at pin "));
    Serial.println(IR_RECEIVE_PIN);
}

void loop()
{

    if (IrReceiver.decode())
    {

        // Print a short summary of received data
        IrReceiver.printIRResultShort(&Serial);
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            // We have an unknown protocol here, print more info
            IrReceiver.printIRResultRawFormatted(&Serial, true);
        }
        Serial.println();


        IrReceiver.resume(); // Enable receiving of the next value

        switch (IrReceiver.decodedIRData.command)
        {
        case 0x5:
            Serial.println("Button 1 pressed!\n");
            break;
        case 0x4:
            Serial.println("Button 2 pressed\n");
            break;
        case 0x6:
            Serial.println("Button 3 pressed\n");
            break;
        case 0x7:
            Serial.println("Button 4 pressed\n");
            break;
        case 0x9:
            Serial.println("Button 5 pressed\n");
            break;

        }
        // if (IrReceiver.decodedIRData.command == 0x10) {
        //     // do something
        // } else if (IrReceiver.decodedIRData.command == 0x11) {
        //     // do something else
        // } else if (IrReceiver.decodedIRData.command == 0x11)
    }
}