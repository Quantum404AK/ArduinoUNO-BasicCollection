void setup() {
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  // Make all red
  digitalWrite(1, HIGH);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  delay(1000);
}

void loop() {
  changeLight(0);
  delay(2700);
  changeLight(1);
  delay(2700);
  changeLight(2);
  delay(2700);
  changeLight(3);
  delay(2700);
}

void changeLight (int x){
  int y = x - 1;
  x = x % 4;
  y = ((y%4)+4)%4;
  
  digitalWrite((y)*3 + 1, HIGH);
  digitalWrite((y)*3 + 2, HIGH);
  digitalWrite((y)*3 + 3, LOW);
  delay(300);
  
  digitalWrite((y)*3 + 1, HIGH);
  digitalWrite((y)*3 + 2, LOW);
  digitalWrite((y)*3 + 3, LOW);
  
  digitalWrite((x)*3 + 1, LOW);
  digitalWrite((x)*3 + 2, HIGH);
  digitalWrite((x)*3 + 3, LOW);
}
