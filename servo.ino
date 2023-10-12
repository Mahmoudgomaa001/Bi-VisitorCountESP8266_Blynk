// including the servo library
// #include <Servo.h>
// // declaring and defining myservo
// Servo in_Servo;
// Servo out_Servo;
// #define in_servo_Pin D1
// #define out_servo_Pin D2


// this variable holds the values that the servo will move
int Position;

void servoSetup() {
  // myservo is connected to PWM pin 9
  in_Servo.attach(in_servo_Pin);
  // in_Servo.attach(out_servo_Pin);
}

void moveServo(Servo myServo, int speed, int fromAngle, int toAngel) {

  if (fromAngle < toAngel) {
    for (int i = fromAngle; i < toAngel; i++) {
      myServo.write(Position);
      delay(speed);
    }

  } else {
    for (int i = fromAngle; i < toAngel; i--) {
      myServo.write(Position);
      delay(speed);
    }
  }
}
