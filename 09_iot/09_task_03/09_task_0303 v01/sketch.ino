#include <Keypad.h>
#include "led_rgb.h"

/* LED */
const byte  ledPin[] = {9, 10, 11};

/* Keypad setup */
const byte ROWS = 4; //строки
const byte COLS = 4; //столбцы
const byte rowsPin[] = {5, 4, 3, 2}; //строки (выходы)
const byte colsPin[] = {A3, A2, A1, A0}; //столбцы (входы)

const char keys [4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Keypad keypad = Keypad(makeKeymap(keys), rowsPin, colsPin, ROWS, COLS);
LedRgb ledRgb1 (9, 10, 11);
char key {0};
char lastKey;

void setup() {
  for (int i = 0; i <= 3; i++) {
    pinMode(rowsPin[i], OUTPUT);
    pinMode(colsPin[i], INPUT_PULLUP);
    digitalWrite(rowsPin[i], HIGH);
  }

  for (int i = 0; i <= 2; i++) {
    pinMode(ledPin[i], OUTPUT);
    analogWrite(ledPin[i], 0);
  }

  Serial.begin(9600);
  Serial.println("begin");
}

void loop() {
  char key = keypad.getKey();

  if (!key) {
    key = lastKey;
  }

  Serial.println(key);

  if (key == '1') {
    ledRgb1.setColor(0, 0, 0);
  }

  //красный
  if (key == '2') {
    ledRgb1.setColor(255, 255, 0);
  }

  //зеленый
  if (key == '3') {
    ledRgb1.setColor(255, 0, 255);
  }

  //синий
  if (key == '4') {
    ledRgb1.setColor(0, 255, 255);
  }

  //yellow
  if (key == '5') {
    ledRgb1.setColor(255, 0, 0);
  }

  //фиолетовый
  if (key == '6') {
    ledRgb1.setColor(0, 255, 0);
  }

  if (key == '7') {
    ledRgb1.setColor(255, 255, 255);
  }

  if (key == 'A') {
    ////////ledRgb1.blink(1000);
  }

  if (key == 'B') {
    ledRgb1.blink(1000);
  }

  if (key == 'C') {
    ledRgb1.blink(500);
  }

  if (key == 'D') {
    ledRgb1.blink(250);
  }

  lastKey = key;
}