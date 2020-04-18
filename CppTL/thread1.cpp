//#include<WiringPi.h>
WiringPi.h>
#include<stdio.h>
#include<iostream>
#include<thread>
#include<chrono>// for time delay in c++
//#include<list>
#include<mutex>
using namespace std;


#include <type_traits>
#ifndef _THREAD_
#define _THREAD_
#endif

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
   public:
       static int tg;
    int tgEW;
    int tyEW;
    //friend void Gettg(CarLightEW*, SensorES&, SensorWN&);// The subfunction do not need friend, tg is static
  public:
    CarLightEW(int tgEW = 0, int tyEW = 3) //main traffic light follow the cycle of red-green-yellow
    {
        /*redEWini();
        greenEWini();
        yellowEWini();*/
        this->tgEW = tgEW;
        this->tyEW = tyEW;
    }

    /* void redEWini() 
     {
         PinMode(1, OUTPUT);
         digitalWrite(1, LOW); // initialize East-West side red light 
     }
     void greenEWini()  
     {
         PinMode(6, OUTPUT);
         digitalWrite(6, LOW); // initialize East-West side green light
     }

     void yellowEWini()   
     {
         PinMode(2, OUTPUT);
         digitalWrite(2, LOW); // initialize East-West side yellow light
     }*/

    virtual int CounterGR()// turn on East-West side green light  EW绿灯亮 
    {
        //greenEWini();
       // redSNini();
        //SNsensorini();变量调用构造函数初始化 initialize variable construction function
        for (tgEW = tg; tgEW > 0; tgEW--)//East-West side turn to green light, and South-North side sensortimer start to work 
        {
            /*digitalWrite(6, 1);
            digitalWrite(4, 1);
            digitalWrite(5, 1); //East-West side green light, else sides red light
            tg--;
            return tg;
            //if(CarLightEW::tg<=5 && tg>0)// counterv t can not exceed 1 minutes?
              //{ obj.InputT();}// 五秒倒计时开始传+ //sensortimer();
        }

    }
    virtual void CounterY()
    {
        // yellowEWini();   //turn on the yellow light
         //redSNini();
        for (tyEW = 3; tyEW > 0; tyEW--)
        {
            ;  //digitalWrite(2, 1);
             //digitalWrite(4, 1);
            //digitalWrite(5, 1); //East-West side yellow light, else red
           
        }

    }
};
        int CarLightEW::tg = 10;//tg initialize.


        class CarLightSN : public CarLightEW
        {
        public:
            int tgSN;
            int tySN;
            CarLightSN(int tgEW = 0, int tyEW = 3, int tySN = 3, int tgSN = 0) : CarLightEW(tgEW, tyEW)
            {
                //redSNini();
               // greenSNini();
                //yellowSNini();       //enter the South-North side main traffic light cycle,same as before
                this->tgSN = tgSN;
                this->tySN = tySN;
            }
            /* void redSNini()   // initialize South-North side red light
             {
                 PinMode(4, OUTPUT);
                 digitalWrite(4, LOW);
             }
             void greenSNini()  // initialize South-North side green light
             {
                 PinMode(26, OUTPUT);
                 digitalWrite(26, LOW);
             }
             void yellowSNini()  // initialize South-North side yellow light
             {
                 PinMode(3, OUTPUT);
                 digitalWrite(3, LOW);
             }*/

            virtual int CounterGR()// turn on South-North side green light SN绿灯亮
            {
                // redEWini();
                 //greenSNini();
                 //EWsesorini(); // South-North side green light, and East-West side sensortimer start to work 
                for (tgEW = CarLightEW::tg; tgSN > 0; tgSN--)
                {
                    /*digitalWrite(1, 1);
                    digitalWrite(26, 1);
                    digitalWrite(27, 1); //South-North side green light, else red;*/
                    CarLightEW::tg--;
                    return CarLightEW::tg;
                    //if(CarLightEW::tg<=5 && tg>0)// counterv t can not exceed 1 minutes?
                        //{ obj.InputT();}// 五秒倒计时开始传 5 seconds countdown
                }
            }

            virtual void CounterY()  // turn on the yellow light黄灯亮
            {
                //yelloeSNini();
                //redEWini();
                for (tySN = 3; tySN > 0; tySN--)
                {
                    //digitalWrite(1, 1);
                    ; //digitalWrite(3, 1);
                    //digitalWrite(5, 1);  // South-North side yellow light, else red
                   
                }

            }
        };


        class SensorES {
          public:
            SensorES()
            {
                t0 = 0;
                t = 0;//initialization
                //PinMode(23, OUTPUT);
            }// pinmode (int pin, int mode), computer control it by 23
            void Input()
            {
                t0 = CarLightEW::tg;// ？！ 此处应该有锁！ set a lock
            }
            void GetT()
            {
                do 
                {
                    t = t + 0.01;
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));  //sleep(0.01)=10ms
                } while (/*digitalRead((27) == 1 &&*/ t0 > 0);// has input signals been blocked
            }
            virtual int outputT()
            {
                //digitalWrite(23, 1);    //operate timer; digitalwrite(int pin, int value)// if value != 0 == high)
                return t;
            }
          private:
            int t;
        public:
            int t0;
        };

        class SensorWN : public SensorES
        {
         private:
            int t2;
           
           public:
               int t1;
            SensorWN()
            {
                t1 = 0;
                t2 = 0;//初始化initialization
               // PinMode(23, OUTPUT);
            }// pinmode (int pin, int mode), computer control it by 23
            void GetT()
            {
                t1 = CarLightEW::tg;
                do {
                    t2 = t2 + 0.01;
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));//delay(10);  //sleep(0.01)=10ms
                } while (/*digitalRead((5) == 1 && */t1 > 0);// has input signals
            }
            virtual int outputT()
            {
                //digitalWrite(23, 1);    //operate timer; digitalwrite(int pin, int value)// if value != 0 == high)
                return t2;
            }
        };

        class Button
        {
            friend class WalkLight;
              private:
                int flag;
                public:
            Button() 
            {//构造函数constructor
                flag = 0;
                //pinMode(0, INPUT); //引脚0为BUTTON输入模式 set pin 0 to input mode
               // pullUpDnControl(0, PUD_UP); //set pin 0 to pull up, so pin 0 defaults to high level设置0号引脚上拉,(设置成上拉输入，引脚上就加了一个上拉电阻，那么引脚就默认是高电平，当再去读取这个引脚的时候，
            }
            int CheckB()
            {
                // if (digitalRead(0) == 0)// 检测到低电平 detect low level signal
                {
                    //delay(20); // 延时销抖delay debounce, for machine button 
                    //if (digitalRead(0) == 0)// 检测到低电平detect low level signal
                    {
                        flag = 1;
                    }
                    //else
                    {
                        flag = -1;
                    }
                    return flag;
                }

            }
            
        };

            class WalkLight
            {
            private:
                Button b;
                int tgside;
                int tw;                        // define sidewalk traffic light
            public:
                WalkLight(int tgside = 10, int tw = 0) :b()
                {
                    this->tgside = tgside;
                    this->tw = tw;
                }
                int CheckB()
                {
                    b.CheckB();
                    return b.flag;
                }
                void WLighting()
                {
                    tw = CheckB();//digitalWrite(18, GPIO.HIGH); // all side greenlight lighting
                    if (tw = 1) {
                        for (tgside = 10; tgside > 0; tgside--)
                        {
                            /*digitalWrite(1, 1);
                            digitalWrite(4, 1);
                            digitalWrite(22, 1); //sidewalk green light, else red*/
                        }
                    }
                }
                void WNLighting() {
                    tw = CheckB();
                    if (tw = 0)
                    {
                        /*digitalWrite(1, LOW);// no signal was checked, no light respon
                        digitalWrite(4, LOW);
                        digitalWrite(22, LOW);*/
                    }
                }

                void Setflag()
                {
                    b.flag = 0;
                }
            };


            class LogicalMutex
            {
            private:
                CarLightEW CEW;
                CarLightSN CSN;
                SensorES SE, SS;
                SensorWN SW, SN;
                WalkLight WLSN, WLEW;
                std::mutex m1, m2, m3, m4, sensor, sensor1, car, car1, button2, button1;  
            public:
                LogicalMutex()
                {
                    car.lock(); car1.lock(); button2.lock(); button1.lock();     //Initialize all classes in the defined order
                }
                //初始化所有类按照定义顺序
            public:
                int  YellowLight(CarLightEW* YL)//virtual yellow light work, polymorphism黄灯运行，多态
                {
                    YL->CounterY();
                }

                int GRLight(CarLightEW* GRL)//virtual green & red light work, polymorphism红绿灯灯运行，多态
                {
                    GRL->CounterGR();
                }

                int Newtg(SensorES& Ts)//calculate output sensor time, polymorphism  输出的时间进行计算virtual， 多态
                {
                    if (Ts.outputT() < 1)
                    {
                        return 10;//Tc.Gettg()= Tc.Gettg();// 3 chooses
                    }
                    else if (Ts.outputT() >= 1 && Ts.outputT() <= 2)
                    {
                        return 15;//Tc.Gettg()+=5; 
                    }
                    else if (Ts.outputT() >= 2)
                    {
                        return 20;//Tc.Gettg()+=10;
                    }
                }// 以上为四个sensor线程需要的全部过程：输出时间并计算output time and calculate for 4 sensor threds

                void Gettg(CarLightEW* pt, SensorES& Obj1, SensorWN& Obj2)// make comparison, then assign value to tg 作比较, 然后给重新给静态函数tg赋值 输入对象（同一个类的不同对象）
                {
                    pt->tg = 0;//局部变量 Local variables
                  //SensorES tes; SensorWN twn;
                    if (Newtg(Obj1) >= Newtg(Obj2))
                    {
                        pt->tg = Newtg(Obj1);
                    }
                    else {
                        pt->tg = Newtg(Obj2);
                    }
                }
            public:
                void SensorW()
                {
                    for (;;) {
                        m1.lock();
                        SW.GetT();
                        while(SW.t1> 0);
                        sensor.lock();
                        SW.outputT();
                        sensor.unlock();
                        Newtg(SW);
                        m1.unlock(); //When calling the constructor of this class, lock it在调用这个类的构造函数时，锁定（锁的成对出现理论）。
                    }
                }

                void SensorE()
                {
                    for (;;) {
                        m2.lock();
                        SE.GetT();// 不用再加锁，tg 来控制。use tg to control
                        while(SE.t0> 0);
                        sensor.lock();//共享一个23号口输出；share the output of pin 23
                        SE.outputT();
                        sensor.unlock();
                        Newtg(SE);
                        m2.unlock();
                    }
                }

                void SensorS()
                {
                    for (;;) {
                        m3.lock();
                        SS.GetT();
                        while (SS.t0 > 0);
                        sensor1.lock();
                        SS.outputT();
                        sensor1.unlock();
                        Newtg(SS);
                        m3.unlock();
                    }
                }

                void SensorN()
                {
                    for (;;) {
                        m4.lock();
                        SN.GetT();
                        while(SN.t1 > 0);
                        sensor1.lock();
                        SN.outputT();
                        sensor1.unlock();
                        Newtg(SN);
                        m4.unlock();
                    }
                }
                //LogicalMutex(){car.lock();car1.lock(); m1.lock(); m2.lock(); m3.lock();m4.lock();button.lock();button1.lock();} 
               //构造函数中只锁了一次，利用程序体循环锁（＋各函数for(;;)做循环）sensor的锁无论是谁先用23进行输出无所谓，所以不许放在构造函数中。。
               //除去构造函数中，程序“体”中的锁成对出现。
                void CL()
                {
                    for (;;) {
                        GRLight(&CEW);
                        YellowLight(&CEW);
                        if (GRLight(&CEW) > 5)
                        {
                            m3.unlock();
                            m4.unlock();
                        }
                        if (WLEW.CheckB() == 1 && YellowLight(&CEW) == 0)
                        {
                            button2.unlock();
                        }
                        else if (WLEW.CheckB() == -1 && YellowLight(&CEW) == 0) {
                            WLEW.WNLighting();
                           std::this_thread::sleep_for(std::chrono::milliseconds(500));//delay(500);
                            car.unlock(); //对应的  car.lock() 在构造函数中；
                        }//只有一个获得了锁。
                        car.lock();
                        m3.lock();
                        m4.lock();
                        Gettg(&CEW, SS, SN);
                        //m3.unlock();
                       //m4.unlock();
                        GRLight(&CSN);
                        if (GRLight(&CSN) > 5)
                        {
                            m1.unlock();
                            m2.unlock();
                        }
                        YellowLight(&CSN);//少一个carlock，和button lock，构造。
                        if (WLSN.CheckB() == 1)
                        {
                            button1.unlock();
                        }
                        else if (WLSN.CheckB() == -1) 
                        {
                            WLSN.WNLighting();
                            std::this_thread::sleep_for(std::chrono::milliseconds(500));// make thread sleep for 500 ms(can both add in void /main after thread.。
                            car1.unlock();//对应的  car1.lock() 在构造函数中；
                        }//只有一个获得了锁。 
                        car1.lock();
                        m1.lock();
                        m2.lock();
                        Gettg(&CSN, SE, SW);
                        //m1.unlock();
                         //m2.unlock();
                    }
                }

                void WLABEW()//EW方向
                {
                    for (;;) {
                        WLEW.CheckB();
                        button2.lock();
                        WLEW.WLighting();
                        WLEW.Setflag();
                        car.unlock(); //if and else 注意 
                         //button.lock();
                    }
                }

                void WLABSN() //South-North side
                {
                    for (;;) {
                        WLSN.CheckB();
                        button1.lock();
                        WLSN.WLighting();
                        WLSN.Setflag();
                        //button1.lock();
                        car1.unlock();  //if and else 注意
                    }
                }
            };


            int main()
            {
                /*if (WiringPiSetup() == -1) //initialize wiringpi store fail or not
                {
                    printf("you set up wiringpi failed"); //failed
                    return 1;
                }*/
                LogicalMutex LM;
                std::thread t1(&LogicalMutex::SensorW, std::ref(LM));
                std::thread t2(&LogicalMutex::SensorE, std::ref(LM));
                std::thread t3(&LogicalMutex::SensorS, std::ref(LM));
                std::thread t4(&LogicalMutex::SensorN, std::ref(LM));//第二个参数，保证线程里用的同一个对象
                std::thread t5((&LogicalMutex::WLABSN, std::ref(LM)));
                std::thread t6((&LogicalMutex::WLABEW, std::ref(LM)));
                std::thread t7((&LogicalMutex::CL, std::ref(LM)));
                t1.join();
                t2.join();
                t3.join();
                t4.join();
                t5.join();
                t6.join();
                t7.join();
                cout << "this is a trafficlight system" << endl;
                return 0;
            }
