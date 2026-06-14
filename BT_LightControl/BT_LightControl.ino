
#define L1M 2
#define L1 3
#define L2M 4
#define L2 5
#define L3M 8
#define L3 9
#define L4M 10
#define L4 12


int incomingByte = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(8, LOW);
  digitalWrite(10, LOW);

  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.print("Character received: ");
    Serial.write(incomingByte);  // prints the character
    Serial.print(" | ASCII value: ");
    Serial.println(incomingByte);  // prints decimal value
    char ch = (char)incomingByte;
    Serial.println(ch);
    // Sequences
    if (ch == 65) {  //A
      digitalWrite(L1, LOW);
      digitalWrite(L2, LOW);
      digitalWrite(L3, LOW);
      digitalWrite(L4, LOW);

      digitalWrite(L1, HIGH);
      delay(250);
      digitalWrite(L1, LOW);

      digitalWrite(L2, HIGH);
      delay(250);
      digitalWrite(L2, LOW);

      digitalWrite(L3, HIGH);
      delay(250);
      digitalWrite(L3, LOW);

      digitalWrite(L4, HIGH);
      delay(250);
      digitalWrite(L4, LOW);
    }

    if (ch == 66) {  //B
      digitalWrite(L1, HIGH);
      digitalWrite(L2, HIGH);
      digitalWrite(L3, HIGH);
      digitalWrite(L4, HIGH);

      delay(300);
      digitalWrite(L1, LOW);

      delay(300);
      digitalWrite(L2, LOW);

      delay(300);
      digitalWrite(L3, LOW);

      delay(300);
      digitalWrite(L4, LOW);
    }
    if (ch == 67) {  //C
      digitalWrite(L1, LOW);
      digitalWrite(L2, LOW);
      digitalWrite(L3, LOW);
      digitalWrite(L4, LOW);

      digitalWrite(L1, HIGH);
      delay(500);
      digitalWrite(L2, HIGH);
      delay(500);
      digitalWrite(L1, LOW);

      digitalWrite(L3, HIGH);
      delay(500);
      digitalWrite(L2, LOW);

      digitalWrite(L4, HIGH);
      delay(500);
      digitalWrite(L3, LOW);
      delay(500);
      digitalWrite(L4, LOW);
    }
    if (ch == 68) {  //D
      digitalWrite(L1, LOW);
      digitalWrite(L2, LOW);
      digitalWrite(L3, LOW);
      digitalWrite(L4, LOW);

      digitalWrite(L1, HIGH);
      delay(250);
      digitalWrite(L1, LOW);

      digitalWrite(L2, HIGH);
      delay(250);
      digitalWrite(L2, LOW);

      digitalWrite(L3, HIGH);
      delay(250);
      digitalWrite(L3, LOW);

      digitalWrite(L4, HIGH);
      delay(250);
      digitalWrite(L4, LOW);

      digitalWrite(L3, HIGH);
      delay(250);
      digitalWrite(L3, LOW);

      digitalWrite(L2, HIGH);
      delay(250);
      digitalWrite(L2, LOW);

      digitalWrite(L1, HIGH);
      delay(250);
      digitalWrite(L1, LOW);
    }
  }
}