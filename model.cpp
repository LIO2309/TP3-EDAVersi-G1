/**
 * @brief Implements the Reversi game model
 * @author Marc S. Ressl
 * Luciano E. Colugnatti; Santiago A. Riverós; Leandro A. Yiu.
 * Estructuras de Datos y Algoritmos (25.03).
 * @copyright Copyright (c) 2023-2024
 */

#include "raylib.h"

#include "model.h"

void initModel(GameModel &model)
{
    model.gameOver = true;

    model.playerTime[0] = 0;
    model.playerTime[1] = 0;

    memset(model.board, PIECE_EMPTY, sizeof(model.board));
}

void startModel(GameModel &model)
{
    model.gameOver = false;

    model.currentPlayer = PLAYER_BLACK;

    model.playerTime[0] = 0;
    model.playerTime[1] = 0;
    model.turnTimer = GetTime();

    memset(model.board, PIECE_EMPTY, sizeof(model.board));
    model.board[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1] = PIECE_WHITE;
    model.board[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2] = PIECE_BLACK;
    model.board[BOARD_SIZE / 2][BOARD_SIZE / 2] = PIECE_WHITE;
    model.board[BOARD_SIZE / 2][BOARD_SIZE / 2 - 1] = PIECE_BLACK;
}

Player getCurrentPlayer(GameModel &model)
{
    return model.currentPlayer;
}

int getScore(GameModel &model, Player player)
{
    int score = 0;

    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (((model.board[y][x] == PIECE_WHITE) &&
                 (player == PLAYER_WHITE)) ||
                ((model.board[y][x] == PIECE_BLACK) &&
                 (player == PLAYER_BLACK)))
                score++;
        }

    return score;
}

double getTimer(GameModel &model, Player player)
{
    double turnTime = 0;

    if (!model.gameOver && (player == model.currentPlayer))
        turnTime = GetTime() - model.turnTimer;

    return model.playerTime[player] + turnTime;
}

Piece getBoardPiece(GameModel &model, Square square)
{
    return model.board[square.y][square.x];
}

void setBoardPiece(GameModel &model, Square square, Piece piece)
{
    model.board[square.y][square.x] = piece;
}

bool isSquareValid(Square square)
{
    return (square.x >= 0) &&
           (square.x < BOARD_SIZE) &&
           (square.y >= 0) &&
           (square.y < BOARD_SIZE);
}

void getValidMoves(GameModel &model, Moves &validMoves)
{
    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            Square move = {x, y};

            Piece currentPiece =
                (getCurrentPlayer(model) == PLAYER_WHITE)
                ? PIECE_WHITE
                : PIECE_BLACK;

            Piece oppositePiece =
                (getCurrentPlayer(model) == PLAYER_WHITE)
                ? PIECE_BLACK
                : PIECE_WHITE;

            if(getBoardPiece(model, move) == PIECE_EMPTY)    
            {
                bool f_current, f_empty;
                bool f_pushback = false;

                for(int i= x-1; i <= x+1 ;i++)
                {
                    for (int j = y - 1; j <= y+1; j++)
                    {
                        Square aux = {i , j};

                        if (isSquareValid(aux))
                        {
                            if (getBoardPiece(model, aux) == oppositePiece)
                            {
                                int difX = aux.x - move.x;
                                int difY = aux.y - move.y;
                                f_current = false;
                                f_empty = false;

                                while(isSquareValid(aux) && (!f_current) && (!f_empty))
                                {
                                    aux.x += difX;
                                    aux.y += difY;

                                    Piece auxPiece = getBoardPiece(model, aux);

                                    if(auxPiece == currentPiece)
                                    {
                                        f_current = true;
                                        f_pushback = true;
                                    }
                                    else if(auxPiece == PIECE_EMPTY)
                                        f_empty = true;
                                } 
                            }
                        }
                    }
                }
                if(f_pushback)
                    validMoves.push_back(move);
            }
        }
}

bool playMove(GameModel &model, Square move)
{
    // Set game piece
    Piece piece =
        (getCurrentPlayer(model) == PLAYER_WHITE)
            ? PIECE_WHITE
            : PIECE_BLACK;

    setBoardPiece(model, move, piece);
    
    operatePiece(model,move,IN_GAME);

    // Update timer
    double currentTime = GetTime();
    model.playerTime[model.currentPlayer] += currentTime - model.turnTimer;
    model.turnTimer = currentTime;

    // Swap player
    model.currentPlayer =
        (model.currentPlayer == PLAYER_WHITE)
            ? PLAYER_BLACK
            : PLAYER_WHITE;

    // Game over?
    Moves validMoves;
    getValidMoves(model, validMoves);

    if (validMoves.size() == 0)
        model.gameOver = true;

    return true;
}

int operatePiece(GameModel &model, Square move, Mode mode)
{
    Piece piece =
        (getCurrentPlayer(model) == PLAYER_WHITE)
            ? PIECE_WHITE
            : PIECE_BLACK;

    Piece oppositePiece =
                (getCurrentPlayer(model) == PLAYER_WHITE)
                ? PIECE_BLACK
                : PIECE_WHITE;

    int finalGainsCount = 0;

    for(int i= move.x-1; i <= move.x+1 ;i++)
    {
        for (int j = move.y-1; j <= move.y+1; j++)
        {
            Square neighbourPos = {i , j};
            if (isSquareValid(neighbourPos))
            {
                if (getBoardPiece(model, neighbourPos) == oppositePiece)
                { 
                    int difX = neighbourPos.x - move.x;
                    int difY = neighbourPos.y - move.y;

                    Square linearMove = neighbourPos;
                    int gainsCount = 0;

                    while(isSquareValid(linearMove) && (getBoardPiece(model, linearMove) == oppositePiece))
                    {
                        linearMove.x += difX;
                        linearMove.y += difY;
                        gainsCount++; 
                    }
                    if(!isSquareValid(linearMove) || getBoardPiece(model, linearMove) == PIECE_EMPTY)
                    {
                        gainsCount = 0; 
                    }

                    if((gainsCount != 0)&&(mode == IN_GAME))
                    {
                        while(gainsCount > 0)
                        {
                            linearMove.x -= difX;
                            linearMove.y -= difY;
                            setBoardPiece(model, linearMove, piece);
                            gainsCount--;
                        }
                    }
                    else if(mode == AI)
                    {
                        finalGainsCount += gainsCount;
                    }
                }
            }
        }
    }

    return finalGainsCount;
}