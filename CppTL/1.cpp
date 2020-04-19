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
#define LOW		0
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

class CarLightEW // 杞﹁閬撶孩缁跨伅
{
public:
    static int tg;
    int tgEW;
    int tyEW;
    //friend void Gettg(CarLightEW*, SensorES&, SensorWN&);// 浠栫殑瀛愬嚱鏁颁笉鍐嶉渶瑕佹湁鍙嬪厓锛屽洜涓簍g涓洪潤鎬侊紝 鏀瑰彉杩欎釜灞炴€э紝 鎵€鏈変竴璧峰彉銆?
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

    virtual int CounterGR()// EW缁跨伅浜?
    {
        greenEWini();
        redEWini();
        //SNsensorini();//鍙橀噺璋冪敤鏋勯€犲嚱鏁板垵濮嬪寲
        for (tgEW = tg; tgEW > 0; tgEW--)//EW green, and SN sensortimer star 
        {
            digitalWrite(6, 1);
            digitalWrite(4, 1);
            digitalWrite(5, 1); //EW green, else red
            tg--;
            return tg;
            //if(CarLightEW::tg<=5 && tg>0)// counterv t can not exceed 1 minutes?
              //{ obj.InputT();}// 浜旂鍊掕鏃跺紑濮嬩紶+ //sensortimer();
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

    virtual int CounterGR()// SN缁跨伅浜?
    {
        // redEWini();
         //greenSNini();
         //EWsesorini(); // SN green, and EW sensortimer star 
        for (tgSN = CarLightEW::tg; tgSN > 0; tgSN--)
        {
            digitalWrite(1, 1);
            digitalWrite(26, 1);
            digitalWrite(27, 1); //SN green, else red;
            CarLightEW::tg--;
            return CarLightEW::tg;
            //if(CarLightEW::tg<=5 && tg>0)// counterv t can not exceed 1 minutes?
                //{ obj.InputT();}// 浜旂鍊掕鏃跺紑濮嬩紶
        }
    }

    virtual int CounterY() //榛勭伅浜?
    {
        yellowSNini();
        redEWini();
        for (tySN = 3; tySN > 0; tySN--)
        {
            digitalWrite(1, 1);
            digitalWrite(3, 1);
            digitalWrite(5, 1); //SN yellow, else red
             //return tySN; //return 涔嬪悗鍑芥暟缁撴潫
        }
      return 0;
    }
};


class SensorES {
public:
    SensorES()
    {
        t0 = 0;
        t = 0;//鍒濆鍖?
        PinMode(23, OUTPUT);
    }// pinmode (int pin, int mode), computer control it by 23

    void GetT()
    {
        t0 = CarLightEW::tg;
        do
        {
            t = t + 0.01;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));  //sleep(0.01)=10ms
        } while (/*digitalRead((27) == 1 &&*/ t0 > 0);// has input signals been blocked
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
        t2 = 0;//鍒濆鍖?
       PinMode(23, OUTPUT);
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
    {//鏋勯€犲嚱鏁?
        flag = 0;
        PinMode(0, INPUT); //寮曡剼0涓築UTTON杈撳叆妯″紡
       pullUpDnControl(0, PUD_UP); //璁剧疆0鍙峰紩鑴氫笂鎷?(璁剧疆鎴愪笂鎷夎緭鍏ワ紝寮曡剼涓婂氨鍔犱簡涓€涓笂鎷夌數闃伙紝閭ｄ箞寮曡剼灏遍粯璁ゆ槸楂樼數骞筹紝褰撳啀鍘昏鍙栬繖涓紩鑴氱殑鏃跺€欙紝
    }
    int CheckB()
    {
        //if (digitalRead(0) == 0)// 妫€娴嬪埌浣庣數骞?
        //{
        //    delay(20); // 寤舵椂閿€鎶? for machine button 
        //    if (digitalRead(0) == 0)// 妫€娴嬪埌浣庣數骞?
        //    {
        //        flag = 1;
        //    }
        //    else
        //    {
        //        flag = -1;
        //    }
        //    return flag;
        //}
		return 0;
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
       //car.lock(); car1.lock(); 
       button2.lock(); button1.lock();
    }
    //鍒濆鍖栨墍鏈夌被鎸夌収瀹氫箟椤哄簭
public:
    int  YellowLight(CarLightEW* YL)//virtual榛勭伅杩愯锛屽鎬?
    {
        return YL->CounterY();
        //0;	//TODO lwq
    }

    int GRLight(CarLightEW* GRL)//virtual绾㈢豢鐏伅杩愯锛屽鎬?
    {
         return GRL->CounterGR();
       // 0;	//TODO lwq
    }

    int Newtg(SensorES& Ts)// sensor 杈撳嚭鐨勬椂闂磋繘琛岃绠梫irtual锛?澶氭€?
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
    }// 浠ヤ笂涓哄洓涓猻ensor绾跨▼闇€瑕佺殑鍏ㄩ儴杩囩▼锛氳緭鍑烘椂闂村苟璁＄畻

    void Gettg(CarLightEW* pt, SensorES& Obj1, SensorWN& Obj2)// 浣滄瘮杈? 鐒跺悗缁欓噸鏂扮粰闈欐€佸嚱鏁皌g璧嬪€?杈撳叆瀵硅薄锛堝悓涓€涓被鐨勪笉鍚屽璞★級
    {
        pt->tg = 0;//灞€閮ㄥ彉閲?
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
                m1.unlock(); //鍦ㄨ皟鐢ㄨ繖涓被鐨勬瀯閫犲嚱鏁版椂锛岄攣瀹氾紙閿佺殑鎴愬鍑虹幇鐞嗚锛夈€?
            }
        }
    }

    void SensorE()
    {
        for (;;) {
            if (GRLight(&CEW) == 5)
            {
                m2.lock();
                SE.GetT();// 涓嶇敤鍐嶅姞閿侊紝tg 鏉ユ帶鍒躲€?
                while (SE.t0 > 0);
                sensor.lock();//鍏变韩涓€涓?3鍙峰彛杈撳嚭锛?
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
            m4.lock();//涓€寮€濮嬪氨閿佷簡锛屾病鏈夎幏寰楄幏寰楅攣銆?
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
    //LogicalMutex(){car.lock();car1.lock(); m1.lock(); m2.lock(); m3.lock();m4.lock();button.lock();button1.lock();} 
   //鏋勯€犲嚱鏁颁腑鍙攣浜嗕竴娆★紝鍒╃敤绋嬪簭浣撳惊鐜攣锛堬紜鍚勫嚱鏁癴or(;;)鍋氬惊鐜級sensor鐨勯攣鏃犺鏄皝鍏堢敤23杩涜杈撳嚭鏃犳墍璋擄紝鎵€浠ヤ笉璁告斁鍦ㄦ瀯閫犲嚱鏁颁腑銆傘€?
   //闄ゅ幓鏋勯€犲嚱鏁颁腑锛岀▼搴忊€滀綋鈥濅腑鐨勯攣鎴愬鍑虹幇銆?
    void CL()
    {
#ifdef LWQDBG
		initDbg();
#endif
        for (;;) 
        {
              //car.lock();
             //car1.lock();
            GRLight(&CEW);//GRLight(&CEW)
            YellowLight(&CEW);
            //if (GRLight(&CEW) == 5)锛屾斁鍒颁簡sensor涔嬩腑銆?
            //{ 
                //m3.unlock();
               // m4.unlock();  
         //  }

            // if (WLEW.CheckB() == 1 && YellowLight(&CEW) == 0)
            //{
                 //car.lock();
                //button2.unlock();
               // WLABEW();
            //}  
                //car.lock();
                if (WLEW.CheckB() == -1 && YellowLight(&CEW) == 0) //
                {
                    button1.lock();
                    WLEW.WNLighting();
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));//delay(500);
                    button1.unlock();
                   // car.unlock(); //瀵瑰簲鐨? car.lock() 鍦ㄦ瀯閫犲嚱鏁颁腑锛?
                }//鍙湁涓€涓幏寰椾簡閿併€?
                //car.lock();
                m3.lock();
                m4.lock();
                Gettg(&CEW, SS, SN);
                m3.unlock();
                m4.unlock();
                while (B.flag == 1);
                GRLight(&CSN);
                //if (GRLight(&CSN) == 5)
                //{
                    // m1.unlock();
                    // m2.unlock();

                //}
                YellowLight(&CSN);//灏戜竴涓猚arlock锛屽拰button lock锛屾瀯閫犮€?
               // if (WLSN.CheckB() == 1)
               // {
                    // WLABSN();
                    //button1.unlock();
                //}
                if (WLSN.CheckB() == -1&& YellowLight(&CSN) == 0)//else// car.lock();
                {

                    button2.lock();
                    WLSN.WNLighting();
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));// make thread sleep for 500 ms(can both add in void /main after thread.銆?
                    button2.unlock();//car1.unlock();//瀵瑰簲鐨? car1.lock() 鍦ㄦ瀯閫犲嚱鏁颁腑锛?
                }//鍙湁涓€涓幏寰椾簡閿併€?
                //car1.lock();
                m1.lock();
                m2.lock();
                Gettg(&CSN, SE, SW);
                m1.unlock();
                m2.unlock();
                while (B.flag == 1);
        }
    }

    void WLABEW()//EW鏂瑰悜
    {
        for (;;) 
        {
             WLEW.CheckB();
            if (WLEW.CheckB() == 1 && YellowLight(&CEW) == 0)
            {
                button2.lock();
                WLEW.WLighting();
                WLEW.Setflag();
                //car.unlock(); //if and else 娉ㄦ剰 
                button2.unlock();
            }
        }
    }

    void WLABSN() //SN鏂瑰悜
    {
        for (;;) {
             WLSN.CheckB();
            if (WLSN.CheckB() == 1 && YellowLight(&CSN) == 0)
            {
                button1.lock();
                WLSN.WLighting();
                WLSN.Setflag();
                button1.unlock();
                //car1.unlock();  //if and else 娉ㄦ剰
            }
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
    std::thread t7(&LogicalMutex::CL, std::ref(LM));  
    std::thread t1(&LogicalMutex::SensorW, std::ref(LM));
    std::thread t2(&LogicalMutex::SensorE, std::ref(LM));
    std::thread t3(&LogicalMutex::SensorS, std::ref(LM));
    std::thread t4(&LogicalMutex::SensorN, std::ref(LM));//绗簩涓弬鏁帮紝淇濊瘉绾跨▼閲岀敤鐨勫悓涓€涓璞?
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
