const int rLEDPin = 3;
const int gLEDPin = 4;
const int bLEDPin = 5;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(rLEDPin, OUTPUT);
  pinMode(gLEDPin, OUTPUT);
  pinMode(bLEDPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(rLEDPin, LOW);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(gLEDPin, LOW);
  digitalWrite(bLEDPin, LOW);
  delay(1000); 
  digitalWrite(rLEDPin, HIGH);
  digitalWrite(gLEDPin, LOW);
  digitalWrite(bLEDPin, LOW);
  delay(1000);
}
