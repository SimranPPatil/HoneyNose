#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;
char received = 'N';
const int r = 255;
const int g = 56; 
const int b = 94;
int ACK = 1; 
int ACKpin = 7;
int val = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("hello world");
  lcd.setRGB(r, g, b);
  pinMode(ACKpin, INPUT);      
}

void loop() {
  if( Serial.available() > 0){
    received = (char) Serial.read();
    Serial.println(received);
    if(received == 'F'){
      lcd.clear();
      lcd.print("Something's fishy!");
      ACK = 0;
    }
    else if(received == 'P'){
      lcd.clear();
      lcd.print("Change the battery");
      ACK = 0;
    }
    else{
      lcd.clear();
      lcd.print("food is good :) ");
      ACK = 1;
    }
    delay(2000);
  }
  val = digitalRead(ACKpin);
  if(val == HIGH && ACK == 0){
    ACK = 1;
    lcd.print("good to go");
    val = LOW;
  }
}
