
#include <iostream>
#include<bits/stdc++.h>


using namespace std;


class Player{
   int playerid;
   int symbolid;
   public:
Player(int id,int sym):playerid(id),symbolid(sym){}

int getId()
{
    return playerid;
}

int getSymbolId()
{
    return symbolid;
}

};
class TicTacToe{
    
    public:
       vector<vector<int>> board;
       int winner;
    
    TicTacToe(int n)
    {
        board.resize(n,vector<int>(n,0));
        winner=false;
    }
    
    int move(const Player& pl,int row,int col)
    {   
        int player=pl.getSymbolId();
        int playerId=pl.getId();
        int n=board.size();
        if(row<0 ||col <0|| row>=n ||col
        >=n)
        {
            throw invalid_argument("Invalid Move");
        }
        else if(board[row][col]!=0)
        {
            throw invalid_argument("Invalid Move");
        }
        else if(player!=1 && player !=2)
        {
            throw invalid_argument("Invalid Player");
        }
        else
        {   
           
            
            board[row][col]=player;
            
            bool winrow=true,wincol=true,diag=true,revdiag=true;
            
            for(int i=0;i<n;i++)
            {
                if(board[i][col]!=player)
                 wincol=false;
                if(board[row][i]!=player)
                 winrow=false;
                if(board[i][i]!=player)
                 diag=false;
                if(board[i][n-i-1]!=player)
                 revdiag=false;
            }
            
            if(winrow||wincol||diag||revdiag)
             winner=playerId;
        }
        
        return getwinner();
         
    }
    
    int getwinner()
    {
        return winner;
    }
    
    
};
int main() {
    // Write C++ code here
    std::cout << "Try programiz.pro";
    TicTacToe game(3);
    Player* player1=new Player(1,1);
    Player* player2=new Player(2,-1);
    cout << game.move(*player1, 0, 0) << endl;  // Output: 0
    cout << game.move(*player2, 1, 0) << endl;  // Output: 0
    cout << game.move(*player1, 0, 1) << endl;  // Output: 0
    cout << game.move(*player2, 1, 1) << endl;  // Output: 0
    cout << game.move(*player1, 0, 2) << endl;
    return 0;
}