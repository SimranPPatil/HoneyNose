//this is slave

#include <SoftwareSerial.h>

//SoftwareSerial BTSerial(10, 11); // RX | TX
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;
int r = 241;
int g = 192;
int b = 106;
int button = 2;

char state = '0';
String readString;
char c;
int val = 0;
bool ack = false;
bool gotF = false;

void setup()
{
  Serial.begin(38400);
  //Serial.begin(9600);
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
    Serial.print("clear");
    lcd.clear();
    lcd.print("ACK");
    Serial.print("sending R");
    Serial.write('R');
    delay(5000);
    lcd.clear();
    val = 0;
    c = 'A';
    ack = true;
  }
  else{
    lcd.setCursor(0,0);
    while (Serial.available()) {
    //small delay to allow input buffer to fill
      c = Serial.read();  //gets one byte from serial buffer
    }

    if ( c == 'F' ) {
      lcd.setCursor(0,0);
      lcd.clear();
      lcd.setRGB(74,14,14);
      Serial.print("F");
      lcd.print("Time to bake ");
      lcd.setCursor(0,1);
      lcd.print("banana bread");
      gotF = true;
      delay(2000);
      //lcd.clear();
    }
    else{
      if(!gotF){
        lcd.setCursor(0,0);
        lcd.setRGB(r,g,b);
        Serial.print("ok no F");
        lcd.clear();
        lcd.print("As good as honey");
        delay(1000);

      }
      else if(gotF){
        if(ack){
          lcd.setCursor(0,0);
          lcd.setRGB(r,g,b);
          Serial.print("f n ack");
          lcd.clear();
          lcd.print("As good as honey");
          delay(1000);
          ack = false;
          gotF = false;
        }
      }
    }
  }


}
