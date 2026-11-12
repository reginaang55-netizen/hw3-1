const int buttonPin = 2;
const int ledPin = 3;

const unsigned long blinkTime[4] = {0, 1000, 400, 100};

int state = 0;
bool ledOn = true;
unsigned long lastToggle = 0;

int lastReading = LOW;
int buttonState = LOW;
unsigned long lastChange = 0;
const unsigned long debounceTime = 30;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastReading) {
    lastChange = millis();
    lastReading = reading;
  }

  if (millis() - lastChange > debounceTime && reading != buttonState) {
    buttonState = reading;
    if (buttonState == HIGH) {
      state = state + 1;
      if (state >= 4) {
        state = 0;
      }
      ledOn = true;
      lastToggle = millis();
      Serial.print("state: ");
      Serial.println(state);
    }
  }

  if (state == 0) {
    ledOn = true;
  } else if (millis() - lastToggle >= blinkTime[state]) {
    ledOn = !ledOn;
    lastToggle = millis();
  }

  if (ledOn) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}