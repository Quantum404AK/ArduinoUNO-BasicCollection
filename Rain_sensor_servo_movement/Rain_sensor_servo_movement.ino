#include <Servo.h>
Servo myservo;  // create Servo object to control a servo
// twelve Servo objects can be created on most boards

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


#define sensor A0
#define power1 2
#define ground1 4

int pos = 0;

void setup() {
  Serial.begin(9600);

  lcd.init();        // Initialize the LCD
  lcd.backlight();   // Turn on the backlight

  pinMode (sensor, INPUT);

  pinMode (power1, OUTPUT);
  pinMode (ground1, OUTPUT);
  digitalWrite (power1, HIGH);
  digitalWrite (ground1, LOW);

  myservo.attach(9);

}

void loop() {
  int value = analogRead(sensor);
  Serial.println(value);
  if (value>=512) {
    myservo.write(180);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  } else if (value<5120){
    myservo.write(0);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  }

