#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(8,9,4,5,6,7);

int ENA = 3;
int IN1 = 1;
int IN2 = 2;
int IN3 = 13;
int IN4 = 12;
int ENB = 11;

int prevLeft = HIGH;
int prevRight = HIGH;

int echoPin = A1;
int trigPin = A2;

float duration, distance;


void setup() {
pinMode(ENA, OUTPUT);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
pinMode(ENB, OUTPUT);

pinMode(echoPin, INPUT);
pinMode(trigPin, OUTPUT);

}

void loop() {
int echo = digitalRead(echoPin);
int trig = digitalRead(trigPin);

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin,HIGH);
distance = (0.034*duration)/2;

if (distance <= 20) {
  turnleft();
}
else {
  forward();
}
}

void forward() {
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
analogWrite(ENA, 150);
analogWrite(ENB, 150);
}

void reverse() {
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
analogWrite(ENA, 200);
analogWrite(ENB, 200);
}

void stop() {
analogWrite(ENA, 0);
analogWrite(ENB, 0);
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
}

void turnright() {
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
analogWrite(ENA, 200);
analogWrite(ENB, 250);
}

void turnleft() {
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
analogWrite(ENA, 250);
analogWrite(ENB, 200);
}