#define echoPin 12
#define trigPin 13
#define M1 5
#define M2 6
#define M3 9
#define M4 10

int duration = 0;
int distance = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT); 
  pinMode(M4, OUTPUT);
}

void loop() {
  //Ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  Serial.print(distance);
  Serial.println(" cm");

  if (distance<20 && distance>=0) {
    //stop
    analogWrite(M1, 0);
    analogWrite(M2, 0);
    analogWrite(M3, 0);
    analogWrite(M4, 0);
  } else if (distance>=20 && distance<65) {
    //slow movement
    analogWrite(M1, 0);
    analogWrite(M2, 75);
    analogWrite(M3, 75);
    analogWrite(M4, 0);
  } else if (distance>=65 && distance<100) {
    //fast movement
    analogWrite(M1, 0);
    analogWrite(M2, 125);
    analogWrite(M3, 125);
    analogWrite(M4, 0);
  } else if (distance>=100) {
    //stop
    analogWrite(M1, 0);
    analogWrite(M2, 0);
    analogWrite(M3, 0);
    analogWrite(M4, 0);
  }
}
