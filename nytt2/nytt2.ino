

//afram haegri gradur 30 <80
//afram vinstri gradur 100 > 80

#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h>


#define PING_PIN1 4 // Arduino pin for both trig and echo
#define PING_PIN2 5 // Arduino pin for both trig and echo
//#define PING_PIN3 6
#define PING_PIN4 6
#define PING_PIN5 7
#define PING_PIN6 8
#define PING_PIN7 9
#define PING_PIN8 10
#define PING_PIN9 11

unsigned int duration,Sensor1,Sensor2,Sensor3,Sensor4,Sensor5,Sensor6,Sensor7,Sensor8, Sensor9,Sensor2old, Sensor3old, Sensor4old, Sensor5old, Sensor6old; 
unsigned long timeToMovieFw, timeToTurn, startTimeBw, TimeToPing;

NewPing sonar1(PING_PIN1, PING_PIN1 );
NewPing sonar2(PING_PIN2, PING_PIN2 );
NewPing sonar3(PING_PIN3, PING_PIN3 );
NewPing sonar4(PING_PIN4, PING_PIN4 );
NewPing sonar5(PING_PIN5, PING_PIN5 );
NewPing sonar6(PING_PIN6, PING_PIN6 );
//NewPing sonar7(PING_PIN7, PING_PIN7 );
NewPing sonar8(PING_PIN8, PING_PIN8 );
NewPing sonar9(PING_PIN9, PING_PIN9 );

Servo myservo;
Servo myservo2;

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
  myservo2.attach(9);  // attaches the servo on pin 9 to the servo object

  myservo.attach(10);  // attaches the servo on pin 9 to the servo
  delay(15);
  myservo2.write(135);
  delay(15);
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(60);
  myMotor2->setSpeed(60);
  myMotor->run(FORWARD);
  myMotor2->run(FORWARD);

    //keyra afram i byrjun
  while(1){

        Serial.println("servo armur");
        Serial.println(myservo2.read());
        Serial.println("while lykkja 1");
        //myservo2.write(140);
        delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonar6.ping();// Send ping, get ping time in microseconds 
        Sensor6 = duration/US_ROUNDTRIP_CM;// convert time into distance
    //    duration = sonar7.ping();// Send ping, get ping time in microseconds 
      //  Sensor7 = duration/US_ROUNDTRIP_CM;// convert time into distance

        //Servo stilltur aðeins til vinstri
        myservo.write(85);              // tell servo to go to position in variable 'pos'
        

        Serial.println("myservo is");
        Serial.println(myservo.read());

        //skynjar sulu+raudan takka
        if (/*Sensor6 < 35 && Sensor6 != 0 && */Sensor6 <35 && Sensor6 != 0 && Sensor6old<35 && Sensor6old!=0) {
            delay(500);
            //Stoppar
            myMotor->setSpeed(0);
            myMotor2->setSpeed(0);
            Serial.println("vinstri sensor");
            Serial.println(Sensor6);
            //skrifar 40 gradur á servoinn til að geta beygt og bakkað
            myservo.write(45);
            delay(25);
            myservo2.write(140);
            break;

            }
            Sensor6old=Sensor6;
    }

    TimeToPing=millis();
    startTimeBw = millis();
    while(1){
      //beygir thar til skynjar takka ad framan
      timeToMovieFw = millis() - startTimeBw;
        Serial.println("while lykkja 2");
        //Serial.println("servo armur");
        //Serial.println(myservo2.read());
        //myservo2.write(140);

         // delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay
         Serial.println("timetoping");
         Serial.println(TimeToPing);
         if((millis()-TimeToPing) % 50 ==0)
         {
        duration = sonar2.ping();// Send ping, get ping time in microseconds 
        Sensor2 = duration/US_ROUNDTRIP_CM;// convert time into distance
        //duration = sonar3.ping();// Send ping, get ping time in microseconds 
        //Sensor3 = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonar4.ping();// Send ping, get ping time in microseconds 
        Sensor4 = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonar5.ping();// Send ping, get ping time in microseconds 
        Sensor5 = duration/US_ROUNDTRIP_CM;// convert time into distance
        Serial.println("mod virkar!");
         }
          /*SonarSensor(trigPin2, echoPin2);
          Sensor2 = distance;*/
          //Bakkar
          myMotor->run(BACKWARD);
          myMotor2->run(BACKWARD);
          myMotor->setSpeed(80);
          myMotor2->setSpeed(80);


          Serial.println(Sensor3);
          //Ef skynjar súlu með takka í minna en 40 cm fjarlægð
          if((Sensor5 <40&& Sensor5 !=0 && Sensor4 <40&& Sensor4 !=0 && Sensor5old <40&& Sensor5old !=0 || Sensor4 <40&& Sensor4 !=0 && Sensor4old <40&& Sensor4old !=0 )&& timeToMovieFw>2000){

            delay(500);
            /*Serial.println("sensor3");
            Serial.println(Sensor3);
            Serial.println("sensor3old");
            Serial.println(Sensor3old);*/
            Serial.println("sensor2");
            Serial.println(Sensor2);
            Serial.println("sensor2old");
            Serial.println(Sensor2old);
            Serial.println("sensor4");
            Serial.println(Sensor4);
            Serial.println("sensor4old");
            Serial.println(Sensor4old);
            Serial.println("sensor5");
            Serial.println(Sensor5);
            Serial.println("sensor5old");
            Serial.println(Sensor5old);

            //stoppar
            myMotor->setSpeed(0);
            myMotor2->setSpeed(0);

            delay(25);
            //skrifar 80 gráður á sevoinn til að fara beint
             myservo.write(80);
            delay(505);
            break;
          }
          //geymum gamalt gildi á skynjurum til að bera saman við ný gildi
          Sensor4old=Sensor4;
          Sensor2old=Sensor2;
          Sensor5old=Sensor5;
    }

  startTimeBw = millis();
  while(1){
      //keyrir i att ad takka
    Serial.println("while lykkja 3");
    timeToMovieFw = millis() - startTimeBw;
        //notum skynjara 2-5 sem eru allir skynjarar að framan
        delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonar2.ping();// Send ping, get ping time in microseconds 
        Sensor2 = duration/US_ROUNDTRIP_CM;// convert time into distance
        //duration = sonar3.ping();// Send ping, get ping time in microseconds 
        //Sensor3 = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonar4.ping();// Send ping, get ping time in microseconds 
        Sensor4 = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonar5.ping();// Send ping, get ping time in microseconds 
        Sensor5 = duration/US_ROUNDTRIP_CM;// convert time into distance

    //keyrum beint áfram í átt að takka
    myMotor->run(FORWARD);
    myMotor2->run(FORWARD);
    myMotor->setSpeed(70);
    myMotor2->setSpeed(70);

    Serial.println(Sensor2);

          //stoppum ef einher skynjari er kominn nógu nálægt rauða takkanum
          if((Sensor2 <10 && Sensor2 !=0 && Sensor2old <10 && Sensor2old !=0|| /*Sensor3 < 10 && Sensor3 !=0 && Sensor3old <10 && Sensor3old !=0||*/ Sensor4 < 10 &&Sensor4!=0 && Sensor4old <10 && Sensor4old !=0||Sensor5 < 10 &&Sensor5!=0&&Sensor5old <10 && Sensor5old !=0) && timeToMovieFw>1500 ){

              Serial.println(" sensor2");
              Serial.println(Sensor2);

               /*Serial.println("sensor3");
               Serial.println(Sensor3);*/

               Serial.println("sensor4");
               Serial.println(Sensor4);
               
               Serial.println("sensor5");
               Serial.println(Sensor5);
              //stoppum
              myMotor->setSpeed(0);
              myMotor2->setSpeed(0);
              //bíðum í 2 sek eftir að boltar fara oní 
              delay(2000);


          //delay(25);
          /*
          //setjum servoinn á 120 gráður til að beygja og bakka
          myservo.write(120);*/
          //bokkum beint
          
          //delay(505);
          break;
      }
          Sensor4old=Sensor4;
          //Sensor3old=Sensor3;
          Sensor2old=Sensor2;
          Sensor5old=Sensor5;
  }

 startTimeBw = millis();

  while(1){
      //bakkar fra takka
   Serial.println("while lykkja 4");
   //notum lika timer þannig hann leggi ekki of fljott af stað
    timeToMovieFw = millis() - startTimeBw;

    //notum skynjara 2-5 sem eru allir skynjararnir að framan
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonar2.ping();// Send ping, get ping time in microseconds 
        Sensor2 = duration/US_ROUNDTRIP_CM;// convert time into distance
        /*duration = sonar3.ping();// Send ping, get ping time in microseconds 
        Sensor3 = duration/US_ROUNDTRIP_CM;// convert time into distance*/
        duration = sonar4.ping();// Send ping, get ping time in microseconds 
        Sensor4 = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonar5.ping();// Send ping, get ping time in microseconds 
        Sensor5 = duration/US_ROUNDTRIP_CM;// convert time into distance

        //bökkum
    myMotor->run(BACKWARD);
    myMotor2->run(BACKWARD);
    myMotor->setSpeed(80);
    myMotor2->setSpeed(80);

    
    //Serial.println(Sensor2);
    Serial.println("timeToMOvie");
    Serial.println(timeToMovieFw);

    //ef allir fjarlaegdarskynjararnir ad framan skynja meira en 30 cm
    if(Sensor2>30&&Sensor4>30&&Sensor5>30 && Sensor2old>30&&Sensor4old>30&&Sensor5old>30 && timeToMovieFw > 1500){
      myMotor->setSpeed(0);
        myMotor2->setSpeed(0);
        delay(25);
        //setjum servoinn í 45 /annig hann beygi til haegri
        myservo.write(45);
        delay(505);
        break;
        
    }
    /*
    //skynjum fjærvegginn. þe. þegar þeir skynja meira en 60 cm og skynjarinn lengst til vinstri á bílnum skynjar minna en 120 cm
    //svo við vitum að hann er fyrir framan vegginn en er ekki að skynja út af brautinni
    //og bíllinn hefur verið að bakka í 2.6 sek amk
    if(Sensor2>60&&Sensor2old>60&&/*Sensor3>60&&*//*Sensor4>60&&Sensor4old>60&&Sensor5>60&&Sensor5old>60&&Sensor5<120 && Sensor5old<120 && (timeToMovieFw > 2600 /*&& timeToMovieFw < 4000*/ /*) ){
       
        Serial.print(Sensor4);
        Serial.print("   ");
        Serial.print(Sensor5);
        //stoppum
        myMotor->setSpeed(0);
        myMotor2->setSpeed(0);
        delay(25);
        //setjum servoinn í 74 þannig hann beygi aðeins til vinstri
        myservo.write(74);
        delay(505);
        break;
    }*/
    Sensor2old=Sensor2;
    Sensor4old=Sensor4;
    Sensor5old=Sensor5;
  }
  while(1){
    Serial.println("while lykkja 4.5");
     myMotor->run(FORWARD);
      myMotor2->run(FORWARD);
      myMotor->setSpeed(70);
      myMotor2->setSpeed(70);
      //skynjum fjærvegginn. þe. þegar þeir skynja meira en 60 cm og skynjarinn lengst til vinstri á bílnum skynjar minna en 120 cm
    //svo við vitum að hann er fyrir framan vegginn en er ekki að skynja út af brautinni
    //og bíllinn hefur verið að bakka í 2.6 sek amk
    if(Sensor2>60&&Sensor2old>60&&/*Sensor3>60&&*/Sensor4>60&&Sensor4old>60&&Sensor5>60&&Sensor5old>60&&Sensor5<100 && Sensor5old<100 && (timeToMovieFw > 2600 /*&& timeToMovieFw < 4000*/ ) ){
       
        Serial.print(Sensor4);
        Serial.print("   ");
        Serial.print(Sensor5);
        //stoppum
        myMotor->setSpeed(0);
        myMotor2->setSpeed(0);
        delay(25);
        //setjum servoinn í 74 þannig hann beygi aðeins til haegri
        myservo.write(74);
        delay(505);
        break;

      
  }
  }

  startTimeBw = millis();
  while(1){
      //keyrir i att ad vegg
      Serial.println("while lykkja 5");
      reynaaftur:
      //notum tíma þannig hann beygi ekki of snemma
      timeToTurn = millis() - startTimeBw;
        //notum alla skynjara að framan
        delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay
        duration = sonar2.ping();// Send ping, get ping time in microseconds 
        Sensor2 = duration/US_ROUNDTRIP_CM;// convert time into distance
        /*duration = sonar3.ping();// Send ping, get ping time in microseconds 
        Sensor3 = duration/US_ROUNDTRIP_CM;// convert time into distance*/
        duration = sonar4.ping();// Send ping, get ping time in microseconds 
        Sensor4 = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonar5.ping();// Send ping, get ping time in microseconds 
        Sensor5 = duration/US_ROUNDTRIP_CM;// convert time into distance

      //förum beint áfram í átt að vegg
      myMotor->run(FORWARD);
      myMotor2->run(FORWARD);
      myMotor->setSpeed(70);
      myMotor2->setSpeed(70);

      Serial.println("i att ad vegg sensor 2:");
      Serial.println(Sensor2);
      //delay(2000);

          Serial.println("i att ad vegg sensor 4:");
          Serial.println(Sensor4);

          //ef bíllinn er minna en 40cm frá veggnum:
          // og hefur keyrt í amk 2 sek
         if( (Sensor2 < 40 && Sensor2!=0 && Sensor4 <40 && Sensor4!=0 ||/*  Sensor3 <40 && Sensor3!=0 && Sensor4 < 40 && Sensor4!=0||*/  Sensor5 <40 && Sensor5!=0 && Sensor4 < 40 && Sensor4!=0) && timeToTurn>1600){

              Serial.println(" sensor4");
              Serial.println(Sensor4);
              Serial.println(" sensor3");
              Serial.println(Sensor3);

              //stoppum bílinn
              
              myMotor->setSpeed(0);
              myMotor2->setSpeed(0);
              delay(25);
              //setjum servoinn í 45 gráður til að beygja
              myservo.write(45);
              delay(505);
              break;
              }

              //eða ef skynjarinn lengst til vinstri skynjar að bíllinn sé að keyra út af, þ.e. skynjar meira en 130 cm
        else if(Sensor5 >130){
          //látum servoinn í 65 graður svo hann fari ekki út af 
          Serial.println("skynjarinn lengst til vinstri skynjar að bíllinn sé að keyra út af, þ.e. skynjar meira en 130 cm");
              myMotor->setSpeed(0);
              myMotor2->setSpeed(0);
              delay(25);
              myservo.write(65);
              delay(35);
              myMotor->run(FORWARD);
              myMotor2->run(FORWARD);
              myMotor->setSpeed(70);
              myMotor2->setSpeed(70);
              while(Sensor5>120 || Sensor5old>120){
                Sensor5old=Sensor5;
                duration = sonar5.ping();// Send ping, get ping time in microseconds 
                Sensor5 = duration/US_ROUNDTRIP_CM;// convert time into distance
                
              }
              //ef skynjarinn lengst til vinstri er minna en 120 cm er hann ekki lengur að keyra út af svo förum beint
              //if(Sensor5 <120 && Sensor4!=0){
              myMotor->setSpeed(0);
              myMotor2->setSpeed(0);
              delay(25);
              myservo.write(80);
              delay(35);
              //goto reynaaftur;       
          }
          //eða ef vinstra horn bílsins klessir á hliðarvegginn, skynjarinn lengst til vinstri skynjar minna en 7 cm
          else if(Sensor5<7 && Sensor5!=0 && Sensor5old<7 && Sensor5old != 0&& timeToTurn>2000){
              /*startTimeBw = millis();
              timeToTurn = millis() - startTimeBw;*/
              Serial.println("vinstra horn bílsins klessir á hliðarvegginn, skynjarinn lengst til vinstri skynjar minna en 7 cm");
              myMotor->setSpeed(0);
              myMotor2->setSpeed(0);
              delay(25);
              myservo.write(110);
              delay(505);

              myMotor->run(BACKWARD);
              myMotor2->run(BACKWARD);
              myMotor->setSpeed(70);
              myMotor2->setSpeed(70);
              delay(2000);
              myMotor->setSpeed(0);
              myMotor2->setSpeed(0);
              delay(25);
              myservo.write(80);
              delay(505);
              break;
            }
            Sensor5old=Sensor5;
    }


    startTimeBw = millis();
    while(1){
      //beygir til haegri fra vegg
          Serial.println("while lykkja 6");
          reynaaftur2:
          timeToTurn = millis() - startTimeBw;
          delay(50);
          duration = sonar5.ping();// Send ping, get ping time in microseconds 
        Sensor5 = duration/US_ROUNDTRIP_CM;// convert time into distance
        duration = sonar1.ping();// Send ping, get ping time in microseconds 
        Sensor1 = duration/US_ROUNDTRIP_CM;// convert time into distance
          /*SonarSensor(trigPin4, echoPin4);
          Sensor4 = distance;
          SonarSensor(trigPin3, echoPin3);
          Sensor3 = distance;*/

          myMotor->run(FORWARD);
          myMotor2->run(FORWARD);
          myMotor->setSpeed(70);
          myMotor2->setSpeed(70);

          Serial.println(Sensor2);
          //delay(3000);
          
          if(timeToTurn>2000 && Sensor5 > 10){
          //beygir til vinstri,kominn framhja veggjum
          myMotor->setSpeed(0);
          myMotor2->setSpeed(0);
          delay(25);
          myservo.write(110);
          delay(505);
          //timeToTurn = millis() - startTimeBw;
          myMotor->run(FORWARD);
          myMotor2->run(FORWARD);
          myMotor->setSpeed(70);
          myMotor2->setSpeed(70);
          /*delay(2000);
          myMotor->setSpeed(0);
          myMotor2->setSpeed(0);*/
          break;
          }

          //eða ef vinstra horn bílsins klessir á hliðarvegginn, skynjainn lengst til vinstri skynjar minna en 7 cm
          else if(Sensor5<7 && Sensor5!=0 && Sensor5old<7 && Sensor5old != 0&& timeToTurn>2000){
              /*startTimeBw = millis();
              timeToTurn = millis() - startTimeBw;*/
              myMotor->setSpeed(0);
              myMotor2->setSpeed(0);
              delay(25);
              myservo.write(110);
              delay(505);

              myMotor->run(BACKWARD);
              myMotor2->run(BACKWARD);
              myMotor->setSpeed(70);
              myMotor2->setSpeed(70);
              delay(2000);
              myMotor->setSpeed(0);
              myMotor2->setSpeed(0);
              delay(25);
              myservo.write(80);
              delay(505);
              //goto reynaaftur2;
            }
            //eda ef sensor 1 skynjar ad hann er ad keyra ut af 
          else if(Sensor1>40){
            myMotor->setSpeed(0);
              myMotor2->setSpeed(0);
              delay(25);
              myservo.write(50);
              delay(505);

              myMotor->run(BACKWARD);
              myMotor2->run(BACKWARD);
              myMotor->setSpeed(80);
              myMotor2->setSpeed(80);
              delay(1000);
              myMotor->setSpeed(0);
              myMotor2->setSpeed(0);
              delay(25);
          }
            Sensor5old=Sensor5;
          }
          

          startTimeBw = millis();
          while(1){
            //keyrir fr' veggjum i att ad korfu
                  Serial.println("while lykkja 7");
            //notum tíma þannig hann beygi ekki of snemma
            
            timeToTurn = millis() - startTimeBw;
            //notum alla skynjara að framan
            delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay
            duration = sonar2.ping();// Send ping, get ping time in microseconds 
            Sensor2 = duration/US_ROUNDTRIP_CM;// convert time into distance
                      myMotor->run(FORWARD);
              myMotor2->run(FORWARD);
              myMotor->setSpeed(70);
              myMotor2->setSpeed(70);
            
          }


  
}

void loop() {
  // put your main code here, to run repeatedly:

}
