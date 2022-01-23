#include "CButton.h"

CButton::CButton(const byte id, const byte pinNumber, CEventQueue* queue)
{
  _id = id;
  _pin = pinNumber;
  _state = BS_WAIT;
  _lastValue = false;
  _eventQueue = queue;
};
    
void CButton::Setup()
{
  ;
}

void CButton::Exec()
{
  if (_state == BS_WAIT)
  {
    bool newValue = (digitalRead(_pin)==HIGH);
    if (newValue != _lastValue)
    {
      // включить режим ожидания дребезга
      _lastTime = millis();
      _period = 50;
      _state = BS_BOUNCE;
    }
  } 
  else if (_state == BS_BOUNCE)
  {
    if(millis()-_lastTime >= _period)
    {
      bool newValue = (digitalRead(_pin)==HIGH);
      if (newValue != _lastValue)
      {
        _lastValue = newValue;

        Event event;
        if (newValue)
        {
          event.Type = EventType::ButtonDown;
        }
        else
        {
          event.Type = EventType::ButtonUp;
        }
        event.id = _id;
        _eventQueue->Push(event);
        
        //Serial.print("BattonState = "); Serial.println(_lastValue);
      }
      _state = BS_WAIT;
    }      
  }
}
