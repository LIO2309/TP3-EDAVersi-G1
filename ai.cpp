/**
 * @brief Implements the Reversi game AI
 * @author Marc S. Ressl
 * Luciano E. Colugnatti; Santiago A. Riverós; Leandro A. Yiu.
 * Estructuras de Datos y Algoritmos (25.03).
 * @copyright Copyright (c) 2023-2024
 */

#include <cstdlib>
#include <limits.h>

#include "ai.h"
#include "controller.h"

#define DEPTH 7

Square getBestMove(GameModel &model)
{
    //////////////////////////////////////////////////////
    // +++ TEST
    // Returns a random valid move...
    /*
    Moves validMoves;
    getValidMoves(model, validMoves);

    int index = rand() % validMoves.size();
    return validMoves[index];
    */
    // --- TEST
    ////////////////////////////////////////////////////
    
    treeNode currentBoard;
    Moves validMoves;
    getValidMoves(model, validMoves);

    int index = miniMax(model,currentBoard, DEPTH, MAX, INT_MIN, INT_MAX, true);
    
    return validMoves[index];
    
}

int miniMax(GameModel &model, treeNode node, int depth, bool maxOrMin, int alpha, int beta, bool isFirstIteration)
{
    int gains, maxGains, minGains;
    Moves validMoves;
    getValidMoves(model, validMoves);
    node.validMoves = validMoves.size();
    static std::vector<int> secondLevelGains; 


    if((depth == 0) || (node.validMoves == 0))          //recordar actualizar en algun lado el campo validmoves del nodo
    {
        return aiPieceBalance(model);
    }

    GameModel auxModel = model;
    
    for (int i = 0; i < node.validMoves; i++)
    {
        treeNode* childNode = new treeNode;
        node.nextBoards.push_back(childNode);
    }

    if(maxOrMin)
    {
        int i = 0;
        maxGains = INT_MIN;
        for(auto childNode : node.nextBoards)
        {
            playMove(auxModel, validMoves[i++]);   //hace la jugada de la IA y te cambia el turno al humano
            gains = miniMax(auxModel,*childNode, depth - 1, !maxOrMin, alpha, beta, false);

            //Visit postorder
            auxModel = model;
            delete childNode;
            
            maxGains = max(maxGains, gains);
            alpha = max(alpha, gains);
            if (beta <= alpha)
                break;
        }

        if(isFirstIteration)
        {
            int index = 0;
            while(secondLevelGains[index] != maxGains)
            {
                index++;
            }
            maxGains = index;

            secondLevelGains = std::vector<int>();
        }
        return maxGains;
    }
    else
    {
        int i = 0;
        minGains = INT_MAX;
        for(auto childNode : node.nextBoards)
        {
            playMove(auxModel, validMoves[i++]);   //hace la jugada del humano y te cambia el turno a la IA
            gains = miniMax(auxModel, *childNode, depth - 1, !maxOrMin, alpha, beta, false);

            //Visit postorder
            auxModel = model;
            delete childNode;
            
            minGains = min(minGains, gains);
            beta = min(beta, gains);
            if(beta <= alpha)
                break;
        }

        if(depth == DEPTH - 1)
        {
            secondLevelGains.push_back(minGains);
        }
        return minGains;

    }   
}

int aiPieceBalance(GameModel &model)
{
    int aiCount = 0;
    Piece currentPiece;
    Square position;

    Piece currentAIPiece = (model.humanPlayer == PLAYER_WHITE)
                            ? PIECE_BLACK
                            : PIECE_WHITE;

    for(int i=0 ; i < BOARD_SIZE; i++)
    {
        for(int j=0 ; j < BOARD_SIZE; j++)
        {
            position.x = i;
            position.y = j;
            currentPiece = getBoardPiece(model, position);
            if (currentPiece != PIECE_EMPTY)
            {
                if(currentPiece == currentAIPiece)
                {
                    aiCount++;
                }
                else
                {
                    aiCount--;
                }
            }
        }
    }
    return aiCount;
}
