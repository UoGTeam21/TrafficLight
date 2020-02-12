# TrafficLight
#include<iostream>
  #include <siringPi.h>
  #include<stdio.h>
  #include<stdlib.h>
using namespace std;
  import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
  sensor= ;    //sensor GPIO code
GPIO.setup(sensor,GPIO.IN) 

int main()
  {
  int redEW=18; // pin 12
  int redSN=23; // pin 16
  int greenEW=25; // pin 22
  int greenSN=12; // pin 32
  int yellowEW=2; // pin 3
  int yellowSN=3; // pin 5
  int sider=5; // pin 29
  int sideg=6; // pin 31
  int flag=0;
  
  import RPi.GPIO as GPIO
  import time  
GPIO.setup(18,GPIO.OUT)
GPIO.setup(23,GPIO.OUT)
GPIO.setup(25,GPIO.OUT)
GPIO.setup(12,GPIO.OUT)
GPIO.setup(2,GPIO.OUT)
GPIO.setup(3,GPIO.OUT)

  GPIO.output(18, GPIO.LOW); //initialize
  GPIO.output(23, GPIO.LOW);
  GPIO.output(25, GPIO.LOW);
  GPIO.output(12, GPIO.LOW);
  GPIO.output(2, GPIO.LOW);
  GPIO.output(3, GPIO.LOW);
  
 
  while (1)
  {
  int tr,tg,ty; //timing
  for (tr=5,tr>0,tr--)
  {
  GPIO.output(18, GPIO.HIGH);
  GPIO.output(23, GPIO.HIGH);
  GPIO.output(5, GPIO.HIGH); // all red
  }
  
  for(tgEW=10,tgEW>0,tgEW--)
  {
   GPIO.output(25, GPIO.HIGH);
  GPIO.output(23, GPIO.HIGH);
  GPIO.output(5, GPIO.HIGH); //EW green, else red
}
for(tyEW=3,tyEW>0,tyEW--)
 {
  GPIO.output(2, GPIO.HIGH);
  GPIO.output(23, GPIO.HIGH);
  GPIO.output(5, GPIO.HIGH); //EW yellow, else red
  }
    for(tgSN=10,tgSN>0,tgSN--)
  {
   GPIO.output(18, GPIO.HIGH);
  GPIO.output(12, GPIO.HIGH);
  GPIO.output(5, GPIO.HIGH); //SN green, else red
}
for(tySN=3,tySN>0,tySN--)
 {
  GPIO.output(18, GPIO.HIGH);
  GPIO.output(3, GPIO.HIGH);
  GPIO.output(5, GPIO.HIGH); //SN yellow, else red
  }
  
  if(button)                  //pederstrain button check
  {
    for(tgside=10,tgEW>0,tgEW--)
  {
   GPIO.output(18, GPIO.HIGH);
  GPIO.output(23, GPIO.HIGH);
  GPIO.output(6, GPIO.HIGH); //side green, else red
  flag=0;
}
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
if(wiringPiSetup()<0) //初始化wiringPi库
 {
 printf("can't init wiringPi\n"); //初始化失败时，打印出提示信息，并且推出
   return -1;
  }
  printf("test interrput\n"); //打印提示信息
  pinMode(0,INPUT); //引脚0为输入模式
  pullUpDnControl(0,PUD_UP); //设置0号引脚上拉
  
  //注册中断程序
  if(wiringPiISR(0,INT_EDGE_FALLING,&myInterruptService)<0) //设置引脚下降沿触发
  {
     printf("unable ISR\n");   
  }
 
  while(1)
  {
     if(flag)
{
while(digitalRead(0)==LOW); //检测按键是否松开，没有松开的话，一直等待
return flag; //打印提示信息
}
 } 
