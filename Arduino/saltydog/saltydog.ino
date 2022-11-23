#include "time.h"
#include "lpf.h"
#include <Servo.h>

// 0:debug MODE 1:実機 TEST MODE 2:実機 本番 MODE
#define MODE 0

// pin配置
#if MODE == 0
const int mic_pin = A2;
const int led_pin =  4;

#elif MODE == 1
const int mic_pin =  A0;
const int led_pin = 13;

#elif MODE == 2
const int mic_pin =  A0;
const int led_pin = 13;
const int servo_pin = 11;

#endif

// サーボ設定
#if MODE == 2
Servo servo;
const int servo_1st_ang = 0;
const int servo_2nd_ang = 90;
#endif


// class
TimeClass wait_time(1000);

LpfClass lpf1(0.6);
LpfClass lpf2(0.6);

// micの閾値
const int siki_val = 500;

//func
void set_pin_mode(void);
void set_serial(void);
void send_data(int, int);
void servo_move(int);


void setup()
{
  set_pin_mode();
  set_serial();
}

void loop() 
{
  int mic_val = analogRead(mic_pin);
  int mic_val_lpf = lpf1.LPF(lpf2.LPF(mic_val));

  send_data(mic_val, mic_val_lpf);
  servo_move(mic_val_lpf);
}

void set_pin_mode(void)
{
  pinMode(led_pin, OUTPUT);
  
  #if MODE == 2
  servo.attach(servo_pin);
  #endif
}

void set_serial(void)
{
  Serial.begin(115200);
  while(!Serial);
}

void send_data(int nama, int lpf)
{
  Serial.print(0);
  Serial.print(",");
  Serial.print(1024);
  Serial.print(",");
  Serial.print(siki_val);
  Serial.print(",");
  Serial.print(nama);
  Serial.print(",");
  Serial.print(lpf);
  Serial.print("\n");
}

void servo_move(int val)
{
  static int count = 0;
  switch(count)
  {
  case 0:
    if(val > siki_val)
    {
      wait_time.time_ms_wait(false);
      count = 1;
    }
    else
    {
      #if MODE == 2
      servo.write(servo_1st_ang);
      #endif
    }
    break;
  
  case 1:
    digitalWrite(led_pin, HIGH);

    #if MODE == 2
    servo.write(servo_2nd_ang);
    #endif

    if(!wait_time.time_ms_wait(true))
    {
      digitalWrite(led_pin, LOW);
      count = 0;
    }
  }
}