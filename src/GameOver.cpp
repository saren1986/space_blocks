#include "GameOver.h"

GameOver::GameOver(ScoreContainer *sc)
    : ptrSC(sc), score(ptrSC->score), level(ptrSC->level), lines(ptrSC->lines), sScore(ptrSC->sScore),
       sLevel(ptrSC->sLevel), sLines(ptrSC->sLines), board(&piece)
{
    x = 0;
    y = 23;
    io ->playSoundEffect(7);
}

GameOver::~GameOver()
{
    //dtor
}


void GameOver::logic()
{
}

void GameOver::render()
{
    io -> clearScreen();

    int color = rand()%7;


    board.putOneBlockInTheBoard(x,y,color);

    for(int i=0; i<sizeBoardY; i++)             ///drawBoard
        for(int j=0; j<sizeBoardX; j++)
        {
            if (board.board[i][j] == pos_fill )
                io ->renderPiece(board.boardOfColors[i][j], positionBoardX + sizeBlock * j, positionBoardY + sizeBlock * i  );
        }

    io ->drawText("Game Over", white, 400, 80, 28);
    io ->drawText("press escape...", white, 400, 120, 28);
    io ->drawText(sScore, white, 575, 195, 28, 1, 194);
    io ->drawText(sLevel, white, 575, 493, 28, 1, 88);
    io ->drawText(sLines, white, 682, 493, 28, 1, 88);
    io ->refreshScreen();


    if (x>=9)
    {
        x=0;
        y--;
    }
    else x++;

    if (y<=3)
    {
        y=23;
    }


}

void GameOver::handleEvents()
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
            if(event.key.keysym.sym == SDLK_ESCAPE)
            ptrChanger ->setNext(STATE_MENU);
        }
    }


}
