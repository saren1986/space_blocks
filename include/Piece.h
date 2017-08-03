#ifndef PIECE_H
#define PIECE_H

#include"IO.h"


extern IO* io;
extern const int sizeBlock; // size of Block in pixels
extern const int sizeBoardX;
extern const int sizeBoardY;

class Piece
{
    public:
        Piece();


    int getPieceType (int wPiece, int wRotation, int x, int y);
    int getStartXBlockPosition(int wPiece, int wRotation);
    int getStartYBlockPosition(int wPiece, int wRotation);
    int getSmallWindowXBlockPosition(int wPiece, int wRotation);
    int getSmallWindowYBlockPosition(int wPiece, int wRotation);
    void drawPiece(int numberOfPiece, int numberOfRotation, int posX, int posY );

};//end of class

#endif // PIECE_H
