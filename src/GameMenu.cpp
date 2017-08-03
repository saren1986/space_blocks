#include "GameMenu.h"

GameMenu::GameMenu()
:menuPosition(RESUME), pressEnter(false)
{}


void GameMenu::drawMenu()
{
    int y = SCREEN_HEIGHT/2;
    eColor color1 = white, color2 = white, color3 = white;
    if (menuPosition == 0)
        color1 = yellow;
    else if(menuPosition == 1)
        color2 = yellow;
    else if (menuPosition == 2)
        color3 = yellow;


    io ->drawText("Resume", color1, SCREEN_WIDTH /2, y);
    io ->drawText("Restart", color2, SCREEN_WIDTH /2, y+40);
    io ->drawText("Quit Game", color3, SCREEN_WIDTH /2, y+80);

}

void GameMenu::changeMenuPosition(int position)
{
    menuPosition += position;
    if (menuPosition > MENU_QUIT )
        menuPosition = RESUME;
    else if (menuPosition < RESUME)
        menuPosition = MENU_QUIT;

}


int GameMenu::logic()
{

    if (pressEnter == true && menuPosition == RESUME)
    {
        pressEnter = false;
        return 1;
    }

    else if (pressEnter == true && menuPosition == RESTART)
    {
        pressEnter = false;
        return 2;

    }
    else if (pressEnter == true && menuPosition == MENU_QUIT)
    {
        pressEnter = false;
        return 3;
    }
    else
    {
        pressEnter = false;
        return 0;
    }
}//<--------Menu::logic()--------------------------------


void GameMenu::handleEvents()
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
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                ptrChanger ->setNext(STATE_EXIT);
                break;

            case SDLK_DOWN:
                changeMenuPosition(1);
                io->playSoundEffect(1);
                break;

            case SDLK_UP:
                changeMenuPosition(-1);
                io->playSoundEffect(1);
                break;

            case SDLK_RETURN:
                pressEnter = true;
                io->playSoundEffect(2);
                break;

            }
        }
    }
}



void GameMenu::render()
{

    SDL_RenderClear( io -> renderer);
    SDL_RenderCopy( io -> renderer, io -> menuBackground, NULL, NULL );
        drawMenu();

    io ->refreshScreen();

}//<--------Menu::draw()--------------------------------



