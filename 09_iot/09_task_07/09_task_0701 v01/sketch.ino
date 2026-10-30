#include <Stepper.h>
#include "button.h"

Button btn_run(2);
Button btn_left(3);
Button btn_right(4);

const int stepsPerRevolution = 200;
int stepCount = 0;
Stepper stepper_1(stepsPerRevolution, 8, 9, 10, 11);

short step {0};
bool mode {0};

void setup() {
  btn_run.begin();
  btn_left.begin();
  btn_right.begin();

  Serial.begin(9600);
  Serial.println("Выберите направление вращения (лев./черн. кнопка - прав./зелен. кнопка).");
}

void loop() {
  int sensor = analogRead(A0);
  int motorSpeed = map(sensor, 0, 1023, 0, 100);

  if (btn_left.wasPressed()) {
    if (!mode) {
      step = -1;
      Serial.println("Выбрано \"Влево\"");
    }
  }

  if (btn_right.wasPressed()) {
    if (!mode) {
      step = 1;
      Serial.println("Выбрано \"Вправо\"");
    }
  }

  if (btn_run.wasPressed()) {
    if (step != 0) {
      if (!mode) {
        mode = 1;
        Serial.println("Пуск (задайте скорость вращения > 0)");
      } else {
        mode = 0;
        Serial.println("Стоп");
      }
    } else {
      Serial.println("Не выбрано направление вращения! Сделайте выбор.");
    }
  }

  if (mode) {
    if (motorSpeed > 0) {
      stepper_1.setSpeed(motorSpeed);
      stepper_1.step(step);
      if (btn_left.wasPressed() || btn_right.wasPressed()) {
        Serial.println("Сначала нажмите \"Стоп\"");
      }
    }
  }
}