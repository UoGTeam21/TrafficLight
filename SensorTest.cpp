#include<WiringPi.h>
#include<stdio.h>

void SNsensorini()
 {
PinMode(5,GPIO.INPUT)
PinMode(6,GPIO.INPUT)
PinMode(4,GPIO.INPUT)
PinMode(21,GPIO.INPUT)
 GetnewtEW();//EW green, and SN sensortimer star (SN RED)
 }

  void EWsesorini()
{
PinMode(27,GPIO.INPUT)
PinMode(26,GPIO.INPUT)
PinMode(1,GPIO.INPUT)
PinMode(21,GPIO.INPUT)
 GetnewtSN();//SN  green, and EW sensortimer star (EW RED)
 }



int main()
{
SNsensorini();
EWsensorini();
PinMode(23,GPIO.OUTPUT);

for(;;)
{
if(digitalRead (5) == 1)
digitalWrite (23,1);
}
return 0;
}
