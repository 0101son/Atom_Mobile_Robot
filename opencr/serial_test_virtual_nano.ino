int virtualDigitalRead();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int FR_speed = virtualDigitalRead();
  int FL_speed = virtualDigitalRead();
  Serial.print(FR_speed);
  Serial.print(" ");
  Serial.print(FL_speed); 
  Serial.println();
  delay(100);
}

int virtualDigitalRead()
{
  static int i = 0;
  i++;
  if (i>1024) i=0;
  return i;
}
