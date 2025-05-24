

#include <bits/stdc++.h>

using namespace std;


class MotherBoard{

    public:
     bool checkMotherBoardonBoot(){
        cout<<" MotherBoard status on "<<endl;

        return true;
     }
};


class RAM{

    public:
     bool checkRAMonBoot(){
        cout<<" RAM status on "<<endl;

        return true;
     }
};

class OSCheck{

    public:
     bool checkOSonBoot(){
        cout<<" OS status on "<<endl;

        return true;
     }
};

class HardwareChecks{
    MotherBoard* motherBoard;
    RAM* ram;
    public:
     HardwareChecks()
     {
        this->motherBoard=new MotherBoard();
        this->ram=new RAM();
     }

     bool checkAllHardware()
     {
        return (motherBoard->checkMotherBoardonBoot() && ram->checkRAMonBoot());
     }
};


class DriverCheck{

    public:
     bool DriverCheckonBoot(){
        cout<<" Driver status on "<<endl;

        return true;
     }
};


class SoftwareChecks{
    DriverCheck* driverCheck;
    OSCheck* osCheck;
    public:
     SoftwareChecks()
     {
        this->driverCheck=new DriverCheck;
        this->osCheck=new OSCheck;
     }

     bool checkAllSoftware()
     {
        return (driverCheck->DriverCheckonBoot() && osCheck->checkOSonBoot());
     }


};

class LaptopOnSwitch{
    SoftwareChecks* softwareChecks;
    HardwareChecks* hardwareChecks;
    public:
     LaptopOnSwitch()
     {
        this->softwareChecks=new SoftwareChecks;
        this->hardwareChecks=new HardwareChecks;
     }

     void switchLaptopOn()
     {
         if(softwareChecks->checkAllSoftware() && hardwareChecks->checkAllHardware())
          cout<<" Laptop is opening "<<endl;
         else{
            cout<<" Error opening Laptop"<<endl;
         }
     }


};





int main()
{
    LaptopOnSwitch* pc=new LaptopOnSwitch();
    pc->switchLaptopOn();
   return 0;
}