/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

#include <NewPing.h>
#define PING_PIN1 4 // Arduino pin for both trig and echo
#define PING_PIN2 5 // Arduino pin for both trig and echo
#define PING_PIN3 6
#define PING_PIN4 7
#define PING_PIN5 8
//#define PING_PIN6 9
#define PING_PIN7 13


NewPing sonar1(PING_PIN1, PING_PIN1 );
NewPing sonar2(PING_PIN2, PING_PIN2 );
NewPing sonar3(PING_PIN3, PING_PIN3 );
NewPing sonar4(PING_PIN4, PING_PIN4 );
NewPing sonar5(PING_PIN5, PING_PIN5 );
//NewPing sonar6(PING_PIN6, PING_PIN6 );
NewPing sonar7(PING_PIN7, PING_PIN7 );

unsigned int duration,Sensor1,Sensor2,Sensor3,Sensor4,Sensor5,Sensor6,Sensor7; 

Servo myservo;  // create servo object to control a servo
Servo myservo2;
// twelve servo objects can be created on most boards

int pos = 60;    // variable to store the servo position

void setup() {
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(10);
}

void loop() {
  for (pos = 60; pos <= 100; pos += 1) { // goes from 0 degrees to 180 degrees
     delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay

        duration = sonar5.ping();// Send ping, get ping time in microseconds 
        Sensor5 = duration/US_ROUNDTRIP_CM;// convert time into distance
   //     duration = sonar6.ping();// Send ping, get ping time in microseconds 
 //       Sensor6 = duration/US_ROUNDTRIP_CM;// convert time into distance
    // in steps of 1 degree
    //myservo.write(pos);              // tell servo to go to position in variable 'pos'
      myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    //delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 100; pos >= 60; pos -= 1) { // goes from 180 degrees to 0 degrees
     delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay

        duration = sonar5.ping();// Send ping, get ping time in microseconds 
        Sensor5 = duration/US_ROUNDTRIP_CM;// convert time into distance
//        duration = sonar6.ping();// Send ping, get ping time in microseconds 
   //     Sensor6 = duration/US_ROUNDTRIP_CM;// convert time into distance
    //myservo.write(pos);              // tell servo to go to position in variable 'pos'
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    //delay(15);                       // waits 15ms for the servo to reach the position
  }
}

