#include "Arduino.h"
#include "lpf.h"

LpfClass::LpfClass(double a){
    this->a = a;
}

int LpfClass::LPF(int x){
    y = a * y + (1-a) * x;
    return y;
}