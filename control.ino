#include <Servo.h>

byte C4 = 3;
byte C2 = 5;
byte C5 = 11;

float V4;
float V2;
float V5;
 
Servo S;
Servo TR;
Servo TL;

 
void setup() {
  pinMode(C4, INPUT);
  pinMode(C2, INPUT);
  pinMode(C5, INPUT);
  S.attach(6);
  TR.attach(9);
  TL.attach(10);
  TR.writeMicroseconds(1500);
  TL.writeMicroseconds(1500);
  delay(1000);
  Serial.begin(9600);
}

void ReadValues () {
  V4 = pulseIn(C4, HIGH);
  V2 = pulseIn(C2, HIGH);
  V5 = pulseIn(C5, HIGH);
}

void Select () {
  if (V5 > 1650){
    MoveDP();
  }
  else if (V5 < 1350) {
    MoveS();
  }
  else if (V5 > 1350 & V5 < 1650){
    Vision();
  }
}

void MoveDP (){
  float y;
  float R;
  float L;
  float x;
  if ((V4 > 1470 & V4 < 1515) & (V2 > 1470 & V2 < 1515)){
    TR.writeMicroseconds(1500);
    TL.writeMicroseconds(1500);
  }
  else if ((V4 > 1470 & V4 < 1515) & (V2 < 1470 || V2 > 1515)) {
    TR.writeMicroseconds(map(V2, 988, 2012, 1100, 1900));
    TL.writeMicroseconds(map(V2, 988, 2012, 1100, 1900));
  }
  else if ((V4 < 1470 || V4 > 1515) & (V2 > 1470 & V2 < 1515)) {
    R=map(V4, 975, 2025, 1900, 1100);
    L=map(V4, 975, 2025, 1100, 1900);
    TR.writeMicroseconds(R);
    TL.writeMicroseconds(L);
  }
  else if ((V4 < 1470) & (V2 < 1470 || V2 > 1515)) {
    y = (V2-(V2-1500)*(1500-V4)/525);
    R=map(V2, 975, 2025, 1100, 1900);
    L=map(y, 975, 2025, 1100, 1900);
    TR.writeMicroseconds(R);
    TL.writeMicroseconds(L);
  }
  else if ((V4 > 1515) & (V2 < 1470 || V2 > 1515)) {
    y = (V2-(V2-1500)*(V4-1500)/525);
    R=map(y, 975, 2025, 1100, 1900);
    L=map(V2, 975, 2025, 1100, 1900);
    TR.writeMicroseconds(R);
    TL.writeMicroseconds(L);
  }
}

void MoveS (){
  if (V4 > 1470 & V4 < 1530){
    S.write(90);
  }
  else {
    S.write(map(V4, 2000, 950, 0, 180));
  }
  if (V2 > 1470 & V2 < 1515) {
    TR.writeMicroseconds(1500);
    TL.writeMicroseconds(1500);
  }
  else {
    TR.writeMicroseconds(map(V2, 988, 2012, 1100, 1900));
    TL.writeMicroseconds(map(V2, 988, 2012, 1100, 1900));
  }
}

void Vision (){
  
}

void loop() {
  ReadValues();
  Select();
}
