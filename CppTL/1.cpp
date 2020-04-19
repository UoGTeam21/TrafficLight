#include<stdio.h>//WiringPi.h 
#include<iostream>
#include<thread>
#include<chrono>// for time delay in c++
//#include<list>
#include<mutex>
#include <string>
#include <vector>
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


#define OUTPUT "out"
#define INPUT  "in"
#define LOW     0
#define PUD_UP	1

#define LWQDBG 1

#if LWQDBG
vector<string> pinNames(100);
void initDbg()
{
	pinNames[redEW] = "redEW";
	pinNames[redSN] = "redSN";
	pinNames[greenEW] = "greenEW";
	pinNames[greenSN] = "greenSN";
	pinNames[yellowEW] = "yellowEW";
	pinNames[yellowSN] = "yellowSN";
	pinNames[sider] = "sider";
	pinNames[sideg] = "sideg";
	pinNames[sensorEW] = "sensorEW";
	pinNames[sensorSN] = "sensorSN";
	pinNames[button] = "button";
}
mutex mux;
void PinMode(int pinNum,string mode)
{
	mux.lock();
	cout << pinNames[pinNum] << " has been set " << mode << " mode" << endl;
	mux.unlock();
}
void digitalWrite(int pinNum, int level)
{
	mux.lock();
	cout << pinNames[pinNum] << string(level ? " high" : " low") << endl;
	mux.unlock();
}
void pullUpDnControl(int pinNum, int level)
{
	mux.lock();
	cout << pinNames[pinNum] << string(level ? "high" : "low") << endl;
	mux.unlock();
}
#endif

class CarLightEW 
{
public:
    static int tg;
    int tgEW;
    int tyEW;
public:
    CarLightEW(int tgEW = 0, int tyEW = 3)
    {
        redEWini();
        greenEWini();
        yellowEWini();
        this->tgEW = tgEW;
        this->tyEW = tyEW;
    }

    void redEWini()
     {
         PinMode(1, OUTPUT);
         digitalWrite(1, LOW);
     }
     void greenEWini()
     {
		 cout << "greenEWini" << endl;
         PinMode(6, OUTPUT);
         digitalWrite(6, LOW);
     }

     void yellowEWini()
     {
         PinMode(2, OUTPUT);
         digitalWrite(2, LOW);
     }

    virtual int CounterGR()
    {
        greenEWini();
        redEWini();
        for (tgEW = tg; tgEW > 0; tgEW--)//EW green, and SN sensortimer star 
        {
            digitalWrite(6, 1);
            digitalWrite(4, 1);
            digitalWrite(5, 1); //EW green, else red
            tg--;
		{
            return tg;
		}
        }

    }
    virtual int CounterY()
    {
         yellowEWini();
         redEWini();
        for (tyEW = 3; tyEW > 0; tyEW--)
        {
            digitalWrite(2, 1);
            digitalWrite(4, 1);
            digitalWrite(5, 1); //EW yellow, else red
            //return tyEW;
        }
         return 0;
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
        redSNini();
        greenSNini();
        yellowSNini();
        this->tgSN = tgSN;
        this->tySN = tySN;
    }
      void redSNini()
     {
		  cout << "redSNini" << endl;
         PinMode(4, OUTPUT);
         digitalWrite(4, LOW);
     }
     void greenSNini()
     {
     cout << "greenSNini" << endl;
         PinMode(26, OUTPUT);
         digitalWrite(26, LOW);
     }
     void yellowSNini()
     {
      cout << "yellowSNini" << endl;
         PinMode(3, OUTPUT);
         digitalWrite(3, LOW);
     }

    virtual int CounterGR()
    {
         redEWini();
         greenSNini();
        for (tgSN = CarLightEW::tg; tgSN > 0; tgSN--)
        {
            digitalWrite(1, 1);
            digitalWrite(26, 1);
            digitalWrite(27, 1); //SN green, else red;
            CarLightEW::tg--;
	    {
            return CarLightEW::tg;
            }
        }
    }

    virtual int CounterY() 
    {
        yellowSNini();
        redEWini();
        for (tySN = 3; tySN > 0; tySN--)
        {
            digitalWrite(1, 1);
            digitalWrite(3, 1);
            digitalWrite(5, 1); //SN yellow, else red
        }
        return 0;
    }
};


class SensorES {
public:
    SensorES()
    {
        t0 = 0;
        t = 0;
        PinMode(23, OUTPUT);
    }// pinmode (int pin, int mode), computer control it by 23

    void GetT()
    {
        t0 = CarLightEW::tg;
        do
        {
            t = t + 0.01;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));  //sleep(0.01)=10ms
        } while (digitalRead((27) == 1 && t0 > 0);// has input signals been blocked
    }
    virtual int outputT()
    {
        digitalWrite(23, 1);    //operate timer; digitalwrite(int pin, int value)// if value != 0 == high)
        return t;
        t = 0;
    }
private:
    double t;
public:
    int t0;
};

class SensorWN : public SensorES
{
private:
    double t2;

public:
    int t1;
    SensorWN()
    {
        t1 = 0;
        t2 = 0;
       PinMode(23, OUTPUT);
    }// pinmode (int pin, int mode), computer control it by 23

    void GetT()
    {
        t1 = CarLightEW::tg;
        do {
            t2 = t2 + 0.01;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));//delay(10);  //sleep(0.01)=10ms
        } while (digitalRead((5) == 1 && t1 > 0);// has input signals
    }
    virtual int outputT()
    {
        digitalWrite(23, 1);    //operate timer; digitalwrite(int pin, int value)// if value != 0 == high)
        return t2;
       t2 = 0;
    }
};

class Button
{
    friend class WalkLight;
public:
    int flag;
public:
    Button()
    {
        flag = 0;
        PinMode(0, INPUT); 
       pullUpDnControl(0, PUD_UP);
    }
    int CheckB()
    {
        if (digitalRead(0) == 0)
        {
            delay(20); 
            if (digitalRead(0) == 0)
           {
               flag = 1;
           }
           else
           {
                flag = -1;
            }
           return flag;
    }
};

class WalkLight
{
private:
    Button b;
    int tgside;
    int tw;
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
        if (tw == 1) {
            for (tgside = 10; tgside > 0; tgside--)
            {
                digitalWrite(1, 1);
                digitalWrite(4, 1);
                digitalWrite(22, 1); //side green, else red
            }
        }
    }
    void WNLighting() {
        tw = CheckB();
        if (tw == 0)
        {
            digitalWrite(1, LOW);// no signal was checked, no light respon
            digitalWrite(4, LOW);
            digitalWrite(22, LOW);
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
    Button B;
    CarLightEW CEW;
    CarLightSN CSN;
    SensorES SE, SS;
    SensorWN SW, SN;
    WalkLight WLSN, WLEW;
    std::mutex m1, m2, m3, m4, sensor, sensor1, button2, button1,car, car1;
public:
    LogicalMutex()
    {
        m1.lock(); m2.lock(); m3.lock();  m4.lock(); 
       button2.lock(); button1.lock();
    }
    
public:
    int  YellowLight(CarLightEW* YL)
    {
        return YL->CounterY();
    }

    int GRLight(CarLightEW* GRL)
    {
         return GRL->CounterGR();
    }

    int Newtg(SensorES& Ts)
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
    }

    void Gettg(CarLightEW* pt, SensorES& Obj1, SensorWN& Obj2)
        pt->tg = 0;
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
            if (GRLight(&CEW) == 5)
            {
                m1.lock();
                SW.GetT();
                while (SW.t1 > 0);
                sensor.lock();
                SW.outputT();
                sensor.unlock();
                Newtg(SW);
                m1.unlock(); 
            }
        }
    }

    void SensorE()
    {
        for (;;) {
            if (GRLight(&CEW) == 5)
            {
                m2.lock();
                SE.GetT();
                while (SE.t0 > 0);
                sensor.lock();
                SE.outputT();
                sensor.unlock();
                Newtg(SE);
                m2.unlock();
            }
        }
    }

    void SensorS()
    {
        for (;;) {
            if (GRLight(&CSN) == 5)
            {
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
    }

    void SensorN()
    {
        for (;;) 
        {
            if (GRLight(&CSN) == 5)
            {
            m4.lock();
            SN.GetT();
            while (SN.t1 > 0);
            sensor1.lock();
            SN.outputT();
            sensor1.unlock();
            Newtg(SN);
            m4.unlock();
            }
        }
    }
    //LogicalMutex(){ m1.lock(); m2.lock(); m3.lock();m4.lock();button.lock();button1.lock();}
    void CL()
    {
#ifdef LWQDBG
		initDbg();
#endif
        for (;;) 
        {
            
            GRLight(&CEW);//GRLight(&CEW)
            YellowLight(&CEW);
          
                if (WLEW.CheckB() == -1 && YellowLight(&CEW) == 0) //
                {
                    button1.lock();
                    WLEW.WNLighting();
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));//delay(500);
                    button1.unlock();
                }
                m3.lock();
                m4.lock();
                Gettg(&CEW, SS, SN);
                m3.unlock();
                m4.unlock();
                while (B.flag == 1);
                GRLight(&CSN);
               
                YellowLight(&CSN);//灏戜竴涓猚arlock锛屽拰button lock锛屾瀯閫犮€?
               
                if (WLSN.CheckB() == -1&& YellowLight(&CSN) == 0)//else// car.lock();
                {

                    button2.lock();
                    WLSN.WNLighting();
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));// make thread sleep for 500 ms(can both add in void /main after thread.銆?
                    button2.unlock();//car1.unlock();//瀵瑰簲鐨? car1.lock() 鍦ㄦ瀯閫犲嚱鏁颁腑锛?
                }
                m1.lock();
                m2.lock();
                Gettg(&CSN, SE, SW);
                m1.unlock();
                m2.unlock();
                while (B.flag == 1);
        }
    }

    void WLABEW()
    {
        for (;;) 
        {
             WLEW.CheckB();
            if (WLEW.CheckB() == 1 && YellowLight(&CEW) == 0)
            {
                button2.lock();
                WLEW.WLighting();
                WLEW.Setflag();
                button2.unlock();
            }
        }
    }

    void WLABSN() 
    {
        for (;;) {
             WLSN.CheckB();
            if (WLSN.CheckB() == 1 && YellowLight(&CSN) == 0)
            {
                button1.lock();
                WLSN.WLighting();
                WLSN.Setflag();
                button1.unlock();               
            }
        }
    }
};


int main()
{
    LogicalMutex LM;
    std::thread t7(&LogicalMutex::CL, std::ref(LM));  
    std::thread t1(&LogicalMutex::SensorW, std::ref(LM));
    std::thread t2(&LogicalMutex::SensorE, std::ref(LM));
    std::thread t3(&LogicalMutex::SensorS, std::ref(LM));
    std::thread t4(&LogicalMutex::SensorN, std::ref(LM));
    std::thread t5(&LogicalMutex::WLABSN, std::ref(LM));
    std::thread t6(&LogicalMutex::WLABEW, std::ref(LM));
    
     t7.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    
    cout << "this is a trafficlight system" << endl;
    return 0;
}
