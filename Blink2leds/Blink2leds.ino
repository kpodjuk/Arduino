// the setup function runs once when you press reset or power the board
void setup() {
// initialize digital pin LED_BUILTIN as an output.
Serial.begin(115200);
Serial.println();
Serial.println("Running Setup");
Serial.print("LED_BUILTIN = ");
Serial.println(LED_BUILTIN, DEC);
pinMode(LED_BUILTIN, OUTPUT);
pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
int counter = 0;
void loop() {

if(counter%100) Serial.println("TEST");
counter++;
Serial.println("TEST");
digitalWrite(LED_BUILTIN, HIGH); // turn the NodeMCU LED off (HIGH is the voltage level)
delay(1000); // wait for a second
digitalWrite(LED_BUILTIN, LOW); // turn the NodeMCU LED on by making the voltage LOW
delay(1000); // wait for a second
}
