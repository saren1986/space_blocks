#ifndef IO_H
#define IO_H
#include<iostream>
#include<SDL2/SDL.h>
#include <stdio.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 680;


const int sizeBlock = 25; // size of Block in pixels
const int sizeBoardX = 10;
const int sizeBoardY = 24;
const int positionBoardX = (  ( SCREEN_WIDTH / 2 )  - ( sizeBoardX * sizeBlock )/ 2  );
const int positionBoardY = sizeBlock*3;


enum eColor {white, black, blue, green, yellow, max_color};

class IO
{
    public:

        IO();
        virtual ~IO();
        bool init();

        void clearScreen();
        void refreshScreen();

        void renderPiece( int, int, int, int =25, int =25 );

        void drawText( std::string, eColor, int, int, int fontSize = 28,  int fontKind = 1, int sizeWindow = 0 );
        void playSoundEffect(int = 0);

    private:

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    //pointers to PNG Graph
    SDL_Texture *background = NULL,
                *orangePiece = NULL,
                *greenPiece = NULL,
                *redPiece = NULL,
                *cyanPiece = NULL,
                *greyPiece = NULL,
                *yellowPiece = NULL,
                *violetPiece = NULL,

                *starPiece = NULL,
                *starPiece2 = NULL,

                *textTexture = NULL,

                *menuBackground = NULL,
                *gameInfoBackground = NULL;

    TTF_Font    *allFont = NULL;

    Mix_Chunk   *tickSound = NULL,
                *enterSound = NULL,
                *rotateSound = NULL,
                *downSound = NULL,
                *gameOverSound = NULL,
                *fourLineDeletedSound = NULL,
                *deleteLineSound = NULL;

    SDL_Texture* loadTexture(std::string path);

    bool loadMedia();
    void clean();

    friend class Menu;
    friend class GameMenu;
    friend class GameInfo;
};

#endif // IO_H
