#ifndef BOARD_H
#define BOARD_H

#include<SDL2/SDL.h>

#include"Piece.h"

extern IO *io;

extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;

extern const int sizeBlock; // size of Block in pixels
extern const int sizeBoardX;
extern const int sizeBoardY;
extern const int positionBoardX;
extern const int positionBoardY;

enum {pos_empty, pos_fill};


class Board
{

private:

    Piece *piece;


public:
    Board(Piece *aa);
    void draw();
    void putPieceInTheBoard(int numberOfPiece, int numberOfRotation, int posX, int posY);

    int  checkLine();
    bool checkTopLine();
    void clearBoard();
    void putOneBlockInTheBoard(int, int, int);

    int board[sizeBoardY][sizeBoardX];
    int boardOfColors[sizeBoardY][sizeBoardX];


    void drawDeletingAnimation(int = -1);
    void copyToDown(int line);

};

#endif // BOARD_H
