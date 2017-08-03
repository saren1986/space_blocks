#ifndef GAME_H
#define GAME_H

#include<sstream>
#include<cmath>

#include"Piece.h"
#include"Board.h"
#include"Timer.h"

#include"StateChanger.h"
#include"GameMenu.h"


extern const int positionBoardX;
extern const int positionBoardY;
extern const int sizeBoardX;
extern const int sizeBoardY;

class StateChanger;

extern StateChanger *ptrChanger;

class Game: public MainGame
{
public:

    Game(ScoreContainer *sc);

    //virtual functions
    void handleEvents();
    void logic();
    void render();

private:
    Piece piece;
    Board board;
    ScoreContainer *ptrSC;
    Timer gameLogicTimer;
    Timer pieceDownSpeedTimer;
    Timer  rotateTime, fastDownTime, moveTime;

    bool isPieceCreated;
    int piecePositionX;
    int piecePositionY;
    int kindOfPiece;
    int kindOfRotation;

    int kindOfPiece2;
    int kindOfRotation2;
    int piecePositionX2;
    int piecePositionY2;

    double currentTimeSpeed;

    int numberOfDeletedLines;
    int score;
    int level;
    const double EPS;

    std::ostringstream osScore;
    std::string sScore, sLines, sLevel;

//--------------methods
    void moveLeft();
    void moveRight();
    void moveDown();
    void pieceRotate();
    void fastDown();
    void newGame();

    int randKindOfPieces();
    int randKindOfRotation();
    void createNewPiece();
    void getNewPiece();
    bool isMovePossible( int, int, int, int);
    bool isRotationPossible(int, int, int, int);
    void countScore();
    void drawNextPiece(int tP, int tR, int tx, int ty); /// this function render next piece exactly on the center of preview
    void intToString();

};

#endif // GAME_H
