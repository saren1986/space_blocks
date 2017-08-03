#ifndef MAINGAME_H
#define MAINGAME_H


class MainGame
{
    public:
        MainGame();
        virtual ~MainGame();

        virtual void handleEvents() = 0;
        virtual void logic() = 0;
        virtual void render() = 0;
};

#endif // MAINGAME_H
