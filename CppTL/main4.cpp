#include<WiringPi.h>
#include<stdio.h>
#include<iostream>
#include<thread>
#include<chrono>// for time delay in c++
#include<list>
#include<mutex>
using namespace std;

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

class CarLightEW // 车行道红绿灯
{
 friend void Gettg(CarLightEW*, SensorES &, SensorWN & );// 他的子函数不再需要有友元，因为tg为静态， 改变这个属性， 所有一起变。
public: 
  CarLightEW(int tgEW=0, int tyEW=3)
  { 
    redEWini();
    greenEWini();
    yellowEWini();
    this->tgEW= tgEW;
    this->tg= tg;
   }
 public:
  void redEWini()
{
PinMode(1,OUTPUT);
digitalWrite(1, LOW);
}

void greenEWini()
{
PinMode(6,OUTPUT);
digitalWrite(6, LOW);
}

void yellowEWini()
{
PinMode(3,OUTPUT);
digitalWrite(3, LOW);
}
 
  virtual void CounterGR()// EW绿灯亮 
    {
    greenEWini();
  redSNini();
  //SNsensorini();变量调用构造函数初始化
   for(tgEW=tg;tgEW>0;tgEW--)//EW green, and SN sensortimer star 
{
   digitalWrite(6, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 1); //EW green, else red
     tg--;
    if(CarLightEW::tg<=5 && tg>0)// counterv t can not exceed 1 minutes?
      { obj.InputT();}// 五秒倒计时开始传+ //sensortimer();
     }
   
 virtual void CounterY() 
 {
 yellowEWini();
 //redSNini();
for(tyEW=3;tyEW>0;tyEW--)
 {
 digitalWrite(2, 1);
  //digitalWrite(4, 1);
  //digitalWrite(5, 1); //EW yellow, else red(不用）
  }
  public: 
  static int tg;
  private:
  int tgEW;
   int tyEW;
  }
  int CarLightEW::tg=0;//tg initialize.

  class CarLightSN: public CarLightEW
 {
     CarLightSN(int tgEW=0, int tyEW=3, int tySN=3, int tgSN=0 ): CarLightEW(tgEW, tyEW)
     { 
      redSNini();
      greenSNini();
      yellowSNini();
       this->tgSN= tgSN;
       this->tySN= tySN;
     }
   void redSNini()
{
PinMode(4,OUTPUT);
digitalWrite(4, LOW);
}
   void greenSNini()
{
PinMode(26,OUTPUT);
digitalWrite(26, LOW);
}
void yellowSNini()
{
PinMode(2,OUTPUT);
digitalWrite(2, LOW);
} 

  virtual void CounterGR(SensorES& obj)// SN绿灯亮
    {
   redEWini();
  greenSNini();
   EWsesorini(); // SN green, and EW sensortimer star 
  for(tgEW=CarLightEW::tg; tgSN>0; tgSN--)
   {
     digitalWrite(1, 1);
    digitalWrite(26, 1);
    digitalWrite(27, 1); //SN green, else red;
      CarLightEW::tg--;
  if(CarLightEW::tg<=5 && tg>0)// counterv t can not exceed 1 minutes?
      { obj.InputT();}// 五秒倒计时开始传
    }
   
virtual void CounterY() //黄灯亮
  {
  yelloeSNini();
//redEWini();
 for(tySN=3;tySN>0;tySN--)
   {
  //digitalWrite(1, 1);
  digitalWrite(3, 1);
  //digitalWrite(5, 1); //SN yellow, else red
   sensortimer();
   }
  private:
     int tgSN;
     int tySN;
     
class SensorES{
   public: 
  SensorES(){
     t0=0;
      t=0;//初始化
    PinMode(23,OUTPUT);
     }// pinmode (int pin, int mode), computer control it by 23
 void Input()
  {   
  t0 = CarLight::tg;// ？！ 此处应该有锁！
  }
  void GetT()
  {
   do {
   t=t+0.01;
   ds delay(10);  //sleep(0.01)=10ms
  }while(digitalRead(12)==(1)&& t0>0);// has input signals 被遮挡
    }
  virtual int outputT()
    { 
    digitalWrite (23,1);    //operate timer; digitalwrite(int pin, int value)// if value != 0 == high)
    reture t; }
  private: 
    int t;
    static int t0;

class SensorWN: punlic SensorES 
{
  SensorES(){
     t1=0;
      t2=0;//初始化
    PinMode(23,OUTPUT);
     }// pinmode (int pin, int mode), computer control it by 23
  public:
    void GetT()
    {
    t1= CarLight::tg;
   do{
   t2=t2+0.01;
   ds delay(10);  //sleep(0.01)=10ms
  }while(digitalRead(18==(1) && t1>0);// has input signals
    }
  virtual int outputT()
    {  
    digitalWrite (23,1);    //operate timer; digitalwrite(int pin, int value)// if value != 0 == high)
    reture t2; 
    }
  private: 
  int t2;
  static int t1;

class Button{
 private: int flag;
  public:
  friend class WalkLight;
  Button(){//构造函数
   int flag=0;
    pinMode(0,INPUT); //引脚0为BUTTON输入模式
  pullUpDnControl(0,PUD_UP); //设置0号引脚上拉,(设置成上拉输入，引脚上就加了一个上拉电阻，那么引脚就默认是高电平，当再去读取这个引脚的时候，
   }
 int CheckB()
  {
    if(digitalRead(0) == 0)// 检测到低电平
     {
        delay(20); // 延时销抖, for machine button 
        if(digitalRead(0) == 0)// 检测到低电平
        { flag= 1;}
   else 
       { flag=-1;}
     return flag;
       }
     
   class WalkLight{
     int tgside;
     int tw;
     public:
   WalkLight(int tgside=10; int tw=0)
     { 
       this->tgside= tgside;
      this->tw=tw;
     }
   int CheckB()
     {b.CheckB();}
   void WLighting()
   { 
     tw=CheckB();//digitalWrite(18, GPIO.HIGH); // all side greenlight lighting
     if(tw=1){
    for(tgside=10;tgside>0;tgside--)
  {
  digitalWrite(1, 1);
  digitalWrite(4, 1);
  digitalWrite(6, 1); //side green, else red
    }
     }
     void WNLighting(){
    if(tw=0)
      {
   digitalWrite(1, LOW);// no signal was checked, no light respon
       digitalWrite(4, LOW);
       digitalWrite(6, LOW);
        }
     }
  void Setflag()
     {b.flag=0;}
  private: Button b;
     }
  
  void YellowLight(CarLightEW*YL)//virtual黄灯运行，多态
    { 
    YL->CounterY();
    }
 
  void GRLight(CarLightEW*GRL)//virtual红绿灯灯运行，多态
     {
     GRL->CounterGR();
     }
     
  int Newtg(SensorES & Ts)// sensor 输出的时间进行计算virtual， 多态
   {
  if(Ts.outputT()<1)
  {
   return 10;//Tc.Gettg()= Tc.Gettg();// 3 chooses
  }
     else if(Ts.outputT()>=1 && Ts.outputT()<=2)
    {
      return 15//Tc.Gettg()+=5; 
    }
       else if(Ts.outputT()>=2)
  {
    return 20;//Tc.Gettg()+=10;
  }
 }// 以上为四个sensor线程需要的全部过程：输出时间并计算
 
void Gettg(CarLightEW*pt, SensorES & Obj1, SensorWN & Obj2)// 作比较, 然后给重新给静态函数tg赋值 输入对象（同一个类的不同对象）
{
  int pt->tg=0;//局部变量
  //SensorES tes; SensorWN twn;
  if(Newtg(Obj1)>=Newtg(Obj2))
  { 
    pt->tg=Newtg(Obj1);
  }
  else {pt->tg=Newtg(Obj2);
    }
 }


int main()
  {
 int tag=0;
   CarLightEW CEW;
  CarLightSN CSN;
  SensorES SE, SS; 
  SensorWN SW, SN;
  WalkLight WL;

  if(WiringPiSetup() == -1) //initialize wiringpi store fail or not
 {
  printf("you set up wiringpi failed"); //failed
  return 1;
   
   while true//一条线 按照C语言改写成C++；
   {
    GRLight(&CEW);
    YellowLight(&CEW);
     Gettg(&CEW, SS, SN);
     GRLight(&CSN); 
     YellowLight(&CSN);
     Gettg(&CSN, SE, SW);
      if(WL.CheckB()=1)
      { WL. WLighting()
      WL.Setflag();}
    else
    {WL. WNLighting();
    WL.Setflag();}
   }
  return 0；
   }
 
