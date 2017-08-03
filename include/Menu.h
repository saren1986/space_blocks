#ifndef MENU_H
#define MENU_H

#include"StateChanger.h"


extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;


class Menu: public MainGame
{
    public:
        Menu();

        void logic();
        void render();
        void handleEvents();

    protected:
        enum {START_GAME, GAME_INFO, QUIT};
        void drawMenu();
        void changeMenuPosition(int);

        int menuPosition;
        bool pressEnter;

};

#endif // MENU_H

