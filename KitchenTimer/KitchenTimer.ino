#include "TimerController.h"
#include "CDisplay.h"

#define Display_SC_Pin 2
#define Display_DI_Pin 5
#define Display_CLK_Pin 3 // CLK предположительно

CDisplay _display(Display_SC_Pin, Display_DI_Pin, Display_CLK_Pin);

CTimerController timerController;

void setup()
{
  _display.Setup();

  delay (2000);
  //_display.SetString(QD_NONE, QD_O, QD_F, QD_F);
  //_display.SetTime(2,30,MODE_TIMER_PAUSE);
  //_display.SetTime(4,40,MODE_TIMER_ON);
  //_display.SetTime(10,56,MODE_SET_SECOND);
  _display.SetTime(13,88,MODE_SET_MINUTE);

  timerController.Setup();
}

void loop()
{
  //_display.
//    _display._QD.displayClear();
//    _display._QD.displayDigits(QD_O,QD_O, QD_O, QD_f); // off
//    delay(1000);
//    _display._QD.displayDigits(QD_O, QD_f, QD_f,QD_NONE); // off
//    delay(1000);
  _display.Exec();
  timerController.Exec();
}
