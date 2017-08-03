#ifndef GAMEINFO_H
#define GAMEINFO_H

#include"StateChanger.h"

extern IO *io;


class GameInfo : public MainGame
{
    public:
        GameInfo();
        ~GameInfo();

        void logic();
        void render();
        void handleEvents();

};

#endif // GAMEINFO_H
