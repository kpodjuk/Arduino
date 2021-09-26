/* Example code for HC-SR501 PIR motion sensor with Arduino. More info: www.www.makerguides.com */
// Define connection pins:

#define MOTION_SENSOR_PIN 16 // D0
#define LED_PIN 2 // onboard LED

// Create variables:
int val = 0;
bool motionState = false; // We start with no motion detected.
void setup() {
  // Configure the pins as input or output:
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTION_SENSOR_PIN, INPUT);
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(115200);
        Serial.println("I work!");
}
void loop() {
  // Read out the pirPin and store as val:
  val = digitalRead(MOTION_SENSOR_PIN);
  // If motion is detected (pirPin = HIGH), do the following:
  if (val == HIGH) {
    digitalWrite(LED_PIN, HIGH); // Turn on the on-board LED.
    // Change the motion state to true (motion detected):
    if (motionState == false) {
      Serial.println("Motion detected!");
      motionState = true;
    }
  }
  // If no motion is detected (pirPin = LOW), do the following:
  else {
    digitalWrite(LED_PIN, LOW); // Turn off the on-board LED.
    // Change the motion state to false (no motion):
    if (motionState == true) {
      Serial.println("Motion ended!");
      motionState = false;
    }
  }
}