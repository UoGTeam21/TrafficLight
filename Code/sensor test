
#include<wiringPi.h>
#include<stdio.h>

void SNsensorini()
 {
pinMode(5,INPUT);
pinMode(6,INPUT);
pinMode(4,INPUT);
pinMode(21,INPUT);
 }

  void EWsensorini()
{
pinMode(27,INPUT);
pinMode(26,INPUT);
pinMode(1,INPUT);
pinMode(21,INPUT);
}



int main()
{
wiringPiSetup();
SNsensorini();
EWsensorini();
pinMode(23,OUTPUT);
pinMode(1,INPUT);

for(;;)
{

if (digitalRead(1)==HIGH)
{
digitalWrite (23,HIGH);
delay(1000);
}

if (digitalRead(1)==LOW)
{
digitalWrite (23,LOW);
delay(1000);
}

}
return 0;
}
