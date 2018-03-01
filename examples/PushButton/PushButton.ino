/*
 * Drive a servo by using a push button
 * Uses the Bounce2 library. This library can be installed using the library manager
 */
 
#include <Servo.h>
#include <SlowMotionServo.h>
#include <Bounce2.h>

SMSSmoothBounce myServo;
Bounce myButton;

const byte servoPin = 3;
const byte buttonPin = 4;
const byte ledPin = 13;

void setup()
{
  pinMode(ledPin, OUTPUT);
  /* when the button is pressed, the input is LOW */
  pinMode(buttonPin, INPUT_PULLUP);

  myButton.attach(buttonPin);
  /* scan interval for debounce */
  myButton.interval(5);

  myServo.setMin(800);
  myServo.setMax(2200);
  myServo.setSpeed(1.5);
  myServo.setInitialPosition(0.0);
  myServo.setPin(servoPin);
  digitalWrite(ledPin, HIGH);
}

void loop()
{
  static float servoTarget = 0.0;

  /* update the state of the button */
  myButton.update();
  /* update the position of the servo */
  SlowMotionServo::update();
  
  if (myServo.isStopped()) {
    digitalWrite(ledPin, LOW);
    if (myButton.fell()) {
      /* look at the button only when the servo is stopped */
      /* change the target */
      servoTarget = 1.0 - servoTarget;
      /* set the new target for the servo */
      myServo.goTo(servoTarget);
      digitalWrite(ledPin, HIGH);
    }
  }
}

