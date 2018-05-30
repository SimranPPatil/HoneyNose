//this is master

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);

char state = '0';

void setup() 
{
  BTSerial.begin(38400);
  Serial.begin(9600);
  Serial.write("this is master");
}

void loop()
{
 if(BTSerial.available() > 0)
 { 
    // Checks whether data is comming from the serial port
    state = BTSerial.read(); // Reads the data from the serial port
 }
 
 if (state == 'R') 
 {
  analogWrite(A0, 225);
  BTSerial.write('F');
  delay(2000);
  analogWrite(A0, LOW);
  delay(2000);
  state = 'P';
 }
 else{
  analogWrite(A0, LOW);
  BTSerial.write('P');
  delay(2000);
 }
}
