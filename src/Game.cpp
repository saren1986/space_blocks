#include "../include/Game.h"

#include<cstdlib>
#include<time.h>

extern SDL_Color colors;


Game::Game(ScoreContainer *sc)
    :piece(), board(&piece), ptrSC(sc),

     rotateTime(0.20), fastDownTime(0.30), moveTime(0.05),
     EPS(0.00001)
{
    srand(time(NULL));
    newGame();
}

void Game::newGame()
{
    board.clearBoard();
    isPieceCreated = false;

    currentTimeSpeed = 1;
    pieceDownSpeedTimer.setTimerFrequence(currentTimeSpeed);

    score = 0;
    level = 1;
    numberOfDeletedLines = 0;

    createNewPiece();
    pieceDownSpeedTimer.startTimer();

}


void Game::createNewPiece()
{
    kindOfPiece2 = randKindOfPieces();
    kindOfRotation2 = randKindOfRotation();

    piecePositionX2 = positionBoardX +  sizeBlock*(sizeBoardX/2) - piece.getStartXBlockPosition(kindOfPiece2, kindOfRotation2) * sizeBlock;
    piecePositionY2 = positionBoardY - piece.getStartYBlockPosition(kindOfPiece2, kindOfRotation2) * sizeBlock;

}


void Game::getNewPiece()
{
    isPieceCreated = true;
    kindOfPiece = kindOfPiece2;
    kindOfRotation = kindOfRotation2;

    piecePositionX = piecePositionX2;
    piecePositionY = piecePositionY2;
}



int Game::randKindOfPieces()
{
    return rand()%7;
}

int Game::randKindOfRotation()
{
    return rand()%4;
}

void Game::moveLeft()
{
    if( isMovePossible( kindOfPiece, kindOfRotation, piecePositionX - sizeBlock, piecePositionY ) )
        piecePositionX -= sizeBlock;
}

void Game::moveRight()
{
    if( isMovePossible( kindOfPiece, kindOfRotation, piecePositionX + sizeBlock, piecePositionY ) )
        piecePositionX += sizeBlock;
}

void Game::moveDown()
{
    if (isMovePossible(kindOfPiece, kindOfRotation, piecePositionX, piecePositionY+sizeBlock))
    {
        piecePositionY+=sizeBlock;
    }
    else
    {
        board.putPieceInTheBoard(kindOfPiece, kindOfRotation, piecePositionX, piecePositionY) ;
        isPieceCreated = false;
    }
}

void Game::pieceRotate()
{
    int temp = kindOfRotation;
    if(temp<3)
        temp++;
    else
        temp = 0;

    if( isMovePossible( kindOfPiece, temp, piecePositionX, piecePositionY ) )
    {

        if(kindOfRotation<3)
            kindOfRotation++;
        else
            kindOfRotation = 0;
    }

    if( ! isRotationPossible( kindOfPiece, temp, piecePositionX, piecePositionY ) )
    {
        while ( !( isRotationPossible(kindOfPiece, temp, piecePositionX, piecePositionY) )  )
        {


            if ( (piecePositionX - positionBoardX)/sizeBlock + piece.getStartXBlockPosition(kindOfPiece, kindOfRotation) >= 1
                    && (piecePositionX - positionBoardX)/sizeBlock + piece.getStartXBlockPosition(kindOfPiece, kindOfRotation) <= 3 )

                piecePositionX += sizeBlock;



            else if( (piecePositionX - positionBoardX) / sizeBlock + piece.getStartXBlockPosition( kindOfPiece, kindOfRotation ) <= sizeBoardX
                     && ( ( piecePositionX - positionBoardX )/sizeBlock + piece.getStartXBlockPosition( kindOfPiece, kindOfRotation ) >= sizeBoardX-2 )
                   )
                piecePositionX -= sizeBlock;
        }

        if(kindOfRotation<3)
            kindOfRotation++;
        else
            kindOfRotation = 0;
    }
}

void Game::fastDown()
{
    while( isMovePossible(kindOfPiece, kindOfRotation, piecePositionX, piecePositionY+sizeBlock) )
    {
        piecePositionY+=sizeBlock;
    }

    board.putPieceInTheBoard(kindOfPiece, kindOfRotation, piecePositionX, piecePositionY) ;
    isPieceCreated = false;
}


bool Game::isRotationPossible(int numberOfPiece, int numberOfRotation, int posX, int posY)
{
    int x = (posX - positionBoardX)/sizeBlock; //position of the beginning of particular piece array relative to main board


    for (int i=0; i<5; i++)  //y
        for(int j=0; j<5; j++) //x
            if (piece.getPieceType(numberOfPiece, numberOfRotation, i, j) != 0 && ( x+j < 0 || x+j >= sizeBoardX) )
            {
                return false;
            }
    return true;
}

bool Game::isMovePossible(int numberOfPiece, int numberOfRotation, int posX, int posY)
{
    int x = (posX - positionBoardX)/sizeBlock; //position of the beginning of particular piece array relative to main board
    int y = ( posY - positionBoardY)/sizeBlock;

    for (int i=0; i<5; i++)  //y
        for(int j=0; j<5; j++) //x
        {
            if( ( piece.getPieceType(numberOfPiece, numberOfRotation, i, j) != 0 ) && ( board.board[y+i][x+j] == pos_fill)   )
            {
                return false;
            }

            else if ( (piece.getPieceType(numberOfPiece, numberOfRotation, i, j) != 0 ) && ( ( x + j < 0 || x + j >= sizeBoardX) || ( y + i >= sizeBoardY ) ) )
            {
                return false;
            }
            else if (piece.getPieceType(numberOfPiece, numberOfRotation, i, j) != 0 && (
                         ( y+i >= sizeBoardY ) || board.board[i+y][j+x] == pos_fill ) )
            {
                return false;
            }
        }
    return true;
}


void Game::countScore()
{
    int line = board.checkLine();

    if( line != 0)
    {
        int previousNODL = numberOfDeletedLines;
        previousNODL = previousNODL % 10;
        numberOfDeletedLines += line;

        switch (line)
        {
        case 1:
            score += 1 * level;
            break;

        case 2:
            score += 4 * level;
            break;

        case 3:
            score += 9 * level;
            break;

        case 4:
            score += 16 * level;
            break;
        }
        if(level == 10)
            score += level * level;
        else if (level == 11)
            score += level * level * 2;
        else if (level == 12)
            score += level * level * 3;
        else if (level == 13)
            score += level * level * 4;
        else if (level > 13)
            score += level * level * 10;

        if  (
            ( numberOfDeletedLines % 10 == 0 )
            || (    ( numberOfDeletedLines % 10 == 1 ) && ( previousNODL == 7 || previousNODL == 8 || previousNODL == 9  )   )
            || (    ( numberOfDeletedLines % 10 == 2 ) && ( previousNODL == 8 || previousNODL == 9)                          )
            || (    ( numberOfDeletedLines % 10 == 3 ) && ( previousNODL == 9 )                                              )

        )//if
        {


            if( currentTimeSpeed > 0.1 && ( fabs( 0.1 - currentTimeSpeed ) > EPS ) )
            {
                currentTimeSpeed -= 0.1;
                level++;
                pieceDownSpeedTimer.setTimerFrequence(currentTimeSpeed);
            }
            else if( currentTimeSpeed > 0.06 && ( fabs( 0.06 - currentTimeSpeed ) > EPS ) )
            {
                currentTimeSpeed -= 0.01;
                pieceDownSpeedTimer.setTimerFrequence(currentTimeSpeed);
                level++;

            }
            else
            {
                level++;
            }

        }
    }

}


void Game::drawNextPiece(int tP, int tR, int tx, int ty)
{
    int x = tx;
    int y = ty;

    if (tP == 0)
    {
        x-=12;
        y-=12;
    }

    else if ( (tP == 2 && tR == 0) || (tP == 3 && tR == 0) || (tP == 3 && tR == 2) || (tP == 1 && tR == 3) || (tP == 4 && (tR == 0 || tR == 2) ) )
        x+=12;

    else if ( (tP == 4 && (tR == 1 || tR == 3) ) || (tP == 2 && tR == 1) || (tP == 1 && tR == 2 ) )
        y+=12;


    else if( (tP == 2 && tR == 2) || (tP == 1 && tR == 1) )
        x-=12;


    else if ( (tP == 1 && tR == 0 ) || (tP == 2 && tR == 3) ||  (tP == 3 && ( tR == 1 || tR == 3 ) ) )
        y-=12;

    else if (tP == 5 && tR == 0)
    {
        x-=25;
        y+=12;
    }

    else if (tP == 5 && tR == 1)
    {
        x+=12;
        y+=25;
    }

    else if (tP == 5 && tR == 2)
    {
        x+=25;
        y-=12;
    }

    else if (tP == 5 && tR == 3)
    {
        x-=12;
        y-=25;
    }

    else if (tP == 6 && tR == 0)
    {
        x-=25;
        y-=12;
    }

    else if (tP == 6 && tR == 1)
    {
        x-=12;
        y+=25;
    }

    else if (tP == 6 && tR == 2)
    {
        x+=25;
        y+=12;
    }

    else if (tP == 6 && tR == 3)
    {
        x+=12;
        y-=25;
    }

    piece.drawPiece( tP, tR, x, y );
}


void Game::handleEvents()
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
            {
                pieceDownSpeedTimer.pauseTimer();
                GameMenu *gameMenu = new GameMenu;
                while(true)
                {
                    gameMenu ->handleEvents();

                    int menuOption = gameMenu -> logic();

                    if( menuOption  == 1)
                        break;

                    else if( menuOption == 2)
                    {
                        ptrChanger ->setNext(STATE_RESTART);
                        break;
                    }

                    else if( menuOption  == 3)
                    {
                        ptrChanger ->setNext(STATE_MENU);
                        break;
                    }
                    gameMenu ->render();
                }
                delete gameMenu;
                pieceDownSpeedTimer.resumeTimer();
            }
        }
    }
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( moveTime.getTime() )
    {
        if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
            moveLeft();
        else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
            moveRight();
        else if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
            moveDown();
    }
    if( currentKeyStates[ SDL_SCANCODE_Z ] && rotateTime.getTime() )
    {
        pieceRotate();
        io->playSoundEffect(5);

    }
    else if( currentKeyStates[ SDL_SCANCODE_SPACE ] &&  fastDownTime.getTime() )
    {
        io->playSoundEffect(4);
        fastDown();
    }


}

void Game::logic()
{

    if(!isPieceCreated)
    {
        getNewPiece();
        createNewPiece();
    }


    if( pieceDownSpeedTimer.getTime() )
        moveDown();

    countScore();


    if (board.checkTopLine()) //checking is top line empty
    {

        ptrSC->score = score;
        ptrSC ->level = level;
        ptrSC ->lines = numberOfDeletedLines;
        ptrSC ->sScore = sScore;
        ptrSC ->sLevel = sLevel;
        ptrSC ->sLines = sLines;
        ptrChanger ->setNext(GAME_OVER);

    }


    // << game go on
}


void Game::intToString()
{
    osScore << score;

    sScore = osScore.str();
    if (sScore.length() == 1 )
        sScore.insert(0, "00000");
    else if(sScore.length() == 2 )
        sScore.insert(0, "0000");
    else if(sScore.length() == 3 )
        sScore.insert(0, "000");
    else if(sScore.length() == 4 )
        sScore.insert(0, "00");
    else if(sScore.length() == 5 )
        sScore.insert(0, "0");

    osScore.str("");

    osScore << numberOfDeletedLines;
    sLines = osScore.str();
    if (sLines.length() == 1 )
        sLines.insert(0, "00");
    else if(sLines.length() == 2 )
        sLines.insert(0, "0");

    osScore.str("");

    osScore << level;
    sLevel = osScore.str();
    if(sLevel.length() == 1 )
        sLevel.insert(0, "0");

    osScore.str("");
}

void Game::render()
{
    io -> clearScreen();

    for(int i=0; i<sizeBoardY; i++)
        for(int j=0; j<sizeBoardX; j++)
        {
            ///drawBoard
            if (board.board[i][j] == pos_fill )
                io ->renderPiece(board.boardOfColors[i][j], positionBoardX + sizeBlock * j, positionBoardY + sizeBlock * i  );
        };

///draw pieces
    piece.drawPiece( kindOfPiece, kindOfRotation, piecePositionX, piecePositionY );


    drawNextPiece( kindOfPiece2, kindOfRotation2, 610, 300 );
    intToString();
///draw text

    io ->drawText(sScore, white, 575, 195, 28, 1, 194);
    io ->drawText(sLevel, white, 575, 493, 28, 1,  88);
    io ->drawText(sLines, white, 682, 493, 28, 1,  88);

    io -> refreshScreen();
}

