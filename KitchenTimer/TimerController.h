#ifndef file_TimerController
#define file_TimerController

#include "CDisplay.h"
#include "CEventQueue.h"
#include "CActiveZoomerController.h"

#define STATE_OFF 0
#define STATE_SET_SECOND 1
#define STATE_SET_MINUTE 2
#define STATE_TIMER_PAUSE 3
#define STATE_TIMER_ON 4

class CTimerController
{
  private:
    CDisplay* _display;
    byte _state;
    CEventQueue* _eventQueue;
    CActiveZoomerController* _zoomer;

    long _time;

    unsigned long _lastTime;
    unsigned long _period;

    void SetStateOFF();
    void SetStateSetSecond();
    void SetStateSetMinute();
    void SetStatePause();
    void SetStateON();
    void IncSeconds(int value);
    void IncMinutes(int value);
    void Beep();

  public:
    CTimerController(CDisplay* disp, CEventQueue* queue, CActiveZoomerController* zoomer);
    void Setup();
    void Exec();
    byte GetMinutes();
    byte GetSeconds();
};

#endif
