//afram haegri gradur  60<80
//afram vinstri gradur 100>80

//ATHATHATHATHAT  Port 9 bilað
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

int pushbutton = 3; //a hjoli
int pushbutton2 = 2; // takki a hlid
int ljosastaurgildi=30;

unsigned int duration,Sensorljosastaur, Sensorljosastaurold, Sensorframanhaegri,Sensorframanhaegriold,Sensorframanmidja,Sensorframanmidjaold,Sensorframanvinstri,Sensorframanvinstriold,Sensorvinstri, Sensorvinstriold,Sensoraftanvinstri, Sensoraftanvinstriold, Sensoraftanhaegri, Sensoraftanhaegriold; 

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

Adafruit_DCMotor *dcvinstri = AFMS.getMotor(4);
Adafruit_DCMotor *dchaegri = AFMS.getMotor(3);
Adafruit_DCMotor *lokMotor = AFMS.getMotor(2);

void setup() 
{
  Serial.begin(9600); 
   pinMode(pushbutton, INPUT);
  pinMode(pushbutton2, INPUT);
  int takkihjol, oldtakkihjol; //= digitalRead(pushbutton);
  int takki, oldtakki; //= digitalRead(pushbutton2);  
     
  AFMS.begin(2000);
  delay(30);
  servoarmur.attach(9);  
  servobeygja.attach(10);  
  delay(15);
  servoarmur.write(120);
  delay(15);
  dcvinstri->setSpeed(80);
  dchaegri->setSpeed(80);
  dcvinstri->run(FORWARD);
  dchaegri->run(FORWARD);
  
//keyra afram i byrjun
  while(1)
  {
        Serial.println("servo armur");
        Serial.println(servoarmur.read());
        Serial.println("while lykkja 1");
        delay(30); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonarvinstri.ping();// Send ping, get ping time in microseconds 
        Sensorvinstri = duration/US_ROUNDTRIP_CM;// convert time into distance
//Servo stilltur aðeins til vinstri
        servobeygja.write(86);              // tell servo to go to position in variable 'pos'
        Serial.println("servobeygja is");
        Serial.println(servobeygja.read());
//skynjar sulu+raudan takka

        if (Sensorvinstri <40 && Sensorvinstri>5 && Sensorvinstriold<40 && Sensorvinstriold>5) 
            {
            //Stoppar
            dcvinstri->setSpeed(0);
            dchaegri->setSpeed(0);            
            Serial.println("vinstri sensor");
            Serial.println(Sensorvinstri);
            //skrifar 40 gradur á servoinn til að geta beygt og bakkað
            servobeygja.write(40);
            //Bakkar
            delay(25);
            dcvinstri->setSpeed(110);
            dchaegri->setSpeed(110);
            dcvinstri->run(BACKWARD);
            dchaegri->run(BACKWARD);
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
        duration = sonaraftanhaegri.ping();// Send ping, get ping time in microseconds 
        Sensoraftanhaegri = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonaraftanvinstri.ping();// Send ping, get ping time in microseconds 
        Sensoraftanvinstri = duration/US_ROUNDTRIP_CM;// convert time into distance
        Serial.println("Sensorframanhaegri");
        Serial.println(Sensorframanhaegri);
        Serial.println("Sensorframanmidja");
        Serial.println(Sensorframanmidja);
        Serial.println("Sensorframanvinstri");
        Serial.println(Sensorframanvinstri);
                 
//Ef skynjar súlu með takka í minna en 60 cm fjarlægð
        if(Sensorframanvinstri <60 && Sensorframanvinstri >5 && Sensorframanvinstriold <60 && Sensorframanvinstriold >5 && Sensorframanhaegri <60 && Sensorframanhaegri >5 && Sensorframanhaegriold <60 && Sensorframanhaegriold >5 || Sensorframanmidja <60 && Sensorframanmidja >1 && Sensorframanmidjaold <60 && Sensorframanmidjaold >1 && Sensorframanvinstri <60 && Sensorframanvinstri >5 && Sensorframanvinstriold <60 && Sensorframanvinstriold >5 || Sensorframanmidja <60 && Sensorframanmidja >1 && Sensorframanmidjaold <60 && Sensorframanmidjaold >1 && Sensorframanhaegri <60 && Sensorframanhaegri >5 && Sensorframanhaegriold <60 && Sensorframanhaegriold >5  ){
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
            dcvinstri->setSpeed(0);
            dchaegri->setSpeed(0);
            delay(25);
            //skrifar 80 gráður á servoinn til að fara beint
            servobeygja.write(79);
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
        dcvinstri->setSpeed(90);
        dchaegri->setSpeed(90);
        dcvinstri->run(FORWARD);
        dchaegri->run(FORWARD);
        Serial.println(Sensorframanhaegri);
        Serial.println(Sensorframanmidja);
        Serial.println(Sensorframanvinstri);

//stoppum ef einhver skynjari er kominn nógu nálægt rauða takkanum
        if(Sensorframanhaegri <5 && Sensorframanhaegri >1 && Sensorframanhaegriold <5 && Sensorframanhaegriold >1 || Sensorframanmidja <5 && Sensorframanmidja >1 && Sensorframanmidjaold <5 && Sensorframanmidjaold >1 || Sensorframanvinstri<5 && Sensorframanvinstri>1 && Sensorframanvinstriold<5 && Sensorframanvinstriold>1){
          delay(1000);
          Serial.println(Sensorframanhaegri);
          Serial.println(Sensorframanmidja);
          Serial.println(Sensorframanvinstri);
          //stoppum
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);

          //bíðum í 1 sek eftir að boltar fara oní 
          delay(1000);
          break;
      }
          Sensorframanhaegriold=Sensorframanhaegri;
          Sensorframanmidjaold=Sensorframanmidja;
          Sensorframanvinstriold=Sensorframanvinstri;
  }


  while(1){
    //bakkar fra takka
      Serial.println("while lykkja 4");

   

//notum skynjara 2-5 sem eru allir skynjararnir að framan
      delay(40); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delay
      duration = sonarframanhaegri.ping();// Send ping, get ping time in microseconds 
      Sensorframanhaegri = duration/US_ROUNDTRIP_CM;// convert time into distance
      duration = sonarframanmidja.ping();// Send ping, get ping time in microseconds 
      Sensorframanmidja = duration/US_ROUNDTRIP_CM;// convert time into distance
      duration = sonarframanvinstri.ping();// Send ping, get ping time in microseconds 
      Sensorframanvinstri = duration/US_ROUNDTRIP_CM;// convert time into distance
//bökkum
      dcvinstri->setSpeed(85);
      dchaegri->setSpeed(85);
      dcvinstri->run(BACKWARD);
      dchaegri->run(BACKWARD);
      
      Serial.println(Sensorframanhaegri);
      Serial.println(Sensorframanmidja);
      Serial.println(Sensorframanvinstri);
      
// skynjum suluna. passa ad ALLIR skynjarar seu lengra en 37cm fra sulu
        if(Sensorframanhaegri >37 && Sensorframanhaegriold >37 && Sensorframanmidja >37 && Sensorframanmidjaold >37 && Sensorframanvinstri>37  && Sensorframanvinstriold>37){
        Serial.println(Sensorframanhaegri);
        Serial.println(Sensorframanmidja);
        Serial.println(Sensorframanvinstri);
        //stoppum
        dcvinstri->setSpeed(0);
        dchaegri->setSpeed(0);
        delay(500);
        //setjum servoinn í 45 til ad beygja til haegri
        servobeygja.write(45);
        delay(500);
        //förum beint áfram í átt að vegg
        dcvinstri->setSpeed(105);
        dchaegri->setSpeed(105);
        dcvinstri->run(FORWARD);
        dchaegri->run(FORWARD);
        break;
    }
    Sensorframanhaegriold=Sensorframanhaegri;
    Sensorframanmidjaold=Sensorframanmidja;
    Sensorframanvinstriold=Sensorframanvinstri;
  }

  while(1){
      Serial.println("while lykkja 5");
      delay(35); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delay
      duration = sonarframanhaegri.ping();// Send ping, get ping time in microseconds 
      Sensorframanhaegri = duration/US_ROUNDTRIP_CM;// convert time into distance
      duration = sonarframanmidja.ping();// Send ping, get ping time in microseconds 
      Sensorframanmidja = duration/US_ROUNDTRIP_CM;// convert time into distance
      duration = sonarframanvinstri.ping();// Send ping, get ping time in microseconds 
      Sensorframanvinstri = duration/US_ROUNDTRIP_CM;// convert time into distance

      Serial.println(Sensorframanhaegri);
      Serial.println(Sensorframanmidja);
      Serial.println(Sensorframanvinstri);
      
        if(Sensorframanmidja <90 && Sensorframanmidja >50 && Sensorframanmidjaold <90 && Sensorframanmidjaold >50 && Sensorframanvinstri<90 && Sensorframanvinstri>50 && Sensorframanvinstriold<90 && Sensorframanvinstriold>50){
          Serial.println(Sensorframanhaegri);
          Serial.println(Sensorframanmidja);
          Serial.println(Sensorframanvinstri);
          //forum beint afram
          dcvinstri->setSpeed(85);
          dchaegri->setSpeed(85);
          servobeygja.write(79);
          delay(25);
          break;
          }
          Sensorframanhaegriold=Sensorframanhaegri;
          Sensorframanmidjaold=Sensorframanmidja;
          Sensorframanvinstriold=Sensorframanvinstri;
  }

  


  while(1){
      //keyrir ad vegg og beygir svo framhja veggjum
          Serial.println("while lykkja 6");
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

          //beygir til haegri framhja seinni vegg
        if(Sensorframanhaegri <55 && Sensorframanhaegri >5 && Sensorframanhaegriold <55 && Sensorframanhaegriold >5 && Sensorframanmidja <55 && Sensorframanmidja >5 && Sensorframanmidjaold <55 && Sensorframanmidjaold >5 || Sensorframanvinstri<55 && Sensorframanvinstri>5 && Sensorframanvinstriold<55 && Sensorframanvinstriold>5 && Sensorframanmidja <55 && Sensorframanmidja >5 && Sensorframanmidjaold <55 && Sensorframanmidjaold >5 || Sensorframanvinstri<55 && Sensorframanvinstri>5 && Sensorframanvinstriold<55 && Sensorframanvinstriold>5 && Sensorframanhaegri <55 && Sensorframanhaegri >5 && Sensorframanhaegriold <55 && Sensorframanhaegriold >5){
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servobeygja.write(55);
          delay(500);
          dcvinstri->setSpeed(90);
          dchaegri->setSpeed(90);
          dcvinstri->run(FORWARD);
          dchaegri->run(FORWARD);
          break;
          }
          Sensorframanhaegriold=Sensorframanhaegri;
          Sensorframanmidjaold=Sensorframanmidja;
          Sensorframanvinstriold=Sensorframanvinstri;
          }
          
int timataka,timi;
timataka=millis();
while(1){
      //  i haegri beygju !!
          Serial.println("while lykkja 7");
          timi=millis()-timataka;
          delay(40); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delay
          duration = sonarframanvinstri.ping();// Send ping, get ping time in microseconds 
          Sensorframanvinstri = duration/US_ROUNDTRIP_CM;// convert time into distance
          duration = sonarframanmidja.ping();// Send ping, get ping time in microseconds 
          Sensorframanmidja = duration/US_ROUNDTRIP_CM;// convert time into distance
           duration = sonarljosastaur.ping();// Send ping, get ping time in microseconds 
        Sensorljosastaur = duration/US_ROUNDTRIP_CM;// convert time into 
          Serial.println(Sensorljosastaur);
          Serial.println(Sensorframanmidja);
          Serial.println(Sensorframanvinstri);

          //ef sensorarnir vinstri eda i midju eru komnir framhja veggnum tha begir hann til vinstri
        if(Sensorframanvinstri >60 && Sensorframanvinstriold >60 || Sensorframanmidja >60 && Sensorframanmidjaold >60){
          delay(200);
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servobeygja.write(98);
          delay(2000);
          dcvinstri->setSpeed(90);
          dchaegri->setSpeed(90);
          dcvinstri->run(FORWARD);
          dchaegri->run(FORWARD);
          break;
          }
          //ef of langur timi lidur tha er hann klesstur a fjaervegginn og vid bokkum og rettum okkur af til ad komast i gegn
          else if(timi>5000){
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servobeygja.write(100);
          dcvinstri->setSpeed(90);
          dchaegri->setSpeed(90);
          dcvinstri->run(BACKWARD);
          dchaegri->run(BACKWARD);
          delay(1200);
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servobeygja.write(80);
          delay(35);
          dcvinstri->setSpeed(90);
          dchaegri->setSpeed(90);
          dcvinstri->run(FORWARD);
          dchaegri->run(FORWARD);
          }
          //eda ljosastaur skynjar ad hann er ad keyra utaf
          if(abs(Sensorljosastaur- ljosastaurgildi) > 2 && abs(Sensorljosastaurold- ljosastaurgildi) > 2 &&timi>2000){
                dcvinstri->setSpeed(0);
                dchaegri->setSpeed(0);
                delay(35);
                servobeygja.write(60);
                delay(35);
                dcvinstri->setSpeed(90);
                dchaegri->setSpeed(90);
                dcvinstri->run(BACKWARD);
                dchaegri->run(BACKWARD);
                delay(1000);
                servoarmur.write(5);
                delay(600);
                goto while9;
          }
          
          Sensorframanvinstriold=Sensorframanvinstri;
          Sensorframanmidjaold=Sensorframanmidja;
          Sensorljosastaurold=Sensorljosastaur;

}


while(1){
      //rettir sig af,   beygir til vinstri
          Serial.println("while lykkja 8");
        delay(50); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonaraftanvinstri.ping();// Send ping, get ping time in microseconds 
        Sensoraftanvinstri = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonaraftanhaegri.ping();// Send ping, get ping time in microseconds 
        Sensoraftanhaegri = duration/US_ROUNDTRIP_CM;// convert time into distance
         duration = sonarljosastaur.ping();// Send ping, get ping time in microseconds 
        Sensorljosastaur = duration/US_ROUNDTRIP_CM;// convert time into 
          Serial.println(Sensorljosastaur);
          Serial.println(Sensorframanmidja);
          Serial.println(Sensorframanvinstri);
          
        if(Sensoraftanvinstri>10 && Sensoraftanvinstriold>10 && Sensoraftanvinstri<60 && Sensoraftanvinstriold<60){
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          delay(30);
          servobeygja.write(79);
          delay(35);
          servoarmur.write(5);
          delay(600);

          break;
          }
          //ef of langur timi lidur tha er hann klesstur a fjaervegginn og vid bokkum og rettum okkur af til ad komast i gegn
          else if(timi>6000){
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servobeygja.write(100);
          dcvinstri->setSpeed(90);
          dchaegri->setSpeed(90);
          dcvinstri->run(BACKWARD);
          dchaegri->run(BACKWARD);
          delay(1200);
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servobeygja.write(80);
          delay(35);

          }

          //ef ljosastaurinn fer framaf
                if(abs(Sensorljosastaur- ljosastaurgildi) > 2 && abs(Sensorljosastaurold- ljosastaurgildi) > 2){
                dcvinstri->setSpeed(0);
                dchaegri->setSpeed(0);
                delay(35);
                servobeygja.write(60);
                delay(35);
                dcvinstri->setSpeed(90);
                dchaegri->setSpeed(90);
                dcvinstri->run(BACKWARD);
                dchaegri->run(BACKWARD);
                delay(1000);
                servoarmur.write(5);
                delay(600);
                break;
          }
          
          Sensorframanvinstriold=Sensorframanvinstri;
          Sensorframanmidjaold=Sensorframanmidja;
          Sensoraftanhaegriold=Sensoraftanhaegri;
          Sensoraftanvinstriold=Sensoraftanvinstri; 
          Sensorljosastaurold=Sensorljosastaur;         
}

//nidri med arminn rettir sig af
while(1){
        Serial.println("while lykkja 9");
        while9:
        delay(50); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonaraftanvinstri.ping();// Send ping, get ping time in microseconds 
        Sensoraftanvinstri = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonaraftanhaegri.ping();// Send ping, get ping time in microseconds 
        Sensoraftanhaegri = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonarljosastaur.ping();// Send ping, get ping time in microseconds 
        Sensorljosastaur = duration/US_ROUNDTRIP_CM;// convert time into  

          dcvinstri->setSpeed(80);
          dchaegri->setSpeed(80);
          dcvinstri->run(FORWARD);
          dchaegri->run(FORWARD);
          
        takkihjol = digitalRead(pushbutton);
        takki = digitalRead(pushbutton2);

      //ef takkahjol er fyrir utan braut
      if(takkihjol == 0 && oldtakkihjol == 0){
        //ef ljosastaur skynjar a[ hann er inni 
        if(abs(Sensorljosastaur- ljosastaurgildi) <= 2 && abs(Sensorljosastaurold- ljosastaurgildi) <= 2){
          servobeygja.write(80);
          delay(150);
        }
        //annars ef hann er utaf
        else
        {
                dcvinstri->setSpeed(0);
                dchaegri->setSpeed(0);
                delay(35);
                servobeygja.write(60);
                delay(35);
                servoarmur.write(120);
                delay(40);
                dcvinstri->setSpeed(90);
                dchaegri->setSpeed(90);
                dcvinstri->run(BACKWARD);
                dchaegri->run(BACKWARD);
                delay(700);
                dcvinstri->setSpeed(0);
                dchaegri->setSpeed(0);
                delay(30);
               servoarmur.write(5);
                delay(600);
        }
      }
      // ef takkahjol er fyrir innan braut
      else{
        //ef ljosastaur skynjar ad hann er uti
        if(abs(Sensorljosastaur- ljosastaurgildi) > 2 && abs(Sensorljosastaurold- ljosastaurgildi) > 2){
                dcvinstri->setSpeed(0);
                dchaegri->setSpeed(0);
                delay(35);
                servobeygja.write(60);
                delay(35);
                dcvinstri->setSpeed(90);
                dchaegri->setSpeed(90);
                dcvinstri->run(BACKWARD);
                dchaegri->run(BACKWARD);
                delay(1000);
        }
        servobeygja.write(73);
     }

    if(takki == 0 && oldtakki == 0){
      dchaegri->setSpeed(0);
      dcvinstri->setSpeed(0);
      delay(30);
      servoarmur.write(120);
      break;
    }
    
    Sensorljosastaurold=Sensorljosastaur;
    oldtakkihjol=takkihjol;
    oldtakki=takki;
  
}

/*
while(1){
      //rettir sig af
          Serial.println("while lykkja 8");
        delay(35); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonaraftanvinstri.ping();// Send ping, get ping time in microseconds 
        Sensoraftanvinstri = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonaraftanhaegri.ping();// Send ping, get ping time in microseconds 
        Sensoraftanhaegri = duration/US_ROUNDTRIP_CM;// convert time into distance
        
          Serial.println(Sensorljosastaur);
          Serial.println(Sensorframanmidja);
          Serial.println(Sensorframanvinstri);
          
        if(Sensoraftanhaegriold > 40 && Sensoraftanhaegri >40 ){
          servobeygja.write(72);
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          delay(2000);
          dcvinstri->setSpeed(85);
          dchaegri->setSpeed(85);
          break;
          }
          Sensoraftanhaegriold=Sensoraftanhaegri;
}

while(1){
      //keyrir ad brun
          Serial.println("while lykkja 8");
          delay(35); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delay
          duration = sonarljosastaur.ping();// Send ping, get ping time in microseconds 
          Sensorljosastaur = duration/US_ROUNDTRIP_CM;// convert time into distance
          servoarmur.write(3);
        
          Serial.println(Sensorljosastaur);
          Serial.println(Sensorframanmidja);
          Serial.println(Sensorframanvinstri);
          
        if(Sensorljosastaur >35 && Sensorljosastaurold >35 ){

          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          delay(25);
          servobeygja.write(120);
          delay(1000);
          dcvinstri->setSpeed(120);
          dchaegri->setSpeed(120);
          dcvinstri->run(FORWARD);
          dchaegri->run(FORWARD);
          break;
          }
          Sensorljosastaurold=Sensorljosastaur;
          
}
while(1){
      //keyrir ad brun
          Serial.println("while lykkja 8");
          delay(35); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delay
          duration = sonarljosastaur.ping();// Send ping, get ping time in microseconds 
          Sensorljosastaur = duration/US_ROUNDTRIP_CM;// convert time into distance
          int statehjol = digitalRead(takkihjol);
          int statetakki = digitalRead(takki);
        
          Serial.println(Sensorljosastaur);
          Serial.println(Sensorframanmidja);
          Serial.println(Sensorframanvinstri);
          
        if(statehjol==0){
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servoarmur.write(120);
          servobeygja.write(79);
          delay(10000);
          dcvinstri->setSpeed(200);
          dchaegri->setSpeed(0);
          dcvinstri->run(BACKWARD);
          dchaegri->run(FORWARD);
          delay(500);
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);

          break;
          }
          Sensorljosastaurold=Sensorljosastaur;
          
}
/*
while(1){
      //rettir sig af þegar beinn
          Serial.println("while lykkja 9");
          delay(30); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonaraftanvinstri.ping();// Send ping, get ping time in microseconds 
        Sensoraftanvinstri = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonaraftanhaegri.ping();// Send ping, get ping time in microseconds 
        Sensoraftanhaegri = duration/US_ROUNDTRIP_CM;// convert time into distance
        
          Serial.println(Sensorljosastaur);
          Serial.println(Sensorframanmidja);
          Serial.println(Sensorframanvinstri);
          Serial.println("Mismunur a fjarlaegdum" + Sensoraftanvinstri-Sensoraftanhaegri);

        if(Sensoraftanvinstri<85 && Sensoraftanvinstriold<85 && Sensoraftanvinstri-Sensoraftanhaegri <1 && Sensoraftanvinstriold-Sensoraftanhaegriold <1 && Sensoraftanhaegriold !=0 && Sensoraftanhaegri !=0 ){
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servobeygja.write(82);
          delay(25);
          servoarmur.write(0);
          delay(4000);
          dcvinstri->setSpeed(85);
          dchaegri->setSpeed(85);
          dcvinstri->run(FORWARD);
          dchaegri->run(FORWARD);
          break;
          }
          Sensoraftanhaegriold=Sensoraftanhaegri;
          Sensoraftanvinstriold=Sensoraftanvinstri;


          
}

while(1){
      //keyrir ad brun
          Serial.println("while lykkja 8");
          delay(35); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonarljosastaur.ping();// Send ping, get ping time in microseconds 
        Sensorljosastaur = duration/US_ROUNDTRIP_CM;// convert time into distance
        
          Serial.println(Sensorljosastaur);
          Serial.println(Sensorframanmidja);
          Serial.println(Sensorframanvinstri);
          
        if(Sensorljosastaur <40 && Sensorljosastaurold <40){
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          delay(10000);
          dcvinstri->setSpeed(80);
          dchaegri->setSpeed(80);
          dcvinstri->run(FORWARD);
          dchaegri->run(FORWARD);
          break;
          }
          Sensorljosastaurold=Sensorljosastaur;
          
}

*/


}
//
void loop() {
  // put your main code here, to run repeatedly:

}
