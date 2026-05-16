#include <Servo.h>

const int FLAME_PIN     = A0;   //flame sensor
const int SCAN_SERVO_PIN = 9;   //servo for sensor
const int FAN_SERVO_PIN  = 10;  //servo for water pump
const int FAN_PIN        = 8;   // TIP122 base drive
Servo scanServo;
Servo fanServo;

const int PAN_MIN = 20;
const int PAN_MAX = 160;
int flameThreshold = 500;
int scanAngle      = PAN_MIN;
int scanDirection  = 1;
bool flameDetected = false;

void setup() {
  Serial.begin(9600);
  scanServo.attach(SCAN_SERVO_PIN);
  fanServo.attach(FAN_SERVO_PIN);
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);  
  scanServo.write(scanAngle);
  fanServo.write((PAN_MIN + PAN_MAX) / 2);
  Serial.println("Flame Tracking System Ready (TIP122)");
}

void loop() {
  int reading = analogRead(FLAME_PIN);
  if (reading > flameThreshold) {
    flameDetected = true;

    Serial.print("Flame detected at ");
    Serial.print(scanAngle);
    Serial.print(" deg | Value: ");
    Serial.println(reading);
    fanServo.write(scanAngle);S
    digitalWrite(FAN_PIN, HIGH);  
    delay(100);
  }
  else {
    flameDetected = false;
    digitalWrite(FAN_PIN, LOW);   
    scanServo.write(scanAngle);
    delay(30);
    scanAngle += scanDirection;

    if (scanAngle >= PAN_MAX || scanAngle <= PAN_MIN) {
      scanDirection = -scanDirection;
    }
  }
}