#define enA 3
#define in1 4
#define in2 5
#define outA 6
#define outB 7
#define PI 3.1415926536

void setMotor(int speed);
void driveTime(int speed, int ms);
void driveDistance(int speed, double mm);
void increment();
void reset();

volatile int count = 0;
double kWheelDiameter = 5.0; // in millimeters
double kCountsPerRevolution = 960.0;
double kDistancePerCount = (PI * kWheelDiameter) / kCountsPerRevolution; // in millimeters


void setup() {
  // Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(outA, INPUT);
  pinMode(outB, INPUT);
  reset();
}

void loop() {
  
}

void setMotor(int speed) {
  // Serial.println("Called setMotor(" + speed + ")");
  analogWrite(enA, speed);
}

void driveTime(int speed, int ms) {
  // Serial.println("Called driveTime(" + speed + ", " + ms + ")");
  setMotor(speed);
  unsigned long referenceTime = millis();
  while (millis() - referenceTime < ms);
  reset();
}

void driveDistance(int speed, double mm) {
  // Serial.println("Called driveDistance(" + speed + ", " + mm + ")");
  attachInterrupt(outB, increment, RISING);
  setMotor(speed);
  double currentDistance = count * kDistancePerCount;
  double targetDistance = currentDistance + mm;
  while (currentDistance < targetDistance);
  detachInterrupt(outB);
  reset();
}

void increment() {
  detachInterrupt(outB);
  count++;
  attachInterrupt(outB, increment, RISING);
}

void reset() {
  // Serial.println("Called reset()");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 0);
}