#include <util/atomic.h>
#include "PIDcontrol.hpp"
#include "pins.hpp"

PIDcontrol pid[NMOTORS];

// Pins
const int enca[2] = {2,3};
const int encb[2] = {4,5};
const int pwm[2] = {6,9};
const int in1[2] = {7,12};
const int in2[2] = {8,13};

// Globals
long prevT = 0;
volatile int posi[2] = {0,0};

// PID class instances
PIDcontrol pid[NMOTORS];

void setup() {
  Serial.begin(9600);

  for(int k = 0; k < NMOTORS; k++){
    pinMode(enca[k],INPUT);
    pinMode(encb[k],INPUT);
    pinMode(pwm[k],OUTPUT);
    pinMode(in1[k],OUTPUT);
    pinMode(in2[k],OUTPUT);

    pid[k].setParams(1,0,0,255);
  }
  
  attachInterrupt(digitalPinToInterrupt(enca[0]),readEncoder<0>,RISING);
  attachInterrupt(digitalPinToInterrupt(enca[1]),readEncoder<1>,RISING);
  
  Serial.println("target pos");
}

void loop() {

  // set target position
  int target[NMOTORS];
  target[0] = 990*sin(prevT/1e6);
  target[1] = -990*sin(prevT/1e6);

  // time difference
  long currT = micros();
  float deltaT = ((float) (currT - prevT))/( 1.0e6 );
  prevT = currT;

  // Read the position in an atomic block to avoid a potential misread
  int pos[NMOTORS];
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    for(int k = 0; k < NMOTORS; k++){
      pos[k] = posi[k];
    }
  }
  
  // loop through the motors
  for(int k = 0; k < NMOTORS; k++){
    int pwr, dir;
    // evaluate the control signal
    pid[k].evalu(pos[k],target[k],deltaT,pwr,dir);
    // signal the motor
    setMotor(dir,pwr,pwm[k],in1[k],in2[k]);
  }

  for(int k = 0; k < NMOTORS; k++){
    Serial.print(target[k]);
    Serial.print(" ");
    Serial.print(pos[k]);
    Serial.print(" ");
  }
  Serial.println();
}

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  analogWrite(pwm,pwmVal);
  if(dir == 1){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
  }
  else if(dir == -1){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
  }
  else{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
  }  
}

template <int j>
void readEncoder(){
  int b = digitalRead(encb[j]);
  if(b > 0){
    posi[j]++;
  }
  else{
    posi[j]--;
  }
}
