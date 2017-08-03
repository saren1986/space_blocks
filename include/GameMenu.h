#ifndef GAMEMENU_H
#define GAMEMENU_H

#include"StateChanger.h"


class GameMenu
{
    public:
        GameMenu();

        int logic();
        void render();
        void handleEvents();

    protected:

    private:
        void    drawMenu();
         enum {RESUME, RESTART, MENU_QUIT};

        void changeMenuPosition(int);

       int menuPosition;
       bool pressEnter;

};

#endif // GAMEMENU_H
