
/*
    #define trigPin1 12
    #define echoPin1 13
    #define trigPin2 10
    #define echoPin2 11
    #define trigPin3 8
    #define echoPin3 9*/
    //nr1
                #define trigPin1 8
    #define echoPin1 9

            #define trigPin2 2
    #define echoPin2 3

        #define trigPin3 4
    #define echoPin3 5

        #define trigPin4 6
    #define echoPin4 7

        #define trigPin5 10
    #define echoPin5 11

        #define trigPin6 12
    #define echoPin6 13



    //frontleft

    long duration, distance, Sensor1,Sensor2,Sensor3,Sensor4,Sensor5,Sensor6;

    void setup()
    {
    Serial.begin (9600);
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    pinMode(trigPin3, OUTPUT);
    pinMode(echoPin3, INPUT);

        pinMode(trigPin4, OUTPUT);
    pinMode(echoPin4, INPUT);
    pinMode(trigPin5, OUTPUT);
    pinMode(echoPin5, INPUT);
    pinMode(trigPin6, OUTPUT);
    pinMode(echoPin6, INPUT);
    }

    void loop() {
    SonarSensor(trigPin1, echoPin1);
    Sensor1 = distance;
    SonarSensor(trigPin2, echoPin2);
    Sensor2 = distance;
    SonarSensor(trigPin3, echoPin3);
    Sensor3 = distance;

    SonarSensor(trigPin4, echoPin4);
    Sensor4 = distance;
    SonarSensor(trigPin5, echoPin5);
    Sensor5 = distance;
    SonarSensor(trigPin6, echoPin6);
    Sensor6 = distance;

    
    Serial.print(Sensor1);
    Serial.print("  virkar ");
    Serial.print(Sensor2);
    Serial.print("   ");
    Serial.println(Sensor3);
        Serial.print("   ");
        Serial.print(Sensor4);
    Serial.print("   ");
    Serial.print(Sensor5);
    Serial.print("   ");
    Serial.println(Sensor6);
    delay(2000);
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

