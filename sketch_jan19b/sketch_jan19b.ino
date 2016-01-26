/*
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2
----> http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards



int pos = 0;    // variable to store the servo position

#define trigPin 12 // define the pins of your sensor
#define echoPin 13

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(1);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  myservo.attach(10);  // attaches the servo on pin 9 to the servo
  myservo.write(0);              // tell servo to go to position in variable 'pos'

  pinMode(trigPin, OUTPUT);// set the trig pin to output (Send sound waves)
  pinMode(echoPin, INPUT);// set the echo pin to input (recieve sound waves)

  AFMS.begin(2000);  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz


  
  /*
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(200);
   myMotor2->setSpeed(200);
  myMotor->run(FORWARD);
  myMotor2->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);
  myMotor2->run(RELEASE);
*/

  // turn on motor

}

  double startTime = millis(); // BUM TIL TIMA
  double currentTime;
void loop() {
  while(currentTime - startTime < 10000){
    currentTime = millis();
    Serial.println(currentTime);
  }
  //Serial.println("While lykkju er lokid");
 /* uint8_t i;
   long duration, distance; // start the scan
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); // delays are required for a succesful sensor operation.
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;// convert the distance to centimeters.
  if (distance < 33 && distance > 7) //if there's an obstacle 25 centimers, ahead, do the following:
  {


    Serial.println ("Close Obstacle detected!" );
    Serial.println ("Obstacle Details:");
    Serial.print ("Distance From Robot is " );
    Serial.print ( distance);
    Serial.print ( " CM!");// print out the distance in centimeters.
    Serial.println (" The obstacle is declared a threat due to close distance. ");
    Serial.println (" Turning !");
     myMotor->setSpeed(0);
     myMotor2->setSpeed(0);
   delay(5000);
    myservo.write(60);              // tell servo to go to position in variable 'pos'
    delay(1000);
    myMotor->setSpeed(200);
     myMotor2->setSpeed(200);
    myMotor->run(BACKWARD); //if there's no obstacle ahead, Go Forward!
    myMotor2->run(BACKWARD);
    myMotor->run(RELEASE);
  myMotor2->run(RELEASE);
    //myMotor->run(FORWARD);  // Turn as long as there's an obstacle ahead.
    //myMotor2->run(BACKWARD);
  }
    else if (distance <=7){
    Serial.println ("VERY Close Obstacle detected!" );
Serial.println ("Obstacle Details:");
Serial.print ("Distance From Robot is " );
Serial.print ( distance);
Serial.print ( " CM!");// print out the distance in centimeters.

  Serial.println (" The obstacle is declared a threat due to close distance. ");
  Serial.println (" going backwards!");
  myservo.write(0);              // tell servo to go to position in variable 'pos'

    myMotor->run(BACKWARD);  // go backwards as long as the obstacle is less than 7 cm away.
    myMotor2->run (BACKWARD);
    }
  else
  {
      myservo.write(0);              // tell servo to go to position in variable 'pos'

   Serial.println ("No obstacle detected. going forward");
   delay (2000);
   myMotor->run(FORWARD); //if there's no obstacle ahead, Go Forward!
    myMotor2->run(FORWARD);
  }
  */
}
