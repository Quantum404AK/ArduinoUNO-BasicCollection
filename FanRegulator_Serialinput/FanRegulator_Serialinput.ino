#define fan 9

void setup() {
  Serial.begin(9600);
  pinMode(fan, OUTPUT);
}

void loop() {
   int speed = Serial.read();
if (speed == 0){
  analogWrite(fan, 0);
}else if (speed == 1) {
  analogWrite(fan, 130);
} else if (speed == 2) {
  analogWrite(fan, 160);
}else if (speed == 3) {
  analogWrite(fan, 200);
}else if(speed == 4) {
  analogWrite(fan, 255);
} 
}
