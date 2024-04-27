/**
 * @brief Implements the Reversi game AI
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2023-2024
 */

#ifndef AI_H
#define AI_H

#include "model.h"

using namespace std;

/**
 * @brief Returns the best move for a certain position.
 *
 * @return The best move.
 */

class treeNode
{
	public:
		int gains;
		int validMoves;
		vector<treeNode*> nextBoards;
};

Square getBestMove(GameModel &model);

#endif
