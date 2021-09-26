// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!

#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 7
unsigned int incomingByte = 0; // for incoming serial data

void setup() {
  Serial.begin(9600); //Ustawienie prędkości transmisji
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

}

void setLedColor(
  unsigned int red,
  unsigned int green,
  unsigned int blue
) {



  // Serial.println(green);
  // Serial.println(blue);
  analogWrite(REDPIN, red);// 1 - niebieski
  analogWrite(GREENPIN, green);// 2 - czerwony
  analogWrite(BLUEPIN, blue);// 3 - zielony
}
// db8c3d
#define DELAY 1000
void loop() {
  setLedColor(0xFF, 0x00, 0x00); Serial.println("RED"); delay(DELAY);
  setLedColor(0x00, 0xFF, 0x00); Serial.println("GREEN");  delay(DELAY);
  setLedColor(0x00, 0x00, 0xFF); Serial.println("BLUE");  delay(DELAY);
  setLedColor(0xFF, 0xFF, 0xFF); Serial.println("WHITE");  delay(DELAY);
}
