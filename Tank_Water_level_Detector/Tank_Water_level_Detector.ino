#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int level = 0;
int levelold = 0;

#define LED1 8
#define LED2 9
#define LED3 10
#define LED4 11
#define LED5 12

#define SensorVCC A0
#define SensorSignal A1

void setup()
{
  pinMode(SensorVCC, OUTPUT);
  pinMode(SensorSignal, INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
}

void loop()
{
  digitalWrite(SensorVCC, HIGH);
  delay(10);
  level = analogRead(SensorSignal);
  digitalWrite(SensorVCC, LOW);
  
  Serial.println(level);
  
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  
  if (level > 0) {
    digitalWrite(LED1, HIGH);
  }
  if (level > 200) {
    digitalWrite(LED2, HIGH);
  }
  if (level > 400) {
    digitalWrite(LED3, HIGH);
  }
  if (level > 600) {
    digitalWrite(LED4, HIGH);
  }
  if (level > 800) {
    digitalWrite(LED5, HIGH);
  }
  
  
  if (level != levelold){
    levelold = level;
    lcd.clear();
    lcd.setCursor(0, 0);
    if (level < 800) {
      lcd.print("Tank not full");
    } else if (level >= 800) {
      lcd.print("TANK FULL!!");
    }
    lcd.setCursor(0, 1);
    lcd.print("Level: ");
    lcd.print(level);
  }
  
  delay(100);
}
