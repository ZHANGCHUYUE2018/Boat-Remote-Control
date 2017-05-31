#include <Servo.h>

byte C4 = 4;
byte C2 = 2;
byte C3 = 3;
byte C5 = 5;

float V4;
float V2;
float V3;
float V5;
 
Servo SR;
Servo SL;
Servo TRB;
Servo TLB;
Servo TRF;
Servo TLF;
 
void setup() {
  pinMode(C4, INPUT);
  pinMode(C2, INPUT);
  pinMode(C3, INPUT);
  SR.attach(6);
  SL.attach(7);
  TRB.attach(10);
  TLB.attach(11);
  TRF.attach(8);
  TLF.attach(9);
  TRB.writeMicroseconds(1500);
  TLB.writeMicroseconds(1500);
  TRF.writeMicroseconds(1500);
  TLF.writeMicroseconds(1500);
  delay(1000);
  Serial.begin(9600);
}

void ReadValues () {
  V4 = pulseIn(C4, HIGH);
  V2 = pulseIn(C2, HIGH);
  V3 = pulseIn(C3, HIGH);
  V5 = pulseIn(C5, HIGH);
}

void Select(){
  if (V5 > 1530){
    Move();
  }
  else if (V5 < 1470){
    Vision;
  }
}

void Move (){
  if (V4 > 1470 & V4 < 1530){
    SR.write(90);
    SL.write(90);
  }
  else {
    SR.write(map(V4, 2000, 950, 0, 180));
    SL.write(map(V4, 2000, 950, 0, 180));
  }
  if (V2 > 1470 & V2 < 1515) {
    TRB.writeMicroseconds(1500);
    TLB.writeMicroseconds(1500);
  }
  else {
    TRB.writeMicroseconds(map(V2, 988, 2012, 1100, 1900));
    TLB.writeMicroseconds(map(V2, 988, 2012, 1100, 1900));
  }
  if (V3 > 1470 & V3 < 1515) {
    TRF.writeMicroseconds(1500);
    TLF.writeMicroseconds(1500);
  }
  else {
    TRF.writeMicroseconds(map(V2, 988, 2012, 1100, 1900));
    TLF.writeMicroseconds(map(V2, 988, 2012, 1100, 1900));
  }
}

void Vision(){
  
}

void loop() {
  ReadValues();
  Select();
}
