#include <Servo.h>

//Receiver arduino pins
const int pin4 = 4;
const int pin2 = 2;
const int pin3 = 3;
const int pin5 = 5;

//Receiver channels
float channel4;
float channel2;
float channel3;
float channel5;

//Servos and thrusters 
Servo servoRight;
Servo servoLeft;
Servo thrusterRearRight;
Servo thrusterRearLeft;
Servo thrusterFrontRight;
Servo thrusterFrontLeft;
 
void setup() {
  //Pin modes
  pinMode(pin4, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  pinMode(pin5, INPUT);
  servoRight.attach(6);
  servoLeft.attach(7);
  thrusterRearRight.attach(10);
  thrusterRearLeft.attach(11);
  thrusterFrontRight.attach(8);
  thrusterFrontLeft.attach(9);
  //Stop thrusters
  thrusterRearRight.writeMicroseconds(1500);
  thrusterRearLeft.writeMicroseconds(1500);
  thrusterFrontRight.writeMicroseconds(1500);
  thrusterFrontLeft.writeMicroseconds(1500);
  //Driver setup
  delay(1000);
  Serial.begin(9600);
}

void read_values () {
  //Read channel frequecies
  channel4 = pulseIn(pin4, HIGH);
  channel2 = pulseIn(pin2, HIGH);
  channel3 = pulseIn(pin3, HIGH);
  channel5 = pulseIn(pin5, HIGH);
}

void select(){
  //Use channel 5 to select current mode
  if (channel5 > 1600){
    Move();
  }
  else{
    vision();
  }
}

void Move (){ //Remote control movement
  if (channel4 > 1470 & channel4 < 1530){
    //Servos at the middle
    servoRight.write(90);
    servoLeft.write(90);
  }
  else {
    //Servo movement relation
    servoRight.write(map(channel4, 2000, 950, 0, 180));
    servoLeft.write(map(channel4, 2000, 950, 0, 180));
  }
  if (channel2 > 1470 & channel2 < 1530) {
    //Range to stop rear thrusters
    thrusterRearRight.writeMicroseconds(1500);
    thrusterRearLeft.writeMicroseconds(1500);
  }
  else {
    //Rear thrusters signal
    thrusterRearRight.writeMicroseconds(map(channel2, 988, 2012, 1100, 1900));
    thrusterRearLeft.writeMicroseconds(map(channel2, 988, 2012, 1100, 1900));
  }
  if (channel3 > 1470 & channel3 < 1530) {
    //Range to stop front thrusters
    thrusterFrontRight.writeMicroseconds(1500);
    thrusterFrontLeft.writeMicroseconds(1500);
  }
  else {
    //Front thrusters signal
    thrusterFrontRight.writeMicroseconds(map(channel3, 988, 2012, 1100, 1900));
    thrusterFrontLeft.writeMicroseconds(map(channel3, 988, 2012, 1100, 1900));
  }
}

void vision(){
  //Vision movement
}

void loop() {
  read_values();
  select();
}
