#ifndef time_h
#define time_h

class TimeClass{
private:
  unsigned long time1 = 0;
  unsigned long time2 = 0;
  int wait_time = 0;

public:
  TimeClass(int t);
  bool time_ms_wait(bool f);
};

#endif