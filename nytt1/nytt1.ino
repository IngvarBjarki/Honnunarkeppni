
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h>

    #define trigPin1 12
    #define echoPin1 13
    #define trigPin2 10
    #define echoPin2 11
    #define trigPin3 8
    #define echoPin3 9
    long duration, distance, RightSensor,BackSensor,FrontSensor,LeftSensor;

    Servo myservo;

     // Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(1);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);


    void setup()
    {

    Serial.begin(9600);           // set up Serial library at 9600 bps

    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    pinMode(trigPin3, OUTPUT);
    pinMode(echoPin3, INPUT);

  myservo.attach(10);  // attaches the servo on pin 9 to the servo
  myservo.write(70);              // tell servo to go to position in variable 'pos'
  AFMS.begin(2000);  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(75);
  myMotor2->setSpeed(75);
  myMotor->run(FORWARD);
  myMotor2->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);
  myMotor2->run(RELEASE);

    while(1){

        Serial.println("while lykkja 1");
        myMotor->run(FORWARD);
        myMotor2->run(FORWARD);
        SonarSensor(trigPin2, echoPin2);
        LeftSensor = distance;

        if (LeftSensor < 50) {
            myMotor->setSpeed(0);
            myMotor2->setSpeed(0);
           /* delay(15);
            myservo.write(40);
            delay(15);*/
            for(int x = 0; x<31; x++){
              // fer fra 70 i 40
              myservo.write(70-x);
            }
            break;

            }
    }
    while(1){
         Serial.println("while lykkja 2");
          SonarSensor(trigPin1, echoPin1);
          FrontSensor = distance;
           myMotor->run(BACKWARD);
           myMotor2->run(BACKWARD);

          if(FrontSensor <60){
              myMotor->setSpeed(0);
              myMotor2->setSpeed(0);
              delay(15);
             myservo.write(70);
            delay(15);
            break;
          }
    }

    while(1){
         Serial.println("while lykkja 1");
          SonarSensor(trigPin1, echoPin1);
          FrontSensor = distance;
          myMotor->run(FORWARD);
          myMotor2->run(FORWARD);

          if(FrontSensor <3 || FrontSensor > 80 ){
              myMotor->setSpeed(0);
              myMotor2->setSpeed(0);
              break;
              }
          }
    }






    void loop() {
      /*
    SonarSensor(trigPin1, echoPin1);
    FrontSensor = distance;
    SonarSensor(trigPin2, echoPin2);
    LeftSensor = distance;
    SonarSensor(trigPin3, echoPin3);
    RightSensor = distance;
    */
    }


    void SonarSensor(int trigPin,int echoPin)
    {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;

    }
