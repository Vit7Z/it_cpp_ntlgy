#include <Servo.h>

Servo servo;

#define TRIG 13
#define ECHO 12
#define SERVO 9

const unsigned long delay_sensor {10};
unsigned long timer_sensor = 0;

float distance_cm;

void ReadUltrasonicDistance() {  
  if (millis() - timer_sensor >= delay_sensor) {
    pinMode(TRIG, OUTPUT);
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    pinMode(ECHO, INPUT);
    distance_cm = (pulseIn(ECHO, HIGH) / 58);
    timer_sensor = millis();
  }
}

void SetServo(){
  servo.write(map(distance_cm, 0, 400, 180, 0));
}

void setup() {
  servo.attach(SERVO);
}

void loop() {
  ReadUltrasonicDistance();
  SetServo();
}
