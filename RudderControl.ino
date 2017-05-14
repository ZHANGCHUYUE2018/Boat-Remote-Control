#include <Servo.h>

byte C4 = 3;
byte C2 = 5;

int V4;
int V2;
 
Servo S1;
Servo S2;
Servo T;

 
void setup() {
  pinMode(C4, INPUT);
  pinMode(C2, INPUT);
  S1.attach(6);
  S2.attach(9);
  T.attach(10);
  T.writeMicroseconds(1500);
  delay(1000);
  Serial.begin(9600);
}
 
void ReadValues () {
  V4 = pulseIn(C4, HIGH);
  V2 = pulseIn(C2, HIGH);
  Serial.println(V4);
  Serial.println(V2);
}

void Move (){
  if (V4 > 1470 & V4 < 1500){
    S1.write(90);
    S2.write(90);
  }
  else {
    S1.write(map(V4, 2000, 950, 0, 180));
    S2.write(map(V4, 2000, 950, 0, 180));
  }
  if (V2 > 1470 & V2 < 1515) {
    T.writeMicroseconds(1500);
  }
  else {
    T.writeMicroseconds(map(V2, 988, 2012, 1100, 1900));
  }
}

void loop() {
  ReadValues();
  Move();
}
