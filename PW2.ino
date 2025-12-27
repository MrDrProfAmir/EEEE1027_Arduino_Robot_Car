#include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,4,5,6,7);

int ENA = 3;
int IN1 = 1;
int IN2 = 2;
int IN3 = 13;
int IN4 = 12;
int ENB = 11;

int prevLeft = HIGH;
int prevRight = HIGH;

int left_sensor = A1;
int right_sensor = A2;

const int LEFT_D0  = A3;
const int RIGHT_D0 = A4;

volatile long leftCount  = 0;
volatile long rightCount = 0;

const float WHEEL_D = 0.065;
const int PPR = 20;
const float PI_F = 3.14159;
const float DIST_PER_COUNT = (PI_F * WHEEL_D) / PPR;

unsigned long lastPrint = 0;
unsigned long startTime = 0;

void setup() {
pinMode(ENA, OUTPUT);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
pinMode(ENB, OUTPUT);

pinMode(left_sensor, INPUT);
pinMode(right_sensor, INPUT);

pinMode(LEFT_D0, INPUT_PULLUP);
pinMode(RIGHT_D0, INPUT_PULLUP);
lcd.begin(16, 2); 
lcd.setCursor(0,0);
lcd.print("Distance: ");
lcd.setCursor(0, 1);
lcd.print("Time: ");
}

void loop() {
int right = digitalRead(right_sensor);
int left = digitalRead(left_sensor);

if (left == 1 && right == 1) {
  forward();
}
else if (left == 1 && right == 0) {
  reverse();
  delay(50);
  turnleft();
  delay(200);
}
else if (left == 0 && right == 1) {
  reverse();
  delay(50);
  turnright();
  delay(200);
}
else {
  while(1){
  stop();
  }
}

int curLeft = digitalRead(LEFT_D0);
if (prevLeft == LOW && curLeft == HIGH) {
  leftCount++;
}
prevLeft = curLeft;

int curRight = digitalRead(RIGHT_D0);
if (prevRight == LOW && curRight == HIGH) {
  rightCount++;
}
prevRight = curRight;

if (millis() - lastPrint >= 200) {
  noInterrupts();
  long lCnt = leftCount;
  long rCnt = rightCount;
  interrupts();

  float leftDist  = lCnt * DIST_PER_COUNT;
  float rightDist = rCnt * DIST_PER_COUNT;
  float avgDist   = (leftDist + rightDist) / 2.0;
  float time = (millis() - startTime) / 1000.0;

  lcd.setCursor(11,0);
  lcd.print(avgDist, 2);
  lcd.setCursor(7, 1);
  lcd.print(time);

  lastPrint = millis();
}
}

void forward() {
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
analogWrite(ENA, 200);
analogWrite(ENB, 200);
}

void reverse() {
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
analogWrite(ENA, 200);
analogWrite(ENB, 200);
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

void stop() {
analogWrite(ENA, 0);
analogWrite(ENB, 0);
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
}


