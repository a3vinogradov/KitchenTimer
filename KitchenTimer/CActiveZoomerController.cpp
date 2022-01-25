#include "CActiveZoomerController.h"

CActiveZoomerController::CActiveZoomerController(const byte pin)
{
  _pin = pin;
  _state = ZoomerState::Wait;
}

void CActiveZoomerController::Setup()
{
  pinMode(_pin, OUTPUT);
}

void CActiveZoomerController::Exec()
{
  if(_state == ZoomerState::Active)
  {
    //Serial.println("Zoomer exec Active");
    if(millis()-_lastTime >= _period)
    {
      _curPart++;
      if(_curPart == 5)
      {
        digitalWrite(_pin, LOW);
        _state = ZoomerState::Wait;
      }
      else
      {
        _lastTime = millis();
        _period = _beepParts[_curPart];
        digitalWrite(_pin, _curPart%2==1?LOW:HIGH);
      }
      Serial.println("Zoomer change"+String(_curPart%2==1?LOW:HIGH) );
    }
  }
}

void CActiveZoomerController::Beep()
{
  Serial.println("Beep!");
  _state = ZoomerState::Active;
  _curPart = 0;
  _lastTime = millis();
  _period = _beepParts[_curPart];
  digitalWrite(_pin, _curPart%2==1?LOW:HIGH);
}
