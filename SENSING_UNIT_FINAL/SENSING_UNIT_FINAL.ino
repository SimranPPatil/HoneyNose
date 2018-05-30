//this is master

#include <SoftwareSerial.h>
#include <Wire.h>
#include <math.h>


//Bluetooth
SoftwareSerial BTSerial(10, 11);
char state = '0';

//general
char transmit[10];

//MH-Z14
//SoftwareSerial SerialCom (A1,A0);
int myDelay = 200;
byte addArray[] = { 0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79 };
byte zeroCalib[] = { 0xFF, 0x01, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78 };
char dataValue[9];
int counter = 10;

void setup()
{
  BTSerial.begin(38400);
  Serial.begin(9600);
  //SerialCom.begin(9600);
  Serial.write("this is master");
  Serial.write(zeroCalib, 9);
}

void loop()
{

 //BTSerial.listen();
 delay(2000);
 //BTSerial.flush();
 while(BTSerial.available() > 0)
 {
    // Checks whether data is comming from the serial port
    delay(500);
    state = BTSerial.read(); // Reads the data from the serial port
    delay(1000);
    Serial.print("State: ");
    Serial.print(state);
    Serial.print("\n");
 }

    delay(500);
   //SerialCom.listen();
   //Serial.println("Data from co2 sensor:");
  
   if (state == 'R')
   {
     Serial.println("Resetting");
     Serial.write(zeroCalib, 9);
     delay(1000);
     state = '0';
     counter = 10;
   }
  
   //Read MHZ14
   Serial.write(addArray, 9);
   Serial.readBytes(dataValue, 9);
   int resHigh = (int) dataValue[2];
   int resLow  = (int) dataValue[3];
   int pulse = (256*resHigh)+resLow;
  
   Serial.print("CO2: ");
   Serial.print(pulse);
   Serial.print("\n");
   delay(500);
  
   if(pulse > 200 && counter != 0){
     counter -= 1;
     Serial.print("counter: ");
     Serial.print(counter);
     Serial.print("\n");
     BTSerial.write('F');
     delay(500);
   }
 
}

