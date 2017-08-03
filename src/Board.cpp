#include "../include/Board.h"


Board::Board(Piece *tPiece)
: piece(tPiece)
{
    clearBoard();
}

void Board::clearBoard()
{
    for(int i=0; i<sizeBoardY; i++)
    {
        for(int j=0; j<sizeBoardX; j++)
        {
            board[i][j] = pos_empty;
            boardOfColors[i][j] = 8;
        }
    }
}//<---------Board::clearBoard()-------------------------------


void Board::putPieceInTheBoard(int numberOfPiece, int numberOfRotation, int posX, int posY)
{
    int x = (posX - positionBoardX)/sizeBlock;
    int y = (posY - positionBoardY)/sizeBlock;

    for (int i=0; i<5; i++)
        for(int j=0; j<5; j++)
        {
            if( piece->getPieceType(numberOfPiece, numberOfRotation, i, j) != 0)
            {
                board[i+y][j+x] = pos_fill;
                boardOfColors[i+y][j+x] = numberOfPiece;
            }
        }

}//<-------------------------putPieceInTheBoard()---------------------------------------------------



void Board::copyToDown(int line)
{
    for (int i=line; i>0; i--)
        for(int j=0; j<sizeBoardX; j++)
        {
            board[i][j] = board[i-1][j];
            boardOfColors[i][j] =  boardOfColors[i-1][j];
        }

}//<-------------------copyToDown()----------------------------

int  Board::checkLine()
{
    int howMuchLines = 0;

    for (int i=0; i<sizeBoardY; i++)
        for(int j=0; j<sizeBoardX; j++)
        {
            if ( board[i][j] != pos_fill )
                break;
            else if (board[i][j] == pos_fill && j == sizeBoardX-1)
            {
                howMuchLines++;
                drawDeletingAnimation(i);
                copyToDown(i);
            }
        }
       if(howMuchLines > 0 && howMuchLines < 4)
           io->playSoundEffect(3);
        else if (howMuchLines == 4)
           io->playSoundEffect(6);


    return howMuchLines;
}//<---------------------------checkLine()------------------------------------

bool Board::checkTopLine()
{
    for(int i=0; i<sizeBoardX; i++)
    {
        if ( board[3][i] == pos_fill )
            return true;
    }
    return false;
}//<---------------checkTopLine()-----------------------------------------------


void Board::putOneBlockInTheBoard(int x, int y, int color)
{

            board[y][x] = pos_fill;
            boardOfColors[y][x] = color;

}//<---------Board::putOneBlockInTheBoard()-------------------------------

void Board::drawDeletingAnimation(int y)
{
    int a=-1;

    for (int k=0; k<5; k++)
    {

    for(int i=0; i<10; i++)
    {
        boardOfColors[y][i] = 8+a;
    }
               ///drawBoard
        for(int j=0; j<sizeBoardX; j++)
        {
                io ->renderPiece(boardOfColors[y][j], positionBoardX + sizeBlock * j, positionBoardY + sizeBlock * y  );
        };
        io->refreshScreen();

        SDL_Delay(20);

        a = -a;

    }


}//<--------------Board::drawDeletingAnimation(int y)--------------------------------------
