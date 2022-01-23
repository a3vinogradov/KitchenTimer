#include "TimerController.h"
#include "CDisplay.h"
#include "CButton.h"
#include "CEncoder.h"

#define Display_SC_Pin 2
#define Display_DI_Pin 5
#define Display_CLK_Pin 3 // CLK предположительно

#define Encoder_S1_Pin 6
#define Encoder_S2_Pin 7
#define Encoder_Key_Pin 8

#define ButtonOk_Pin 9 
#define ButtonCansel_Pin 10 

CEventQueue gEventQueue;
CButton gButtonOk(1, ButtonOk_Pin, &gEventQueue);
CButton gButtonCansel(2, ButtonCansel_Pin, &gEventQueue);

CEncoder gEncoder(3, Encoder_S1_Pin, Encoder_S2_Pin, Encoder_Key_Pin, &gEventQueue);

CDisplay gDisplay(Display_SC_Pin, Display_DI_Pin, Display_CLK_Pin);

CTimerController gTimerController(&gDisplay, &gEventQueue);


void setup()
{
  Serial.begin(9600);
  gButtonOk.Setup();
  gButtonCansel.Setup();
  gEncoder.Setup();
  
  gDisplay.Setup();
  gTimerController.Setup();
  delay (1000);
}

void loop()
{
  gButtonOk.Exec();
  gButtonCansel.Exec();
  gEncoder.Exec();
  gDisplay.Exec();
  gTimerController.Exec();
}
