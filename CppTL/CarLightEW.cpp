
    CarLightEW(int tgEW = 0, int tyEW = 3)
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
         digitalWrite(1, LOW);
     }
     void greenEWini()
     {
         PinMode(6, OUTPUT);
         digitalWrite(6, LOW);
     }
     void yellowEWini()
     {
         PinMode(2, OUTPUT);
         digitalWrite(2, LOW);
     }*/

    virtual int CounterGR()// EW绿灯亮 
    {
        //greenEWini();
       // redSNini();
        //SNsensorini();变量调用构造函数初始化
        for (tgEW = tg; tgEW > 0; tgEW--)//EW green, and SN sensortimer star 
        {
            /*digitalWrite(6, 1);
            digitalWrite(4, 1);
            digitalWrite(5, 1); //EW green, else red*/
            tg--;
            return tg;
            //if(CarLightEW::tg<=5 && tg>0)// counterv t can not exceed 1 minutes?
              //{ obj.InputT();}// 五秒倒计时开始传+ //sensortimer();
        }

    }
    virtual void CounterY()
    {
        // yellowEWini();
         //redSNini();
        for (tyEW = 3; tyEW > 0; tyEW--)
        {
            ;  //digitalWrite(2, 1);
             //digitalWrite(4, 1);
            //digitalWrite(5, 1); //EW yellow, else red
           
        }

    }
};
        int CarLightEW::tg = 10;//tg initialize.
