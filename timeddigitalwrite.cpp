/*A class to do non blocking digital writes for a duration of time in millis
 * Usage:
 * call start(p,v,d) with the pin, value(LOW or HIGH),and the duration
 * call handle() somewhere in your loop
 * you can also set a default duration by setting defaultduration to a duration in millis
 * and then call start with only pin and value
 * Author: David Hack
 * Date: 06.06.2022
 */

#include "timeddigitalwrite.h"

//set default duration
unsigned long timeddigitalwrite::defaultduration = 1000;

LinkedPointerList<timeddigitalwrite> timeddigitalwrite::handlelist = LinkedPointerList<timeddigitalwrite>();

//receives the pin, value and duration and initializes an object to keep track of them
//also makes the initial call to digitalWrite
timeddigitalwrite::timeddigitalwrite(uint8_t pin,uint8_t value,unsigned long duration){
  this->pin = pin;
  this->value = value;
  this->endtime = millis() + duration;
  digitalWrite(pin,value);
  Serial.println("pin on");
}

//sets the Pin to !value when the duration is over
timeddigitalwrite::~timeddigitalwrite(){
  digitalWrite(pin,(value == LOW)? HIGH :LOW);
  Serial.println("pin off");
  }

//returns true if duration is over
bool timeddigitalwrite::timeup(){
  return (millis() >= endtime);
}

//returns pin of object
uint8_t timeddigitalwrite::getpin(){
  return pin;
}

//to be called in loop to check if duration has passed
//if duration has passed it deletes the object
//which also calls ~timeddigitalwrite to set the pin to !value
void timeddigitalwrite::handle(){
for(int i = 0; i < handlelist.size();i++){
 if(handlelist.get(i)->timeup())delete (handlelist.remove(i));
 }
}

//receives pin, value and duration
//creates new object with pin, value and duration and adds it to handlelist
//if pin not allready in use
//returns false if pin allready in use
bool timeddigitalwrite::start(uint8_t pin,uint8_t value,unsigned long duration){
 for(int i = 0; i < handlelist.size();i++){
  if(handlelist.get(i)->getpin() == pin)return false;
 }
 handlelist.add(new timeddigitalwrite(pin,value,duration));
 return true;
}

//same as start(p,v,d) but only receives pin and value and uses the default duration
bool timeddigitalwrite::start(uint8_t pin,uint8_t value){
  return start(pin, value, defaultduration);
}
