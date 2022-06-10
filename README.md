# TimedDigitalWrite
a library for doing non blocking digitalWrites for a duration of time on arduino compatible devices.
basically the "blink without delay" example as an easy to use library.
Uses LinkedPointerList library from the Library Manager so make sure you have it installed as well.


Example:

#include "timeddigitalwrite.h"

#define PIN 2
#define DURATION 1000

setup (){
pinMode(PIN,OUTPUT); //set PIN as OUTPUT
}

loop(){
timeddigitalwrite::handle(); // call in loop to handle ending the digitalWrites after duration has passed

timeddigitalwrite::start(PIN,HIGH,DURATION); //will set PIN 2 HIGH for about 1 second then low again
}



You can have multiple timeddigitalwrites running at the same time but there can be only on per pin at any time.
start will return false if pin allready in use.
