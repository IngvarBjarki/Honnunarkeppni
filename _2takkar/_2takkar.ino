int pushbutton = 2;
int pushbutton2 = 3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pushbutton, INPUT);
    pinMode(pushbutton2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(pushbutton);
    int buttonState2 = digitalRead(pushbutton2);


  Serial.println(buttonState);
    Serial.println("   ");

  Serial.println(buttonState2);
    Serial.println("\n");


  delay(1);

}
