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
  Serial.begin(57600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  pinMode(trigPin, OUTPUT);// set the trig pin to output (Send sound waves)
  pinMode(echoPin, INPUT);// set the echo pin to input (recieve sound waves)

  AFMS.begin(2000);  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(100);
   myMotor2->setSpeed(100);
  myMotor->run(FORWARD);
  myMotor2->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);
  myMotor2->run(RELEASE);
  
  
  // turn on motor
  
}

void loop() {
  uint8_t i;
   long duration, distance; // start the scan
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); // delays are required for a succesful sensor operation.
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;// convert the distance to centimeters.
  if (distance < 25)/*if there's an obstacle 25 centimers, ahead, do the following: */ 
  {   
    Serial.println ("Close Obstacle detected!" );
    Serial.println ("Obstacle Details:");
    Serial.print ("Distance From Robot is " );
    Serial.print ( distance);
    Serial.print ( " CM!");// print out the distance in centimeters.
    Serial.println (" The obstacle is declared a threat due to close distance. ");
    Serial.println (" Turning !");
    myMotor->run(FORWARD);  // Turn as long as there's an obstacle ahead.
    myMotor2->run(BACKWARD);
  }
  else 
  {
   Serial.println ("No obstacle detected. going forward");
   delay (15);
   myMotor->run(FORWARD); //if there's no obstacle ahead, Go Forward! 
    myMotor2->run(FORWARD);  
  }  
  
}
