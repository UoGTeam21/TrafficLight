#include<WiringPi.h>
#include<stdio.h>
#include<iostream>
#include<thread>
#include<chrono>// for time delay in c++
#include<list>
#include<mutex>
using namespace std;

#define redEW 1 // Pin 12(wiringPi)
#define redSN 4 // Pin 16
#define greenEW 6 // Pin 22
#define greenSN 26 // Pin 32
#define yellowEW 2// Pin 13
#define yellowSN 3 // Pin 15
#define sider 21// Pin 29 
#define sideg 22// Pin 31 
#define sensorEW 27//Pin 36
#define sensorSN 5 //Pin 18
#define button 0//Pin 11

class CarLightEW // East-West side mian traffic light
{
 friend void Gettg(CarLightEW*, SensorES &, SensorWN & );// The subfunction do not need friend, tg is static
public: 
  CarLightEW(int tgEW=10, int tyEW=3)
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
digitalWrite(1, LOW); // initialize East-West side red light 
}

void greenEWini()
{
PinMode(6,OUTPUT);
digitalWrite(6, LOW); // initialize East-West side green light
}

void yellowEWini()
{
PinMode(2,OUTPUT);
digitalWrite(2, LOW); // initialize East-West side yellow light
}
 
  virtual void CounterGR()// turn on East-West side green light绿灯亮 
    {
    greenEWini();
  redSNini();
  //SNsensorini();变量调用构造函数初始化initialize variable construction function
   for(tgEW=tg;tgEW>0;tgEW--)//East-West side turn to green light, and South-North side sensortimer start to work 
{
   digitalWrite(6, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 1); //East-West side green light, else sides red light
     tg--;
    if(tg<=5 && tg>0)// counterv t can not exceed 1 minutes?
      { obj.InputT();}// 五秒倒计时开始传+ //sensortimer();
     }
   
 virtual void CounterY() //turn on the yellow light
 {
 yellowEWini();
 //redSNini();
for(tyEW=3;tyEW>0;tyEW--)
 {
 digitalWrite(2, 1);//digitalWrite(4, 1); //digitalWrite(5, 1); //East-West side yellow light, else red
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
     CarLightSN(int tgEW=10, int tyEW=3, int tySN=3, int tgSN=10 ): CarLightEW(tgEW, tyEW)
     { 
      redSNini();
      greenSNini();
      yellowSNini();
       this->tgSN= tgSN;
       this->tySN= tySN;
     }
   void redSNini() // initialize South-North side red light
{
PinMode(4,OUTPUT);
digitalWrite(4, LOW);
}
   void greenSNini() // initialize South-North side green light
{
PinMode(26,OUTPUT);
digitalWrite(26, LOW);
}
void yellowSNini() // initialize South-North side yellow light
{
PinMode(3,OUTPUT);
digitalWrite(3, LOW);
} 

  virtual void CounterGR(SensorES& obj) // turn on South-North side green light绿灯亮
    {
   redEWini();
  greenSNini();
   EWsesorini(); // South-North side green light, and East-West side sensortimer start to work 
  for(tgEW=CarLightEW::tg; tgSN>0; tgSN--)
   {
     digitalWrite(1, 1);
    digitalWrite(26, 1);
    digitalWrite(27, 1); //SN green, else red;
      CarLightEW::tg--;
  if(CarLightEW::tg<=5 && tg>0)// counterv t can not exceed 1 minutes?
      { obj.InputT();}// 五秒倒计时开始传5 seconds countdown
    }
   
virtual void CounterY() // turn on the yellow light黄灯亮
  {
  yelloeSNini();
//redEWini();
 for(tySN=3;tySN>0;tySN--)
   {
   digitalWrite(3, 1);//digitalWrite(1, 1);//digitalWrite(5, 1); //South-North side yellow light, else red
 }
  private:
     int tgSN;
     int tySN;
     
class SensorES{
   public: 
  SensorES(){
     t0=0;
      t=0;//initialization
    PinMode(23,OUTPUT);
     }// pinmode (int pin, int mode), computer control it by 23
 void Input()
  {   
  t0 = CarLight::tg;// set a lock
  }
  void GetT()
  {
   do {
   t=t+0.01;
   ds delay(10);  //sleep(0.01)=10ms
  }while(digitalRead(27)==1 && t0>0);// has input signals been blocked
    }
  virtual int outputT()
    { 
    digitalWrite (23,1);    //operate timer; digitalwrite(int pin, int value)// if value != 0 == high)
    reture t; }
  private: 
    int t;
    static int t0;

class SensorWN: public SensorES 
{
  SensorES(){
     t1=0;
      t2=0;//initialization
    PinMode(23,OUTPUT);
     }// pinmode (int pin, int mode), computer control it by 23
  public:
   void GetT()
    {
    t1= CarLight::tg;
   do{
   t2=t2+0.01;
   ds delay(10);  //sleep(0.01)=10ms
  }while(digitalRead((5)==1 && t1>0);// has input signals
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
  Button()//构造函数construct function
  {
   int flag=0;
    pinMode(0,INPUT); //引脚0为BUTTON输入模式 set pin 0 to input mode
  pullUpDnControl(0,PUD_UP); //Set pin 0 to pull up, so pin 0 defaults to high level设置0号引脚上拉,(设置成上拉输入，引脚上就加了一个上拉电阻，那么引脚就默认是高电平，当再去读取这个引脚的时候
   }
 int CheckB()
  {
    if(digitalRead(0) == 0)// detect low level signal
     {
        delay(20); // 延时销抖Delay debounce, for machine button 
        if(digitalRead(0) == 0)// 检测到低电平detect low level signal
        { flag= 1;}
   else 
       { flag=-1;}
     return flag;
       }
     
   class WalkLight{  // define sidewalk traffic light
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
     tw=CheckB();//digitalWrite(22, GPIO.HIGH); // all side greenlight lighting
     if(tw=1){
    for(tgside=10;tgside>0;tgside--)
  {
  digitalWrite(1, 1);
  digitalWrite(4, 1);
  digitalWrite(22, 1); //sidewalk green light, else red
    }
     }
     void WNLighting(){
    if(tw=0)
      {
   digitalWrite(1, LOW);// no signal was checked, no light respon
       digitalWrite(4, LOW);
       digitalWrite(22, LOW);
        }
     }
  void Setflag()
     {b.flag=0;}
  private: Button b;
     }
    
  class LogicalMutex{
   public: 
   LogicalMutex(){ car.lock(); m1.lock(); m2.lock(); m3.lock();m4.lock();}//初始化所有类按照定义顺序Initialize all classes in the defined order
   public:
  void YellowLight(CarLightEW*YL)//virtual yellow light, polymorphism黄灯运行，多态
    { 
    YL->CounterY();
    }
 
  void GRLight(CarLightEW*GRL)//virtual green & red light, polymorphism红绿灯运行，多态
     {
     GRL->CounterGR();
     }
     
  int Newtg(SensorES & Ts)// calculate output sensor time, polymorphism 输出的时间进行计算， 多态
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
 }// 以上为四个sensor线程需要的全部过程：输出时间并计算 output time and calculate for 4 sensor threds
 
void Gettg(CarLightEW*pt, SensorES & Obj1, SensorWN & Obj2)// 作比较, 然后给重新给静态函数tg赋值 输入对象（同一个类的不同对象）make comparison, then assign value to tg
{
  int pt->tg=0;//局部变量 Local variables
  //SensorES tes; SensorWN twn;
  if(Newtg(Obj1)>=Newtg(Obj2))
  { 
    pt->tg=Newtg(Obj1);
  }
  else {pt->tg=Newtg(Obj2);
    }
 }
  public://while (1){}
   void SensorW()
   {
   SW.GetT();
    sensor.lock();
    SW.outputT();
    sensor.unlock();
    Newtg(SW);
    m1.unlock(); //在调用这个类的构造函数时，锁定（锁的成对出现理论）。When calling the constructor of this class, lock
   }
    void SensorE()
     {
     SE.GetT();// 不用再加锁，tg 来控制。use tg to control
     sensor.lock();//共享一个23号口输出；share the output of pin 23
     SE.outputT();
     sensor.unlock();
     Newtg(SE);
     m2.unlock(); 
    void SensorS()
    {   
       SS.GetT();
      sensor1.lock();
      SS.outputT();
      sensor1.unlock();
      Newtg(SS);
      m3.unlock();
     
    void SensorN()
    { 
     SS.GetT();
      sensor1.lock();
       SN.outputT();
     sensor1.unlock();
      Newtg(SN);
     m4.unlock();
    
     void CL()
    {
     GRLight(&CEW);
    YellowLight(&CEW);
     if(WL.CheckB()=1)
      {    
       button.unlock();
     }
     else{  
      WL.WNLighting();
     delay(500);
    car.unlock(); 
       }//只有一个获得了锁。
      car.lock();
      m3.lock();
      m4.lock();
     Gettg(&CEW, SS, SN);
       m3.unlock();
      m4.unlock();
     GRLight(&CSN); 
     YellowLight(&CSN);//少一个carlock，和button lock，构造。
      if(WL.CheckB()=1)
      {    
       button.unlock();
     }
     else{  
      WL.WNLighting();
     delay(500);
    car.unlock(); 
       }//只有一个获得了锁。 
      car.lock();
      m1.lock();
      m2.lock();
    Gettg(&CSN, SE, SW);
     m1.unlock();
      m2.unlock();
      
    void WLAB()
    {
     WL.CheckB();
     button.lock();
       WL. WLighting();
      WL.Setflag();
       button.lock();
        car.unlock();  
      }   
   private:
  CarLightEW CEW;
  CarLightSN CSN;
  SensorES SE, SS; 
  SensorWN SW, SN;
  WalkLight WL;
   std::mutex m1, m2, m3, m4, sensor,sensor1,car;

int main()
{
   if(WiringPiSetup() == -1) //initialize wiringpi store fail or not
 {
  printf("you set up wiringpi failed"); //failed
  return 1;
  LogicalMutex LM;
  std::thread t1(&LogicalMutex::SensorW,std::ref(LM));
   std::thread t2(&LogicalMutex::SensorE,std::ref(LM));
   std::thread t3(&LogicalMutex::SensorS,std::ref(LM));
   std::thread t4(&LogicalMutex::SensorN,std::ref(LM));//第二个参数，保证线程里用的同一个对象
   std::thread t5((&LogicalMutex::WLAB,std::ref(LM));
   std::thread t6((&LogicalMutex::CL,std::ref(LM));
       t1.join();
        t2.join();
       t3.join();
         t4.join();
          t5.join();
          t6.join();
       cout<<"this is a trafficlight system"<<endl;
     return 0；
   }
