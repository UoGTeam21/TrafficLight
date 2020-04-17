  class LogicalMutex{
   public: 
   LogicalMutex(){car.lock();car1.lock();button.lock();button1.lock();}
   //初始化所有类按照定义顺序
   public:
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
  public:
   void SensorW()
   {
     for(;;){
      m1.lock();
    SW.GetT();
    sensor.lock();
    SW.outputT();
    sensor.unlock();
    Newtg(SW);
    m1.unlock(); //在调用这个类的构造函数时，锁定（锁的成对出现理论）。
   }}
   
    void SensorE()
     { 
     for(;;){
      m2.lock();
     SE.GetT();// 不用再加锁，tg 来控制。
     sensor.lock();//共享一个23号口输出；
     SE.outputT();
     sensor.unlock();
     Newtg(SE);
     m2.unlock();
     }}
   
    void SensorS()
    {  
       for(;;){
        m3.lock();
       SS.GetT();
      sensor1.lock();
      SS.outputT();
      sensor1.unlock();
      Newtg(SS);
      m3.unlock();
     }}
    
    void SensorN()
    {   
     for(;;){
        m4.lock();
     SS.GetT();
      sensor1.lock();
       SN.outputT();
     sensor1.unlock();
      Newtg(SN);
     m4.unlock();
     }}
    //LogicalMutex(){car.lock();car1.lock(); m1.lock(); m2.lock(); m3.lock();m4.lock();button.lock();button1.lock();} 
   //构造函数中只锁了一次，利用程序体循环锁（＋各函数for(;;)做循环）sensor的锁无论是谁先用23进行输出无所谓，所以不许放在构造函数中。。
   //除去构造函数中，程序“体”中的锁成对出现。
     void CL()
    {
     for(;;){
     GRLight(&CEW);  
     YellowLight(&CEW); 
     if(YellowLight(&CEW)>5)
      {m3.unlock();
      m4.unlock();}
     if(WL.CheckB()=1&&YellowLight(&CEW)=0)
      {    
       button.unlock();
     }
     else{  
      WL.WNLighting();
     td::this_thread::sleep_for(std::chrono::milliseconds(500));//delay(500);
    car.unlock(); //对应的  car.lock() 在构造函数中；
       }//只有一个获得了锁。
      car.lock();
      m3.lock();
      m4.lock();
     Gettg(&CEW, SS, SN);
       //m3.unlock();
      //m4.unlock();
     GRLight(&CSN); 
     YellowLight(&CSN);//少一个carlock，和button lock，构造。
      if(YellowLight(&CSN)>5)
      {m1.unlock();
      m2.unlock();}
       if(WL.CheckB()=1&&YellowLight(&CSN)=0)
      {    
       button1.unlock();
     }
     else{  
      WL.WNLighting();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));// make thread sleep for 500 ms(can both add in void /main after thread.。
    car1.unlock();//对应的  car1.lock() 在构造函数中；
       }//只有一个获得了锁。 
      car1.lock();
      m1.lock();
      m2.lock();
    Gettg(&CSN, SE, SW);
     //m1.unlock();
      //m2.unlock();
      }}
    void WLABEW()//EW方向
    {  
     for(;;){
     WL.CheckB();
     button.lock();
       WL. WLighting();
      WL.Setflag();
      car.unlock(); //if and else 注意 
       //button.lock();
        } }
      
    void WLABSN() //SN方向
     {
         for(;;){
     WL.CheckB();
     button1.lock();
       WL. WLighting();
      WL.Setflag();
       //button1.lock();
        car1.unlock();  //if and else 注意
      }}
   
   private:
  CarLightEW CEW;
  CarLightSN CSN;
  SensorES SE, SS; 
  SensorWN SW, SN;
  WalkLight WLSN, WLEW;
   std::mutex m1, m2, m3, m4, sensor,sensor1,car,car1,button,button1;

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
   std::thread t5((&LogicalMutex::WLABSN,std::ref(LM));
   std::thread t6((&LogicalMutex::WLABEW,std::ref(LM));
   std::thread t7((&LogicalMutex::CL,std::ref(LM));
       t1.join();
        t2.join();
       t3.join();
         t4.join();
          t5.join();
          t6.join();
          t7.join();  
       cout<<"this is a trafficlight system"<<endl;
     return 0；
   }
