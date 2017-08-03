#include "GameInfo.h"

GameInfo::GameInfo()
{
    //ctor
}

GameInfo::~GameInfo()
{
//dtor
}


void GameInfo::render()
{
    SDL_RenderClear( io -> renderer);
    SDL_RenderCopy( io -> renderer, io -> gameInfoBackground, NULL, NULL );

    io->drawText("ABOUT GAME", black, SCREEN_WIDTH/2, 98, 32 );
    io->drawText("ABOUT GAME", yellow, SCREEN_WIDTH/2, 100, 32 );

    io->drawText("Made by ", black, SCREEN_WIDTH/2, 168, 15 );
    io->drawText("Made by ", white, SCREEN_WIDTH/2, 170, 15 );

    io->drawText("Mateusz Sarnowski", black, SCREEN_WIDTH/2, 188, 15 );
    io->drawText("Mateusz Sarnowski", white, SCREEN_WIDTH/2, 190, 15 );

    io->drawText("sarnowskimateusz86@gmail.com", black, SCREEN_WIDTH/2+1, 208, 22, 0 );
    io->drawText("sarnowskimateusz86@gmail.com", green, SCREEN_WIDTH/2, 210, 22, 0 );

    io->drawText("SDL2 C++", black, SCREEN_WIDTH/2, 248, 25, 0 );
    io->drawText("SDL2 C++", white, SCREEN_WIDTH/2, 250, 25, 0);

    io->drawText("GAME KEYS", black, SCREEN_WIDTH/2, 348, 25 );
    io->drawText("GAME KEYS", white, SCREEN_WIDTH/2, 350, 25 );

    io->drawText("Press any key to exit", black, SCREEN_WIDTH/2, 308, 10 ); //648
     io->drawText("Press any key to exit", yellow, SCREEN_WIDTH/2, 310, 10 );//650
    io ->refreshScreen();
}

void GameInfo::handleEvents()
{
SDL_Event event;
    while ( SDL_PollEvent(&event) )
    {
        if(event.type == SDL_QUIT)
        {
            ptrChanger ->setNext(STATE_EXIT);
        }
        if(event.type == SDL_KEYDOWN)
        {
                ptrChanger ->setNext(STATE_MENU);
        }
    }

}

void GameInfo::logic()
{
}
