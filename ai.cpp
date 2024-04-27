/**
 * @brief Implements the Reversi game AI
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2023-2024
 */

#include <cstdlib>

#include "ai.h"
#include "controller.h"

Square getBestMove(GameModel &model)
{
     // +++ TEST
    // Returns a random valid move...
    Moves validMoves;
    getValidMoves(model, validMoves);

    int bestMoveIndex;

    GameModel auxModel = model;

    


    treeNode currentBoard;
    currentBoard.validMoves = validMoves.size();



        
        
    //rand() % validMoves.size();
    return validMoves[bestMoveIndex];
    // --- TEST
}
