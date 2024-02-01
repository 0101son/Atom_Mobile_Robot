#include <IBusBM.h>

IBusBM IBus;    // IBus object

void setup() {
  IBus.begin(Serial1);    // iBUS object connected to serial0 RX pin
  Serial.begin(9600);
}

void loop() {
  int val1, val2, val3, val4, val5, val6, val7, val8;
  val1 = IBus.readChannel(0); // get latest value for servo channel 1
  val2 = IBus.readChannel(1);
  val3 = IBus.readChannel(2);
  val4 = IBus.readChannel(3);
  val5 = IBus.readChannel(4);
  val6 = IBus.readChannel(5);
  val7 = IBus.readChannel(6);
  val8 = IBus.readChannel(7);
  
  Serial.print("channel 1 : ");
  Serial.print(val1);
  Serial.print(", ");
  
  Serial.print("channel 2 : ");
  Serial.print(val2);
  Serial.print(", ");
  
  Serial.print("channel 3 : ");
  Serial.print(val3);
  Serial.print(", ");
  
  Serial.print("channel 4 : ");
  Serial.print(val4);
  Serial.print(", ");

  Serial.print("channel 5 : ");
  Serial.print(val5);
  Serial.print(", ");

  Serial.print("channel 6 : ");
  Serial.print(val6);
  Serial.print(", ");

  Serial.print("channel 7 : ");
  Serial.print(val7);
  Serial.print(", ");

  Serial.print("channel 8 : ");
  Serial.println(val8);
  
  delay(50);
}
