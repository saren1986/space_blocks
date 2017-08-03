#ifndef GAMEOVER_H
#define GAMEOVER_H

#include"StateChanger.h"


class GameOver : public MainGame
{
public:
    GameOver(ScoreContainer *sc);
    ~GameOver();

    void handleEvents();
    void logic();
    void render();
    ScoreContainer *ptrSC;

private:
    int x,y;
    int score;
    int level;
    int lines;
    std::string sScore,
        sLevel,
        sLines;
    Piece piece;
    Board board;



};

#endif // GAMEOVER_H
