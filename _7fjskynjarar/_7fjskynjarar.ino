//this is a code for using a 4 pin hc sr04 sensor as a 3 pin ping sensor By robobot3112

#include <NewPing.h>

#define PING_PIN 4 // Arduino pin for both trig and echo

#define PING_PIN2 5 // Arduino pin for both trig and echo
#define PING_PIN3 6
#define PING_PIN4 7
#define PING_PIN5 8
//#define PING_PIN6 9
#define PING_PIN7 13 

//        #define trigPin1 2
  //  #define echoPin1 3

long duration, distance, RightSensor,BackSensor,FrontSensor,LeftSensor;

NewPing gunnar(PING_PIN, PING_PIN );

NewPing sonar(PING_PIN2, PING_PIN2 );

NewPing sonar3(PING_PIN3, PING_PIN3 );
NewPing sonar4(PING_PIN4, PING_PIN4 );
NewPing sonar5(PING_PIN5, PING_PIN5 );
//NewPing sonar6(PING_PIN6, PING_PIN6 );
NewPing sonar7(PING_PIN7, PING_PIN7 );






void setup() {

//Serial.begin(115200);
    Serial.begin (9600);
//    pinMode(trigPin1, OUTPUT);
   // pinMode(echoPin1, INPUT);
}

void loop() {
 //SonarSensor(trigPin1, echoPin1);
   // FrontSensor = distance;
    
delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay

unsigned int uS = gunnar.ping(); // Send ping, get ping time in microseconds (uS).
unsigned int uS2 = sonar.ping(); // Send ping, get ping time in microseconds (uS).
unsigned int uS3 = sonar3.ping();
unsigned int uS4 = sonar4.ping();
unsigned int uS5 = sonar5.ping();
//unsigned int uS6 = sonar6.ping();
unsigned int uS7 = sonar7.ping();


//Serial.print("Ping: ");
Serial.print(uS / US_ROUNDTRIP_CM); // convert time into distance

//Serial.println("cm"); 
    Serial.print("  ");
    

//Serial.print("Ping2: ");
Serial.print(uS2 / US_ROUNDTRIP_CM); // convert time into distance

Serial.print("  ");
Serial.print(uS3 / US_ROUNDTRIP_CM);
Serial.print("  ");
Serial.print(uS4 / US_ROUNDTRIP_CM);
Serial.print("  ");
Serial.print(uS5 / US_ROUNDTRIP_CM);
Serial.print("  ");
//Serial.print(uS6 / US_ROUNDTRIP_CM);
Serial.print("  ");
Serial.print(uS7 / US_ROUNDTRIP_CM);

//Serial.println("cm"); 
    Serial.print(" \n");
  //  Serial.print("FrontSensor :");
    //Serial.print(FrontSensor);

       // Serial.print("   ");


    }

     void SonarSensor(int trigPin,int echoPin)
    {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;

    }

