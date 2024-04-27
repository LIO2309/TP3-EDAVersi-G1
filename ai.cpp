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

Square getBestMove(GameModel &model)
{
    //////////////////////////////////////////////////////
    // +++ TEST
    // Returns a random valid move...
    
    /*Moves validMoves;
    getValidMoves(model, validMoves);

    int index = rand() % validMoves.size();
    return validMoves[index];*/
    // --- TEST
    ////////////////////////////////////////////////////

    treeNode currentBoard;

    GameModel auxModel = model;

    //minimax(auxModel,currentBoard, 7, MAX, INT_MIN, INT_MAX);

    currentBoard.validMoves = validMoves.size();    
    int index
    return validMoves[index];    

}

void analyzeMove(GameModel& model, Square move)
{
    int gains = operatePiece(model, move, AI);

}

int miniMax(GameModel &auxModel, treeNode node, int depth, bool maxOrMin, int alpha, int beta)
{
    int gains, maxGains, minGains;
    
    

    if((depth == 0) || (node.validMoves = 0))          //recordar actualizar en algun lado el campo validmoves del nodo
    {
        return node.gains;
    }

    //Visit preorder: avanzo en el tablero aux 1 paso
    Moves validMoves;
    getValidMoves(auxModel, validMoves);
    node.validMoves = validMoves.size();

    //Validar con maxormin qué valid mves hay q analizar, si son los del humano o la
    
    //hay q modificar manualmente auxmodel.currentplayer para levantar los validmoves correctos

    //LOS CAMBIOS SÍ SE VAN A REALIZAR EN EL TABLERO AUX. ENTONCES HAY Q AVILITAR QUE PINTE Y HACER UN 
    //SWITCH PARA QUE DESHAGA LOS CAMBIOS (PINTAR LOS Q HABIA PINTADO CON EL COLOR DE LA FICHA OPUESTA)


    for (int i = 0; i < node.validMoves; i++)
    {
        treeNode* childNode = new treeNode;
        node.nextBoards.push_back(childNode);
    }
    

    if(maxOrMin)
    {
        maxGains = INT_MIN;
        for(auto childNode : node.nextBoards)
        {
            gains = miniMax(node, depth - 1, !maxOrMin, alpha, beta);
            maxGains = max(maxGains, gains);
            alpha = max(alpha, gains);
            if (beta <= alpha)
                break;
            return maxGains;
        }
        //Visit postorder: revierto los cambios en el tablero aux a un paso atrás
    }
    else
    {
        minGains = INT_MAX;
        for(auto childNode : node.nextBoards)
        {
            gains = miniMax(node, depth - 1, !maxOrMin, alpha, beta);
            minGains = min(minGains, gains);
            beta = min(beta, gains);
            if(beta <= alpha)
                break;
            return minGains;
        }
        //Visit postorder
    }   
}

