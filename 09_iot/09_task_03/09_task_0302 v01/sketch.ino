const int pinX = A0;
const int pinY = A1;
const int pinSel = 2;
const int leds[] = {11, 10, 9, 6, 5, 3};
const int button =  2;
int lastButton = LOW;
int curButton = LOW;
int curLed = 0;
int x, y, prev_x, prev_y;
int brightness;

#define JOY_GAP ((int)50)
#define JOY_MIDDLE ((int)512)

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 6; i++) {
    pinMode(leds[i], OUTPUT);
    analogWrite(leds[i], 0);
  }

  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);

  x = analogRead(pinX);
  prev_x = x;

  y = analogRead(pinY);
  prev_y = y;

  brightness = map(y, 0, 1023, 0, 250);
  
  analogWrite(leds[curLed], brightness);
}

void loop() {
  x = analogRead(pinX);
  y = analogRead(pinY);

  if (x != prev_x) {
    prev_x = x;
    if (x < (JOY_MIDDLE - JOY_GAP)) {
      if (curLed < (sizeof(leds) / sizeof(int) - 1)) {
        analogWrite(leds[curLed], 0);
        curLed++;
        analogWrite(leds[curLed], brightness);
      }
    }

    if (x > (JOY_MIDDLE + JOY_GAP)) {
      if (curLed > 0) {
        analogWrite(leds[curLed], 0);
        curLed--;
        analogWrite(leds[curLed], brightness);
      }
    }
  }

  if (y != prev_y) {
    prev_y = y;
    if (y < (JOY_MIDDLE - JOY_GAP)) {
      if (brightness >= 10) {
        brightness -= 10;
        analogWrite(leds[curLed], brightness);
      }
      else {
        brightness = 0;
        analogWrite(leds[curLed], brightness);
      }
    }

    if (y > (JOY_MIDDLE + JOY_GAP)) {
      if (brightness <= 240) {
        brightness += 10;
        analogWrite(leds[curLed], brightness);
      }
    }
  }

  curButton = debounce (lastButton);
  if (lastButton == HIGH && curButton == LOW) {
    analogWrite(leds[curLed], 0);
    curLed = 0;
    analogWrite(leds[curLed], brightness);
  }

  lastButton = curButton;
  delay(100);
}

int debounce (int last) {
  int current = digitalRead(button);
  if (last != current) {
    delay(5);
    current =  digitalRead(button);
  }
  return current;
}