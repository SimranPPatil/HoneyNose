//this is master

#include <SoftwareSerial.h>
#include <String.h>
#include <stdio.h>


SoftwareSerial BTSerial(10, 11);

char state = '0';
char pulse_string[10]; 

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
 
 if (state == '0') 
 {
  Serial.print("Send something:");
 }

  int pulse = 338;
  sprintf(pulse_string, "%d", pulse);
  int TGSread = 124;
 BTSerial.write('M'); //CO2
 Serial.print('M');
 delay(1000);
 BTSerial.write(pulse_string);
 Serial.print("ps:");
 Serial.print(pulse_string);
 delay(1000);
 BTSerial.write(',');
 delay(1000);

 BTSerial.write('A'); //alcohol
 delay(1000);
 BTSerial.write(TGSread);
 delay(1000);
 BTSerial.write(',');
 delay(1000);
}
