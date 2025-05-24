// Online C++ compiler to run C++ program online
#include <iostream>
#include <bits/stdc++.h>
#include<random>

using namespace std;


enum Direction{
    UP,
    DOWN,
    NONE
};



class Elevator{
   int ElevatorId;
   int currentFloor;
   Direction currentDir;
   set<int> targets;// target floors
   
   public:
    Elevator(int id):ElevatorId(id),currentFloor(0),currentDir(NONE){}

  void addRequest(int floor)
  { 
      targets.insert(floor);
      updateDirection();
  }
  
  
  void updateDirection()
  {
      if(targets.empty())
      {
          currentDir=NONE;
          return;
      }
      
      if(*targets.begin()>currentFloor)
       currentDir=UP;
      else
       currentDir=DOWN;
  }
  void move()
  {
      if(currentDir==UP) 
      {
          currentFloor++;
          
      }
      
      else if(currentDir==DOWN)
      {
          currentFloor--;

      }
      
      cout<<"Elevator "<<ElevatorId<< "is at Floor"<<currentFloor<<"\n";
      
      if(targets.find(currentFloor)!=targets.end())
      {   
          cout<<"Elevator "<<ElevatorId<<" stopping at Floor "<<currentFloor<<"\n";
          targets.erase(currentFloor);
      }
      
      updateDirection();
  }
  
  bool willServe(int floor,Direction direction)
  {   if(currentDir==direction)
      {
         if((currentFloor>floor && direction==UP) || (currentFloor<floor && direction==DOWN))
         {
             return true;
         }
      }
      return false;
      
  }
  
   int distanceTo(int floor)
   {
       return abs(floor-currentFloor);
   }
   
   bool isIdle()
   {
       return currentDir==NONE;
   }
   
   
   
   int getId()
   {
       return ElevatorId;
   }
};




class ElevatorSystem{
    vector<Elevator*> elevators;
    
    public:
     ElevatorSystem(int n)
     {
         for(int i=0;i<n;i++)
         {
             elevators.push_back(new Elevator(i));
         }
     }
     
     
     void externalRequest(int floor,Direction direction)
     {
         Elevator* bestElevator=NULL;
         
         int minScore=INT_MAX;
         
         for(auto e:elevators)
         {
             if(e->willServe(floor,direction))
             {
                 int score=e->distanceTo(floor);
                 if(score<minScore)
                 {
                     bestElevator=e;
                     minScore=score;
                 }
             }
         }
         
         if(!bestElevator)
         {
            for(auto e:elevators)
            {
             if(e->isIdle())
             {
                 bestElevator=e;
                 break;
             }
             }
         }
         bestElevator->addRequest(floor);
          cout<<" Assigned Floor "<< floor<<"to elevator "<<bestElevator->getId()<<"\n";
         
     }
     
     void step()
     {
         for(auto e:elevators)
         {
             if(!e->isIdle())
             {
                 e->move();
             }
         }
     }
     
    void addElevatorRequest(Elevator* id,int floor)
    {
        elevators[id]->addrequest(floor);
    }
     
};



class ButtonControllerClass{
   
     ElevatorSystem* system;
    public:
      ButtonControllerClass(ElevatorSystem* sys): system(sys){}



    void pressFloorButton(int floor,Direction dir)
    {     
          cout << "[Button] Floor " << floor << " pressed " << (dir == UP ? "UP" : "DOWN") << endl;
          system->externalRequest(floor,dir);
    }
    void pressElevatorButton(int id,int floor)
    {   

        system->addElevetorRequest(id,floor);
    }
    
}



int main() {
    // Write C++ code here
    ElevatorSystem es(3); // 3 elevators
    ButtonController controller(es);

    controller.pressFloorButton(5, UP);
    controller.pressFloorButton(2, DOWN);

    // simulate internal button presses
    controller.pressElevatorButton(0, 7);
    controller.pressElevatorButton(1, 3);

    for (int i = 0; i < 10; ++i) {
        es.step();
    }
    return 0;
}