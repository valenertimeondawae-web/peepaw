const int buttonPin = 2; 
const int ledPin = 3;

int buttonState = HIGH;
int lastButtonState = HIGH;
int mode = 0;

bool ledState = false;
unsigned long lastBlinkTime = 0;
unsigned long blinkInterval = 1000;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(ledPin, HIGH);
}

void loop() {
  checkButton();
  updateLED();
}

void checkButton() {
  buttonState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && buttonState == LOW) {
    mode++;
    if (mode > 3) mode = 0;
    delay(50); 
  }

  lastButtonState = buttonState;
}

void updateLED() {
  if (mode == 0) {
    digitalWrite(ledPin, LOW);
  } else {
    if (mode == 1) blinkInterval = 1000;
    else if (mode == 2) blinkInterval = 500;
    else blinkInterval = 200;

    unsigned long currentTime = millis();
    if (currentTime - lastBlinkTime >= blinkInterval) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState ? LOW : HIGH);
      lastBlinkTime = currentTime;
    }
  }
}
