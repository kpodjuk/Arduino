#define REDPIN 7
#define GREENPIN 6
#define BLUEPIN 5

void setup()

{

  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

Serial.begin(9600);

while (!Serial);

Serial.println("Input 1 to Turn LED on and 2 to off");

}

void loop() {

if (Serial.available())

{

int state = Serial.parseInt();


      analogWrite(REDPIN, state >> 16);// 1 - niebieski
      analogWrite(GREENPIN, state >> 8);// 2 - czerwony
      analogWrite(BLUEPIN, state);// 3 - zielony



}

}
