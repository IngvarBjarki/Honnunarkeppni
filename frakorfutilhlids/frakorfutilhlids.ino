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
  delay(35);
  //stillum servo thannig billinn keyrir aftur a bak i vinstri beygju 
 // servobeygja.write(80);
  delay(30);
  servobeygja.write(100);
  delay(30);
  
  timataka=millis();
  
  while(1){
    Serial.println("while lykkja eitt");
    timi=millis()-timataka;
    delay(50);
    duration = sonaraftanhaegri.ping();// Send ping, get ping time in microseconds 
    Sensoraftanhaegri = duration/US_ROUNDTRIP_CM;// convert time into 
    myMotor->setSpeed(80);
    myMotor2->setSpeed(80);
    myMotor->run(BACKWARD);
    myMotor2->run(BACKWARD);
    //thangad til
    if(Sensoraftanhaegri<58&&Sensoraftanhaegriold<58&&timi>1300 &&Sensoraftanhaegri!=0 &&Sensoraftanhaegriold!=0||timi>2200){
      Serial.println("if lykkja eitt");
      Serial.println(Sensoraftanhaegri);
              myMotor->setSpeed(0);
              myMotor2->setSpeed(0);
              delay(25);
            //setjum servoinn í 45 /annig hann beygi aftur a bak i haegri beygju
            servobeygja.write(60);
            delay(100);
            break;
    }
    Sensoraftanhaegriold=Sensoraftanhaegri;
  }

timataka=millis();
  while(1){
    Serial.println("while lykkja 2");
    timi=millis()-timataka;
    delay(50);
    duration = sonaraftanhaegri.ping();// Send ping, get ping time in microseconds 
    Sensoraftanhaegri = duration/US_ROUNDTRIP_CM;// convert time into 
    /*duration = sonaraftanvinstri.ping();// Send ping, get ping time in microseconds 
    Sensoraftanvinstri = duration/US_ROUNDTRIP_CM;// convert time into */
    myMotor->setSpeed(90);
    myMotor2->setSpeed(90);

    if(Sensoraftanhaegri>50 && Sensoraftanhaegriold>50 && Sensoraftanhaegri<90 && Sensoraftanhaegriold<90 && timi>1300 || timi>2500 || Sensoraftanhaegri<7 && Sensoraftanhaegri!=0 && Sensoraftanhaegriold<7 && Sensoraftanhaegri!=0&& timi>1300){
      Serial.println("if lykkja 2");
      Serial.println(Sensoraftanhaegri);
       myMotor->setSpeed(0);
       myMotor2->setSpeed(0);
       delay(25);
       //setjum servoinn í 75 thannig hann beygi slightly til haegri
       servobeygja.write(75);
       delay(100);  
       break;
    }
     Sensoraftanhaegriold=Sensoraftanhaegri;
  }


  // "BEINT" ..slightly til haegri
    timataka=millis();
  while(1){
    Serial.println("while lykkja 3");
    timi=millis()-timataka;
    delay(50);
    duration = sonaraftanhaegri.ping();// Send ping, get ping time in microseconds 
    Sensoraftanhaegri = duration/US_ROUNDTRIP_CM;// convert time into 
    duration = sonaraftanvinstri.ping();// Send ping, get ping time in microseconds 
    Sensoraftanvinstri = duration/US_ROUNDTRIP_CM;// convert time into 
    myMotor->setSpeed(80);
    myMotor2->setSpeed(80);
    myMotor->run(FORWARD);
    myMotor2->run(FORWARD);
    //ef skynjaramunurinn er a akvednu bili tha er hann i midjunni og fer beint
    
    if(Sensoraftanhaegri-Sensoraftanvinstri>500 && Sensoraftanhaegri-Sensoraftanvinstri<530 && 
    //tekkum thetta lika fyrir old gildi
    Sensoraftanhaegriold-Sensoraftanvinstriold>500 && Sensoraftanhaegriold-Sensoraftanvinstriold<530){
      Serial.println("if lykkja 3");
      Serial.println("Sensoraftanhaegri");
      Serial.println(Sensoraftanhaegri);
      Serial.println("Sensoraftanvinstri");
      Serial.println(Sensoraftanvinstri);
       //myMotor->setSpeed(0);
        //myMotor2->setSpeed(0);
       delay(25);
       servobeygja.write(80);
       delay(500);
    }
    //ef haegri skynjarinn er miklu staerri en sa vinstri er hann of langt vinstra megin og fer slightly til haegri
    else if(Sensoraftanhaegri-Sensoraftanvinstri>530 && Sensoraftanhaegriold-Sensoraftanvinstriold>530){
       Serial.println("else if lykkja 1");
      Serial.println("Sensoraftanhaegri");
      Serial.println(Sensoraftanhaegri);
      Serial.println("Sensoraftanvinstri");
      Serial.println(Sensoraftanvinstri);
       // myMotor->setSpeed(0);
       //myMotor2->setSpeed(0);
       delay(25);
       servobeygja.write(75);
       delay(500);
    }
    //ef vinstri skynjarinn er miklu staerri en sa haegri er hann of langt haegra megin og fer slightly til vinstri
    else if(Sensoraftanhaegri-Sensoraftanvinstri<-5 && Sensoraftanhaegriold-Sensoraftanvinstriold<-5){
       Serial.println("else if lykkja 2");
      Serial.println("Sensoraftanhaegri");
      Serial.println(Sensoraftanhaegri);
      Serial.println("Sensoraftanvinstri");
      Serial.println(Sensoraftanvinstri);
       // myMotor->setSpeed(0);
       //myMotor2->setSpeed(0);
       delay(25);
       servobeygja.write(85);
       delay(500);
    }
    else if(timi >2800){
       delay(25);
       servobeygja.write(80);
       delay(25);
      break;
    }
     Sensoraftanhaegriold=Sensoraftanhaegri;
     Sensoraftanvinstriold=Sensoraftanvinstri;
  }

  //enn ad keyra i att ad vegg while lykkja 4444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444

  timataka=millis();
  while(1){
    Serial.println("while lykkja 4");
    timi=millis()-timataka;
    delay(50);
    duration = sonaraftanhaegri.ping();// Send ping, get ping time in microseconds 
    Sensoraftanhaegri = duration/US_ROUNDTRIP_CM;// convert time into 
    duration = sonaraftanvinstri.ping();// Send ping, get ping time in microseconds 
    Sensoraftanvinstri = duration/US_ROUNDTRIP_CM;// convert time into 
    myMotor->setSpeed(80);
    myMotor2->setSpeed(80);
    myMotor->run(FORWARD);
    myMotor2->run(FORWARD);
    //ef skynjaramunurinn er a akvednu bili tha er hann i midjunni og fer beint
    if(Sensoraftanhaegri-Sensoraftanvinstri>500 && Sensoraftanhaegri-Sensoraftanvinstri<530 && 
    //tekkum thetta lika fyrir old gildi
    Sensoraftanhaegriold-Sensoraftanvinstriold>500 && Sensoraftanhaegriold-Sensoraftanvinstriold<530){
      Serial.println("if lykkja 3");
      Serial.println("Sensoraftanhaegri");
      Serial.println(Sensoraftanhaegri);
      Serial.println("Sensoraftanvinstri");
      Serial.println(Sensoraftanvinstri);
       //myMotor->setSpeed(0);
        //myMotor2->setSpeed(0);
       delay(25);
       servobeygja.write(80);
       delay(500);
    }
    //ef haegri skynjarinn er miklu staerri en sa vinstri er hann of langt vinstra megin og fer slightly til haegri
    else if(Sensoraftanhaegri-Sensoraftanvinstri>530 && Sensoraftanhaegriold-Sensoraftanvinstriold>530){
       Serial.println("else if lykkja 1");
      Serial.println("Sensoraftanhaegri");
      Serial.println(Sensoraftanhaegri);
      Serial.println("Sensoraftanvinstri");
      Serial.println(Sensoraftanvinstri);
       // myMotor->setSpeed(0);
       //myMotor2->setSpeed(0);
       delay(25);
       servobeygja.write(75);
       delay(500);
    }
    //ef vinstri skynjarinn er miklu staerri en sa haegri er hann of langt haegra megin og fer slightly til vinstri
    else if(Sensoraftanhaegri-Sensoraftanvinstri<300 && Sensoraftanhaegriold-Sensoraftanvinstriold<300){
       Serial.println("else if lykkja 2");
      Serial.println("Sensoraftanhaegri");
      Serial.println(Sensoraftanhaegri);
      Serial.println("Sensoraftanvinstri");
      Serial.println(Sensoraftanvinstri);
       // myMotor->setSpeed(0);
       //myMotor2->setSpeed(0);
       delay(25);
       servobeygja.write(85);
       delay(500);
    }
    else if( Sensoraftanhaegri >1700 && Sensoraftanhaegri <2100 && Sensoraftanvinstri >1700 && Sensoraftanvinstri <2100 &&
            //tokum lika gomlu gildin
            Sensoraftanhaegriold >1700 && Sensoraftanhaegriold <2100 && Sensoraftanvinstriold >1700 && Sensoraftanvinstriold <2100){
                     delay(25);
       servobeygja.write(90);
       delay(500);
     }

     else if( Sensoraftanhaegri <1600 && Sensoraftanhaegri >80 && Sensoraftanvinstri <1600 && Sensoraftanvinstri >80 &&
            //tokum lika gomlu gildin
            Sensoraftanhaegriold <1600 && Sensoraftanhaegriold >80 && Sensoraftanvinstriold <1600 && Sensoraftanvinstriold >80){
              delay(25);
       servobeygja.write(70);
       delay(500);
            }
      

     Sensoraftanhaegriold=Sensoraftanhaegri;
     Sensoraftanvinstriold=Sensoraftanvinstri; 
  } 
}

void loop() {
  // put your main code here, to run repeatedly:

}
