#ifndef CONTROLLER_H
#define CONTROLLER_H

#define recvCH1 8   
#define recvCH2 9  
#define recvCH3 10
#define recvCH4 11
#define recvCH5 12
#define recvCH6 13

class ControlSig {
public:
  Controlsig();
  void setCH(unsinged long value, int i);
  unsigned long getCH(int i);
private:
  unsigned long valueCH[6];
};

#endif
