
//afram haegri gradur 30 <70
//afram vinstri gradur 100 > 70

#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h>


#define PING_PIN1 4 // Arduino pin for both trig and echo
#define PING_PIN2 5 // Arduino pin for both trig and echo
#define PING_PIN3 6
#define PING_PIN4 7
#define PING_PIN5 8
#define PING_PIN6 9
#define PING_PIN7 13

unsigned int duration,Sensor1,Sensor2,Sensor3,Sensor4,Sensor5,Sensor6,Sensor7,Sensor2old, Sensor3old, Sensor4old, Sensor5old; 
unsigned long timeToMovieFw, timeToTurn;

NewPing sonar1(PING_PIN1, PING_PIN1 );
NewPing sonar2(PING_PIN2, PING_PIN2 );
NewPing sonar3(PING_PIN3, PING_PIN3 );
NewPing sonar4(PING_PIN4, PING_PIN4 );
NewPing sonar5(PING_PIN5, PING_PIN5 );
//NewPing sonar6(PING_PIN6, PING_PIN6 );
NewPing sonar7(PING_PIN7, PING_PIN7 );

Servo myservo;
Servo myservo2;

     // Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(4);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(1);
Adafruit_DCMotor *lokMotor = AFMS.getMotor(3);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);


void setup() {
 Serial.begin(9600);           // set up Serial library at 9600 bps
  
  AFMS.begin(2000);  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  //delay(30);
 myservo2.attach(9);  // attaches the servo on pin 9 to the servo object

  myservo.attach(10);  // attaches the servo on pin 9 to the servo
  delay(15);
myservo2.write(100);
delay(15);
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(70);
  myMotor2->setSpeed(70);
  myMotor->run(FORWARD);
  myMotor2->run(FORWARD);

    int servoinn;

    //keyra afram i byrjun
  while(1){

        Serial.println("while lykkja 1");
        delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay

        duration = sonar5.ping();// Send ping, get ping time in microseconds 
        Sensor5 = duration/US_ROUNDTRIP_CM;// convert time into distance
    //    duration = sonar6.ping();// Send ping, get ping time in microseconds 
      //  Sensor6 = duration/US_ROUNDTRIP_CM;// convert time into distance

        myservo.write(80);              // tell servo to go to position in variable 'pos'
        servoinn = myservo.read();

        Serial.println("myservo is");
        Serial.println(servoinn);

//skynjar sulu+raudan takka
        if (/*Sensor6 < 35 && Sensor6 != 0 && */Sensor5 <35 && Sensor5 != 0 && Sensor5old<35 && Sensor5old!=0) {
            delay(500);
            myMotor->setSpeed(0);
            myMotor2->setSpeed(0);
            Serial.println("vinstri sensor");
            Serial.println(Sensor6);

            myservo.write(40);
            delay(15);
            break;

            }
            Sensor5old=Sensor5;
    }
    while(1){
      //beygir thar til skynjar takka ad framan
         Serial.println("while lykkja 2");
          delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonar2.ping();// Send ping, get ping time in microseconds 
        Sensor2 = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonar3.ping();// Send ping, get ping time in microseconds 
        Sensor3 = duration/US_ROUNDTRIP_CM;// convert time into distance

          /*SonarSensor(trigPin2, echoPin2);
          Sensor2 = distance;*/
          myMotor->run(BACKWARD);
          myMotor2->run(BACKWARD);
          myMotor->setSpeed(70);
          myMotor2->setSpeed(70);


          Serial.println(Sensor2);
          if(Sensor2 <40&& Sensor2 !=0 && Sensor2old <40&& Sensor2old !=0 || Sensor3<40&& Sensor3!=0&& Sensor3old<40&& Sensor3old!=0){
            delay(500);
            Serial.println("sensor2");
            Serial.println(Sensor2);
            Serial.println("sensor3");
            Serial.println(Sensor3);

            myMotor->setSpeed(0);
            myMotor2->setSpeed(0);

            delay(25);
             myservo.write(80);
            delay(505);
            break;
          }
          Sensor2old=Sensor2;
          Sensor3old=Sensor3;
          //Sensor4old=Sensor4
    }

  while(1){
      //keyrir i att ad takka
   Serial.println("while lykkja 3");
        delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonar2.ping();// Send ping, get ping time in microseconds 
        Sensor2 = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonar3.ping();// Send ping, get ping time in microseconds 
        Sensor3 = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonar4.ping();// Send ping, get ping time in microseconds 
        Sensor4 = duration/US_ROUNDTRIP_CM;// convert time into distance


    myMotor->run(FORWARD);
    myMotor2->run(FORWARD);
    myMotor->setSpeed(70);
    myMotor2->setSpeed(70);

    Serial.println(Sensor2);




          if(Sensor2 <5 && Sensor2 !=0 || Sensor3 < 5 && Sensor3 !=0 ||Sensor4 < 5 &&Sensor4!=0 ){
               /*Serial.println("sensor1");
               Serial.println(Sensor1);*/

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

    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonar2.ping();// Send ping, get ping time in microseconds 
        Sensor2 = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonar3.ping();// Send ping, get ping time in microseconds 
        Sensor3 = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonar4.ping();// Send ping, get ping time in microseconds 
        Sensor4 = duration/US_ROUNDTRIP_CM;// convert time into distance

    myMotor->run(BACKWARD);
    myMotor2->run(BACKWARD);
    myMotor->setSpeed(65);
    myMotor2->setSpeed(65);

    Serial.println(Sensor2);
    Serial.println("timeToMOvie");
    Serial.println(timeToMovieFw);

    if(Sensor2>60&&Sensor3>60&&Sensor4>60&&Sensor4<120 && (timeToMovieFw > 2600 /*&& timeToMovieFw < 4000*/ ) ){
       //delay(1500);
        Serial.print(Sensor2);
        Serial.print("   ");
        Serial.println(Sensor3);
        Serial.print("   ");
        Serial.print(Sensor4);

        myMotor->setSpeed(0);
        myMotor2->setSpeed(0);
        delay(25);
        myservo.write(80);
        delay(505);
        break;
    }
  }

  startTimeBw = millis();
  while(1){
      //keyrir i att ad vegg
      Serial.println("while lykkja 5");
      reynaaftur:
      timeToTurn = millis() - startTimeBw;


        delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonar2.ping();// Send ping, get ping time in microseconds 
        Sensor2 = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonar3.ping();// Send ping, get ping time in microseconds 
        Sensor3 = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonar4.ping();// Send ping, get ping time in microseconds 
        Sensor4 = duration/US_ROUNDTRIP_CM;// convert time into distance


      myMotor->run(FORWARD);
      myMotor2->run(FORWARD);
      myMotor->setSpeed(70);
      myMotor2->setSpeed(70);

      Serial.println(Sensor2);
      //delay(2000);

          Serial.println("i att ad vegg sensor 4:");
          Serial.println(Sensor4);



         if( (Sensor2 < 40 && Sensor2!=0 && Sensor3 <40 && Sensor3!=0 ||  Sensor3 <40 && Sensor3!=0 && Sensor4 < 40 && Sensor4!=0) && timeToTurn>2000){

              Serial.println(" sensor4");
              Serial.println(Sensor4);
              Serial.println(" sensor3");
              Serial.println(Sensor3);

              myMotor->setSpeed(0);
              myMotor2->setSpeed(0);
              delay(25);
              myservo.write(45);
              delay(505);
              break;
              }
        else if(Sensor4 >130){
              myservo.write(60);
              delay(15);
              if(Sensor4 <120 && Sensor4!=0){
                  myservo.write(80);
                  delay(15);
                  goto reynaaftur;
              }
          }
  }
  
  while(1){
      //beygir til haegri fra vegg
          Serial.println("while lykkja 6");
          /*SonarSensor(trigPin4, echoPin4);
          Sensor4 = distance;
          SonarSensor(trigPin3, echoPin3);
          Sensor3 = distance;*/

          myMotor->run(FORWARD);
          myMotor2->run(FORWARD);
          myMotor->setSpeed(60);
          myMotor2->setSpeed(60);

          Serial.println(Sensor2);
          delay(3000);

          myMotor->setSpeed(0);
          myMotor2->setSpeed(0);
          delay(25);
          myservo.write(110);
          delay(505);
//beygir til vinstri,kominn framhja veggjum
          myMotor->run(FORWARD);
          myMotor2->run(FORWARD);
          myMotor->setSpeed(70);
          myMotor2->setSpeed(70);
          delay(2000);
          myMotor->setSpeed(0);
          myMotor2->setSpeed(0);
          break;


}

  
}

void loop() {
  // put your main code here, to run repeatedly:

}
