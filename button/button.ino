const int buttonPin = 2;
const int RledPin = 3;
const int GledPin = 4;
const int BledPin = 5;

int buttonState = 0;
int ledState = LOW;
int ledcolor = 0;
int direction = 1;

bool ButtonPressed = false;
String currentcolor = "led";
unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  Serial.begin(9600);

  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  Serial.print("Current Color: ");
  Serial.println(currentcolor);

  if (buttonState == LOW && !ButtonPressed) {
    direction = direction*-1;
    
    ButtonPressed = true;
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledcolor = ledcolor + direction;
    if (ledState == LOW) {
      ledState = HIGH;
    }
    else{
      ledState = LOW;
    }
  }

  if (buttonState == HIGH && ButtonPressed){
    ButtonPressed = false;
  }

  if (ledcolor == 0){
    //ded
    currentcolor="Red";
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 1){
    //Cyan
    currentcolor="Green";
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, LOW);
      digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 2){
    //
    currentcolor="Green";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }
    else if (ledcolor == 3){
    //Yellow
    currentcolor="Blue";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  }
  else if (ledcolor == 4){
    //White
    currentcolor="White";
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
  }
  else if (ledcolor == 5){
    ledcolor = 0;
  }
  else if (ledcolor == -1)
  {
    ledcolor = 4;
  }
}

