#include "time.h"
#include "lpf.h"
#include <Servo.h>

// 0:debug MODE 1:実機 TEST MODE 2:実機 本番 MODE
#define MODE 2

// 0:シリアルプロット 1:Python 2:teraterm 
#define PY 0

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
const int servo_1st_ang = 20;
const int servo_2nd_ang = 0;
#endif


// class
TimeClass wait_time1(1000);
TimeClass wait_time2(2000);

#if MODE == 0
LpfClass lpf1(0.6);
LpfClass lpf2(0.6);
#elif MODE == 1 || MODE == 2
LpfClass lpf1(0.6);
LpfClass lpf2(0.6);
#endif


// micの閾値
#if MODE == 0
const int siki_val = 540;
#elif MODE == 1 || MODE == 2
const int siki_val = 450;
#endif

//func
void set_pin_mode(void);
void set_serial(void);
void send_data(int, int);
void servo_move(int);


void setup()
{
  set_pin_mode();
  set_serial();

  #if MODE == 2
    servo.write(servo_1st_ang);
    delay(1000);
  #endif
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
  Serial.begin(9600);
  //while(!Serial);
}

void send_data(int nama, int lpf)
{
  #if PY == 0
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

  #elif PY == 1
  Serial.print(uint16_t(nama));

  #elif PY == 2
  Serial.println(uint16_t(nama));

  #endif
}

void servo_move(int val)
{
  static int count = 0;
  switch(count)
  {
  case 0:
    if(val > siki_val)
    {
      wait_time1.time_ms_wait(false);
      count = 1;
    }
    else
    {
      /*
      #if MODE == 2
      servo.write(servo_1st_ang);
      #endif
      */
    }
    break;
  
  case 1:
    digitalWrite(led_pin, HIGH);

    #if MODE == 2
    servo.write(servo_1st_ang);
    #endif

    if(!wait_time1.time_ms_wait(true))
    {
      digitalWrite(led_pin, LOW);
      wait_time2.time_ms_wait(false);
      count = 2;
      #if MODE == 2
      servo.write(servo_2nd_ang);
      #endif
    }
    break;

  case 2:
    if(!wait_time2.time_ms_wait(true))
    {
      count = 0;
    }
    break;
  }
}