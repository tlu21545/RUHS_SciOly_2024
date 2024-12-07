#define enA 3 // right motor
#define enB 5 // left motor
#define in1 6
#define in2 7
#define in3 8
#define in4 9

#include <IRremote.h>
#define IR_BUTTON_0 22
#define IR_BUTTON_1 12
#define IR_BUTTON_2 24
#define IR_BUTTON_3 94
#define IR_BUTTON_4 8
#define IR_BUTTON_5 28
#define IR_BUTTON_6 90
#define IR_BUTTON_7 66
#define IR_BUTTON_8 82
#define IR_BUTTON_9 74
#define IR_RECEIVE_PIN 11

void setMotors(int speed);
void driveStraight(int ms, int speed);
void turn(int ms, int speed, int direction);
void sixYardDash();
void fourConeXDrill();
void resetRobot();

void setup() {
  // Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  resetRobot();
}

void loop() {
  if (IrReceiver.decode()) {
    IrReceiver.resume();
    int code = IrReceiver.decodedIRData.command;
    // Serial.println(code);
    switch (code) {
    case IR_BUTTON_1:
      // Serial.println("pressed button 1");
      sixYardDash();
      resetRobot();
      IrReceiver.stop();
      IrReceiver.begin(IR_RECEIVE_PIN);
      break;
    case IR_BUTTON_2:
      turn(5000, 255, 0);
      delay(500);
      turn(5000, 255, 1);
      IrReceiver.stop();
      IrReceiver.begin(IR_RECEIVE_PIN);
      break;
    case IR_BUTTON_3:
      IrReceiver.stop();
      IrReceiver.begin(IR_RECEIVE_PIN);
      break;
    case IR_BUTTON_4:
      IrReceiver.stop();
      IrReceiver.begin(IR_RECEIVE_PIN);
      break;
    case IR_BUTTON_5:
      IrReceiver.stop();
      IrReceiver.begin(IR_RECEIVE_PIN);
      break;
    case IR_BUTTON_6:
      IrReceiver.stop();
      IrReceiver.begin(IR_RECEIVE_PIN);
      break;
    case IR_BUTTON_7:
      IrReceiver.stop();
      IrReceiver.begin(IR_RECEIVE_PIN);
      break;
    case IR_BUTTON_8:
      IrReceiver.stop();
      IrReceiver.begin(IR_RECEIVE_PIN);
      break;
    case IR_BUTTON_9:
      // Serial.println("pressed button 9");
      fourConeXDrill();
      resetRobot();
      IrReceiver.stop();
      IrReceiver.begin(IR_RECEIVE_PIN);
      break;
    default:
      IrReceiver.stop();
      IrReceiver.begin(IR_RECEIVE_PIN);
      return;
    }
  }
}

void setMotors(int speed) {
  // Serial.println("setting motors");
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void driveStraight(int ms, int speed) {
  // Serial.println("starting drive straight");
  setMotors(speed);
  unsigned long referenceTime = millis();
  while (millis() - referenceTime < ms);
  resetRobot();
}

void turn(int ms, int speed, int direction) {
  // Serial.println("starting turn");
  switch (direction) {
    case 0:
      // Serial.println("reversing left");
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      break;
    case 1:
      // Serial.println("reversing right");
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      break;
  }
  
  setMotors(speed);
  unsigned long referenceTime = millis();
  while (millis() - referenceTime < ms);
  resetRobot();
}

void sixYardDash() {
  // Serial.println("started six yard dash");
  driveStraight(10000, 255);
  // Serial.println("ended six yard dash");
}

void fourConeXDrill() {
  // Serial.println("started four cone x drill");
  driveStraight(3500, 255);
  delay(500);
  turn(600, 255, 0);
  delay(500);
  driveStraight(5400, 255);
  delay(500);
  turn(600, 255, 1);
  delay(500);
  driveStraight(3500, 255);
  delay(500);
  turn(600, 255, 1);
  delay(500);   
  driveStraight(4000, 255);
  // Serial.println("ended four cone x drill");
}

void resetRobot() {
  // Serial.println("resetting robot");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}