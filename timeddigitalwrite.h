/*A class to do non blocking digital writes for a duration of time in millis
 * Usage:
 * call start(p,v,d) with the pin, value(LOW or HIGH),and the duration
 * call handle() somewhere in your loop
 * you can also set a default duration by setting defaultduration to a duration in millis
 * and then call start with only pin and value
 * Author: David Hack
 * Date: 06.06.2022
 */
#pragma once
#include <Arduino.h>
#include <LinkedPointerList.h> //https://github.com/jonnieZG/LinkedPointerList

class timeddigitalwrite{
  private:
    static LinkedPointerList<timeddigitalwrite> handlelist;
    unsigned long endtime = 0;
    uint8_t pin;
    uint8_t value;
    timeddigitalwrite(uint8_t pin,uint8_t value,unsigned long duration);
    ~timeddigitalwrite();
    bool timeup();
    uint8_t getpin();
  public:
    static unsigned long defaultduration;
    static void handle();
    static bool start(uint8_t pin,uint8_t value,unsigned long duration);
    static bool start(uint8_t pin,uint8_t value);
    };
