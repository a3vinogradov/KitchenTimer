#include "CDisplay.h"

void PrintData(CDisplayData* pData, String lable)
{
    return;
//    Serial.print(lable);
//    Serial.println(" - Data {");
//    Serial.print("  displayMode = "); Serial.print(pData->displayMode); Serial.println(";");
//    Serial.print("  secondVal = "); Serial.print(pData->secondVal); Serial.println(";");
//    Serial.print("  minuteVal = "); Serial.print(pData->minuteVal); Serial.println(";");
//    Serial.print("  symbol = {"); 
//    Serial.print(pData->symbol[3]);Serial.print(";");
//    Serial.print(pData->symbol[2]);Serial.print(";");
//    Serial.print(pData->symbol[1]);Serial.print(";");
//    Serial.print(pData->symbol[0]);Serial.println("}");
//    Serial.println("}");
}
void CopyData(CDisplayData* src, CDisplayData* dst)
{
  dst->displayMode = src->displayMode;
  dst->secondVal = src->secondVal;
  dst->minuteVal = src->minuteVal;
  dst->symbol[0] = src->symbol[0];
  dst->symbol[1] = src->symbol[1];
  dst->symbol[2] = src->symbol[2];
  dst->symbol[3] = src->symbol[3];
}

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
  //Serial.println("========== SetString ===========");
  PrintData(&_newData, "NewData");
  Refresh();
};

void CDisplay::SetSeconds(const byte value)
{};

void CDisplay::SetMinutes(const byte value)
{};

void CDisplay::SetTime(const byte valueMin, const byte valueSec, const byte mode)
{
  //Serial.println("SetTime; mode="+String(mode)+", curMode="+String(_currentData.displayMode));
  if (_currentData.displayMode != mode){
    _newData.displayMode = mode;
    if( (mode == MODE_TIMER_ON) ||
        (mode == MODE_SET_SECOND) ||
        (mode == MODE_SET_MINUTE) ||
        (mode == MODE_TIMER_PAUSE)
       )
    {
      _lastTime = millis();
      _blinkState = true;
    }
    //Serial.println("SetTime");
  }
  
  _newData.secondVal = valueSec;
  _newData.minuteVal = valueMin;  

  _newData.symbol[3] = ByteToSymbol(_newData.minuteVal/10);
  _newData.symbol[2] = ByteToSymbol(_newData.minuteVal%10);
  _newData.symbol[1] = ByteToSymbol(_newData.secondVal/10);
  _newData.symbol[0] = ByteToSymbol(_newData.secondVal%10); 

  //_newData.symbol[1] &= QD_DOT;
  if (_blinkState)
  {
    _newData.symbol[1] &= QD_DOT;
  } 
  else 
  {
    _newData.symbol[1] |= 0b00000001;
  }
  Refresh();
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
         (_currentData.symbol[0] != _newData.symbol[0]) ||
         (_currentData.symbol[1] != _newData.symbol[1]) ||
         (_currentData.symbol[2] != _newData.symbol[2]) ||
         (_currentData.symbol[3] != _newData.symbol[3]) ;
}

void CDisplay::Refresh()
{
  if (CheckUpdate())
  {
    PrintData(&_currentData, "CurrentData");   
    PrintData(&_newData, "NewData");   
    CopyData(&_newData,&_currentData);
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
    case MODE_STRING:  
      //_blinkState = false;
      //Serial.println("ModeString.Exec");
      break;
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
        //Serial.println("blink = "+String(_blinkState));
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
    
    case MODE_TIMER_PAUSE : 
      break;
  }
  Refresh();
};
