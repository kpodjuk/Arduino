#define LED_PIN 0
#define DELAY 200


void setup() {
  pinMode(LED_PIN, OUTPUT);
}



// the loop function runs over and over again forever
void loop() {

firstFunction(4, 6);

  digitalWrite(5, HIGH);
  delay(200);                       
  digitalWrite(5, LOW);    // turn the LED off by making the voltage LOW
  delay(200);
                         // wait for a second
}



int firstFunction(int liczba, int liczba2){
  int wynik = liczba + liczba2;
}