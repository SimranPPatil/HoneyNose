void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("start");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    Serial.write('F');
    delay(1000);
  }
}


