#include <LiquidCrystal.h>
#include <MPU6050.h>
#include <Wire.h>

LiquidCrystal lcd(8,9,4,5,6,7);
MPU6050 mpu;

int ENA = 3;
int IN1 = 1;
int IN2 = 2;
int IN3 = 13;
int IN4 = 12;
int ENB = 11;

bool rotatedOnce = false;
bool peak = false;

float peakAngle = 0.0;
float lastAngle = 0.0;


                     


void rot_360() {
  float angleAccum = 0;
  unsigned long lastMicros = micros();
  turnright();
  while (angleAccum < 360.0f) {
    int16_t ax,ay,az,gx,gy,gz;
    mpu.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);
    unsigned long now = micros();
    float dt = (now - lastMicros) / 1000000.0;
    if (dt <= 0) dt = 1e-6;
    lastMicros = now;
    float gz_dps = (float)gz / 131.0f;
    angleAccum += fabs(gz_dps) * dt;
    
  
    lcd.setCursor(0,1);
    lcd.print("Rot:");
    lcd.print(angleAccum,0);
    lcd.print("deg   ");
    delay(3);
  }
  stop();
  delay(100);
}




void setup() {

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  Wire.begin();
  mpu.initialize();

  lcd.begin(16,2);
  delay(1000);
  forward();
  delay(1000);
  

}




void loop() {
  int16_t ax,ay,az,gx,gy,gz;
  mpu.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);

  float angle1 = atan2(ay,az) * 180.0f / PI; 

  if (!peak && angle1 > peakAngle) {
    peakAngle = angle1;
  }

  if (!peak && angle1 < peakAngle - 1.0) {
    stop();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Angle: ");
    lcd.print(peakAngle,1);
    delay(1000);
    forward();
    delay(1000);
    peak = true;
  }

  if (!rotatedOnce && fabs(angle1)<2.0f) {
    lcd.setCursor(0,1);
    lcd.print("Stop 4s  ");
    stop();
    delay(4000);
    lcd.clear();
    rot_360();
    forward();
    rotatedOnce = true;
  }
}




void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
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