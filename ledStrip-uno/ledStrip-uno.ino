// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!

#define REDPIN 9
#define GREENPIN 10
#define BLUEPIN 11


void setColorHex(uint32_t);

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
  // setLedColor(0xFF, 0x00, 0x00); Serial.println("RED"); delay(DELAY);
  // setLedColor(0x00, 0xFF, 0x00); Serial.println("GREEN");  delay(DELAY);
  // setLedColor(0x00, 0x00, 0xFF); Serial.println("BLUE");  delay(DELAY);
  // setLedColor(0xFF, 0xFF, 0xFF); Serial.println("WHITE");  delay(DELAY);



  setColorHex(0xffffff); delay(DELAY);
  // setColorHex(0xcc6a08); delay(DELAY);
  // setColorHex(0x96d97c); delay(DELAY);
  // setColorHex(0x528f3b); delay(DELAY);
}


void setColorHex(uint32_t hex){



	uint8_t red, green, blue;

	red = hex>>16;
	green = ((hex & 0x00FF00) >> 8);
	blue =	hex & 0x0000FF;


// Serial.println("COLOR:");
// Serial.println(hex, HEX);
// Serial.println(red, HEX);
// Serial.println(green, HEX);
// Serial.println(blue, HEX);

setLedColor(red, green, blue);

}
