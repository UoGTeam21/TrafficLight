#include<WiringPi.h>
#include<stdio.h>
#include<stdlib.h>//?

#define redEW 18 // Pin 12
#define redSN 23 // Pin 16
#define greenEW 25 // Pin 22
#define greenSN 12 // Pin 32
#define yellowEW 2// Pin 13
#define yellowSN 3 // Pin 15
#define sider 5// Pin 29 BCM !!!
#define sideg 6// Pin 31 BCM !!!
#define extrasensor1 4//Pin 16
#define extrasensor2 5 //Pin 18
#define button 11//Pin 11


void SNsensorini()
 {
PinMode(12,GPIO.INPUT)
PinMode(18,GPIO.INPUT)
PinMode(2,GPIO.INPUT)
PinMode(3,GPIO.INPUT)
 GetnewtEW();//EW green, and SN sensortimer star (SN RED)
 }

  void EWsesorini()
{
PinMode(23,GPIO.INPUT)
PinMode(25,GPIO.INPUT)
PinMode(4,GPIO.INPUT)
PinMode(5,GPIO.INPUT)
 GetnewtSN();//SN  green, and EW sensortimer star (EW RED)
 }

void redEWini()
{
PinMode(1,GPIO.OUTPUT);
digitalWrite(1, GPIO.LOW);
 redSNini();
  greenEWini();
   greenSNini();
   yellowEWini();
   yellowSNini();
}

void redSNini()
{
PinMode(4,GPIO.OUTPUT);
digitalWrite(4, GPIO.LOW);
  greenEWini();
   greenSNini();
   yellowEWini();
   yellowSNini();
}

void greenEWini()
{
PinMode(25,GPIO.OUTPUT);
digitalWrite(23, GPIO.LOW);
  redEWini();
 redSNini();
   yellowEWini();
   yellowSNini();
}

void greenSNini()
{
PinMode(26,GPIO.OUTPUT);
digitalWrite(26, GPIO.LOW);
  redEWini();
 redSNini();
   yellowEWini();
   yellowSNini();
}

void yellowEWini()
{
PinMode(2,GPIO.OUTPUT);
digitalWrite(2, GPIO.LOW);
  redEWini();
 redSNini();
  greenEWini();
   greenSNini();
}

void yellowSNini()
{
PinMode(3,GPIO.OUTPUT);
digitalWrite(3, GPIO.LOW);
  redEWini();
 redSNini();
  greenEWini();
   greenSNini();
}

void Button()// check the button
{
  pinMode(11,GPIO.INPUT); //引脚0为BUTTON输入模式
  pullUpDnControl(11,PUD_UP); //设置0号引脚上拉,(设置成上拉输入，引脚上就加了一个上拉电阻，那么引脚就默认是高电平，当再去读取这个引脚的时候，
 //就可以检测到低电平了)
}

/*1.void sensortimer()
{
PinMode(23,GPIO.OUTPUT);// pinmode (int pin, int mode), computer control it by 23
int timer=0;
do
{
t=t+0.01;
delay(10);  //sleep(0.01)=10ms 
  if(t>=1)// counterv t can not exceed 1 minutes?
  {
   t=0;
   digitalWrite (23,1);    //operate timer; digitalwrite(int pin, int value)// if value != 0 == high)
  }
}
while(digitalRead(12==1)&&digitalRead(18==1));// has input signals
}

*/void sensortimer()
{
PinMode(23,GPIO.OUTPUT);// pinmode (int pin, int mode), computer control it by 23
int t1,t=0;
do
{
t=t+0.01;
delay(10);  //sleep(0.01)=10ms 
    if(tgEW=t1-5 ||tgSN=t1-5)// only check for 5 mins each time
  {
    break;
  }
}while(digitalRead(12==1)&&digitalRead(18==1));// has input signals
    digitalWrite (23,1); //operate timer;// digitalwrite(int pin, int value)// if value != 0 == high)
     t=0;
}

 void GetnewtEW()
 {
  if(t<=1)
  {
   tgEW=tgEW;// 3 chooses
  }
    else if(t>=1 && t<=2)
    {
      tgEW+=5; 
    }
       else if(t>=2)
  {
   tgEW+=10;
  }
  t1=tgEW;// change t1 every time
 }

/*tgEW=(t<=1)? 15:15+(t-1)*10;// 2 or more chooses

 */void GetnewtSN()
 {
  if(t<=1)
  {
   tgSN=tgSN; // 3 chooses
  }
    else if(t>=1 && t<=2)
    {
   tgSN+=5;
    }
       else if(t>=2)
     {
     tgSN+=10; 
     }
  t1=tgSN;// change t1 every time
 }

/*tgSN=(t<=1)? 15:15+(t-1)*10;// 2 or more chooses


*/int main()
  {
 
  auto int tgSN,tgEW,t1;// t1为整体变量，子函数可以调用
  int tr,tg,ty; //timing

  if(WiringPiSetup() == -1) //initialize wiringpi store fail or not
 {
  printf("you set up wiringpi failed"); //failed
  return 1;
 }

PinMode(1,GPIO.OUTPUT);
PinMode(4,GPIO.OUTPUT);
PinMode(6,GPIO.OUTPUT);
PinMode(26,GPIO.OUTPUT);
PinMode(2,GPIO.OUTPUT);
PinMode(3,GPIO.OUTPUT);

  digitalWrite(1, GPIO.LOW); //Initialize
  digitalWrite(4, GPIO.LOW);
  digitalWrite(6, GPIO.LOW);
  digitalWrite(26, GPIO.LOW);
  digitalWrite(2, GPIO.LOW);
  digitalWrite(3, GPIO.LOW);
  
 
   while true // intialize succeed
  {
   
  redSNini();
  redEWini();
  for (tr=3,tr>0,tr--)
  {
  digitalWrite(1,1);
  digitalWrite(4, 1);
  digitalWrite(5, 1); // all red
  }
  
  greenEWini();
  redSNini();
  SNsensorini(); //EW green, and SN sensortimer star 
  for(tgEW=10,tgEW>0,tgEW--)
{
   digitalWrite(6, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 1); //EW green, else red
   sensortimer();
}

 yellowEWini();
 //redSNini();
for(tyEW=3,tyEW>0,tyEW--)
 {
 digitalWrite(2, 1);
  //digitalWrite(4, 1);
  digitalWrite(5, 1); //EW yellow, else red
  }
  
  redEWini();
  greenSNini();
   EWsesorini(); // SN green, and EW sensortimer star 
    for(tgSN=10,tgSN>0,tgSN--)
  {
  digitalWrite(1, 1);
 digitalWrite(26, 1);
  digitalWrite(5, 1); //SN green, else red;
   }
   
  yelloeSNini();
//redEWini();
for(tySN=3,tySN>0,tySN--)
 {
  //digitalWrite(1, 1);
  digitalWrite(3, 1);
  digitalWrite(5, 1); //SN yellow, else red
   sensortimer();
 }
    
  if(digitalRead(0) == 0)// 检测到低电平
     {
        delay(20); // 延时销抖, for machine button 
        if(digitalRead(0) == 0)// 检测到低电平
        { 
 goto  walk_light;
     }
   else 
       {
       digitalWrite(1, GPIO.LOW);// no signal was checked, no light respon
       digitalWrite(4, GPIO.LOW);
       digitalWrite(6, GPIO.LOW);
        }
 
  walk_light:
   //digitalWrite(18, GPIO.HIGH); // all side greenlight lighting
    for(tgside=10,tgside>0,tgside--)
  {
  digitalWrite(1, 1);
  digitalWrite(4, 1);
  digitalWrite(6, 1); //side green, else red
    }
 return 0;
 }
   


 
 
 
 //  while(1)
  {
     //if(flag)
//{
//while(digitalRead(0)==LOW); //检测按键是否松开，没有松开的话，一直等待
 // GPIO.output(18, GPIO.HIGH);
//flag=0;
//}


