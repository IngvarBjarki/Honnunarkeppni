
/*
    #define trigPin1 12
    #define echoPin1 13
    #define trigPin2 10
    #define echoPin2 11
    #define trigPin3 8
    #define echoPin3 9*/
        #define trigPin1 12
    #define echoPin1 13
    //frontright
    #define trigPin2 2
    #define echoPin2 1
    //frontleft
    #define trigPin3 8
    #define echoPin3 9

    long duration, distance, RightSensor,BackSensor,FrontSensor,LeftSensor;

    void setup()
    {
    Serial.begin (9600);
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    pinMode(trigPin3, OUTPUT);
    pinMode(echoPin3, INPUT);
    }

    void loop() {
    SonarSensor(trigPin1, echoPin1);
    FrontSensor = distance;
    SonarSensor(trigPin2, echoPin2);
    LeftSensor = distance;
    SonarSensor(trigPin3, echoPin3);
    RightSensor = distance;

    Serial.print(LeftSensor);
    Serial.print("   ");
    Serial.print(FrontSensor);
    Serial.print("   ");
    Serial.println(RightSensor);
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

