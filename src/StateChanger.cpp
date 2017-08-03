#include "StateChanger.h"


StateChanger::StateChanger()
    :ptrScoreContainer(&scoreContainer), currentState(0), stateID(STATE_MENU), nextState(STATE_MENU)
{
    //ctor
}

StateChanger::~StateChanger()
{
    if(nextState == STATE_EXIT)
    delete currentState;
    currentState = 0;

}


void StateChanger::setNext(GameStates next)
{
    nextState = next;
}

MainGame * StateChanger::change()
{
    if ( nextState != STATE_NULL )
    {
        if (nextState != STATE_EXIT)
        {
            delete currentState;

            switch (nextState)
            {
            case STATE_GAME:
                currentState = new Game(ptrScoreContainer);
                break;

            case STATE_RESTART:
                currentState = new Game(ptrScoreContainer);
                break;

            case STATE_MENU:
                currentState = new Menu;
                break;

            case STATE_GAME_INFO:
                currentState = new GameInfo;
                break;

            case GAME_OVER:
                currentState = new GameOver(ptrScoreContainer);
                break;

            }
        }
        stateID = nextState;
        nextState = STATE_NULL;

    }
    return currentState;
}


int StateChanger::getStateID()
{
return stateID;
}
