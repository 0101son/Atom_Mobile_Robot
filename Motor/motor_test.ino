#define MOTOR1_A 5
#define MOTOR1_B 6
#define MOTOR2_A 9
#define MOTOR2_B 10

int i = 0;
String inputString = "";
int chValue[6] = { 0 };

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR1_A, OUTPUT);
  pinMode(MOTOR1_B, OUTPUT);
  pinMode(MOTOR2_A, OUTPUT);
  pinMode(MOTOR2_B, OUTPUT);
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

  for (int j = 0; j < 6; j++) {
//    chValue[j] = map(chValue[j], 980, 2000, 0, 200);
//    chValue[j] = chValue[j] * 200 / 1020;
    if (j != 5) {
      Serial.print(map(chValue[j], 980, 2000, 0, 200));
      Serial.print(" ");
    }
    else
      Serial.println(map(chValue[j], 980, 2000, 0, 200));
  }

  analogWrite(MOTOR1_A, map(chValue[2], 980, 2000, 0, 200));
  analogWrite(MOTOR1_B, 0);
  analogWrite(MOTOR2_A, map(chValue[2], 980, 2000, 0, 200));
  analogWrite(MOTOR2_B, 0);
  
  delay(10);
}

int mymap(int value, int fromLow, int fromHigh, int toLow, int toHigh) {
  int fromDiff = fromHigh - fromLow;
  int toDiff = toHigh- toLow;
  value = value * toDiff / fromDiff;
  return value;
}
