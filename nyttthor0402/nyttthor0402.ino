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
float hradafasti=1;
float timafasti=1;

int counter2 =0;
int ljosastaurgildi=30;
int counter=0;
int counter3=0;
int timataka2;
int timi2=0;
int timataka,timi;
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
  int takki=1; 
  int oldtakki = 1; //= digitalRead(pushbutton2);  
  //pinMode(2, INPUT); 
  AFMS.begin(2000);
  delay(10000);
  servoarmur.attach(9);  
  servobeygja.attach(10);  
  delay(15);
  servoarmur.write(100);
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
        if(Sensorframanvinstri <57 && Sensorframanvinstri >5 && Sensorframanvinstriold <57 && Sensorframanvinstriold >5 && Sensorframanhaegri <57 && Sensorframanhaegri >5 && Sensorframanhaegriold <57 && Sensorframanhaegriold >5 || Sensorframanmidja <57 && Sensorframanmidja >1 && Sensorframanmidjaold <57 && Sensorframanmidjaold >1 && Sensorframanvinstri <57 && Sensorframanvinstri >5 && Sensorframanvinstriold <57 && Sensorframanvinstriold >5 || Sensorframanmidja <57 && Sensorframanmidja >1 && Sensorframanmidjaold <57 && Sensorframanmidjaold >1 && Sensorframanhaegri <57 && Sensorframanhaegri >5 && Sensorframanhaegriold <57 && Sensorframanhaegriold >5  ){
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

timataka=millis();
  while(1){
        //keyrir i att ad takka
        Serial.println("while lykkja 3");
        timi= millis()-timataka;
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
        if(Sensorframanhaegri <5 && Sensorframanhaegri >1 && Sensorframanhaegriold <5 && Sensorframanhaegriold >1 || Sensorframanmidja <5 && Sensorframanmidja >1 && Sensorframanmidjaold <5 && Sensorframanmidjaold >1 || Sensorframanvinstri<5 && Sensorframanvinstri>1 && Sensorframanvinstriold<5 && Sensorframanvinstriold>1|| timi>7000){
          delay(1200);
          Serial.println(Sensorframanhaegri);
          Serial.println(Sensorframanmidja);
          Serial.println(Sensorframanvinstri);
          //stoppum
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);

          //bíðum í 1 sek eftir að boltar fara oní 
          delay(1300);
          break;
      }
          Sensorframanhaegriold=Sensorframanhaegri;
          Sensorframanmidjaold=Sensorframanmidja;
          Sensorframanvinstriold=Sensorframanvinstri;
  }


//thetta er bara til ad byrja hja takkanum
//servobeygja.write(79);
//delay(30);
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
        if(Sensorframanhaegri >36 && Sensorframanhaegriold >36 && Sensorframanmidja >36 && Sensorframanmidjaold >36 && Sensorframanvinstri>36  && Sensorframanvinstriold>36){
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
        if(Sensorframanhaegri <60 && Sensorframanhaegri >5 && Sensorframanhaegriold <60 && Sensorframanhaegriold >5 && Sensorframanmidja <60 && Sensorframanmidja >5 && Sensorframanmidjaold <60 && Sensorframanmidjaold >5 || Sensorframanvinstri<60 && Sensorframanvinstri>5 && Sensorframanvinstriold<60 && Sensorframanvinstriold>5 && Sensorframanmidja <60 && Sensorframanmidja >5 && Sensorframanmidjaold <55 && Sensorframanmidjaold >5 || Sensorframanvinstri<60 && Sensorframanvinstri>5 && Sensorframanvinstriold<60 && Sensorframanvinstriold>5 && Sensorframanhaegri <60 && Sensorframanhaegri >5 && Sensorframanhaegriold <60 && Sensorframanhaegriold >5){
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
          delay(500);
          dcvinstri->setSpeed(90);
          dchaegri->setSpeed(90);
          dcvinstri->run(FORWARD);
          dchaegri->run(FORWARD);
          break;
          }
          //ef of langur timi lidur tha er hann klesstur a fjaervegginn og vid bokkum og rettum okkur af til ad komast i gegn bakkupp 33231231132222222333333333333333333333333333333333333
          else if(timi>8000){
            if (Sensorframanhaegri!=0 &&Sensorframanhaegri<7 &&Sensorframanvinstri!=0 && Sensorframanvinstri>20){
               dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servobeygja.write(63);
          dcvinstri->setSpeed(90);
          dchaegri->setSpeed(90);
          dcvinstri->run(BACKWARD);
          dchaegri->run(BACKWARD);
          delay(500);
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servobeygja.write(80);
          delay(35);
          dcvinstri->setSpeed(90);
          dchaegri->setSpeed(90);
          dcvinstri->run(FORWARD);
          dchaegri->run(FORWARD);
            }
            else{
            if (counter3==0){
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servobeygja.write(100);
          dcvinstri->setSpeed(90);
          dchaegri->setSpeed(90);
          dcvinstri->run(BACKWARD);
          dchaegri->run(BACKWARD);
          delay(500);
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servobeygja.write(80);
          delay(35);
          dcvinstri->setSpeed(90);
          dchaegri->setSpeed(90);
          dcvinstri->run(FORWARD);
          dchaegri->run(FORWARD);
          counter3=counter3+1;
            }
            else{
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servobeygja.write(80);
          dcvinstri->setSpeed(90);
          dchaegri->setSpeed(90);
          dcvinstri->run(BACKWARD);
          dchaegri->run(BACKWARD);
          delay(500);
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servobeygja.write(60);
          delay(35);
          dcvinstri->setSpeed(90);
          dchaegri->setSpeed(90);
          dcvinstri->run(FORWARD);
          dchaegri->run(FORWARD);
          counter3=0;
            }
            }
          }
          
          //eda ljosastaur skynjar ad hann er ad keyra utaf
          if(Sensorljosastaur > ljosastaurgildi+2 &&timi>2000){
                dcvinstri->setSpeed(0);
                dchaegri->setSpeed(0);
                delay(35);
                servobeygja.write(60);
                delay(35);
                dcvinstri->setSpeed(90);
                dchaegri->setSpeed(90);
                dcvinstri->run(BACKWARD);
                dchaegri->run(BACKWARD);
                delay(700);
                servoarmur.write(5);
                delay(600);
                timataka=millis();
                goto while9;
          }
          
          Sensorframanvinstriold=Sensorframanvinstri;
          Sensorframanmidjaold=Sensorframanmidja;
          Sensorljosastaurold=Sensorljosastaur;

}

counter3=0;
timataka=millis();
while(1){
      //rettir sig af,   beygir til vinstri
          Serial.println("while lykkja 8");
          timi=millis()-timataka;
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
          else if(timi>7000){
if (counter3==0){
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servobeygja.write(100);
          dcvinstri->setSpeed(90);
          dchaegri->setSpeed(90);
          dcvinstri->run(BACKWARD);
          dchaegri->run(BACKWARD);
          delay(500);
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servobeygja.write(80);
          delay(35);
          dcvinstri->setSpeed(90);
          dchaegri->setSpeed(90);
          dcvinstri->run(FORWARD);
          dchaegri->run(FORWARD);
          counter3=counter3+1;
            }
            else{
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servobeygja.write(80);
          dcvinstri->setSpeed(90);
          dchaegri->setSpeed(90);
          dcvinstri->run(BACKWARD);
          dchaegri->run(BACKWARD);
          delay(500);
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servobeygja.write(60);
          delay(35);
          dcvinstri->setSpeed(90);
          dchaegri->setSpeed(90);
          dcvinstri->run(FORWARD);
          dchaegri->run(FORWARD);
          counter3=0;
            }
          }

          //ef ljosastaurinn fer framaf
                if(Sensorljosastaur- ljosastaurgildi > 2){
                dcvinstri->setSpeed(0);
                dchaegri->setSpeed(0);
                delay(35);
                servobeygja.write(60);
                delay(35);
                dcvinstri->setSpeed(90);
                dchaegri->setSpeed(90);
                dcvinstri->run(BACKWARD);
                dchaegri->run(BACKWARD);
                delay(700);
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

timataka=millis();
//nidri med arminn rettir sig af 123412341234434312222222222222222222222222222222222222222222222222222222222222222223444444444444444444444444444444444444444
while(1){
        Serial.println("while lykkja 9");
        while9:
        timi=millis()-timataka;
        delay(50); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delayMicroseconds
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
    if (timi>30000){
                dcvinstri->setSpeed(0);
                dchaegri->setSpeed(0);
                delay(35);
                servobeygja.write(100);
                delay(35);
                servoarmur.write(100);
                delay(700);
                dcvinstri->setSpeed(90);
                dchaegri->setSpeed(90);
                dcvinstri->run(BACKWARD);
                dchaegri->run(BACKWARD);
                delay(1500);
                dcvinstri->setSpeed(0);
                dchaegri->setSpeed(0);
                delay(35);
                servobeygja.write(80);
                delay(35);
                dcvinstri->setSpeed(90);
                dchaegri->setSpeed(90);
                dcvinstri->run(BACKWARD);
                dchaegri->run(BACKWARD);
                delay(1500);
                servoarmur.write(5);
    }

    if(takki == 0 || oldtakki == 0 ){
      yttatakka:
      dchaegri->setSpeed(0);
      dcvinstri->setSpeed(0);
      delay(30);
      servoarmur.write(100);
      delay(30);
      lokMotor->setSpeed(250);
      lokMotor->run(BACKWARD);
      delay(1000);
      lokMotor->setSpeed(0);
      delay(2000);
      lokMotor->setSpeed(250);
      lokMotor->run(FORWARD);
      delay(400);
      lokMotor->setSpeed(0);
      delay(30);
      servobeygja.write(88); /// mikilvaegt horn fra korfu !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
     //servobeygja.write(95);
       delay(30);
      break;
    }
    /*if(35<Sensorljosastaur && Sensorljosastaur < 55){
      delay(300);
      goto yttatakka;
    }*/
      //ef takkahjol er fyrir utan braut
      if(takkihjol == 0 && oldtakkihjol == 0){
        //setjum takkann adeins nedar ef buinn ad vera ad i 4 sek
        if(timi>8000){
          servoarmur.write(1);
          delay(600);
        }
        //ef ljosastaur skynjar ad hann er inni 
        if(abs(Sensorljosastaur- ljosastaurgildi) <= 2 && abs(Sensorljosastaurold- ljosastaurgildi) <= 2){
          servobeygja.write(80);
          delay(150);
        }
        //annars ef hann er utaf
        else
        {
                if(counter2>6){
                   servobeygja.write(81);
                    delay(150);
                }
                //fyrstu thrju skipti bakkar
                else if(counter<2){
                dcvinstri->setSpeed(0);
                dchaegri->setSpeed(0);
                delay(35);
                servobeygja.write(60);
                delay(35);
                servoarmur.write(100);
                delay(700);
                dcvinstri->setSpeed(90);
                dchaegri->setSpeed(90);
                dcvinstri->run(BACKWARD);
                dchaegri->run(BACKWARD);
                delay(700); 
                dcvinstri->setSpeed(0);
                dchaegri->setSpeed(0);
                delay(35);
                servobeygja.write(80);
                delay(30);
                if(timi>4000){
                  servoarmur.write(1);
                }
                else{servoarmur.write(5);}
                delay(600);
                counter=counter+1;
                }
                //fjorda hvert skipti fer afram og beygir til vinstri
                else if (counter>=2){
                  dcvinstri->setSpeed(0);
                dchaegri->setSpeed(0);
                delay(35);
                servobeygja.write(100);
                delay(35);
                servoarmur.write(100);
                delay(700);
                dcvinstri->setSpeed(90);
                dchaegri->setSpeed(90);
                dcvinstri->run(FORWARD);
                dchaegri->run(FORWARD);
                timataka2=millis();
                while(timi2 < 700){
                  timi2=millis()-timataka;
                  takki = digitalRead(pushbutton2);
                  if(takki == 0){
                    goto yttatakka;
                  }
                  }

                dcvinstri->setSpeed(0);
                dchaegri->setSpeed(0);
                delay(35);
                servobeygja.write(80);
                delay(30);
                servoarmur.write(5);
                delay(600);
                counter=0;
                }
                counter2=counter2+1;     
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


    
    Sensorljosastaurold=Sensorljosastaur;
    oldtakkihjol=takkihjol;
   oldtakki=takki;
  
}

/*
//nytt sem lexi bad um !!
while(1){
  delay(50);
  duration = sonarljosastaur.ping();// Send ping, get ping time in microseconds 
        Sensorljosastaur = duration/US_ROUNDTRIP_CM;// convert time into  

          dcvinstri->setSpeed(90);
          dchaegri->setSpeed(90);
          dcvinstri->run(BACKWARD);
          dchaegri->run(BACKWARD);
          if(abs(Sensorljosastaur- ljosastaurgildi) >2 && abs(Sensorljosastaurold- ljosastaurgildi) > 2){
            break;
          }
}*/


//fra korfu ad hlidi !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
timataka=millis();
  while(1){
    Serial.println("while lykkja 1");
    timi=millis()-timataka;
    //delay(50);
    //duration = sonaraftanhaegri.ping();// Send ping, get ping time in microseconds 
    //Sensoraftanhaegri = duration/US_ROUNDTRIP_CM;// convert time into 
    dcvinstri->setSpeed(80*hradafasti);
    dchaegri->setSpeed(80*hradafasti);
    dcvinstri->run(FORWARD);
    dchaegri->run(FORWARD);
    if(timi > 3500*timafasti){
             dcvinstri->setSpeed(0);
       dchaegri->setSpeed(0);
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
    dcvinstri->setSpeed(80*hradafasti);
    dchaegri->setSpeed(80*hradafasti);
    dcvinstri->run(FORWARD);
    dchaegri->run(FORWARD);
    if(timi > 1500*timafasti){
       dcvinstri->setSpeed(0);
       dchaegri->setSpeed(0);
      delay(30);
      servobeygja.write(80);
      delay(30);
      break;
    }
  }

timataka=millis();
  while(1){
    Serial.println("while lykkja 3");
    timi=millis()-timataka;
    dcvinstri->setSpeed(80*hradafasti);
    dchaegri->setSpeed(80*hradafasti);
    dcvinstri->run(FORWARD);
    dchaegri->run(FORWARD);
    if(timi>2300){
      dcvinstri->setSpeed(0);
       dchaegri->setSpeed(0);
      delay(30);
      break;
    }
  }

  servoarmur.write(110);


servobeygja.write(55); // beygjum til haegri

      
  // Set the speed to start, from 0 (off) to 255 (max speed)
  dcvinstri->setSpeed(80);
  dchaegri->setSpeed(80);
  dcvinstri->run(FORWARD);
  dchaegri->run(FORWARD);

    int servoinn;
    unsigned long timeToSenz, timeToSenz2;
    timeToSenz2 = millis();
    
    // keyrum eftir vasshliðið
    // servo i midju 80, 80+ fer bilinn til vinstri, laegra en 80 fer til haegri
    start: // ef skynajarinn byrjar a undan takkanum forum id hingaad
     /*int takkihjol = digitalRead(pushbutton);
     int takki = digitalRead(pushbutton2);*/
     int counter = 0;
     int graduCounter = 0;

     // beygjum til haegri ad kannti
     while(timeToSenz2 < 1350){
       timeToSenz2 = millis()-timeToSenz2;
       Serial.println("a ad vera 55");
       Serial.println(servobeygja.read());
       
     }

     servoarmur.write(5); // setjum arminn nidur
     delay(650); // debouch utaf takka vesseni

servobeygja.write(79);



     //lykkjan hans þors byrjar !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
     timataka=millis();
//nidri med arminn rettir sig af
while(1){
        Serial.println("while lykkja 9");
        timi=millis()-timataka;
        delay(50); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delayMicroseconds
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
        Serial.println("fyrirr lykkju");
        Serial.println(takkihjol);
        Serial.println(takki);

    if(takki == 0 || oldtakki == 0 ){
      yttatakka2:
      Serial.println("Erum konnir i if lykkjjjuuunua");
      Serial.println(takkihjol);
      Serial.println(takki);
      
      break;
    }
    /*if(35<Sensorljosastaur && Sensorljosastaur < 55){
      delay(300);
      goto yttatakka;
    }*/
      //ef takkahjol er fyrir utan braut
      if(takkihjol == 0 && oldtakkihjol == 0){
        //setjum takkann adeins nedar ef buinn ad vera ad i 4 sek
        if(timi>4000){
          servoarmur.write(2);
          delay(600);
        }
        //ef ljosastaur skynjar ad hann er inni 
        if(abs(Sensorljosastaur- ljosastaurgildi) <= 2 && abs(Sensorljosastaurold- ljosastaurgildi) <= 2){
          servobeygja.write(80);
          delay(150);
        }
        //annars ef hann er utaf
        else
        {
                if(counter2>6){
                   servobeygja.write(80);
                    delay(150);
                }
                //fyrstu thrju skipti bakkar
                else if(counter<2){
                dcvinstri->setSpeed(0);
                dchaegri->setSpeed(0);
                delay(35);
                servobeygja.write(60);
                delay(35);
                servoarmur.write(100);
                delay(700);
                dcvinstri->setSpeed(90);
                dchaegri->setSpeed(90);
                dcvinstri->run(BACKWARD);
                dchaegri->run(BACKWARD);
                delay(700); 
                dcvinstri->setSpeed(0);
                dchaegri->setSpeed(0);
                delay(35);
                servobeygja.write(80);
                delay(30);
                if(timi>4000){
                  servoarmur.write(2);
                }
                else{servoarmur.write(5);}
                delay(600);
                counter=counter+1;
                }
                //fjorda hvert skipti fer afram og beygir til vinstri
                else if (counter>=2){
                  dcvinstri->setSpeed(0);
                dchaegri->setSpeed(0);
                delay(35);
                servobeygja.write(100);
                delay(35);
                servoarmur.write(100);
                delay(700);
                dcvinstri->setSpeed(90);
                dchaegri->setSpeed(90);
                dcvinstri->run(FORWARD);
                dchaegri->run(FORWARD);
                timataka2=millis();
                while(timi2 < 700){
                  timi2=millis()-timataka;
                  takki = digitalRead(pushbutton2);
                  if(takki == 0){
                    goto yttatakka2;
                  }
                  }

                dcvinstri->setSpeed(0);
                dchaegri->setSpeed(0);
                delay(35);
                servobeygja.write(80);
                delay(30);
                servoarmur.write(5);
                delay(600);
                counter=0;
                }
                counter2=counter2+1;     
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


    
    Sensorljosastaurold=Sensorljosastaur;
    oldtakkihjol=takkihjol;
   oldtakki=takki;
  
}

//lykkjan hans þors buin !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111111
  
          
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servoarmur.write(120);
          servobeygja.write(90);
          delay(1000);
          dcvinstri->setSpeed(75);
          dchaegri->setSpeed(75);
          delay(1500);
          dcvinstri->setSpeed(0);
          dchaegri->setSpeed(0);
          servoarmur.write(10);
          delay(1500);
          servoarmur.write(105);
          Serial.println("We have hammerd!");

      
      
  
  
  // Byrjum ad henda golf bolta nidur!!!!!!!!!!!!!!!!!!!
      
      
servobeygja.write(80);
dcvinstri->setSpeed(90);
dchaegri->setSpeed(90);
dcvinstri->run(FORWARD);
dchaegri->run(FORWARD);
counter = 0;
delay(30);
dcvinstri->setSpeed(0);
dchaegri->setSpeed(0);
do{
  Serial.println("KOMINN I INGVARS!!");
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
          if(Sensorljosastaur > 35){
          servobeygja.write(90);
          dcvinstri->setSpeed(100);
          dchaegri->setSpeed(100);
          dcvinstri->run(BACKWARD);
          dchaegri->run(BACKWARD);
          delay(100);
          servobeygja.write(60);
          dcvinstri->setSpeed(100);
          dchaegri->setSpeed(100);
          dcvinstri->run(BACKWARD);
          dchaegri->run(BACKWARD);
          }
          
          if(Sensorframanvinstri > Sensorframanhaegri + 2 && Sensorframanhaegri != 0 && Sensorframanvinstri!= 0){
          //servobeygja.write(78);
          // vinstri lengri fra svo vid beygjum til haegri
          servobeygja.write(170);
          dcvinstri->setSpeed(100);
          dchaegri->setSpeed(100);
          dcvinstri->run(FORWARD);
          dchaegri->run(BACKWARD);
          
          Serial.println("VINSTRI ER STARERI");
          }
          else if(Sensorframanhaegri > Sensorframanvinstri + 2 && Sensorframanhaegri != 0 && Sensorframanvinstri!= 0){
          //servobeygja.write(83);
          servobeygja.write(170);
          servobeygja.write(170);
          dcvinstri->setSpeed(100);
          dchaegri->setSpeed(100);
          dcvinstri->run(BACKWARD);
          dchaegri->run(FORWARD);
          Serial.println("HAEGRI ER STAERIII");
          }
          
          else if(abs(Sensorframanvinstri - Sensorframanhaegri) < 3 && Sensorframanhaegri != 0 && Sensorframanvinstri!= 0 ){
            counter++;
            //servobeygja.write(80);  
            Serial.println("FIRST COUNTER!!!");
          }
  
}
while(counter < 2);



// finnum stad sem vid viljum keyra fra
dcvinstri->setSpeed(0);
dchaegri->setSpeed(0);

delay(50);
dcvinstri->setSpeed(70);
dchaegri->setSpeed(70);
dcvinstri->run(BACKWARD);
dchaegri->run(BACKWARD);
Serial.println("GOING BACKWARDS!!");

counter = 0;
counter2 = 0;

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
              servobeygja.write(82);

              dcvinstri->setSpeed(70);
              dchaegri->setSpeed(70);
              //delay(80);
              dcvinstri->run(FORWARD);
              dchaegri->run(FORWARD);
               //delay(200);
            Serial.println("FORUM NAER1111111111");
            Serial.println(Sensorframanvinstri);
            Serial.println(Sensorframanhaegri);
            counter = 0;
} 

else if (Sensorframanvinstri<= 118 || Sensorframanhaegri<=118){
              servobeygja.write(85);
              dcvinstri->setSpeed(70);
              dchaegri->setSpeed(70);
              delay(80);
              dcvinstri->run(BACKWARD);
              dchaegri->run(BACKWARD);
               Serial.println("FORUM FAEr 2222222222222222222");
            Serial.println(Sensorframanvinstri);
            Serial.println(Sensorframanhaegri);
            counter = 0;
            counter2++;

}
  
         
}
while(counter < 3);


dcvinstri->setSpeed(0);
dchaegri->setSpeed(0);

counter = 0;
counter2 = counter2/4; // kannski ekki 
servobeygja.write(92+graduCounter);
dcvinstri->setSpeed(90);
dchaegri->setSpeed(90);
dcvinstri->run(FORWARD);
dchaegri->run(FORWARD);


// legjum a hann og forum ad boltanum

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
        
        dcvinstri->setSpeed(0);
        dchaegri->setSpeed(0);
        delay(1000);
        servobeygja.write(65);
        
        dcvinstri->setSpeed(110);
        dchaegri->setSpeed(110);
        dcvinstri -> run(FORWARD);
        dchaegri -> run(FORWARD);
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

        dcvinstri->setSpeed(200);
        dchaegri->setSpeed(200);
        dcvinstri -> run(FORWARD);
        dchaegri -> run(FORWARD);
      
       }
       
       // erum bunnir ad berja takkan forum nu og drullum tessari golf kulu nidur!
       

//
void loop() {
  // put your main code here, to run repeatedly:

}

