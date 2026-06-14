void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  randomSeed(analogRead(0));
}

void loop()
{
  int UniqueLED;
  int SingleState;
  int LEDlist[] = {2, 3, 4};
  int values[] = {0, 1};
  
  UniqueLED = (random(3) + 2);
  SingleState = random(2);
  
  digitalWrite(UniqueLED, SingleState);
  digitalWrite(LEDlist[UniqueLED - 3], values[SingleState - 1]);
  digitalWrite(LEDlist[UniqueLED - 4], values[SingleState - 1]);
  delay(50);
}
