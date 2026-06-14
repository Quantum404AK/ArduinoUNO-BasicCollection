#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int value;
int value_old;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  pinMode(4, INPUT);

  // put your setup code here, to run once:

}

void loop() {
  
  lcd.setCursor(0,0);
  lcd.print("Is 4+4=8?");

  value = digitalRead(4);
  Serial.println(value);
  if (value!=value_old){
    Serial.println(value);
    
  }
  value_old=value;
  
  delay(500);/*
  lcd.setCursor(1,0);
  if (value=1){
    lcd.print("Correct Answer!!");
  } else {
    lcd.print("Wrong...");
  } */





}
