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

void redEWini()
{
PinMode(18,GPIO.OUTPUT);
digitalWrite(18, GPIO.LOW);
}

void redSNini()
{
PinMode(23,GPIO.OUTPUT);
digitalWrite(23, GPIO.LOW);
}

void greenEWini()
{
PinMode(25,GPIO.OUTPUT);
digitalWrite(23, GPIO.LOW);
}

void greenSNini()
{
PinMode(12,GPIO.OUTPUT);
digitalWrite(12, GPIO.LOW);
}

void yellowEWini()
{
PinMode(2,GPIO.OUTPUT);
digitalWrite(2, GPIO.LOW);
}

void yellowSNini()
{
PinMode(3,GPIO.OUTPUT);
digitalWrite(3, GPIO.LOW);
}

#include<wiringPi.h>
#include<stdio.h>

int main()
  {
redEW=18; // Pin 12
redSN=23; // Pin 16
greenEW=25; // Pin 22
greenSN=12; // Pin 32
yellowEW=2; // Pin 3
yellowSN=3; // Pin 5
sider=5; // Pin 29 BCM !!!
sideg=6; // Pin 31 BCM !!!
extrasensor1=4;//Pin 16
extrasensor2=5;//Pin 18

PinMode(18,GPIO.OUTPUT);
PinMode(23,GPIO.OUTPUT);
PinMode(25,GPIO.OUTPUT);
PinMode(12,GPIO.OUTPUT);
PinMode(2,GPIO.OUTPUT);
PinMode(3,GPIO.OUTPUT);

  digitalWrite(18, GPIO.LOW); //Initialize
  digitalWrite(23, GPIO.LOW);
  digitalWrite(25, GPIO.LOW);
  digitalWrite(12, GPIO.LOW);
  digitalWrite(2, GPIO.LOW);
  digitalWrite(3, GPIO.LOW);
  
 
  while (1)
  {
  int tr,tg,ty; //timing
  
  redSNini();
  redEWini();
  for (tr=5,tr>0,tr--)
  {
  digitalWrite(18,1);
  digitalWrite(23, 1);
  digitalWrite(5, 1); // all red
  }
  
  greenEWini();
  redSNini();
  for(tgEW=10,tgEW>0,tgEW--)
{
   digitalWrite(25, 1);
  digitalWrite(23, 1);
  digitalWrite(5, 1); //EW green, else red
}

redSNini();
for(tyEW=3,tyEW>0,tyEW--)
 {
 digitalWrite(2, 1);
  digitalWrite(23, 1);
  digitalWrite(5, 1); //EW yellow, else red
  }
  
  redEWini();
  greenSNini();
    for(tgSN=10,tgSN>0,tgSN--)
  {
  digitalWrite(18, 1);
 digitalWrite(12, 1);
  digitalWrite(5, 1); //SN green, else red
   }
   
   redEWini();
for(tySN=3,tySN>0,tySN--)
 {
  digitalWrite(18, 1);
  digitalWrite(3, 1);
  digitalWrite(5, 1); //SN yellow, else red
  }
  
if(wiringPiSetup()<0) //初始化wiringPi库
 {
 printf("can't init wiringPi\n"); //初始化失败时，打印出提示信息，并且推出
   return -1;
  }
  printf("test interrput\n"); //打印提示信息
  pinMode(0,INPUT); //引脚0为输入模式
  pullUpDnControl(0,PUD_UP); //设置0号引脚上拉
  
  //注册中断程序
  if(wiringPiISR(0,INT_EDGE_FALLING,&button)<0) //设置引脚下降沿触发
  {
     printf("unable ISR\n");   
  }
 
  while(1)
  {
     if(flag)
{
    for(tgside=10,tgEW>0,tgEW--)
  {
  digitalWrite(18, 1);
  digitalWrite(23, 1);
  digitalWrite(6, 1); //side green, else red
}
flag=0;
}
}

while True:

GPIO.output(18, GPIO.HIGH)
sleep(1)
GPIO.output(18, GPIO.LOW)
sleep(1)
}

void button()
{
flag=1;
}
