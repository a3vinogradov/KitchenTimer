#include "CDisplay.h"


CDisplay::CDisplay(const byte CS, const byte DI, const byte CLK): 
  //_QD(2, 5, 3)
  _QD(CS, DI, CLK)
{
  
}

void CDisplay::SetString(const byte sym3, const byte sym2, const byte sym1, const byte sym0)
{
  _newData.displayMode = MODE_STRING;
  _newData.secondVal = 0;
  _newData.minuteVal = 0;
  
  _newData.symbol[3] = sym3;
  _newData.symbol[2] = sym2;
  _newData.symbol[1] = sym1;
  _newData.symbol[0] = sym0;
};

void CDisplay::SetSeconds(const byte value)
{};

void CDisplay::SetMinutes(const byte value)
{};

void CDisplay::SetTime(const byte valueMin, const byte valueSec, const byte mode)
{
  _newData.displayMode = mode;
  if( (mode == MODE_TIMER_ON) ||
      (mode == MODE_SET_SECOND) ||
      (mode == MODE_SET_MINUTE)
     )
  {
    _lastTime = millis();
    _blinkState = true;
  }
  
  _newData.secondVal = valueSec;
  _newData.minuteVal = valueMin;  

  _newData.symbol[3] = ByteToSymbol(_newData.minuteVal/10);
  _newData.symbol[2] = ByteToSymbol(_newData.minuteVal%10);
  _newData.symbol[1] = ByteToSymbol(_newData.secondVal/10);
  _newData.symbol[0] = ByteToSymbol(_newData.secondVal%10); 

  _newData.symbol[1] &= QD_DOT;
};

byte CDisplay::ByteToSymbol(const byte source)
{
  const static byte numerals[10] = { QD_0, QD_1, QD_2, QD_3, QD_4, QD_5, QD_6, QD_7, QD_8, QD_9 };    
  return numerals[source];
}

bool CDisplay::CheckUpdate()
{
  return (_currentData.displayMode != _newData.displayMode) ||
         (_currentData.secondVal != _newData.secondVal) ||
         (_currentData.minuteVal != _newData.minuteVal) ||
         (_currentData.symbol != _newData.symbol) ;
}

void CDisplay::Refresh()
{
  if (CheckUpdate())
  {
    _currentData = _newData;
    _QD.displayDigits(_currentData.symbol[3], _currentData.symbol[2], _currentData.symbol[1], _currentData.symbol[0]);
  }
}

void CDisplay::Setup()
{
  _period = 500; // 0.5 sec
  _QD.begin();
  _QD.displayClear();
  SetString(0,0,0,0);
  Refresh();
};

void CDisplay::Exec()
{
  switch(_currentData.displayMode)
  {
    case MODE_STRING:  break;
    case MODE_SET_MINUTE: 
      if(millis()-_lastTime >= _period)
      {
        _lastTime += _period;
        _blinkState = !_blinkState;
        if (_blinkState)
        {
          _newData.symbol[3] = ByteToSymbol(_newData.minuteVal/10);
          _newData.symbol[2] = ByteToSymbol(_newData.minuteVal%10);
        } 
        else 
        {
          _newData.symbol[3] = QD_NONE;
          _newData.symbol[2] = QD_NONE;
        }
      }      
      break;
    case MODE_SET_SECOND : 
      if(millis()-_lastTime >= _period)
      {
        _lastTime += _period;
        _blinkState = !_blinkState;
        if (_blinkState)
        {
          _newData.symbol[1] = ByteToSymbol(_newData.secondVal/10);
          _newData.symbol[0] = ByteToSymbol(_newData.secondVal%10);           
          _newData.symbol[1] &= QD_DOT;
        } 
        else 
        {
          _newData.symbol[1] = QD_DOT;
          _newData.symbol[0] = QD_NONE;
        }
      }
      break;
    case MODE_TIMER_ON : 
      if(millis()-_lastTime >= _period)
      {
        _lastTime += _period;
        _blinkState = !_blinkState;
        if (_blinkState)
        {
          _newData.symbol[1] &= QD_DOT;
        } 
        else 
        {
          _newData.symbol[1] |= 0b00000001;
        }
      }
      break;
    
    case MODE_TIMER_PAUSE : break;
  }
  Refresh();

};
