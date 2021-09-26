// Amblone code for the Arduino Mega
// Author: Bart van der Drift

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
int r1_pin = 9; //red
int g1_pin = 11; //green
int b1_pin = 10; //blue



//---------------------------------------------------------------------------
//----------------------------- IMPLEMENTATIONS -----------------------------
//---------------------------------------------------------------------------

void setup()   {                
  // initialize the serial communication
  Serial.begin(115200);	// opens serial port, sets data rate to 256000 bps
    pinMode(LED_BUILTIN, OUTPUT);
TCCR0B = TCCR0B & B11111000 | B00000010;    // set timer 0 divisor to     8 for PWM frequency of  7812.50 Hz

TCCR1B = TCCR1B & B11111000 | B00000010;    // set timer 1 divisor to     8 for PWM frequency of  3921.16 Hz
TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz

  
  State = S_WAIT_FOR_SF;
}
//---------------------------------------------------------------------------

void loop()                     
{


  if (Serial.available() > 0) {
    if (PacketReceived()) {



      SetPWMs();
    }
  }
}
//---------------------------------------------------------------------------

boolean PacketReceived() {
  Recv = Serial.read();
  // Serial.print("Otrzymano pakiet o tresci:");
  switch(State) {
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
  analogWrite(r1_pin, Payload[0]);
  analogWrite(g1_pin, Payload[1]);
  analogWrite(b1_pin, Payload[2]);
  
 
}
//---------------------------------------------------------------------------
