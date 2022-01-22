#ifndef file_TimerController
#define file_TimerController

#include "CDisplay.h"

#define STATE_OFF 0
#define STATE_SET_SECOND 1
#define STATE_SET_MINUTE 2
#define STATE_TIMER_ON 3
#define STATE_TIMER_PAUSE 4

class CTimerController
{
  private:
    CDisplay* _display;
    byte _state;

    unsigned long _lastTime;
    unsigned long _period;

    void SetStateOFF();
    void SetStateSetSecond();
  
  public:
  CTimerController(CDisplay* disp);
  void Setup();
  void Exec();
};

#endif
