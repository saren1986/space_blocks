#ifndef STATECHANGER_H
#define STATECHANGER_H

#include"ScoreContainer.h"
#include"MainGame.h" //base class
#include"Game.h"
#include"Menu.h"
#include"GameInfo.h"
#include"GameOver.h"

enum GameStates {STATE_NULL, STATE_MENU, STATE_GAME, STATE_RESTART, STATE_GAME_INFO, GAME_OVER, STATE_EXIT};

class StateChanger
{
    public:
        StateChanger();
        ~StateChanger();

        void setNext(GameStates next);
        MainGame * change();
        int getStateID();
        ScoreContainer scoreContainer;
        ScoreContainer *ptrScoreContainer;


    private:
        MainGame *currentState;
        int stateID;
        int nextState;

};

#endif // STATECHANGER_H
