#include <Servo.h>
int pirPin=2;
Servo myservo;
int pos = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(13, OUTPUT);
  myservo.attach(13);
}
void loop() {
  if(digitalRead(pirPin)==HIGH) {
    Serial.println("Open");
    delay(100);
    for (pos = 0; pos <= 180; pos += 1) {                
    myservo.write(pos);
    delay(10);
  }}

  if(digitalRead(pirPin)==LOW) {
    Serial.println("Close");
    delay(100);
    for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);
    delay(10);
  }
  }
  }
  




