// Pin assignments
const int RledPin = 10;
const int GledPin = 11;
const int BledPin = 9;
const int buttonPin = 2; 


int buttonState = 0;
bool buttonPressed = false;
unsigned long pressingTime = 0;
const int longPressInterval = 2000; // ms


int lightNum = 0;
int RLightColor = 0;
int GLightColor = 0;
int BLightColor = 0;


int currentMode = 0;
int RCurrentColor = 0;
int GCurrentColor = 0;
int BCurrentColor = 0;


unsigned long blinkTimer = 0;
const int blinkInterval = 500;
bool blinkOn = true;

// Fade mode
const int fadeAmount = 2;
int fadeDirection = 1;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  checkButton();
  updateLEDColor();
  setRGBLEDColor(RCurrentColor, GCurrentColor, BCurrentColor);
}

void checkButton() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && !buttonPressed) {
    pressingTime = millis();
    buttonPressed = true;
  }

  if (buttonState == HIGH && buttonPressed) {
    unsigned long currentTime = millis();
    if (currentTime - pressingTime < longPressInterval) {
      changeLEDColor();
    } else {
      changeMode();
    }
    buttonPressed = false;
    delay(50); 
  }
}

void changeLEDColor() {
  lightNum++;
  if (lightNum >= 5) lightNum = 0;

  switch (lightNum) {
    case 0: RLightColor = 255; GLightColor = 255; BLightColor = 255; break; // white
    case 1: RLightColor = 255; GLightColor = 0;   BLightColor = 0;   break; // red
    case 2: RLightColor = 0;   GLightColor = 255; BLightColor = 0;   break; // green
    case 3: RLightColor = 0;   GLightColor = 0;   BLightColor = 255; break; // blue
    case 4: RLightColor = 255; GLightColor = 255; BLightColor = 0;   break; // yellow
  }

  RCurrentColor = RLightColor;
  GCurrentColor = GLightColor;
  BCurrentColor = BLightColor;
}

void setRGBLEDColor(int r, int g, int b) {
  analogWrite(RledPin, 255 - r);
  analogWrite(GledPin, 255 - g);
  analogWrite(BledPin, 255 - b);
}

void changeMode() {
  currentMode++;
  if (currentMode >= 3) currentMode = 0;
  Serial.print("Mode: ");
  Serial.println(currentMode);

  if (currentMode == 1) {
    blinkTimer = millis();
    blinkOn = true;
  }

  if (currentMode == 2) {
    fadeDirection = 1;
    RCurrentColor = RLightColor;
    GCurrentColor = GLightColor;
    BCurrentColor = BLightColor;
  }
}

void updateLEDColor() {
  if (currentMode == 0) {
    RCurrentColor = RLightColor;
    GCurrentColor = GLightColor;
    BCurrentColor = BLightColor;
  }

  else if (currentMode == 1) {
    unsigned long currentTime = millis();
    if (currentTime - blinkTimer > blinkInterval) {
      blinkOn = !blinkOn;
      blinkTimer = currentTime;
    }

    if (blinkOn) {
      RCurrentColor = RLightColor;
      GCurrentColor = GLightColor;
      BCurrentColor = BLightColor;
    } else {
      RCurrentColor = 0;
      GCurrentColor = 0;
      BCurrentColor = 0;
    }
  }

  else if (currentMode == 2) {
  bool reverse = false;

  if (RLightColor > 0) {
    RCurrentColor += fadeDirection * fadeAmount;
    if (RCurrentColor <= 0 || RCurrentColor >= RLightColor) reverse = true;
    RCurrentColor = constrain(RCurrentColor, 0, RLightColor);
  } else {
    RCurrentColor = 0;
  }

  if (GLightColor > 0) {
    GCurrentColor += fadeDirection * fadeAmount;
    if (GCurrentColor <= 0 || GCurrentColor >= GLightColor) reverse = true;
    GCurrentColor = constrain(GCurrentColor, 0, GLightColor);
  } else {
    GCurrentColor = 0;
  }

  if (BLightColor > 0) {
    BCurrentColor += fadeDirection * fadeAmount;
    if (BCurrentColor <= 0 || BCurrentColor >= BLightColor) reverse = true;
    BCurrentColor = constrain(BCurrentColor, 0, BLightColor);
  } else {
    BCurrentColor = 0;
  }

  if (reverse) fadeDirection = -fadeDirection;

  delay(10);
}

}
