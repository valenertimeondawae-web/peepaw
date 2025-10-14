const int buttonPin = 2;
const int RledPin = 3;
const int GledPin = 4;
const int BledPin = 5;

int buttonState = 0;
int ledState = LOW;
int ledcolor = 0;

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
    ledcolor = ledcolor + 1;
    ButtonPressed = true;
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
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
    currentcolor="LED off";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 1){
    //Cyan
    currentcolor="Cyan";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
    
  }
  else if (ledcolor == 2){
    currentcolor="Red";
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
    
  }
  else if (ledcolor == 3){
    currentcolor="Green";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 4){
    currentcolor="Blue";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
    
  }
  else if (ledcolor == 5){
    currentcolor="Blue";
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
    
  }
  else if (ledcolor == 6){
    ledcolor = 0;
  }
}

