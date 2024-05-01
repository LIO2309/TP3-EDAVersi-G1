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
#include "view.h"

#define DEPTH 15
#define MAX_NODES 4

Square getBestMove(GameModel &model)
{  
    treeNode currentBoard;
    Moves validMoves;
    int index;
    recursiveParams recParams;
    recParams.model = model;
    recParams.maxNodes = MAX_NODES;
    
    getValidMoves(model, validMoves);
    if (validMoves.size() > 1)
    {
        index = miniMax(model, currentBoard, recParams, DEPTH, MAX, INT_MIN, INT_MAX, true);
    }
    else
    {
        index = 0;
    }
    return validMoves[index];
}

int miniMax(GameModel &model, treeNode node, recursiveParams &recParams, int depth, bool maxOrMin, int alpha, int beta, bool isFirstIteration)
{
    //drawView(recParams.model);                ver como implementar este llamado a la funcion sin que se rompa la visualizacion del juego
    int gains, maxGains, minGains;
    Moves validMoves;
    getValidMoves(model, validMoves);
    node.validMoves = validMoves.size();
    recParams.maxNodes--;


    if((depth == 0) || (node.validMoves == 0) || (recParams.maxNodes == 0))          
    {
        gains = aiPieceBalance(model);

        if(((depth == DEPTH - 1) && (node.validMoves == 0)) 
            || ((depth == DEPTH - 1) && (recParams.maxNodes == 0)))
        {
            recParams.secondLevelGains.push_back(gains);
        }
        
        return gains;
    }

    GameModel auxModel = model;

    if(maxOrMin)
    {    
        maxGains = INT_MIN;
        for (int i = 0; i < validMoves.size();i++)
        {
            if (recParams.maxNodes > 0)
            {
                treeNode* childNode = new treeNode;
                node.nextBoards.push_back(childNode);
                
                playMove(auxModel, validMoves[i]);   //hace la jugada de la IA y te cambia el turno al humano
                //recParams.model.turnTimer = auxModel.turnTimer;
                gains = miniMax(auxModel, *node.nextBoards[0], recParams, depth - 1, !maxOrMin, alpha, beta, false);

                //Visit postorder
                auxModel = model;
                delete node.nextBoards[0];
                node.nextBoards.erase(node.nextBoards.begin()); 

                maxGains = max(maxGains, gains);
                alpha = max(alpha, gains);
                if (beta <= alpha)
                    break;
            }
        }

        if(isFirstIteration)
        {
            int index = 0;
            while(recParams.secondLevelGains[index] != maxGains)
            {
                index++;
            }
            maxGains = index;
        }
        return maxGains;
    }
    else
    {
        minGains = INT_MAX;
        for (int i = 0; i < validMoves.size();i++)
        {
            if (recParams.maxNodes > 0)
            {
                treeNode* childNode = new treeNode;
                node.nextBoards.push_back(childNode);
                
                playMove(auxModel, validMoves[i]);   //hace la jugada del humano y te cambia el turno a la IA
                //recParams.model.turnTimer = auxModel.turnTimer;
                gains = miniMax(auxModel, *node.nextBoards[0], recParams, depth - 1, !maxOrMin, alpha, beta, false);

                //Visit postorder
                auxModel = model;
                delete node.nextBoards[0];
                node.nextBoards.erase(node.nextBoards.begin());

                minGains = min(minGains, gains);
                beta = min(beta, gains);
                if (beta <= alpha)
                    break;
            }
        }

        if(depth == DEPTH - 1)
            recParams.secondLevelGains.push_back(minGains);
        
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

