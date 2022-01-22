#include "TimerController.h"
#include "CDisplay.h"

#define Display_SC_Pin 2
#define Display_DI_Pin 5
#define Display_CLK_Pin 3 // CLK предположительно

CDisplay gDisplay(Display_SC_Pin, Display_DI_Pin, Display_CLK_Pin);

CTimerController gTimerController(&gDisplay);

void setup()
{
  Serial.begin(9600);
  
  gDisplay.Setup();
  gTimerController.Setup();
  delay (1000);
  //gDisplay.SetString(QD_NONE, QD_O, QD_F, QD_F);
  //gDisplay.SetTime(2,30,MODE_TIMER_PAUSE);
  //gDisplay.SetTime(4,40,MODE_TIMER_ON);
  //gDisplay.SetTime(10,56,MODE_SET_SECOND);
  //gDisplay.SetTime(13,88,MODE_SET_MINUTE);
}

void loop()
{
  //gDisplay.
//    gDisplay._QD.displayClear();
//    gDisplay._QD.displayDigits(QD_O,QD_O, QD_O, QD_f); // off
//    delay(1000);
//    gDisplay._QD.displayDigits(QD_O, QD_f, QD_f,QD_NONE); // off
//    delay(1000);
  gDisplay.Exec();
  gTimerController.Exec();
}
