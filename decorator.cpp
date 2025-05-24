#include <bits/stdc++.h>
using namespace std;



class Beverage{
  public:
  string BeverageName="";
  virtual string getBeverageName(){
    return BeverageName;
  }
  
  virtual int getBeveragePrice()=0;
  
};

class Expresso : public Beverage{
  
  public:
   Expresso()
   {
     BeverageName="Expresso";
   }
   
   int getBeveragePrice() override{
     return 10;
   }
};

class Cappuccino : public Beverage{
  
  public:
   Cappuccino()
   {
     BeverageName="Cappuccino";
   }
   
   int getBeveragePrice() override{
     return 11;
   }
};

class Ingredient:public Beverage{

};


class Milk : public Ingredient{
  public:
  Beverage* beverage;
  Milk(Beverage* beverage)
  {
    this->beverage=beverage;
  }
  
  string getBeverageName() override{
    return beverage->getBeverageName()+" With Milk";
  }
  
  int getBeveragePrice() override{
    return beverage->getBeveragePrice()+2;
  }
};

class Caramel : public Ingredient{
  public:
  Beverage* beverage;
  Caramel(Beverage* beverage)
  {
    this->beverage=beverage;
  }
  
  string getBeverageName() override{
    return beverage->getBeverageName()+" With Caramel";
  }
  
  int getBeveragePrice() override{
    return beverage->getBeveragePrice()+3;
  }
};






int main() 
{
    
    Beverage* beverage=new Expresso();
    cout<<"Beverage Name:"<<beverage->getBeverageName()<<endl;
    cout<<"Beverage Price:"<<beverage->getBeveragePrice()<<endl;
    beverage=new Milk(beverage);
    cout<<"Beverage Name:"<<beverage->getBeverageName()<<endl;
    cout<<"Beverage Price:"<<beverage->getBeveragePrice()<<endl;
    beverage=new Caramel(beverage);
    cout<<"Beverage Name:"<<beverage->getBeverageName()<<endl;
    cout<<"Beverage Price:"<<beverage->getBeveragePrice()<<endl;
    
    Beverage* beverage2=new Cappuccino();
    cout<<"Beverage Name:"<<beverage2->getBeverageName()<<endl;
    cout<<"Beverage Price:"<<beverage2->getBeveragePrice()<<endl;
    beverage2=new Milk(beverage2);
    cout<<"Beverage Name:"<<beverage2->getBeverageName()<<endl;
    cout<<"Beverage Price:"<<beverage2->getBeveragePrice()<<endl;
    beverage=new Caramel(beverage2);
    cout<<"Beverage Name:"<<beverage2->getBeverageName()<<endl;
    cout<<"Beverage Price:"<<beverage2->getBeveragePrice()<<endl;
    
    
    return 0;
}