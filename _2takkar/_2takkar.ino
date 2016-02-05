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

  //takki ekki á hjóli 1 þegar takki er uppi 0 þegar hann er niðri
  //Serial.println(buttonState);
    Serial.println("   ");

  //takki á hjóli 1 þegar ýtt er á hann annars núll.
  Serial.println(buttonState2);
    Serial.println("\n");


  delay(1);

}
