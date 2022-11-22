#include "time.h"
#include "lpf.h"

// 1: debug mode 0: 実機mode
#define DEBUG 1

#ifdef DEBUG
const int mic_pin = A2;
const int led_pin =  4;
#else
const int mic_pin =  6;
const int led_pin =  4;
#endif


TimeClass wait_time(1000);

LpfClass lpf1(0.6);
LpfClass lpf2(0.6);

const int siki_val = 500;

void setup() {
  Serial.begin(115200);
  while(!Serial);

  pinMode(led_pin, OUTPUT);
}

void loop() {
  int mic_val = analogRead(mic_pin);
  int mic_val_lpf = lpf1.LPF(lpf2.LPF(mic_val));
  Serial.print(0);
  Serial.print(",");
  Serial.print(1024);
  Serial.print(",");
  Serial.print(siki_val);
  Serial.print(",");
  Serial.print(mic_val);
  Serial.print(",");
  Serial.print(mic_val_lpf);
  Serial.print("\n");
  
  static int count = 0;
  switch(count)
  {
  case 0:
    if(mic_val_lpf > siki_val){
      wait_time.time_ms_wait(false);
      count = 1;
    }
    break;
  
  case 1:
    digitalWrite(led_pin, HIGH);
    if(!wait_time.time_ms_wait(true)){
      digitalWrite(led_pin, LOW);
      count = 0;
    }
  }
}