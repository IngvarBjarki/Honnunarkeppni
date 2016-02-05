//afram haegri gradur 80->40
//afram vinstri gradur 80->100

#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h>

#define PING_PIN4 4 //ljosastaur
#define PING_PIN5 5 //framanhaegri
#define PING_PIN6 7 //framanmidja
#define PING_PIN7 8 //framanvinstri
#define PING_PIN8 9 //vinstri
#define PING_PIN9 10 // aftanvinstri
#define PING_PIN10 11 //aftanhaegri

unsigned int duration,Sensorljosastaur,Sensorframanhaegri,Sensorframanhaegriold,Sensorframanmidja,Sensorframanmidjaold,Sensorframanvinstri,Sensorframanvinstriold,Sensorvinstri, Sensorvinstriold,Sensoraftanvinstri, Sensoraftanvinstriold, Sensoraftanhaegri, Sensoraftanhaegriold, Sensor6old; 

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

Adafruit_DCMotor *myMotor = AFMS.getMotor(4);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(1);
Adafruit_DCMotor *lokMotor = AFMS.getMotor(3);

void setup() 
{
  Serial.begin(9600);          
  AFMS.begin(2000);
  delay(30);
  servoarmur.attach(9);  
  servobeygja.attach(10);  
  delay(15);
  servoarmur.write(130);
  delay(15);
  myMotor->setSpeed(70);
  myMotor2->setSpeed(70);
  myMotor->run(FORWARD);
  myMotor2->run(FORWARD);
  
//keyra afram i byrjun
  while(1)
  {
        Serial.println("servo armur");
        Serial.println(servoarmur.read());
        Serial.println("while lykkja 1");
        delay(35); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonarvinstri.ping();// Send ping, get ping time in microseconds 
        Sensorvinstri = duration/US_ROUNDTRIP_CM;// convert time into distance
//Servo stilltur aðeins til vinstri
        servobeygja.write(88);              // tell servo to go to position in variable 'pos'
        Serial.println("servobeygja is");
        Serial.println(servobeygja.read());
//skynjar sulu+raudan takka

        if (Sensorvinstri <40 && Sensorvinstri>5 && Sensorvinstriold<40 && Sensorvinstriold>5) 
            {
            //Stoppar
            myMotor->setSpeed(0);
            myMotor2->setSpeed(0);            
            servoarmur.write(125);
            Serial.println("vinstri sensor");
            Serial.println(Sensorvinstri);
            //skrifar 40 gradur á servoinn til að geta beygt og bakkað
            servobeygja.write(35);
            //Bakkar
            delay(25);
            myMotor->setSpeed(90);
            myMotor2->setSpeed(90);
            myMotor->run(BACKWARD);
            myMotor2->run(BACKWARD);
            delay(250);
            break;
            }
            Sensorvinstriold=Sensorvinstri;
    }
    
    while(1){
      //beygir thar til skynjar takka ad framan
        Serial.println("while lykkja 2");
        Serial.println("servo armur");
        Serial.println(servoarmur.read());
        delay(40); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonarframanhaegri.ping();// Send ping, get ping time in microseconds 
        Sensorframanhaegri = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonarframanmidja.ping();// Send ping, get ping time in microseconds 
        Sensorframanmidja = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonarframanvinstri.ping();// Send ping, get ping time in microseconds 
        Sensorframanvinstri = duration/US_ROUNDTRIP_CM;// convert time into distance
        Serial.println("Sensorframanhaegri");
        Serial.println(Sensorframanhaegri);
        Serial.println("Sensorframanmidja");
        Serial.println(Sensorframanmidja);
        Serial.println("Sensorframanvinstri");
        Serial.println(Sensorframanvinstri);
                 
//Ef skynjar súlu með takka í minna en 60 cm fjarlægð
        if(Sensorframanvinstri <60 && Sensorframanvinstri >5 && Sensorframanvinstriold <60 && Sensorframanvinstriold >5 && Sensorframanmidja <60 && Sensorframanmidja >5 && Sensorframanmidjaold <60 && Sensorframanmidjaold >5){
            Serial.println("Sensorframanhaegri");
            Serial.println(Sensorframanhaegri);
            Serial.println("Sensorframanhaegriold");
            Serial.println(Sensorframanhaegriold);
            Serial.println("Sensorframanmidja");
            Serial.println(Sensorframanmidja);
            Serial.println("Sensorframanmidjaold");
            Serial.println(Sensorframanmidjaold);
            Serial.println("Sensorframanvinstri");
            Serial.println(Sensorframanvinstri);
            Serial.println("Sensorframanvinstriold");
            Serial.println(Sensorframanvinstriold);
            //stoppar
            myMotor->setSpeed(0);
            myMotor2->setSpeed(0);
            servoarmur.write(126);
            delay(25);
            //skrifar 80 gráður á servoinn til að fara beint
            servobeygja.write(80);
            delay(1000);
            break;
          }
          //geymum gamalt gildi á skynjurum til að bera saman við ný gildi
          Sensorframanhaegriold=Sensorframanhaegri;
          Sensorframanmidjaold=Sensorframanmidja;
          Sensorframanvinstriold=Sensorframanvinstri;
    }

  while(1){
        //keyrir i att ad takka
        Serial.println("while lykkja 3");
        //notum skynjara að framan
        delay(40); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonarframanhaegri.ping();// Send ping, get ping time in microseconds 
        Sensorframanhaegri = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonarframanmidja.ping();// Send ping, get ping time in microseconds 
        Sensorframanmidja = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonarframanvinstri.ping();// Send ping, get ping time in microseconds 
        Sensorframanvinstri = duration/US_ROUNDTRIP_CM;// convert time into distance

//keyrum beint áfram í átt að takka
        myMotor->setSpeed(70);
        myMotor2->setSpeed(70);
        myMotor->run(FORWARD);
        myMotor2->run(FORWARD);
        Serial.println(Sensorframanhaegri);
        Serial.println(Sensorframanmidja);
        Serial.println(Sensorframanvinstri);

//stoppum ef einhver skynjari er kominn nógu nálægt rauða takkanum
        if(Sensorframanhaegri <10 && Sensorframanhaegri >1 && Sensorframanhaegriold <10 && Sensorframanhaegriold >1 || Sensorframanmidja <10 && Sensorframanmidja >1 && Sensorframanmidjaold <10 && Sensorframanmidjaold >1 || Sensorframanvinstri<10 && Sensorframanvinstri>1 && Sensorframanvinstriold<10 && Sensorframanvinstriold>1){
          delay(150);
          Serial.println(Sensorframanhaegri);
          Serial.println(Sensorframanmidja);
          Serial.println(Sensorframanvinstri);
          //stoppum
          myMotor->setSpeed(0);
          myMotor2->setSpeed(0);
          servoarmur.write(127);

          //bíðum í 2 sek eftir að boltar fara oní 
          delay(1500);
          delay(25);
          break;
      }
          Sensorframanhaegriold=Sensorframanhaegri;
          Sensorframanmidjaold=Sensorframanmidja;
          Sensorframanvinstriold=Sensorframanvinstri;
  }


  while(1){
    //bakkar fra takka
      Serial.println("while lykkja 4");
      servoarmur.write(130);

   

//notum skynjara 2-5 sem eru allir skynjararnir að framan
      delay(40); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delay
      duration = sonarframanhaegri.ping();// Send ping, get ping time in microseconds 
      Sensorframanhaegri = duration/US_ROUNDTRIP_CM;// convert time into distance
      duration = sonarframanmidja.ping();// Send ping, get ping time in microseconds 
      Sensorframanmidja = duration/US_ROUNDTRIP_CM;// convert time into distance
      duration = sonarframanvinstri.ping();// Send ping, get ping time in microseconds 
      Sensorframanvinstri = duration/US_ROUNDTRIP_CM;// convert time into distance
//bökkum
      myMotor->setSpeed(70);
      myMotor2->setSpeed(70);
      myMotor->run(BACKWARD);
      myMotor2->run(BACKWARD);
      
      Serial.println(Sensorframanhaegri);
      Serial.println(Sensorframanmidja);
      Serial.println(Sensorframanvinstri);
      
// skynjum suluna. passa ad ALLIR skynjarar seu lengra en 50cm fra sulu
        if(Sensorframanhaegri >30 && Sensorframanhaegriold >30 && Sensorframanmidja >30 && Sensorframanmidjaold >30 && Sensorframanvinstri>30  && Sensorframanvinstriold>30){
        Serial.println(Sensorframanhaegri);
        Serial.println(Sensorframanmidja);
        Serial.println(Sensorframanvinstri);
        //stoppum
        myMotor->setSpeed(0);
        myMotor2->setSpeed(0);
        delay(1000);
        //setjum servoinn í 35 til ad beygja til haegri
        servobeygja.write(40);
        delay(1000);
        //förum beint áfram í átt að vegg
        myMotor->setSpeed(65);
        myMotor2->setSpeed(65);
        myMotor->run(FORWARD);
        myMotor2->run(FORWARD);
        delay(1500);
        break;
    }
    Sensorframanhaegriold=Sensorframanhaegri;
    Sensorframanmidjaold=Sensorframanmidja;
    Sensorframanvinstriold=Sensorframanvinstri;
  }

  while(1){
      Serial.println("while lykkja 5");
      delay(40); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delay
      duration = sonarframanhaegri.ping();// Send ping, get ping time in microseconds 
      Sensorframanhaegri = duration/US_ROUNDTRIP_CM;// convert time into distance
      duration = sonarframanmidja.ping();// Send ping, get ping time in microseconds 
      Sensorframanmidja = duration/US_ROUNDTRIP_CM;// convert time into distance
      duration = sonarframanvinstri.ping();// Send ping, get ping time in microseconds 
      Sensorframanvinstri = duration/US_ROUNDTRIP_CM;// convert time into distance

      Serial.println(Sensorframanhaegri);
      Serial.println(Sensorframanmidja);
      Serial.println(Sensorframanvinstri);
      
        if(Sensorframanmidja <90 && Sensorframanmidja >5 && Sensorframanmidjaold <90 && Sensorframanmidjaold >5 && Sensorframanvinstri<90 && Sensorframanvinstri>5 && Sensorframanvinstriold<90 && Sensorframanvinstriold>5){
          Serial.println(Sensorframanhaegri);
          Serial.println(Sensorframanmidja);
          Serial.println(Sensorframanvinstri);
          //stoppum bílinn
          myMotor->setSpeed(0);
          myMotor2->setSpeed(0);
          delay(1000);
          //setjum servoinn í 60 gráður til að fara hægri
          servobeygja.write(65);
          delay(500);
          break;
          }
  }

  while(1){
      //keyrir ad vegg
          Serial.println("while lykkja 6");
          myMotor->setSpeed(70);
          myMotor2->setSpeed(70);
          myMotor->run(FORWARD);
          myMotor2->run(FORWARD);
          delay(40); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonarframanhaegri.ping();// Send ping, get ping time in microseconds 
        Sensorframanhaegri = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonarframanmidja.ping();// Send ping, get ping time in microseconds 
        Sensorframanmidja = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonarframanvinstri.ping();// Send ping, get ping time in microseconds 
        Sensorframanvinstri = duration/US_ROUNDTRIP_CM;// convert time into distance
          Serial.println(Sensorframanhaegri);
          Serial.println(Sensorframanmidja);
          Serial.println(Sensorframanvinstri);
          
        if(Sensorframanhaegri <50 && Sensorframanhaegri >5 && Sensorframanhaegriold <50 && Sensorframanhaegriold >5 && Sensorframanmidja <50 && Sensorframanmidja >5 && Sensorframanmidjaold <50 && Sensorframanmidjaold >5 || Sensorframanvinstri<50 && Sensorframanvinstri>5 && Sensorframanvinstriold<50 && Sensorframanvinstriold>5 && Sensorframanmidja <50 && Sensorframanmidja >5 && Sensorframanmidjaold <50 && Sensorframanmidjaold >5 || Sensorframanvinstri<50 && Sensorframanvinstri>5 && Sensorframanvinstriold<50 && Sensorframanvinstriold>5 && Sensorframanhaegri <50 && Sensorframanhaegri >5 && Sensorframanhaegriold <50 && Sensorframanhaegriold >5){
          myMotor->setSpeed(0);
          myMotor2->setSpeed(0);
          servobeygja.write(50);
          delay(100);
          myMotor->setSpeed(60);
          myMotor2->setSpeed(60);
          myMotor->run(FORWARD);
          myMotor2->run(FORWARD);
          break;
          }

          
}

}
//
void loop() {
  // put your main code here, to run repeatedly:

}
