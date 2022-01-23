#ifndef file_CButton
#define file_CButton

//#include <Arduino.h>
#include "CEventQueue.h"

#define BS_WAIT 0
#define BS_BOUNCE 1

class CButton
{
  private:
    byte _id;
    byte _pin;
    byte _state;
    byte _lastValue;
    CEventQueue* _eventQueue;

    unsigned long _lastTime;
    unsigned long _period;
    
  public:
    CButton(const byte id, const byte pinNumber, CEventQueue* queue);
    void Setup();
    void Exec();  
};

#endif
