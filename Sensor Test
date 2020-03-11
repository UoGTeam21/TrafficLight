void SNsensorini()
 {
PinMode(12,GPIO.INPUT)
PinMode(18,GPIO.INPUT)
PinMode(2,GPIO.INPUT)
PinMode(3,GPIO.INPUT)
 }

void EWsesorini()
{
PinMode(23,GPIO.INPUT)
PinMode(25,GPIO.INPUT)
PinMode(4,GPIO.INPUT)
PinMode(5,GPIO.INPUT)
}

#include<WiringPi.h>
#include<stdio.h>

int main()
{
SNsensorini();
EWsensorini();
PinMode(23,GPIO.OUTPUT);

for(;;)
{
if(digitalRead (3) == 0)
digitalWrite (23,1);
}
return 0;
}
