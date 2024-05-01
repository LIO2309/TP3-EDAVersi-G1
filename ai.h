/**
 * @brief Implements the Reversi game AI
 * @author Marc S. Ressl
 * Luciano E. Colugnatti; Santiago A. River�s; Leandro A. Yiu.
 * Estructuras de Datos y Algoritmos (25.03).
 * @copyright Copyright (c) 2023-2024
 */

#ifndef AI_H
#define AI_H

#include "model.h"

#define MIN 0
#define MAX 1

using namespace std;

typedef struct
{
	std::vector<int> secondLevelGains;
	GameModel model;						//para implementar el draw view
	int maxNodes;
}recursiveParams;

class treeNode
{
	public:
		int validMoves;
		vector<treeNode*> nextBoards;
};

/**
 * @brief Returns the best move for a certain position.
 *
 * @return The best move.
 */
Square getBestMove(GameModel &model);

/**
 * @brief Implements the minimax algorithm up to a given tree depth, on a copy of the board. 
 *	      Applies alpha-beta pruning.

 * @param model	The game model.
 * @param node	The current node.
 * @param recparams	For passing recursive parameters.
 * @param depht	The depth up to which the tree is analyzed.
 * @param maxOrMin	Indicates whether the gains should be maximized or minimized.
 * @param alpha	Label for alpha-beta pruning.
 * @param beta	Label for alpha-beta pruning.
 * @param isFirstIteration	True if it is the first iteration, false otherwise.
 * @return The amount of pieces won by the AI.
 */
int miniMax(GameModel &model, treeNode node, recursiveParams &recParams, int depth, bool maxOrMin, int alpha, int beta, bool isFirstIteration);
/**
 * @brief Calculates the difference between AI's score and opponent's score.
 *
 * @return The difference between AI's score and opponent's score.
 */
int aiPieceBalance(GameModel &model);

#endif
