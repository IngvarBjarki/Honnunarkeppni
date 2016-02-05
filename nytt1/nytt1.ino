

//afram haegri gradur 30 <70
//afram vinstri gradur 100 > 70
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h>

#define trigPin1 8
 #define echoPin1 9

#define trigPin2 2
#define echoPin2 3

#define trigPin3 4
#define echoPin3 5

#define trigPin4 6
#define echoPin4 7

#define trigPin5 10
#define echoPin5 11

#define trigPin6 12
#define echoPin6 13

long duration, distance, Sensor1,Sensor2,Sensor3,Sensor4,Sensor5,Sensor6;
unsigned long timeToMovieFw, timeToTurn;

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
    pinMode(trigPin4, OUTPUT);
    pinMode(echoPin4, INPUT);
    pinMode(trigPin5, OUTPUT);
    pinMode(echoPin5, INPUT);
    pinMode(trigPin6, OUTPUT);
    pinMode(echoPin6, INPUT);

  AFMS.begin(2000);  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  //delay(30);
  myservo.attach(10);  // attaches the servo on pin 9 to the servo

  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(70);
  myMotor2->setSpeed(70);
  myMotor->run(FORWARD);
  myMotor2->run(FORWARD);
  // turn on motor


  int servoinn;

//keyra afram i byrjun
  while(1){

        Serial.println("while lykkja 1");

        SonarSensor(trigPin6, echoPin6);
        Sensor6 = distance;

        myservo.write(70);              // tell servo to go to position in variable 'pos'
        servoinn = myservo.read();

        Serial.println("myservo is");
        Serial.println(servoinn);

//skynjar sulu+raudan takka
        if (Sensor6 < 35) {
            delay(500);
            myMotor->setSpeed(0);
            myMotor2->setSpeed(0);
            Serial.println("vinstri sensor");
            Serial.println(Sensor6);

            myservo.write(30);
            delay(15);
            break;

            }
    }

    while(1){
      //beygir thar til skynjar takka ad framan
         Serial.println("while lykkja 2");
          SonarSensor(trigPin2, echoPin2);
          Sensor2 = distance;
          myMotor->run(BACKWARD);
          myMotor2->run(BACKWARD);
          myMotor->setSpeed(60);
          myMotor2->setSpeed(60);


          Serial.println(Sensor2);
          if(Sensor2 <40){
            delay(500);
            Serial.println("sensor2");
            Serial.println(Sensor2);

            myMotor->setSpeed(0);
            myMotor2->setSpeed(0);

            delay(25);
             myservo.write(70);
            delay(505);
            break;
          }
    }

    while(1){
      //keyrir i att ad takka
   Serial.println("while lykkja 3");
   SonarSensor(trigPin1, echoPin1);
    Sensor1 = distance;
    SonarSensor(trigPin2, echoPin2);
    Sensor2 = distance;
    SonarSensor(trigPin3, echoPin3);
    Sensor3 = distance;

    SonarSensor(trigPin4, echoPin4);
    Sensor4 = distance;

    myMotor->run(FORWARD);
    myMotor2->run(FORWARD);
    myMotor->setSpeed(70);
    myMotor2->setSpeed(70);

    Serial.println(Sensor2);




          if(Sensor2 <5 || Sensor3 < 5 ||Sensor1 < 5 ||Sensor4 < 5 ){
               Serial.println("sensor1");
               Serial.println(Sensor1);

              Serial.println(" sensor2");
              Serial.println(Sensor2);

               Serial.println("sensor3");
               Serial.println(Sensor3);

               Serial.println("sensor4");
               Serial.println(Sensor4);

              myMotor->setSpeed(0);
              myMotor2->setSpeed(0);


          delay(25);
          myservo.write(120);
          delay(505);
          break;
      }
}

unsigned long startTimeBw = millis();

while(1){
      //bakkar fra takka
   Serial.println("while lykkja 4");
    timeToMovieFw = millis() - startTimeBw;

    SonarSensor(trigPin1, echoPin1);
    Sensor1 = distance;
    SonarSensor(trigPin2, echoPin2);
    Sensor2 = distance;
    SonarSensor(trigPin3, echoPin3);
    Sensor3 = distance;

    SonarSensor(trigPin4, echoPin4);
    Sensor4 = distance;

    myMotor->run(BACKWARD);
    myMotor2->run(BACKWARD);
    myMotor->setSpeed(65);
    myMotor2->setSpeed(65);

    Serial.println(Sensor2);
    Serial.println("timeToMOvie");
    Serial.println(timeToMovieFw);

    if(Sensor1>60 &&Sensor2>60&&Sensor3>60&&Sensor4>60&&Sensor4<120 && (timeToMovieFw > 2600 && timeToMovieFw < 4000 ) ){
       //delay(1500);
        Serial.print(Sensor1);
        Serial.print("  virkar ");
        Serial.print(Sensor2);
        Serial.print("   ");
        Serial.println(Sensor3);
        Serial.print("   ");
        Serial.print(Sensor4);
        Serial.print("   ");
        Serial.print(Sensor5);
        Serial.print("   ");
        Serial.println(Sensor6);
        Serial.println(" sensor4");
        Serial.println(Sensor4);

        myMotor->setSpeed(0);
        myMotor2->setSpeed(0);
        delay(25);
        myservo.write(70);
        delay(505);
        break;
    }
}
//double floor;
double gradur;
startTimeBw = millis();
while(1){
      //keyrir i att ad vegg
      reynaaftur:
      timeToTurn = millis() - startTimeBw;

      Serial.println("while lykkja 5");
      SonarSensor(trigPin4, echoPin4);
      Sensor4 = distance;
      SonarSensor(trigPin3, echoPin3);
      Sensor3 = distance;
      SonarSensor(trigPin2, echoPin2);
      Sensor2 = distance;

      myMotor->run(FORWARD);
      myMotor2->run(FORWARD);
      myMotor->setSpeed(70);
      myMotor2->setSpeed(70);

      Serial.println(Sensor2);
      delay(2000);

      if(timeToTurn>1500){
            gradur = floor(4*(timeToTurn-3000)/1000);
            Serial.println(70+gradur);
             myservo.write(70+gradur);
              //delay(15);
      }

          Serial.println("i att ad vegg sensor 4:");
          Serial.println(Sensor4);



         if( Sensor3 <40 || Sensor2 < 40  /*|| Sensor3 < 4  */ ){

              Serial.println(" sensor4");
              Serial.println(Sensor4);
              Serial.println(" sensor3");
              Serial.println(Sensor3);

              myMotor->setSpeed(0);
              myMotor2->setSpeed(0);
              delay(25);
              myservo.write(35);
              delay(505);
              break;
              }
        else if(Sensor4 >130){
              myservo.write(50);
              delay(15);
              if(Sensor4 <120){
                  myservo.write(70);
                  delay(15);
                  goto reynaaftur;
              }
          }
}

while(1){
      //beygir til haegri fra vegg
          Serial.println("while lykkja 6");
          SonarSensor(trigPin4, echoPin4);
          Sensor4 = distance;
          SonarSensor(trigPin3, echoPin3);
          Sensor3 = distance;

          myMotor->run(FORWARD);
          myMotor2->run(FORWARD);
          myMotor->setSpeed(60);
          myMotor2->setSpeed(60);

          Serial.println(Sensor2);
          delay(3000);


          Serial.println(" sensor4");
          Serial.println(Sensor4);
          Serial.println(" sensor3");
          Serial.println(Sensor3);

          myMotor->setSpeed(0);
          myMotor2->setSpeed(0);
          delay(25);
          myservo.write(100);
          delay(505);
//beygir til vinstri,kominn framhja veggjum
          myMotor->run(FORWARD);
          myMotor2->run(FORWARD);
          myMotor->setSpeed(70);
          myMotor2->setSpeed(70);
          delay(2000);
          break;


}


              /*
              //nyjasta:
              else if(LeftSensor > 100){

                  delay(25);
                  myservo.write(100);
                  delay(505);
                  myMotor->run(FORWARD);
                  myMotor2->run(FORWARD);
                  myMotor->setSpeed(70);
                  myMotor2->setSpeed(70);

                  if(LeftSensor <80){
                       goto reynaaftur;
                  }
              }
          //nyjasta
          reynaaftur: */

    }






    void loop() {
      /*
    SonarSensor(trigPin1, echoPin1);
    LeftSensor = distance;
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
