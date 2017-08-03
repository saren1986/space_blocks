#include "../include/IO.h"
#include<stdlib.h>
#include<SDL2/SDL.h>

#include<iostream>


using namespace std;

extern const int SCREEN_WIDTH;// = 800;
extern const int SCREEN_HEIGHT;// = 680;

//enum eColor {white, black, blue, green, yellow, max_color};

SDL_Color colors[max_color] =
{
    {255, 255, 255, 255}, //white;
    {0,0,0,0}, // black
    {52,27,219,255 }, //blue
    {37, 230, 63, 255}, //green
    {255, 255, 0, 255},//yellow

};


IO::IO()
{
//ctor
}

IO::~IO()
{
    SDL_DestroyWindow(window);
    window = NULL;
    clean();

}


bool IO::init()
{

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
    {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "SpaceBlocks v. 2.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
            return false;
        }
        else
        {
            //create renderer
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (renderer == NULL)
            {
                cerr << "Render could not be created! SDL_Error: " << SDL_GetError() << endl;
                return false;
            }
            else
            {
                //initialize PNG Loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    cerr << "SDL_Image couldn't initialize. IMG_Error: " << IMG_GetError() << endl;
                    return false;
                }
                else
                {
                    if( TTF_Init() == -1 )
                    {
                        std::cerr << "SDL_ttf couldn't initialize. "<< TTF_GetError() <<std::endl;
                    }
                    else
                    {
                        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                        {
                            std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
                            return false;

                        }
                        else
                        {
                            loadMedia();

                        }
                    }
                }
            }
        }
    }
    return true;
}///<--------------------------IO::init()--------------------------------------------

bool IO::loadMedia()
{
    bool success = true;

    background = loadTexture( "media/background.png" );
    menuBackground = loadTexture( "media/menuBackground.png" );
    gameInfoBackground = loadTexture( "media/gameInfoBackground.png" );

    orangePiece = loadTexture("media/orangePiece.png");
    greenPiece = loadTexture("media/greenPiece.png");
    violetPiece = loadTexture("media/violetPiece.png");
    greyPiece = loadTexture("media/greyPiece.png");
    redPiece = loadTexture("media/redPiece.png");
    cyanPiece = loadTexture("media/cyanPiece.png");
    yellowPiece = loadTexture("media/yellowPiece.png");
    starPiece = loadTexture("media/starPiece.png");
    starPiece2 = loadTexture("media/starPiece2.png");

    if( background == NULL )
    {
        std::cerr<<"function IO::loadMedia: Failed to load texture image: ""background.png"" \n\n";
        success = false;
    }
    else if( menuBackground == NULL )
    {
        std::cerr<<"function IO::loadMedia: Failed to load texture image: ""menuBackground.png"" \n\n";
        success = false;
    }

    else if( gameInfoBackground == NULL )
    {
        std::cerr<<"function IO::loadMedia: Failed to load texture image: ""gameInfoBackground.png"" \n\n";
        success = false;
    }


    else if( orangePiece == NULL )
    {
        std::cerr<<"function IO::loadMedia: Failed to load texture image: ""orangePiece.png"" \n\n";
        success = false;
    }
    else if( greenPiece == NULL )
    {
        std::cerr<<"function IO::loadMedia: Failed to load texture image: ""greenPiece.png"" \n\n";
        success = false;
    }
    else if( violetPiece == NULL )
    {
        std::cerr<<"function IO::loadMedia: Failed to load texture image: ""violetPiece.png"" \n\n";
        success = false;
    }
    else if( greyPiece == NULL )
    {
        std::cerr<<"function IO::loadMedia: Failed to load texture image: ""greyPiece.png"" \n\n";
        success = false;
    }
    else if( redPiece == NULL )
    {
        std::cerr<<"function IO::loadMedia: Failed to load texture image: ""redPiece.png"" \n\n";
        success = false;
    }
    else if( cyanPiece == NULL )
    {
        std::cerr<<"function IO::loadMedia: Failed to load texture image: ""cyanPiece.png"" \n\n";
        success = false;
    }
    else if( yellowPiece == NULL )
    {
        std::cerr<<"function IO::loadMedia: Failed to load texture image: ""yellowPiece.png"" \n\n";
        success = false;
    }
    else if( starPiece == NULL )
    {
        std::cerr<<"function IO::loadMedia: Failed to load texture image: ""starPiece.png"" \n\n";
        success = false;
    }
    else if( starPiece2 == NULL )
    {
        std::cerr<<"function IO::loadMedia: Failed to load texture image: ""starPiece2.png"" \n\n";
        success = false;
    }

    tickSound = Mix_LoadWAV( "media/tickSound.wav" );
    if( tickSound == NULL )
    {
        std::cerr<<"Failed to load beat music >> ""tickSound.wav""! SDL_mixer Error: "<<  Mix_GetError() <<std::endl;
        success = false;
    }
    enterSound = Mix_LoadWAV( "media/enterSound.wav" );
    if( enterSound == NULL )
    {
        std::cerr<<"Failed to load beat music >> ""enterSound.wav""! SDL_mixer Error: "<<  Mix_GetError() <<std::endl;
        success = false;
    }
    deleteLineSound = Mix_LoadWAV( "media/deleteLineSound.wav" );
    if( deleteLineSound == NULL )
    {
        std::cerr<<"Failed to load beat music >> ""deleteLineSound.wav""! SDL_mixer Error: "<<  Mix_GetError() <<std::endl;
        success = false;
    }
    rotateSound = Mix_LoadWAV( "media/rotateSound.wav" );
    if( rotateSound == NULL )
    {
        std::cerr<<"Failed to load beat music >> ""rotateSound.wav""! SDL_mixer Error: "<<  Mix_GetError() <<std::endl;
        success = false;
    }

    downSound = Mix_LoadWAV( "media/downSound.wav" );
    if( downSound == NULL )
    {
        std::cerr<<"Failed to load beat music >> ""downSound.wav""! SDL_mixer Error: "<<  Mix_GetError() <<std::endl;
        success = false;
    }
    gameOverSound = Mix_LoadWAV( "media/gameOverSound.wav" );
    if( gameOverSound == NULL )
    {
        std::cerr<<"Failed to load beat music >> ""downSound.wav""! SDL_mixer Error: "<<  Mix_GetError() <<std::endl;
        success = false;
    }

    fourLineDeletedSound = Mix_LoadWAV( "media/fourLineDeletedSound.wav" );
    if( fourLineDeletedSound == NULL )
    {
        std::cerr<<"Failed to load beat music >> ""fourLineDeletedSound.wav""! SDL_mixer Error: "<<  Mix_GetError() <<std::endl;
        success = false;
    }

    return success;
}///<----------IO::loadMedia()------------------------------------------------------------


void IO::drawText( std::string text, eColor enumColor, int x, int y, int fontSize, int fontKind, int sizeWindow )
{
    int xw = 0;
    int xh = 0;
    int xWindow = sizeWindow;
    SDL_DestroyTexture(textTexture);

    if(fontKind)
    allFont = TTF_OpenFont("media/font.ttf", fontSize);
    else
    allFont = TTF_OpenFont("media/font2.ttf", fontSize);


    SDL_Color currentColor = { colors[enumColor].r, colors[enumColor].g, colors[enumColor].b, colors[enumColor].a };

    SDL_Surface* textSurface = TTF_RenderText_Solid( allFont, text.c_str(), currentColor );

    if ( textSurface == NULL )
    {
        std::cerr<<std::endl << "Unable to render text surface " << " TTF_Error: " << TTF_GetError() << std::endl;
    }
    else
    {
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        if( textTexture == NULL )
        {
            std::cerr <<std::endl << "Unable to crate text from surface " << " TTF_Error: " << TTF_GetError() << std::endl;
        }
        xw = textSurface -> w;
        xh = textSurface -> h;
        xWindow = (xWindow-xw)/2;
        SDL_FreeSurface(textSurface);
    }
    SDL_Rect rect = {x+xWindow, y, xw, xh};

    SDL_RenderCopy( renderer, textTexture, NULL, &rect );

    TTF_CloseFont(allFont);
    allFont = NULL;

}///<----------IO::drawText()------------------------------------------------------------


SDL_Texture* IO::loadTexture(std::string path)
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    if (loadedSurface == NULL)
    {
        std::cerr <<std::endl << "Unable to load image from path: " << path << " IMG_Error: " << IMG_GetError() <<std::endl;
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        SDL_FreeSurface(loadedSurface);
    }


    return newTexture;
}///<--------IO::loadTexture------------------------------------------------------------------------


void IO::clearScreen()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL );
}//<--------------------------IO::clearScreen()--------------------------------------------------


void IO::refreshScreen()
{
    SDL_RenderPresent(renderer);
}///<--------IO::refreshScreen()------------------------------------------------------------------------



void IO::renderPiece(int color, int x, int y, int w, int h)
{
    SDL_Texture *currentPieceTexture = NULL;

    SDL_Rect rect = {x, y, w, h };
    switch (color)
    {
    case 0:
        currentPieceTexture = orangePiece;
        break;

    case 1:
        currentPieceTexture = greenPiece;
        break;

    case 2:
        currentPieceTexture = violetPiece;
        break;

    case 3:
        currentPieceTexture = redPiece;
        break;

    case 4:
        currentPieceTexture = yellowPiece;
        break;

    case 5:
        currentPieceTexture = cyanPiece;
        break;

    case 6:
        currentPieceTexture = greyPiece;
        break;

    case 7:
        currentPieceTexture = starPiece;
        break;

    case 8:
        currentPieceTexture = starPiece2;
        break;

    default:
        currentPieceTexture = orangePiece;
        break;
    }

    SDL_RenderCopy( renderer, currentPieceTexture, NULL, &rect );
} ///<--------renderPiece()------------------------------------------------------------------------


void IO::playSoundEffect(int mode)
{
    switch(mode)
    {
    case 1:
        Mix_PlayChannel(-1, tickSound, 0);
        break;
    case 2:
        Mix_PlayChannel(-1, enterSound, 0);
        break;
    case 3:
        Mix_PlayChannel(-1, deleteLineSound, 0);
        break;
    case 4:
        Mix_PlayChannel(-1, downSound, 0);
        break;
    case 5:
        Mix_PlayChannel(-1, rotateSound, 0);
        break;
    case 6:
        Mix_PlayChannel(-1, fourLineDeletedSound, 0);
        break;
    case 7:
        Mix_PlayChannel(-1, gameOverSound, 0);
        break;

    default:
        break;
    }

}

void IO::clean()
{


    SDL_DestroyTexture(orangePiece);
    orangePiece = NULL;

    SDL_DestroyTexture(greenPiece);
    greenPiece = NULL;

    SDL_DestroyTexture(redPiece);
    redPiece = NULL;

    SDL_DestroyTexture(cyanPiece);
    cyanPiece = NULL;

    SDL_DestroyTexture(greyPiece);
    greyPiece = NULL;

    SDL_DestroyTexture(yellowPiece);
    yellowPiece = NULL;

    SDL_DestroyTexture(violetPiece);
    violetPiece = NULL;

    SDL_DestroyTexture(starPiece);
    violetPiece = NULL;

    SDL_DestroyTexture(starPiece2);
    violetPiece = NULL;

    SDL_DestroyTexture(background);
    background = NULL;

    SDL_DestroyTexture(menuBackground);
    menuBackground = NULL;

    SDL_DestroyTexture(gameInfoBackground);
    menuBackground = NULL;

    SDL_DestroyTexture(textTexture);
    textTexture = NULL;


    Mix_FreeChunk(tickSound);
    tickSound = NULL;

    Mix_FreeChunk(enterSound);
    tickSound = NULL;

    Mix_FreeChunk(rotateSound);
    tickSound = NULL;

    Mix_FreeChunk(downSound);
    tickSound = NULL;

    Mix_FreeChunk(gameOverSound);
    tickSound = NULL;

    Mix_FreeChunk(fourLineDeletedSound);
    tickSound = NULL;

    Mix_FreeChunk(deleteLineSound);
    tickSound = NULL;

    Mix_Quit();
    IMG_Quit();


}//<---------------------------IO:Clean();---------------------


