// Amblone code for the Arduino Mega
// Author: Bart van der Drift
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

// License:
// Anyone is free to change, redistribute or copy parts of this code
// as long as it is not for commercial purposes
// Please be so kind to pay credit where due

//---------------------------------------------------------------------------
//---------------------------------- DEFINES --------------------------------
//---------------------------------------------------------------------------

// Flags for the USB communication protocol
#define C_SF1 0xF1 // Startflag for 1-channel mode (1 RGB channel)
#define C_SF2 0xF2 // Startflag for 2-channel mode (2 RGB channels)
#define C_SF3 0xF3 // Startflag for 3-channel mode (3 RGB channels)
#define C_SF4 0xF4 // Startflag for 4-channel mode (4 RGB channels)
#define C_END 0x33 // End flag
#define C_ESC 0x99 // Escape character

// States for receiving the information, see the flow chart for more info
#define S_WAIT_FOR_SF  0
#define S_RECV_RGB     1
#define S_RECV_RGB_ESC 2

//---------------------------------------------------------------------------
//--------------------------- FUNCTION DECLARATIONS -------------------------
//---------------------------------------------------------------------------

// Receives bytes and returns true if a valid packet was received
boolean PacketReceived();

// Uses the rgb values to set the PWMs
void SetPWMs();

//---------------------------------------------------------------------------
//--------------------------- VARIABLE DECLARATIONS -------------------------
//---------------------------------------------------------------------------

int pulse = 0;

// State we are in: one of the S_* defines
int State = 0;
// The payload of a received message
int Payload[32];
// The amount of RGB values we have received
int ByteCount = 0;
// The character we received
int Recv;

// The amount of RGB channels we are using
int ChannelMode;

// PWM pins for channel 1
int REDPIN = 11;
int GREENPIN = 9;
int BLUEPIN = 10;
boolean shouldBlinkFlag = false;


//---------------------------------------------------------------------------
//----------------------------- IMPLEMENTATIONS -----------------------------
//---------------------------------------------------------------------------

void setup()   {                
  // initialize the serial communication
  Serial.begin(115200);	// opens serial port, sets data rate to 256000 bps
    pinMode(REDPIN,   OUTPUT);
    pinMode(GREENPIN, OUTPUT);
    pinMode(BLUEPIN,  OUTPUT);
TCCR0B = TCCR0B & B11111000 | B00000010;    // set timer 0 divisor to     8 for PWM frequency of  7812.50 Hz

TCCR1B = TCCR1B & B11111000 | B00000010;    // set timer 1 divisor to     8 for PWM frequency of  3921.16 Hz
TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz

  
  State = S_WAIT_FOR_SF;
}
//---------------------------------------------------------------------------

void loop()                     
{
  
  if(shouldBlinkFlag){
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
  Serial.println(shouldBlinkFlag);

  if (Serial.available() > 0) {
    if (PacketReceived()) {
      shouldBlinkFlag = false;


      SetPWMs();
    }
  }
}
//---------------------------------------------------------------------------

boolean PacketReceived() {
  Recv = Serial.read();
  
  switch (State) {
    case S_WAIT_FOR_SF:
      // =============================== Wait for start flag state
      switch (Recv) {
        case C_SF1:
          // Start flag for 1-channel mode
          ChannelMode = 1;
          State = S_RECV_RGB;
          ByteCount = 0;
          return false;
        case C_SF2:
          // Start flag for 2-channel mode
          ChannelMode = 2;
          State = S_RECV_RGB;
          ByteCount = 0;
          return false;
        case 243://C_SF3:
          // Start flag for 3-channel mode
          ChannelMode = 3;
          State = S_RECV_RGB;
          ByteCount = 0;
          return false;
        case C_SF4:
          // Start flag for 4-channel mode
          ChannelMode = 4;
          State = S_RECV_RGB;
          ByteCount = 0;
          return false;
        default:
          // No action for all other characters
          return false;
      }
      break;
    case S_RECV_RGB:
      // =============================== RGB Data reception state
      switch (Recv) {
        case C_SF1:
          // Start flag for 1-channel mode
          ChannelMode = 1;
          State = S_RECV_RGB;
          ByteCount = 0;
          return false;
        case C_SF2:
          // Start flag for 2-channel mode
          ChannelMode = 2;
          State = S_RECV_RGB;
          ByteCount = 0;
          return false;
        case C_SF3:
          // Start flag for 3-channel mode
          ChannelMode = 3;
          State = S_RECV_RGB;
          ByteCount = 0;
          return false;
        case C_SF4:
          // Start flag for 4-channel mode
          ChannelMode = 4;
          State = S_RECV_RGB;
          ByteCount = 0;
          return false;
        case C_END:
          // End Flag
          // For each channel, we should have received 3 values. If so, we have received a valid packet
          if (ByteCount == ChannelMode * 3) {
            State = S_WAIT_FOR_SF;
            ByteCount = 0;
            return true; // <------------------------ TRUE IS RETURNED
          }
          else {
            // Something's gone wrong: restart
            State = S_WAIT_FOR_SF;
            ByteCount = 0;
            return false;
          }
        case C_ESC:
          // Escape character
          State = S_RECV_RGB_ESC;
          return false;
        default:
          // The character received wasn't a flag, so store it as an RGB value        
          Payload[ByteCount] = Recv;
          ByteCount++;
          return false;
      }
      case S_RECV_RGB_ESC:
        // =============================== RGB Escaped data reception state
        // Store the value in the payload, no matter what it is
        Payload[ByteCount] = Recv;
        ByteCount++;
        State = S_RECV_RGB;
        return false;
  }
  
  return false;
}

//---------------------------------------------------------------------------

void SetPWMs() {
  // Channel 1
  analogWrite(REDPIN, Payload[0]);
  analogWrite(GREENPIN, Payload[1]);
  analogWrite(BLUEPIN, Payload[2]);
  
 
}
//---------------------------------------------------------------------------
