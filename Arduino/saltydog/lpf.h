#ifndef lpf_h
#define lpf_h

class LpfClass{
private:
  double a = 0.0;
  int y = 0;

public:
  LpfClass(double a);
  int LPF(int x);
};

#endif