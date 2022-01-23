#include "TimerController.h"

#define INACTION_DELAY 60000 // 

CTimerController::CTimerController(CDisplay* disp, CEventQueue* queue)
{
  _display = disp;
  _state = STATE_OFF;
  _eventQueue = queue;
  //_minutes = 0;
  //_seconds = 30;
  _time = 30000; // время таймера в мс
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
  _eventQueue->Clear();
}

void CTimerController::SetStateSetSecond()
{
  _state = STATE_SET_SECOND;
  _display->SetTime(GetMinutes(),GetSeconds(),MODE_SET_SECOND);
  // todo: Ждать нажатия кн 1 для перехода в режим SetMinute
  // todo: Ждать нажатия кн 2 для перехода в режим OFF
  // переход в режим установки минут по таймеру.
  _lastTime = millis();
  _period = INACTION_DELAY;
  _eventQueue->Clear();
}

void CTimerController::SetStateSetMinute()
{
  _state = STATE_SET_MINUTE;
  _display->SetTime(GetMinutes(),GetSeconds(),MODE_SET_MINUTE);
  // todo: Ждать нажатия кн 1 для перехода в режим Pause
  // todo: Ждать нажатия кн 2 для перехода в режим MODE_SET_SECOND
  // todo: Ждать 30 сек для перехода в режим OFF
  // переход в режим паузы.
  _lastTime = millis();
  _period = INACTION_DELAY;
  _eventQueue->Clear();
}

void CTimerController::SetStatePause()
{
  _state = STATE_TIMER_PAUSE;
  _display->SetTime(GetMinutes(),GetSeconds(),MODE_TIMER_PAUSE);
  // todo: Ждать нажатия кн 1 для перехода в режим ON
  // todo: Ждать нажатия кн 2 для перехода в режим OFF
  // переход в режим обратного отсчета (ON).
  _lastTime = millis();
  _period = INACTION_DELAY;
  _eventQueue->Clear();
}

void CTimerController::SetStateON()
{
  _state = STATE_TIMER_ON;
  _display->SetTime(GetMinutes(),GetSeconds(),MODE_TIMER_ON);
  // todo: Ждать нажатия кн 1 для перехода в режим ON
  // todo: Ждать нажатия кн 2 для перехода в режим OFF
  // переход в режим обратного отсчета (ON).
  _lastTime = millis();
  _period = 5000;
  _eventQueue->Clear();
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
      if(!_eventQueue->IsEmpty())
      {
        Event event = _eventQueue->Pop();
        if((event.Type == EventType::ButtonDown)&&
            (event.id == 1))
        {
          SetStateSetSecond();    
        }
      }
      break;

    case STATE_SET_SECOND : 
      if(millis()-_lastTime >= _period)
      {
        SetStateOFF();
      }  

      if(!_eventQueue->IsEmpty())
      {
        Event event = _eventQueue->Pop();
        if(event.Type == EventType::ButtonDown)
        { 
          if (event.id == 1)
          {
            SetStateSetMinute();    
          } 
          else if (event.id == 2)
          {
            SetStateOFF();
          }
        }
      }      
      break;
    
    case STATE_SET_MINUTE : 
      if(millis()-_lastTime >= _period)
      {
        //SetStateOFF();
        SetStatePause();
      } 
      
      if(!_eventQueue->IsEmpty())
      {
        Event event = _eventQueue->Pop();
        if(event.Type == EventType::ButtonDown)
        { 
          if (event.id == 1)
          {
            SetStatePause();    
          } 
          else if (event.id == 2)
          {
            SetStateSetSecond();
          }
        }
      } 
      break;
    case STATE_TIMER_PAUSE : 
      if(millis()-_lastTime >= _period)
      {
        //SetStateOFF();
        //SetStateON();
      }
      
      if(!_eventQueue->IsEmpty())
      {
        Event event = _eventQueue->Pop();
        if(event.Type == EventType::ButtonDown)
        { 
          if (event.id == 1)
          {
            SetStateON();    
          } 
          else if (event.id == 2)
          {
            SetStateSetMinute();
          }
        }
      }
      break;
      
    case STATE_TIMER_ON : 
      long del = millis() - _lastTime; 
      _time -= del;
      _lastTime += del; 
      
      if (_time <= 0)
      {
        // todo: звуковой сигнал 
        SetStateOFF();
      }
      else
      {
        _display->SetTime(GetMinutes(),GetSeconds(),MODE_TIMER_ON);
      }
      
      if(!_eventQueue->IsEmpty())
      {
        Event event = _eventQueue->Pop();
        if(event.Type == EventType::ButtonDown)
        { 
          if (event.id == 2)
          {
            SetStatePause();
          }
        }
      }
      
      break;
  }
}

byte CTimerController::GetMinutes()
{
  return _time/60000;
}

byte CTimerController::GetSeconds()
{
  long ss = _time/1000;
  return ss%60;
}
