#include <Servo.h>

byte C1 = 3;
byte C2 = 5;

int V1;
int V2;
 
Servo TR;
Servo TL;

 
void setup() {
  pinMode(C1, INPUT);
  pinMode(C2, INPUT);
  TR.attach(9);
  TL.attach(10);
  TR.writeMicroseconds(1500);
  TL.writeMicroseconds(1500);
  delay(1000);
  Serial.begin(9600);
}
 
void ReadValues () {
  V1 = pulseIn(C1, HIGH);
  V2 = pulseIn(C2, HIGH);
  Serial.println(V1);
  Serial.println(V2);
}

void Move (){
  int x;
  int y;
  if ((V1 > 1475 & V1 < 1515) & (V2 > 1475 & V2 < 1515)){
    TR.writeMicroseconds(1500);
    TL.writeMicroseconds(1500);
  }
  else if ((V1 > 1475 & V1 < 1515) & (V2 < 1475 || V2 > 1515)) {
    TR.writeMicroseconds(map(V2, 988, 2012, 1100, 1900));
    TL.writeMicroseconds(map(V2, 988, 2012, 1100, 1900));
  }
  else if ((V1 < 1475) & (V2 > 1475 & V2 < 1515)) {
    TR.writeMicroseconds(map(V1, 988, 2012, 1100, 1900));
    TL.writeMicroseconds(1500);
  }
  else if ((V1 > 1515) & (V2 > 1475 & V2 < 1515)) {
    TL.writeMicroseconds(map(V1, 988, 2012, 1100, 1900));
    TR.writeMicroseconds(1500);
  }
  else if ((V1 < 1475) & (V2 < 1475 || V2 > 1515)) {
    y = V2 - (V2 - 1500)*((1500-V1)/512);
    TR.writeMicroseconds(map(V2, 988, 2012, 1100, 1900));
    TL.writeMicroseconds(map(y, 988, 2012, 1100, 1900));
  }
  else if ((V1 > 1515) & (V2 < 1475 || V2 > 1515)) {
    y = V1 - (V1 - 1500)*((V2 - 1500)/512);
    TL.writeMicroseconds(map(V2, 988, 2012, 1100, 1900));
    TR.writeMicroseconds(map(y, 988, 2012, 1100, 1900));
  }
}

void loop() {
  ReadValues();
  Move();
}
