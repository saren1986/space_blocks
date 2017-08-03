#include "../include/Menu.h"



Menu::Menu()
:menuPosition(START_GAME), pressEnter(false)
{
}



void Menu::changeMenuPosition(int position)
{
    menuPosition += position;

    if (menuPosition > QUIT )
        menuPosition = START_GAME;
    else if (menuPosition < START_GAME)
        menuPosition = QUIT;

}//<--------------changeMenuPosition()-------------------


void Menu::handleEvents()
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

}//<--------------handleEvents()-------------------

void Menu::logic()
{

    if (pressEnter == true && menuPosition == START_GAME)
    {
        pressEnter = false;
        ptrChanger ->setNext(STATE_GAME);
    }

    else if (pressEnter == true && menuPosition == GAME_INFO)
    {
        pressEnter = false;
        ptrChanger ->setNext(STATE_GAME_INFO);
    }
    else if (pressEnter == true && menuPosition == QUIT)
    {
        pressEnter = false;
        ptrChanger ->setNext(STATE_EXIT);
    }

}//<--------Menu::logic()--------------------------------

void Menu::drawMenu()
{
    int y = SCREEN_HEIGHT/2;
    eColor color1 = white, color2 = white, color3 = white;
    if (menuPosition == 0)
        color1 = yellow;
    else if(menuPosition == 1)
        color2 = yellow;
    else if (menuPosition == 2)
        color3 = yellow;

    io ->drawText("Start Game", color1, SCREEN_WIDTH /2, y);
    io ->drawText("Game Info", color2, SCREEN_WIDTH /2, y+40);
    io ->drawText("Quit", color3, SCREEN_WIDTH /2, y+80);

}//<--------Menu::drawMainMenu()--------------------------------



void Menu::render()
{

    SDL_RenderClear( io -> renderer);
    SDL_RenderCopy( io -> renderer, io -> menuBackground, NULL, NULL );

    drawMenu();

    io ->refreshScreen();

}//<--------Menu::draw()--------------------------------



