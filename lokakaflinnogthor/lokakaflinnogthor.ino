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

int timataka;
int timi=0;
int counter2 =0;
int ljosastaurgildi=30;
int counter=0;
int timataka2;
int timi2=0;
unsigned int duration,Sensorljosastaur, Sensorljosastaurold, Sensorframanhaegri,Sensorframanhaegriold,Sensorframanmidja,Sensorframanmidjaold,Sensorframanvinstri,Sensorframanvinstriold,Sensorvinstri, Sensorvinstriold,Sensoraftanvinstri, Sensoraftanvinstriold, Sensoraftanhaegri, Sensoraftanhaegriold; 
int oldtakki, oldtakkihjol;

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

void setup() {
 Serial.begin(9600);           // set up Serial library at 9600 bps
  
  AFMS.begin(2000);  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  //delay(30);
  
  pinMode(pushbutton, INPUT);
  pinMode(pushbutton2, INPUT);
    
servoarmur.attach(9);  // attaches the servo on pin 9 to the servo object

servobeygja.attach(10);  // attaches the servo on pin 9 to the servo
 oldtakki = 1;
 
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
     int takkihjol = digitalRead(pushbutton);
     int takki = digitalRead(pushbutton2);
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
        Serial.println("fyrirr lykkju");
        Serial.println(takkihjol);
        Serial.println(takki);

    if(takki == 0 || oldtakki == 0 ){
      yttatakka:
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

//lykkjan hans þors !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111111
   /*
   //chillum adeins
     dcvinstri->setSpeed(0);
     dchaegri->setSpeed(0);
  
  // rettum bilinn vid
     servobeygja.write(111);
     //delay(10);
     Serial.println("a ad vera 120");
     Serial.println(servobeygja.read());
     
    dcvinstri->setSpeed(105);
    dchaegri->setSpeed(105);
    dcvinstri->run(FORWARD);
    dchaegri->run(FORWARD);
    //takkihjol = 1;
    
    int pos = 110; // hofum 110 tvi myservo er i 120 svo breytum vid i while lykkjuni eftir tvi sem vid a
    while(1){
      int oldtakkihjol = takkihjol;
      int oldtakki = takki;
      Serial.println("Her er button state");
      Serial.println(takkihjol);
     
     
     
       if (timeToSenz2>3600 && timeToSenz2 < 4000){
          dcvinstri->setSpeed(70);
          dchaegri->setSpeed(70);
          dcvinstri->run(FORWARD);
          dchaegri->run(FORWARD);
          servobeygja.write(78);
        }
         

   
       Serial.println("Seinni while, a ad vera 75");
       Serial.println(servobeygja.read());
        takkihjol = digitalRead(pushbutton);
        takki = digitalRead(pushbutton2);
        
        
        
         timeToSenz2 = millis()-timeToSenz2;
       
       // hofum 50ms milli skynjana
       if (timeToSenz2 % 50 == 0){
          duration = sonarljosastaur.ping();// Send ping, get ping time in microseconds 
          Sensorljosastaur = duration/US_ROUNDTRIP_CM;
          
          Serial.println("its time to Senz!");
          Serial.println(timeToSenz2);
       
       }
       
       if(Sensorljosastaur>=50){
       
          dcvinstri -> setSpeed(0);
          dchaegri -> setSpeed(0);
          servobeygja.write(65);
          takkihjol = digitalRead(HIGH); // seigjum ad takkin se alltaf 1 og tokum arm upp
          servoarmur.write(110);
          delay(1000);
          while(Sensorljosastaur>=50){
              if (timeToSenz2 % 50 == 0){
              duration = sonarljosastaur.ping();// Send ping, get ping time in microseconds 
              Sensorljosastaur = duration/US_ROUNDTRIP_CM;
              
              Serial.println("its time to Senz!");
              Serial.println(timeToSenz2);
           
             }
              dcvinstri -> setSpeed(70);
              dchaegri -> setSpeed(70);
              dcvinstri ->run(BACKWARD);
              dchaegri -> run(BACKWARD);
              Serial.println("ERUM I WHILEEEEEE");
              Serial.println(Sensorljosastaur);
         
          }
          //delay(1000);
          servobeygja.write(82);
          goto start; // byrjum uppa nytt
          
          Serial.println("SENSOR FRAMAN VIRKUR A UNDAN TAKKA HVAD SKAL GERA");
       }
        
        
        if(takkihjol == 0 && oldtakkihjol == 1){
          // forum i tessa if setningu ef takka gildi var ad breytast
          Serial.println("Hallo fyrsta if lykkjan godan daginn");
          Serial.println(takkihjol);
          Serial.println(oldtakkihjol);
          Serial.println("bottun state out!");
          dcvinstri ->setSpeed(0);
          dchaegri -> setSpeed(0);
          delay(100);
          dcvinstri ->setSpeed(70);
          dchaegri -> setSpeed(70);
          dcvinstri -> run(FORWARD);
          dchaegri -> run(FORWARD);
          
          
          
          servobeygja.write(68);
          timeToSenz = millis();
          while(millis() - timeToSenz < 400){
          // her erum vid i raun ad beygja i 700 ms 76 gradur sja ad ofan
          }
          servoarmur.write(0); // forum alla leid nidur, her er armur utfyrir braut
          
          servobeygja.write(95);
          timeToSenz = millis();
          while(millis() - timeToSenz < 700){
          // her erum vid i raun ad beygja i 700 ms 76 gradur sja ad ofan
          }
          servobeygja.write(80); // vonandi bunnir ad retta hann af og keyrum beint!
          
          dcvinstri ->setSpeed(90);
          dchaegri -> setSpeed(90);
          dcvinstri ->run(FORWARD);
          dchaegri -> run(FORWARD);
          
          while(1){
            Serial.println(takki);
            Serial.println("Kominn of langt!");
            takki = digitalRead(pushbutton2);
            
            timeToSenz2 = millis()-timeToSenz2;
       
       // hofum 50ms milli skynjana
       if (timeToSenz2 % 50 == 0){
          duration = sonarljosastaur.ping();// Send ping, get ping time in microseconds 
          Sensorljosastaur = duration/US_ROUNDTRIP_CM;
         
          
          Serial.println("its time to Senz!");
          Serial.println(Sensorljosastaur);
       
       }
            
       if(Sensorljosastaur>=50){
         timeToSenz = millis(); // getum ekki notad timetosenz2 tvi tad fokkar i while lykkjunni
         if(millis()-timeToSenz < 300 && counter == 0){
         servobeygja.write(100);
         }
         servobeygja.write(82);
         Serial.println("Ljosastaur > 50");
         counter++;
       
       }
       
       
                 
            if(takki == 0){
              Serial.println("its hammer time!");
               // nu vitum vid ad vid erum hja takkanum
               break;
      
            }
          }
          */
          
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
       
       
       
     
void loop(){}
