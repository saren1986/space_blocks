#include <SDL2/SDL.h>
#include <stdlib.h>

#include"StateChanger.h"


IO *io = NULL;
StateChanger *ptrChanger = NULL;

int main( int argc, char* args[] )
{

    IO init;
    io = &init;
    if ( !init.init() )
        return 0;

    StateChanger changer;
    ptrChanger = &changer;


//////////////////////////////////////////////////////////////////////////////
///-------------MAIN LOOP-------------------------------------------------
/////////////////////////////////////////////////////////////////////////////



    while( changer.getStateID()!=STATE_EXIT )
    {

        MainGame *currentState = changer.change();

        currentState ->handleEvents();
        currentState ->logic();
        currentState ->render();

    }

    SDL_Quit();//Quit SDL

    return 0;
}
