#ifndef file_CActiveZoomerController
#define file_CActiveZoomerController

#include <Arduino.h>

enum class ZoomerState
{
    Wait = 1,
    Active = 2
};

class CActiveZoomerController
{
  private:
  byte _pin;
  ZoomerState _state;

  long _beepParts[5] = {1000,500,1000,500,1000};
  byte _curPart;
  unsigned long _lastTime;
  unsigned long _period = 20000;
  
  public:
  CActiveZoomerController(const byte pin);
  void Setup();
  void Exec();
  void Beep();
};

#endif
