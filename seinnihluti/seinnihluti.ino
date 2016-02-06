

//afram haegri gradur 30 <70
//afram vinstri gradur 100 > 70

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
Adafruit_DCMotor *lokMotor = AFMS.getMotor(3);
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
 
servoarmur.write(110);


servobeygja.write(55); // beygjum til haegri

      
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(80);
  myMotor2->setSpeed(80);
  myMotor->run(FORWARD);
  myMotor2->run(FORWARD);

    int servoinn;
    unsigned long timeToSenz, timeToSenz2;
    timeToSenz2 = millis();
    
    // keyrum eftir vasshliðið
    // servo i midju 80, 80+ fer bilinn til vinstri, laegra en 80 fer til haegri
    start: // ef skynajarinn byrjar a undan takkanum forum id hingaad
     int buttonState = digitalRead(pushbutton);
     int buttonState2 = digitalRead(pushbutton2);
     int counter = 0;
     int graduCounter = 0;

     // beygjum til haegri ad kannti
     while(timeToSenz2 < 1050){
       timeToSenz2 = millis()-timeToSenz2;
       Serial.println("a ad vera 55");
       Serial.println(servobeygja.read());
       
     }
     
     servoarmur.write(3); // setjum arminn nidur
     delay(650); // debouch utaf takka vesseni
   
   //chillum adeins
     myMotor->setSpeed(0);
     myMotor2->setSpeed(0);
  
  // rettum bilinn vid
     servobeygja.write(111);
     //delay(10);
     Serial.println("a ad vera 120");
     Serial.println(servobeygja.read());
     
    myMotor->setSpeed(105);
    myMotor2->setSpeed(105);
    myMotor->run(FORWARD);
    myMotor2->run(FORWARD);
    //buttonState = 1;
    int count = 0;
    int pos = 110; // hofum 110 tvi myservo er i 120 svo breytum vid i while lykkjuni eftir tvi sem vid a
    while(1){
      int oldButtonState = buttonState;
      int oldButtonState2 = buttonState2;
      Serial.println("Her er button state");
      Serial.println(buttonState);
     
     
     
       if (timeToSenz2>3600 && timeToSenz2 < 4000){
          myMotor->setSpeed(70);
          myMotor2->setSpeed(70);
          myMotor->run(FORWARD);
          myMotor2->run(FORWARD);
          servobeygja.write(78);
        }
         

   
       Serial.println("Seinni while, a ad vera 75");
       Serial.println(servobeygja.read());
        buttonState = digitalRead(pushbutton);
        buttonState2 = digitalRead(pushbutton2);
        
        
        
         timeToSenz2 = millis()-timeToSenz2;
       
       // hofum 50ms milli skynjana
       if (timeToSenz2 % 50 == 0){
          duration = sonarljosastaur.ping();// Send ping, get ping time in microseconds 
          Sensorljosastaur = duration/US_ROUNDTRIP_CM;
          
          Serial.println("its time to Senz!");
          Serial.println(timeToSenz2);
       
       }
       
       if(Sensorljosastaur>=50){
       
          myMotor -> setSpeed(0);
          myMotor2 -> setSpeed(0);
          servobeygja.write(65);
          buttonState = digitalRead(HIGH); // seigjum ad takkin se alltaf 1 og tokum arm upp
          servoarmur.write(110);
          delay(1000);
          while(Sensorljosastaur>=50){
              if (timeToSenz2 % 50 == 0){
              duration = sonarljosastaur.ping();// Send ping, get ping time in microseconds 
              Sensorljosastaur = duration/US_ROUNDTRIP_CM;
              
              Serial.println("its time to Senz!");
              Serial.println(timeToSenz2);
           
             }
              myMotor -> setSpeed(70);
              myMotor2 -> setSpeed(70);
              myMotor ->run(BACKWARD);
              myMotor2 -> run(BACKWARD);
              Serial.println("ERUM I WHILEEEEEE");
              Serial.println(Sensorljosastaur);
         
          }
          //delay(1000);
          servobeygja.write(82);
          goto start; // byrjum uppa nytt
          
          Serial.println("SENSOR FRAMAN VIRKUR A UNDAN TAKKA HVAD SKAL GERA");
       }
        
        
        if(buttonState == 0 && oldButtonState == 1){
          // forum i tessa if setningu ef takka gildi var ad breytast
          Serial.println("Hallo fyrsta if lykkjan godan daginn");
          Serial.println(buttonState);
          Serial.println(oldButtonState);
          Serial.println("bottun state out!");
          myMotor ->setSpeed(0);
          myMotor2 -> setSpeed(0);
          delay(100);
          myMotor ->setSpeed(70);
          myMotor2 -> setSpeed(70);
          myMotor -> run(FORWARD);
          myMotor2 -> run(FORWARD);
          
          
          
          servobeygja.write(68);
          timeToSenz = millis();
          while(millis() - timeToSenz < 700){
          // her erum vid i raun ad beygja i 700 ms 76 gradur sja ad ofan
          }
          servoarmur.write(0); // forum alla leid nidur, her er armur utfyrir braut
          
          servobeygja.write(95);
          timeToSenz = millis();
          while(millis() - timeToSenz < 700){
          // her erum vid i raun ad beygja i 700 ms 76 gradur sja ad ofan
          }
          servobeygja.write(80); // vonandi bunnir ad retta hann af og keyrum beint!
          
          myMotor ->setSpeed(90);
          myMotor2 -> setSpeed(90);
          myMotor ->run(FORWARD);
          myMotor2 -> run(FORWARD);
          
          while(1){
            Serial.println(buttonState2);
            Serial.println("Kominn of langt!");
            buttonState2 = digitalRead(pushbutton2);
            
            timeToSenz2 = millis()-timeToSenz2;
       
       // hofum 50ms milli skynjana
       if (timeToSenz2 % 50 == 0){
          duration = sonarljosastaur.ping();// Send ping, get ping time in microseconds 
          Sensorljosastaur = duration/US_ROUNDTRIP_CM;
          
         /* duration = sonarframanhaegri.ping();// Send ping, get ping time in microseconds 
          Sensorframanhaegri = duration/US_ROUNDTRIP_CM;
          
          duration = sonarframanmidja.ping();// Send ping, get ping time in microseconds 
          Sensorframanmidja = duration/US_ROUNDTRIP_CM;
          
          duration = sonarframanvinstri.ping();// Send ping, get ping time in microseconds 
          Sensorframanvinstri = duration/US_ROUNDTRIP_CM;*/
          
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
       
       
                 
            if(buttonState2 == 0){
              Serial.println("its hammer time!");
               // nu vitum vid ad vid erum hja takkanum
               break;
      
            }
          }
          myMotor->setSpeed(0);
          myMotor2->setSpeed(0);
          servoarmur.write(120);
          delay(1000);
          myMotor->setSpeed(75);
          myMotor2->setSpeed(75);
          delay(1500);
          myMotor->setSpeed(0);
          myMotor2->setSpeed(0);
          servoarmur.write(10);
          delay(1500);
          servoarmur.write(105);
          Serial.println("We have hammerd!");
          break;
        }
      }
      
      
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
graduCounter = 0;

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
              servobeygja.write(75);

              myMotor->setSpeed(70);
              myMotor2->setSpeed(70);
              //delay(80);
              myMotor->run(FORWARD);
              myMotor2->run(FORWARD);
               //delay(200);
            Serial.println("FORUM NAER1111111111");
            Serial.println(Sensorframanvinstri);
            Serial.println(Sensorframanhaegri);
            counter = 0;
} 

else if (Sensorframanvinstri<= 118 || Sensorframanhaegri<=118){
              servobeygja.write(83);
              myMotor->setSpeed(70);
              myMotor2->setSpeed(70);
              delay(70);
              myMotor->run(BACKWARD);
              myMotor2->run(BACKWARD);
               Serial.println("FORUM FAEr 2222222222222222222");
            Serial.println(Sensorframanvinstri);
            Serial.println(Sensorframanhaegri);
            counter = 0;
            graduCounter++;

}
  
         
}
while(counter < 3);


myMotor->setSpeed(0);
myMotor2->setSpeed(0);

counter = 0;
graduCounter = graduCounter/4; // kannski ekki 
servobeygja.write(92+graduCounter);
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
       
       // erum bunnir ad berja takkan forum nu og drullum tessari golf kulu nidur!
       
       
       
     
void loop(){}
