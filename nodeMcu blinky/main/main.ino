#define LED1 D3


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED1, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED1, HIGH);   // turn the LED on 
  delay(500);                       // wait for half a second
  digitalWrite(LED1, LOW);    // turn the LED off 
  delay(500);                       // wait for half a second
}