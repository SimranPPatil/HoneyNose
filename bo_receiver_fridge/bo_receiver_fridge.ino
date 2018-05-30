//this is slave

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;
int r = 20;
int g = 90;
int b = 55;
int button = 2;

char state = '0';
String readString;
char c;
int val = 0; 

void setup() 
{
  BTSerial.begin(38400);
  Serial.begin(9600);
  Serial.write("This is slave");
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.setRGB(r,g,b);
  lcd.print("hello");
  pinMode(button, INPUT);
}

void loop() 
{

  val = digitalRead(button);
  if(val == HIGH){
    lcd.print("ACK");
    BTSerial.write('R');
    delay(3000);
    lcd.clear();
    val = 0;
    c = 'A';
  }
  else{
    lcd.setCursor(0,0);
    while (BTSerial.available()) {
    //small delay to allow input buffer to fill
      c = BTSerial.read();  //gets one byte from serial buffer
    }   
  
    if ( c == 'F' ) {
      lcd.setCursor(0,0);
      lcd.print("Food is bad");
      Serial.println("Food is bad");
      delay(2000);
      lcd.clear();
    }
    else{
      lcd.setCursor(0,0);
      lcd.print("all good");
      Serial.println("all good");
      delay(1000);
      lcd.clear();
    }
  }
  
  
}
