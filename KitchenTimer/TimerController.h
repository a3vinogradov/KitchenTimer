#ifndef file_TimerController
#define file_TimerController

#define STATE_OFF 0
#define STATE_SET_SECOND 1
#define STATE_SET_MINUTE 2
#define STATE_TIMER_ON 3
#define STATE_TIMER_PAUSE 4

class CTimerController
{
  private:
    byte _state;

    void SetStateOFF();
  
  public:
  CTimerController();
  void Setup();
  void Exec();
};

#endif
