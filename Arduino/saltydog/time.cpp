#include "Arduino.h"
#include "time.h"

/*
引数：設定したい待ち時間(ms)
戻り値：なし
wait_timeに設定したい待ち時間を入れる
*/
TimeClass::TimeClass(int t){
    wait_time = t;
}

/*
引数：false -> タイマーをリセットする true -> タイマーを開始する
戻り値：状態フラグ
タイマーを開始したあと設定した時間内ならtrueをそれ以外はfalseを返す
*/
bool TimeClass::time_ms_wait(bool f){
    if(f){
      time2 = millis();
      if((time2 - time1) <= wait_time){
        return true;
      }
      else{
        return false;
      }
    }
    else{
      time1 = millis();
      return false;
    }
}
