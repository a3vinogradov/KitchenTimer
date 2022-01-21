#ifndef file_CDisplay
#define file_CDisplay

#include <Arduino.h>
#include "QuadDisplay2.h"

#define styleOFF 0
#define styleON 1
#define styleBlink 2

#define MODE_STRING 0
#define MODE_SET_MINUTE 1
#define MODE_SET_SECOND 2
#define MODE_TIMER_ON 3
#define MODE_TIMER_PAUSE 4

// displayMode задает режим интерпретации данных.
// на дисплей выводятся байты из массива symbol.
// в режиме MODE_STRING minuteVal и secondVal игнорируются
// в остальных режимах числа minuteVal и secondVal дублируют данные в массиве symbol
struct CDisplayData
{
  byte displayMode;
  byte symbol[4];
  byte secondVal;
  byte minuteVal;
};

class CDisplay
{
  private: 
    //const static byte numerals[10] = { QD_0, QD_1, QD_2, QD_3, QD_4, QD_5, QD_6, QD_7, QD_8, QD_9 };  
    QuadDisplay _QD; 
    CDisplayData _currentData;
    CDisplayData _newData;    

    unsigned long _lastTime;
    unsigned long _period;
    bool _blinkState;
    
    void Refresh();
    bool CheckUpdate();
    byte ByteToSymbol(const byte source);
  public:
    //QuadDisplay _QD; 
    CDisplay(const byte CS, const byte DI, const byte CLK);
    void SetString(const byte sym3, const byte sym2, const byte sym1, const byte sym0);
    void SetSeconds(const byte value);
    void SetMinutes(const byte value);
    void SetTime(const byte valueMin, const byte valueSec, const byte mode);
    void Setup();
    void Exec();
};

#endif
