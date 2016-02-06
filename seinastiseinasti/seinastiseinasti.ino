#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h>


#define PING_PIN4 4 //ljosastaur
#define PING_PIN5 5 //framanhaegri
#define PING_PIN6 12 //framanmidja
#define PING_PIN7 7 //framanvinstri
#define PING_PIN8 8 //vinstri
#define PING_PIN9 11 // aftanvinstri
#define PING_PIN10 13 //aftanhaegri

unsigned int duration,Sensorljosastaur,Sensorframanhaegri,Sensorframanhaegriold,Sensorframanmidja,Sensorframanmidjaold,Sensorframanvinstri,Sensorframanvinstriold,Sensorvinstri, Sensorvinstriold,Sensoraftanvinstri, Sensoraftanvinstriold, Sensoraftanhaegri, Sensoraftanhaegriold, Sensor6old; unsigned long timeToMovieFw, timeToTurn;
int pushbutton = 3 ; // takki a hjolum
int pushbutton2 = 2; // her eru enginn hjol
int counter;

NewPing sonarljosastaur(PING_PIN4, PING_PIN4);
NewPing sonarframanhaegri(PING_PIN5, PING_PIN5);
NewPing sonarframanmidja(PING_PIN6, PING_PIN6);
NewPing sonarframanvinstri(PING_PIN7, PING_PIN7);
NewPing sonarvinstri(PING_PIN8, PING_PIN8);
NewPing sonaraftanvinstri(PING_PIN9, PING_PIN9);
NewPing sonaraftanhaegri(PING_PIN10, PING_PIN10);

Servo servobeygja;
Servo servoarmur;

     // Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(4);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(3);
Adafruit_DCMotor *lokMotor = AFMS.getMotor(2);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

void setup() {
 Serial.begin(9600);           // set up Serial library at 9600 bps
  
  AFMS.begin(2000);  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  //delay(30);
  
  pinMode(pushbutton, INPUT);
  pinMode(pushbutton2, INPUT);
    
servoarmur.attach(9);  // attaches the servo on pin 9 to the servo object

servobeygja.attach(10);  // attaches the servo on pin 9 to the servo
 
unsigned long timeToSenz, timeToSenz2;




servobeygja.write(80);
myMotor->setSpeed(90);
myMotor2->setSpeed(90);
myMotor->run(FORWARD);
myMotor2->run(FORWARD);
counter = 0;

do{
  delay(50);
    duration = sonarljosastaur.ping();// Send ping, get ping time in microseconds 
          Sensorljosastaur = duration/US_ROUNDTRIP_CM;
          
          duration = sonarframanhaegri.ping();// Send ping, get ping time in microseconds 
          Sensorframanhaegri = duration/US_ROUNDTRIP_CM;
          
          duration = sonarframanmidja.ping();// Send ping, get ping time in microseconds 
          Sensorframanmidja = duration/US_ROUNDTRIP_CM;
          
          duration = sonarframanvinstri.ping();// Send ping, get ping time in microseconds 
          Sensorframanvinstri = duration/US_ROUNDTRIP_CM;
          
          //faum hann rettan
          if(Sensorframanvinstri > Sensorframanhaegri + 2 && Sensorframanhaegri != 0 && Sensorframanvinstri!= 0){
          servobeygja.write(78);
          Serial.println("VINSTRI ER STARERI");
          }
          else if(Sensorframanhaegri > Sensorframanvinstri + 2 && Sensorframanhaegri != 0 && Sensorframanvinstri!= 0){
          servobeygja.write(83);
          Serial.println("HAEGRI ER STAERIII");
          }
          
          else if(abs(Sensorframanvinstri - Sensorframanhaegri) < 3 && Sensorframanhaegri != 0 && Sensorframanvinstri!= 0 ){
            counter++;
            servobeygja.write(80);  
            Serial.println("FIRST COUNTER!!!");
          }
  
}
while(counter < 2);



// finnum stad sem vid viljum keyra fra
myMotor->setSpeed(0);
myMotor2->setSpeed(0);

delay(50);
myMotor->setSpeed(70);
myMotor2->setSpeed(70);
myMotor->run(BACKWARD);
myMotor2->run(BACKWARD);
Serial.println("GOING BACKWARDS!!");

counter = 0;

do{
  delay(50);
    duration = sonarljosastaur.ping();// Send ping, get ping time in microseconds 
          Sensorljosastaur = duration/US_ROUNDTRIP_CM;
          
          duration = sonarframanhaegri.ping();// Send ping, get ping time in microseconds 
          Sensorframanhaegri = duration/US_ROUNDTRIP_CM;
          
          duration = sonarframanmidja.ping();// Send ping, get ping time in microseconds 
          Sensorframanmidja = duration/US_ROUNDTRIP_CM;
          
          duration = sonarframanvinstri.ping();// Send ping, get ping time in microseconds 
          Sensorframanvinstri = duration/US_ROUNDTRIP_CM;
          
          if(Sensorframanvinstri <= 122 && Sensorframanvinstri >118 && Sensorframanhaegri <= 122  && Sensorframanhaegri>118 ){
            counter++;
            Serial.println("WE ARE COUNTING, lefty");
            Serial.println(Sensorframanvinstri);
            Serial.println(Sensorframanhaegri);
          }
          else if(Sensorframanvinstri > 121 || Sensorframanhaegri > 121){
              servobeygja.write(83);

              myMotor->setSpeed(70);
              myMotor2->setSpeed(70);
              delay(80);
              myMotor->run(FORWARD);
              myMotor2->run(FORWARD);
               //delay(200);
            Serial.println("FORUM NAER1111111111");
            Serial.println(Sensorframanvinstri);
            Serial.println(Sensorframanhaegri);
            counter = 0;
} 

else if (Sensorframanvinstri<= 118 || Sensorframanhaegri<=118){
              servobeygja.write(77);
              myMotor->setSpeed(70);
              myMotor2->setSpeed(70);
              delay(10);
              myMotor->run(BACKWARD);
              myMotor2->run(BACKWARD);
               Serial.println("FORUM FAEr 2222222222222222222");
            Serial.println(Sensorframanvinstri);
            Serial.println(Sensorframanhaegri);
            counter = 0;

}
  
         
}
while(counter < 3);


myMotor->setSpeed(0);
myMotor2->setSpeed(0);

counter = 0;
servobeygja.write(91);
myMotor->setSpeed(90);
myMotor2->setSpeed(90);
myMotor->run(FORWARD);
myMotor2->run(FORWARD);



// her byrjum vid ad keyra boltann ofani
do{
  Serial.println("erum i dowhile 2");
  //if (timeToSenz2 % 50 == 0){    
   
  delay(50);
    duration = sonarljosastaur.ping();// Send ping, get ping time in microseconds 
          Sensorljosastaur = duration/US_ROUNDTRIP_CM;
          
          duration = sonarframanhaegri.ping();// Send ping, get ping time in microseconds 
          Sensorframanhaegri = duration/US_ROUNDTRIP_CM;
          
          duration = sonarframanmidja.ping();// Send ping, get ping time in microseconds 
          Sensorframanmidja = duration/US_ROUNDTRIP_CM;
          
          duration = sonarframanvinstri.ping();// Send ping, get ping time in microseconds 
          Sensorframanvinstri = duration/US_ROUNDTRIP_CM;
          
          Serial.println("TIME TO SENZ!!!");
          Serial.println(Sensorframanhaegri);
          Serial.println(Sensorframanmidja); 
          Serial.println(Sensorframanvinstri);
      
      if ((Sensorframanhaegri < 55 && Sensorframanhaegri > 15) && (Sensorframanmidja < 55  &&  Sensorframanmidja > 15 ) && (Sensorframanvinstri < 55  &&  Sensorframanvinstri > 15)&& Sensorframanvinstri != 0 && Sensorframanmidja != 0 && Sensorframanhaegri != 0){
      counter++;
      Serial.println("HER ER COUNTER");
      Serial.println(counter);
      }
        Serial.println(Sensorframanvinstri);
      }while((Sensorframanhaegri > 55 || Sensorframanhaegri < 15) && (Sensorframanmidja > 55 || Sensorframanmidja < 15 ) && (Sensorframanvinstri > 55 || Sensorframanvinstri < 15) && counter < 5 );
        
        myMotor->setSpeed(0);
        myMotor2->setSpeed(0);
        delay(1000);
        servobeygja.write(65);
        
        myMotor->setSpeed(90);
        myMotor2->setSpeed(90);
        myMotor -> run(FORWARD);
        myMotor2 -> run(FORWARD);
        counter = 0;
        
        do{
  Serial.println("erum i dowhile 2");
  if (timeToSenz2 % 50 == 0){
          duration = sonarljosastaur.ping();// Send ping, get ping time in microseconds 
          Sensorljosastaur = duration/US_ROUNDTRIP_CM;
          
          duration = sonarframanhaegri.ping();// Send ping, get ping time in microseconds 
          Sensorframanhaegri = duration/US_ROUNDTRIP_CM;
          
          duration = sonarframanmidja.ping();// Send ping, get ping time in microseconds 
          Sensorframanmidja = duration/US_ROUNDTRIP_CM;
          
          duration = sonarframanvinstri.ping();// Send ping, get ping time in microseconds 
          Sensorframanvinstri = duration/US_ROUNDTRIP_CM;
          
          Serial.println("TIME TO SENZ SEINNI PARTUR!!!");
        }
        Serial.println(Sensorframanvinstri);
        if(abs(Sensorframanvinstri - Sensorframanhaegri)<2)
        {
        counter++;
        }
      }while(counter < 2 );
    
servobeygja.write(80);    

        myMotor->setSpeed(150);
        myMotor2->setSpeed(150);
        myMotor -> run(FORWARD);
        myMotor2 -> run(FORWARD);

}
void loop(){}
