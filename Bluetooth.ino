#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

int ENA = 3;
int IN1 = 1;
int IN2 = 2;
int IN3 = 13;
int IN4 = 12;
int ENB = 11;

SoftwareSerial bt(A2, A1);  

void setup() {
pinMode(ENA, OUTPUT);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
pinMode(ENB, OUTPUT);
pinMode(A2,INPUT);
pinMode(A1,OUTPUT);
bt.begin(9600);
}

void loop() {
if (bt.available()) { 
  char command = bt.read(); 
if (command == '1') { 
forward();
}
else if (command == '2') { 
reverse();
}
else if (command == '3') { 
turnleft();
}
else if (command == '4') { 
turnright();
}
else if (command == '0'){
stop();
}
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