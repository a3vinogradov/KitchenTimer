#include "TimerController.h"
CTimerController::CTimerController(CDisplay* disp)
{
  _display = disp;
  _state = STATE_OFF;
}

void CTimerController::SetStateOFF()
{
  _state = STATE_OFF;
  // вывести на дисплей OFF
  _display->SetString(QD_NONE, QD_O, QD_F, QD_F);
  // todo: Ждать нажатия кн 1 для перехода в режим SetSecond
  // переход в режим установки секунд по таймеру.
  _lastTime = millis();
  _period = 5000;
}

void CTimerController::SetStateSetSecond()
{
  _state = STATE_SET_SECOND;
  _display->SetTime(0,30,MODE_SET_SECOND);
  // todo: Ждать нажатия кн 1 для перехода в режим SetMinute
  // todo: Ждать нажатия кн 2 для перехода в режим OFF
  // переход в режим установки секунд по таймеру.
  _lastTime = millis();
  _period = 5000;
}


void CTimerController::Setup()
{
  SetStateOFF();   
}

void CTimerController::Exec()
{
  switch (_state)
  {
    case STATE_OFF : 
      if(millis()-_lastTime >= _period)
      {
        SetStateSetSecond();
      }  
      break;

    case STATE_SET_SECOND : 
      if(millis()-_lastTime >= _period)
      {
        SetStateOFF();
      }  
      break;
    
    case STATE_SET_MINUTE : break;
    case STATE_TIMER_ON : break;
    case STATE_TIMER_PAUSE : break;
  }
}
