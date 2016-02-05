//afram haegri gradur 30 <80
//afram vinstri gradur 100 > 80

#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h>

#define PING_PIN4 4 //ljosastaur
#define PING_PIN5 5 //framanhaegri
#define PING_PIN6 6 //framanmidja
#define PING_PIN7 7 //framanvinstri
#define PING_PIN8 8 //vinstri
#define PING_PIN9 11 // aftanvinstri
#define PING_PIN10 13 //aftanhaegri

unsigned int duration,Sensorljosastaur,Sensorframanhaegri,Sensorframanhaegriold,Sensorframanmidja,Sensorframanmidjaold,Sensorframanvinstri,Sensorframanvinstriold,Sensorvinstri, Sensorvinstriold,Sensoraftanvinstri, Sensoraftanvinstriold, Sensoraftanhaegri, Sensoraftanhaegriold, Sensor6old; 
unsigned long timataka, timi;
float hradafasti=1;
float timafasti=1;

NewPing sonarljosastaur(PING_PIN4, PING_PIN4);
NewPing sonarframanhaegri(PING_PIN5, PING_PIN5);
NewPing sonarframanmidja(PING_PIN6, PING_PIN6);
NewPing sonarframanvinstri(PING_PIN7, PING_PIN7);
NewPing sonarvinstri(PING_PIN8, PING_PIN8);
NewPing sonaraftanvinstri(PING_PIN9, PING_PIN9);
NewPing sonaraftanhaegri(PING_PIN10, PING_PIN10);

Servo servobeygja;
Servo servoarmur;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *myMotor = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(4);
Adafruit_DCMotor *lokMotor = AFMS.getMotor(2);

void setup() 
{
  Serial.begin(9600);          
  AFMS.begin(2000);
  delay(30);
  servoarmur.attach(9);  
  servobeygja.attach(10);  
  delay(15);
  servoarmur.write(120);
  delay(30);
  servobeygja.write(88);
  delay(30);
  timataka=millis();
  while(1){
    Serial.println("while lykkja 1");
    timi=millis()-timataka;
    //delay(50);
    //duration = sonaraftanhaegri.ping();// Send ping, get ping time in microseconds 
    //Sensoraftanhaegri = duration/US_ROUNDTRIP_CM;// convert time into 
    myMotor->setSpeed(80*hradafasti);
    myMotor2->setSpeed(80*hradafasti);
    myMotor->run(FORWARD);
    myMotor2->run(FORWARD);
    if(timi > 3500*timafasti){
             myMotor->setSpeed(0);
       myMotor2->setSpeed(0);
      delay(30);
      servobeygja.write(70);
      delay(30);
      break;
    }
  }
  timataka=millis();
  while(1){
    Serial.println("while lykkja 2");
        timi=millis()-timataka;
    myMotor->setSpeed(80*hradafasti);
    myMotor2->setSpeed(80*hradafasti);
    myMotor->run(FORWARD);
    myMotor2->run(FORWARD);
    if(timi > 1500*timafasti){
       myMotor->setSpeed(0);
       myMotor2->setSpeed(0);
      delay(30);
      servobeygja.write(80);
      delay(30);
      break;
    }
  }

  while(1){
    Serial.println("while lykkja 3");
    myMotor->setSpeed(80*hradafasti);
    myMotor2->setSpeed(80*hradafasti);
    myMotor->run(FORWARD);
    myMotor2->run(FORWARD);
  }
  
  
    
  }
void loop() {
  // put your main code here, to run repeatedly:

}
