// Online C++ compiler to run C++ program online
#include <iostream>
#include<bits/stdc++.h>


using namespace std;

// class Chess{
    
// };

// class Piece{
//     public:
//     Position currentPosition;
//     Board currentBoard;
    
//     Color color;
//     void move(Position destination)
//     {
//         if(isValid(currentPosition,destination))
//         {
//             currentPosition=destination;
//         }
//         Piece destinationPiece=currentBoard[destination];
//         if(destination)
        
//     }
    
//     bool isValid(Position start,Position end)
//     {   
//         Board temp=new Board();
//         temp.makeMove(this,end);
//         if(KingInCheck(temp,color))
//         {
//             return false;
//         }
//         else
//         {   Piece destinationPiece=currentBoard[destination];
//             if(destinationPiece!=NULL &&  !destinationPiece.getColor()==color)
//             {   
//                 return false;
//             }
//           return isValidMove();
//         }
//     }
    
//     bool isvalidMove(){
        
//     }
    
//     bool kingInCheck(Board board,Color color)
//     {
        
//     }
    
//     bool currentKingInCheck(Board board){
//         return false;
//     }
//     void getAllPossibleMoves();
//     {
        
//     }
    
    
//     Color getColor(){
//         return color;
//     }
// };

// enum Color{
//     WHITE,BLACK
// };
// class Board{
//     public:
//       map<Position,Piece> pieces;
//       void makeMove(Piece piece,Position destination)
//       {   pieces.erase(currentPosition);
//           pieces[destination]=piece;
//       }
       
//       Piece get(Position destination)
//       {
//           return pieces[destination];
//       }
// };

// class Position{
    
// };

// class Pawn{
    
// };

// class King{
    
// };

// class Queen{
    
// };

// class Rook{
    
// };

// class Bishop{
    
// };

#include <iostream>
#include <map>
using namespace std;

enum Color {
    WHITE, BLACK
};

class Position {
public:
    int row, col;
    Position(int r = 0, int c = 0) : row(r), col(c) {}

    bool operator<(const Position& other) const {
        return row < other.row || (row == other.row && col < other.col);
    }
};

class Board; // Forward declaration

class Piece {
public:
    Position currentPosition;
    Color color;

    Piece(Position pos, Color col) : currentPosition(pos), color(col) {}
    virtual ~Piece() = default;

    virtual bool isValidMove(Position destination, Board& board) = 0;

    bool move(Position destination, Board& board);

    Color getColor() {
        return color;
    }

    virtual char getSymbol() const = 0;
};

class Board {
public:
    map<Position, Piece*> pieces;

    void makeMove(Piece* piece, Position destination) {
        pieces.erase(piece->currentPosition);
        piece->currentPosition = destination;
        pieces[destination] = piece;
    }

    Piece* get(Position destination) {
        if (pieces.find(destination) != pieces.end())
            return pieces[destination];
        return nullptr;
    }

    bool isKingInCheck(Color color) {
        // Stub logic
        return false;
    }
};

// Move logic with validation
bool Piece::move(Position destination, Board& board) {
    if (isValidMove(destination, board)) {
        board.makeMove(this, destination);
        return true;
    }
    return false;
}

// Example Piece: King
class King : public Piece {
public:
    King(Position pos, Color col) : Piece(pos, col) {}

    bool isValidMove(Position destination, Board& board) override {
        int dr = abs(destination.row - currentPosition.row);
        int dc = abs(destination.col - currentPosition.col);

        Piece* destPiece = board.get(destination);
        if (destPiece && destPiece->getColor() == color)
            return false;

        return (dr <= 1 && dc <= 1);
    }

    char getSymbol() const override {
        return color == WHITE ? 'K' : 'k';
    }
};

// Similarly, you can define Queen, Pawn, etc.

class Chess {
public:
    Board board;

    void setup() {
        board.pieces[Position(0, 4)] = new King(Position(0, 4), WHITE);
        board.pieces[Position(7, 4)] = new King(Position(7, 4), BLACK);
        // Add more pieces
    }

    ~Chess() {
        for (auto& [pos, piece] : board.pieces)
            delete piece;
    }
};


int main() {
    // Write C++ code here
   
    return 0;
}