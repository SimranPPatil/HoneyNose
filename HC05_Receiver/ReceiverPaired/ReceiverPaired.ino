//this is slave

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX

char state = '0';

void setup() 
{
  BTSerial.begin(38400);
  Serial.begin(9600);
  Serial.write("This is slave");
}
void loop() 
{
 if(BTSerial.available() > 0){ 
    // Checks whether data is comming from the serial port
    state = BTSerial.read(); // Reads the data from the serial port
 }
 
 if (state == 'F') {
  Serial.print("Food went bad\n");
  state = '0';
  BTSerial.write('0');
 }
 else if(state == 'P'){
  Serial.print("Time to get some power\n");
  BTSerial.write('R');
 }
 else{
  Serial.print("All good\n");
  delay(10000);
 }

}
