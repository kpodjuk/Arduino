#define LED1 16
#define LED2 5

#define DELAY 1000

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED1, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(DELAY);                       // wait for a second
  digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(LED1, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(LED2, LOW);    // turn the LED off by making the voltage LOW
  delay(DELAY);                       // wait for a second
}
