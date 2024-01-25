int i = 0;
String inputString = "";
int chValue[6] = { 0 };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == ' ') {
      chValue[i] = inputString.toInt();
      inputString = "";
      i++;
    }
    else if (inChar == '\n') {
      chValue[i] = inputString.toInt();
      inputString = "";
      i = 0;
    }
  }
  for(int j=0; j<6; j++) {
    if (j != 5) {
      Serial.print(chValue[j]);
      Serial.print(" ");
    }
    else
      Serial.println(chValue[j]);
  }
}
