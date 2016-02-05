

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
#define PING_PIN6 10
//#define PING_PIN7 10
#define PING_PIN8 11
#define PING_PIN9 12

unsigned int duration,Sensor1,Sensor2,Sensor3,Sensor4,Sensor5,Sensor6,Sensor7,Sensor8, Sensor9,Sensor2old, Sensor3old, Sensor4old, Sensor5old, Sensor6old; 
unsigned long timeToMovieFw, timeToTurn;
int pushbutton = 3 ; // takki a hjolum
int pushbutton2 = 2; // her eru enginn hjol


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
    
myservo2.attach(9);  // attaches the servo on pin 9 to the servo object

myservo.attach(10);  // attaches the servo on pin 9 to the servo
 
myservo2.write(110);


myservo.write(55); // beygjum til haegri

      
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(90);
  myMotor2->setSpeed(90);
  myMotor->run(FORWARD);
  myMotor2->run(FORWARD);

    int servoinn;
    unsigned long timeToSenz, timeToSenz2;
    timeToSenz2 = millis();
    
    // keyrum eftir vasshliðið
    // servo i midju 80, 80+ fer bilinn til vinstri, laegra en 80 fer til haegri
     int buttonState = digitalRead(pushbutton);
     int buttonState2 = digitalRead(pushbutton2);
     int counter = 0;
     Sensor1 = 0;
     // beygjum til haegri ad kannti
     while(timeToSenz2 < 1150){
       timeToSenz2 = millis()-timeToSenz2;
       Serial.println("a ad vera 55");
       Serial.println(myservo.read());
       
     }
     
     myservo2.write(3); // setjum arminn nidur
     //delay(30);
   
   //chillum adeins
     myMotor->setSpeed(0);
     myMotor2->setSpeed(0);
  
  // rettum bilinn vid
     myservo.write(120);
     //delay(10);
     Serial.println("a ad vera 120");
     Serial.println(myservo.read());
     
    myMotor->setSpeed(100);
    myMotor2->setSpeed(100);
    myMotor->run(FORWARD);
    myMotor2->run(FORWARD);
  
    int count = 0;
    int pos = 120; // hofum 120 tvi myservo er i 120 svo breytum vid i while lykkjuni eftir tvi sem vid a
    while(1){
      int oldButtonState = buttonState;
      int oldButtonState2 = buttonState2;

     
     timeToSenz2 = millis()-timeToSenz2;
     
          
     if(Sensor1>50){
     
     }
     
     else if(sensorar haegrameigin er staeri en vinstrameigin){
     
       count = count + 1
       servo.write(pos - 1)
     }
     
     else if(sensorar vintsrameigin staeri en haegrameigin){
     count = count + 1
     servo.write(pos+1)
     }
     
     else if timeToSenz2>3600 && timeToSenz2 < 5000){
       myservo.write(75);}
       
     else{
       myservo.write(80);
     }

     
     Serial.println("Seinni while, a ad vera 75");
     Serial.println(myservo.read());
      buttonState = digitalRead(pushbutton);
      buttonState2 = digitalRead(pushbutton2);
      
      
      //Serial.println(buttonState);
      //counter = counter + 1;
      /*if ((millis() - timeToSenz2) > 100){
        myservo.write(70);
      }*/
      
      
      //delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay
      
     /* if (timeToSenz % 50 == 0){
        duration = sonar1.ping();// Send ping, get ping time in microseconds 
        Sensor1 = duration/US_ROUNDTRIP_CM;
        Serial.println("its time to Senz!");
        Serial.println(timeToSenz);
      }*/
      
      
      if(Sensor1>90){
        while (counter < 1000){
        myMotor ->setSpeed(0);
        myMotor2 -> setSpeed(0);
        myservo.write(55);
       
        myMotor ->setSpeed(70);
        myMotor2 -> setSpeed(70);
        myMotor ->run(BACKWARD);
        myMotor2 -> run(BACKWARD);
        counter = counter + 1;
        }
        while(counter < 2000){
            
         myMotor ->setSpeed(0);
         myMotor2 -> setSpeed(0);
         myservo.write(100);
       
         myMotor ->setSpeed(70);
         myMotor2 -> setSpeed(70);
         myMotor ->run(BACKWARD);
         myMotor2 -> run(BACKWARD);
          counter = counter+1;
          }
          
         myMotor ->setSpeed(0);
         myMotor2 -> setSpeed(0);
         myservo.write(60);
       
        myMotor ->setSpeed(90);
        myMotor2 -> setSpeed(90);
        myMotor ->run(FORWARD);
        myMotor2 -> run(FORWARD);
       
      }
      
      if(buttonState == 0 && oldButtonState == 1 /*|| Sensor1 > 70*/ ){
        // forum i tessa if setningu ef takka gildi var ad breytast
        Serial.println("Hallo fyrsta if lykkjan godan daginn");
        Serial.println(buttonState);
        Serial.println(oldButtonState);
        Serial.println("bottun state out!");
        myMotor ->setSpeed(0);
        myMotor2 -> setSpeed(0);
        
        myservo.write(90);
        myservo2.write(0); // forum alla leid nidur, her er armur utfyrir braut
        
        myMotor ->setSpeed(90);
        myMotor2 -> setSpeed(90);
        myMotor ->run(FORWARD);
        myMotor2 -> run(FORWARD);
        
        while(1){
          Serial.println(buttonState2);
          Serial.println("Kominn of langt!");
          buttonState2 = digitalRead(pushbutton2);
          if(buttonState2 == 0){
            Serial.println("its hammer time!");
             // nu vitum vid ad vid erum hja takkanum
             break;
    
          }
        }
        myMotor->setSpeed(0);
        myMotor2->setSpeed(0);
        myservo2.write(120);
        delay(1000);
        myMotor->setSpeed(75);
        myMotor2->setSpeed(75);
        delay(1005);
        myMotor->setSpeed(0);
        myMotor2->setSpeed(0);
        myservo2.write(10);
        delay(1500);
        myservo2.write(110);
        Serial.println("We have hammerd!");
        break;
      }
/*else if(Sensor1>70){
        while (counter < 1000){
        myMotor ->setSpeed(0);
        myMotor -> setSpeed(0);
        myservo.write(55);
       
        myMotor ->setSpeed(70);
        myMotor -> setSpeed(70);
        myMotor ->run(BACKWARD);
        myMotor -> run(BACKWARD);
        counter = counter + 1;
        }
        while(counter < 2000){
            
         myMotor ->setSpeed(0);
         myMotor -> setSpeed(0);
         myservo.write(100);
       
         myMotor ->setSpeed(70);
         myMotor -> setSpeed(70);
         myMotor ->run(BACKWARD);
         myMotor -> run(BACKWARD);
          counter = counter+1;
          }
          
         myMotor ->setSpeed(0);
         myMotor -> setSpeed(0);
         myservo.write(90);
       
        myMotor ->setSpeed(70);
        myMotor -> setSpeed(70);
        myMotor ->run(FORWARD);
        myMotor -> run(FORWARD);
       
      }
      
  */    
    }
  
    
    // keyrum a tima i midjuna og athugum hvort hornskynjararnir hafi somu gildi. þa er bilinn bein og vid reddy to go
    unsigned long timeTomiddle = millis();
    myservo.write(100);
    myMotor->setSpeed(90);
    myMotor2->setSpeed(90);
    myMotor->run(FORWARD);
    myMotor2->run(FORWARD);
    
    
    while(1){
    //timeTomiddle = timeTomiddle - millis();
   /* if ((millis()-timeTomiddle) % 50 == 0){
        duration = sonar2.ping();// Send ping, get ping time in microseconds 
        Sensor2 = duration/US_ROUNDTRIP_CM;
        duration = sonar5.ping();// Send ping, get ping time in microseconds 
        Sensor5 = duration/US_ROUNDTRIP_CM;
      }*/
    /*  
    if(timeTomiddle >= 4000 || Sensor2 == Sensor5 && Sensor2 != 0){
      if(Sensor2 == Sensor5){
        myMotor->setSpeed(0);
        myMotor->setSpeed(0);
        Serial.println("Billinn er rettur og kominn i loopu!!!");
        myservo.write(80);
        
        myMotor->setSpeed(70);
        myMotor->setSpeed(70);
        myMotor->run(FORWARD);
        myMotor2->run(FORWARD);
      }
    }
    }*/
}
}

void loop(){}
