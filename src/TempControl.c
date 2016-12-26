#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <Servo.h>

const int defaultTemp = 20;
const int lowServPositionPin = 0;
const int hightServPositionPin = 1;
const int servoPin = 2;

int currentServoPosition = 90;

Servo tempServo;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  tempServo.attach(servoPin);
  pinMode(lowServPositionPin, INPUT); // low position of serv
  pinMode(hightServPositionPin, INPUT); // hight position of serv
  delay(2000);
  Calibrate();
}

// the loop routine runs over and over again forever:
void loop() {
  int currentTemp = GetDefinedTemp();
  delay(1000);               // wait for a second
}

int GetDefinedTemp() {
  int currentTemp = EEPROM.read(0);
  if (currentTemp == 0) {
    EEPROM.write(0, defaultTemp);
    currentTemp = defaultTemp;
  }
  return currentTemp;
}

void TempCheck() {

}

void TempDown(int step) {
  ServControl(step, -1);
}

void TempUp(int step) {
  ServControl(step, 1);
}

void ServControl(int step, int type) {
  step *= type;
  currentServoPosition += step;
  if (currentServoPosition <= 0) {
    currentServoPosition = 0;
  }
  if (currentServoPosition >= 180) {
    currentServoPosition = 180;
  }
  tempServo.write(currentServoPosition);
  delay(15);
}

void Calibrate() {
  int lowPosition = digitalRead(lowServPositionPin);
  int hightPosition = digitalRead(hightServPositionPin);
  Serial.print("\n");
  Serial.print(lowPosition);
  for (size_t i = 0; i < 180; i++) {
    TempUp(1);
    if (lowPosition == HIGHT) {
      break;
    }
  }

  for (size_t i = 0; i < 180; i++) {
    TempDown(1);
    if (hightPosition == HIGHT) {
      break;
    }
  }
  currentServoPosition = 180;
}

void ButtonControl() {

}

void IndicatorAction(int temp) {

}

void MotorDuration(int speed) {

}

void MotorUp(int step) {

}

void MotorDown(int step) {

}
