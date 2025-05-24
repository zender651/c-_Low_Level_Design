// Online C++ compiler to run C++ program online
#include <iostream>
#include <bits/stdc++.h>
#include<random>

using namespace std;

// a board, two players minm, a dice, (snake, ladder ->jumper)

class Player{
    int id;
    string playerName;
    
    public:
    Player(int i,string name):id(i),playerName(name){}
    
    
    string getPlayerName()
    {
        return playerName;
    }
};


class Dice{
    int noOfDice;
    mt19937 gen;
    
    public:
    Dice(int n):noOfDice(n){}
    
    int rollDice()
    {
        uniform_int_distribution<> dist(noOfDice,noOfDice*6);
        return dist(gen);
    }
};

class Jumper{
    int startPoint;
    int endPoint;
    
    public:
    Jumper(int st,int end):startPoint(st),endPoint(end){}
    
    int getStartPoint(){
        return startPoint;
    }
    int getEndPoint()
    {
        return endPoint;
    }
};

class GameBoard{
    Dice* dice;
    queue<Player*> nextTurn;
    vector<Jumper*> snakes;
    vector<Jumper*> ladders;
    map<string,int> playerCurrentPosition;
    int boardSize;
    
    public:
    GameBoard(Dice* d,queue<Player*> pl,vector<Jumper*> snake,vector<Jumper*> laddr,map<string,int> m,int n):dice(d),nextTurn(pl),snakes(snake),ladders(laddr),playerCurrentPosition(m),boardSize(n){}
    
    void startGame(){
        while(!nextTurn.empty())
        {
            Player* currPlayer=nextTurn.front();
            nextTurn.pop();
            
            int currentPos=playerCurrentPosition[currPlayer->getPlayerName()];
            
            int diceVal=dice->rollDice();
            
            int nextPos=currentPos+diceVal;
            
            if(nextPos>boardSize)
             {
                 cout<<"Move out of bounds. Next player ";
        
             }
            else if(nextPos==boardSize)
            {
                cout<<currPlayer->getPlayerName()<<" has won the game";
                
                break;
            }
            else
            {
                for(auto it:ladders)
                {
                    if(it->getStartPoint()==nextPos)
                    {
                        nextPos=it->getEndPoint();
                    }
                }
                
                for(auto it:snakes)
                {
                    if(it->getStartPoint()==nextPos)
                    {
                        nextPos=it->getEndPoint();
                    }
                }
                
                if(nextPos==boardSize)
                {
                    cout<<currPlayer->getPlayerName()<<" has won the game";
                    break;
                }
                
                playerCurrentPosition[currPlayer->getPlayerName()]=nextPos;
                
                nextTurn.push(currPlayer);
                cout<<currPlayer->getPlayerName()<<" is at position " << nextPos<<"\n";
                
                
            }
        }
    }
};

int main() {
    // Write C++ code here
    std::cout << "Try programiz.pro";
    
    
    Dice* dice=new Dice(1);
    Player* p1=new Player(1,"Alice");
    Player* p2=new Player(2,"Bob");
    
    
    queue<Player*> players;
    players.push(p1);
    players.push(p2);
    
    
    vector<Jumper*> snakes = {
        new Jumper(14, 7),
        new Jumper(31, 4),
        new Jumper(38, 20),
        new Jumper(84, 28),
        new Jumper(97, 78)
    };

    vector<Jumper*> ladders = {
        new Jumper(3, 22),
        new Jumper(5, 8),
        new Jumper(11, 26),
        new Jumper(20, 29),
        new Jumper(27, 56)
    };

    map<string, int> positions = {
        {"Alice", 0},
        {"Bob", 0}
    };

    GameBoard game(dice, players, snakes, ladders, positions, 100);
    game.startGame();
    return 0;
}