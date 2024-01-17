#include <util/atomic.h>

class PIDcontrol {
  float kp, kd, ki, umax;
  float eprev, eintegral;

public:
  PIDcontrol() : kp(1), kd(0), ki(0), umax(255), eprev(0.0), eintegral(0.0) {}
  void setParams(float kpIn, float kdIn, float kiIn, float umaxIn) {
    kp = kpIn; kd = kdIn; ki = kiIn; umax = umaxIn; 
  }
  void evalu(int value, int target, float deltaT, int &pwr, int &dir) {
    float e = target - value;
    eintegral = eintegral + e*deltaT;
  
    float u = kp*e + ki*eintegral;

    // Set the motor speed and direction
    int dir = 1;
    if (u<0) {
      dir = -1;
    }
    int pwr = (int) fabs(u); // fabs = float + abs 절대값인데 소수에 붙이는거
    if(pwr > 255) {
      pwr = 255;
    }
  }
};

#define NMOTORS 2

// Pins
const int enca[] = {0, 1};
const int encb[] = {4, 5};
const int pwm[] = {9, 13};
const int in1[] = {8, 11};
const int in2[] = {10, 12};

long prevT = 0;
volatile int posi[] = {0, 0};


// globals
long prevT = 0;
int posPrev = 0;
volatile int pos_i = 0;
volatile float velocity_i = 0;
volatile long prevT_i = 0;

PIDcontrol pid[NMOTORS];

float v1Filt = 0;
float v1Prev = 0;
float v2Filt = 0;
float v2Prev = 0;

float eintegral = 0;

void setup() {
  Serial.begin(115200);
  for (int i=0; i < NMOTORS; i++) {
    pinMode(enca[i], INPUT);
    pinMode(encb[i], INPUT);
    pinMode(in1[i], OUTPUT);
    pinMode(in2[i], OUTPUT);

    pid[i].setParams(1,0,0,255);
  }
  
  attachInterrupt(digitalPinToInterrupt(enca[0]), readEncoder<0>, RISING);
  attachInterrupt(digitalPinToInterrupt(enca[1]), readEncoder<1>, RISING);
}

void loop() {
  // set target position
  int target[NMOTORS];
  target[0] = 750*sin(prevT/1e6);
  target[1] = -750*sin(prevT/1e6);

  // time difference
  long currT = micros();
  float deltaT = ((float) (currT - prevT)) / 1.0e6;
  prevT = currT;
  // // micros() <- 4마이크로 초 분해능으로 프로그램을 돌리기 시작한 후의 
  // // 마이크로 초 수를 반환. 70분 후 오버플로우됨
  // // ramp the speed up over 3 seconds
  // int pwr = 100/3.0*micros()/1.0e6;
  // int dir = 1;
  // setMotor(dir,pwr,PWM,IN1,IN2);

  // read the position in an atomic bolck
  // to avoid potential misreads
  int pos[NMOTORS];
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    for(int i=0; i < NMOTORS; i++)
      pos[i] = pos_i;
  }

  for(int i=0; i < NMOTORS; i++) {
    int pwr, dir;
    pid[i].evalu(pos[i], target[i], deltaT, pwr, dir);
    setMotor(dir, pwr, pwm[i], in1[i], in2[i]);
  }

  // // Compute velocity with method 1
  // long currT = micros();
  // float deltaT = ((float) (currT - prevT))/1.0e6;
  // float velocity1 = (pos - posPrev)/deltaT;
  // posPrev = pos;
  // prevT = currT;

  // // Convert counts/s to rpm
  // float v1 = (velocity1/990) * 60.0;
  // float v2 = (velocity2/990) * 60.0;

  // // Low-pass filter (25 Hz cutoff)
  // v1Filt = 0.854*v1Filt + 0.0728*v1 + 0.0728*v1Prev;
  // v1Prev = v1;
  // v2Filt = 0.854*v2Filt + 0.0728*v2 + 0.0728*v2Prev;
  // v2Prev = v2;

  // // Set a target
  // float vt = 100*(sin(currT/1e6) > 0);

  // // Compute the control signal u
  // float kp = 3;
  // float ki = 1;

  // setMotor(dir, pwr, PWM, IN1, IN2);
  for(int i=0; i < NMOTORS; i++) {
    Serial.print(target[i]);
    Serial.print(" ");
    Serial.print(pos[i]);
    Serial.println();
  }
  Serial.println();
}

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2) {
  analogWrite(pwm, pwmVal);
  if(dir == 1) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else if(dir == -1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}

template <int j>
void readEncoder() {
  int b = digitalRead(encb[j]);
  int increment = 0;
  if(b>0) {
    increment = 1;
    pos_i[j]++;
  }
  else {
    increment = -1;
    pos_i[j]--;
  }

  // compute velocity with method 2
  long currT = micros();
  float deltaT = ((float) (currT - prevT_i))/1.0e6;
  velocity_i = increment/deltaT;
  prevT_i = currT;
}
