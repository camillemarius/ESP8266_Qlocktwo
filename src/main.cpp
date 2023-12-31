/*=================================================================================
--Includes
=================================================================================*/
#include <Arduino.h>
#include <led/WS2812.hpp>
#include <time/SwissTime.hpp>

/*=================================================================================
--Variablen
=================================================================================*/
const int sleeptime = 21; 
const int wakeuptime = 7;

const double wakeupdelay_ms = 60*1000; // ms

// Time instance
SwissTime swissTime(wakeupdelay_ms);
// Led-Strip Instance
WS2812 ws2812(114);



/*=================================================================================
--Setup
=================================================================================*/
void setup()
{
  // Serial Init
  Serial.begin(9600);

  // Init WS2812
  ws2812.ws2812_init();
  ws2812.preview();
}

/*=================================================================================
--Main
=================================================================================*/
void loop()
{
  /*---------------------------------------------------------------------------
  -- Update Time
  ---------------------------------------------------------------------------*/
  bool error = swissTime.getTime();
  if (error == false)
  {
    /*---------------------------------------------------------------------------
    -- Turn qlocktwo off by night
    ---------------------------------------------------------------------------*/
    if ((swissTime.h >= sleeptime) || (swissTime.h < wakeuptime))
    {
      ws2812.all_off();
      if(swissTime.h >= wakeuptime-1) {
        // check time more often one hour before wakeup
        delay(wakeupdelay_ms);
      }
      else {
        //delay(wakeupdelay_ms*60);
        delay(wakeupdelay_ms);
      }
    }
    else
    {
      ws2812.ws2812_refresh(swissTime.s, swissTime.m, swissTime.h);
      //ws2812.regulate_brightness();
      delay(wakeupdelay_ms);
    } 
  }
}