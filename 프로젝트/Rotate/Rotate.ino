const int PIN_RED = 11;
const int PIN_BLUE = 10;
const int PIN_GREEN = 9;

int val;

void setup()
{
  // put your setup code here, to run once:
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
}

void loop()
{
  int val = analogRead(A3)/4;
  analogWrite(PIN_RED, val);
  analogWrite(PIN_BLUE, val);
  analogWrite(PIN_GREEN, val);
}
