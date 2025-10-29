const int buttonPin = 2;
const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;

int mood = 0;
const int neutralMood = 10;
// unsigned long previousMillis = 0;
// int fadingDirection = 1;
unsigned long touchedTimer = 0;
unsigned long reducedTimer = 0;
const long unTouchInterval = 5000;
const long reducedInterval = 1000;

int buttonState = 0;
bool ButtonPressed = false;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  mood = neutralMood;
}

void loop() {
  showLEDState(mood);

  buttonState = digitalRead(buttonPin);

  if(buttonState == HIGH && !ButtonPressed){
    mood = mood + 1;
    if(mood > 20) mood = 20;
    touchedTimer = millis();
    ButtonPressed = true;
  }
  if(buttonState == LOW && ButtonPressed){
    ButtonPressed = false;
  }

  unsigned long currentMillis = millis();
  if(currentMillis - touchedTimer > unTouchInterval){
    if(currentMillis - reducedTimer > reducedInterval){
      mood = mood - 1;
      if(mood < 0) mood = 0;{
        reducedTimer = currentMillis;
      }
    }
  }

  // if(currentMillis - previousMillis > 1000){
  //   mood = mood + fadingDirection;
  //   if(mood >= 20 || mood <=0){
  //     fadingDirection = -fadingDirection;
  //   }
  //   previousMillis = currentMillis;
  // }
}

void showLEDState(int state){
  float brightnessInterval = 255 / 10.0;
  if(mood >= neutralMood){
    analogWrite(RledPin, 255);
    analogWrite(GledPin, brightnessInterval * (mood - neutralMood));
    analogWrite(BledPin, 255 - brightnessInterval * (mood - neutralMood));
  }
  else{
    analogWrite(RledPin, 255 - brightnessInterval * (neutralMood - mood));
    analogWrite(GledPin, brightnessInterval * (neutralMood - mood));
    analogWrite(BledPin, 255);
  }
}
