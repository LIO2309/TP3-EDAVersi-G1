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

 //#define DIFFERENCE
#define WEIGHTED

#define DEPTH 10
#define MAX_NODES 50000

#define MIN 0
#define MAX 1

#if MAX_NODES < 2
#error "Se está definiendo un MAX_NODES MENOR A 2"
#endif
Square getBestMove(GameModel& model)
{
	int index;
	treeNode currentBoard;
	Moves validMoves;
	RecursiveParams recParams;
	recParams.maxNodes = MAX_NODES;

	getValidMoves(model, validMoves);
	if (validMoves.size() > 1)
	{
		miniMax(model, currentBoard, recParams, DEPTH, MAX, INT_MIN, INT_MAX, true);
		index = recParams.index;
	}
	else
		index = 0;

	return validMoves[index];
}

int miniMax(GameModel& model, treeNode node, RecursiveParams& recParams, int depth, bool maxOrMin, int alpha, int beta, bool isFirstIteration)
{
	int gains, maxGains, minGains;
	Moves validMoves;
	getValidMoves(model, validMoves);
	node.validMoves = validMoves.size();
	recParams.maxNodes--;

	if ((depth == 0) || (node.validMoves == 0) || (recParams.maxNodes == 0))
	{
#ifdef DIFFERENCE
		gains = aiPieceBalance(model);
#endif
#ifdef WEIGHTED
		gains = aiPieceBalanceWithWeight(model);
#endif

		if (((depth == DEPTH - 1) && (node.validMoves == 0))
			|| ((depth == DEPTH - 1) && (recParams.maxNodes == 0)))
		{
			recParams.secondLevelGains.push_back(gains);
		}

		return gains;
	}

	GameModel auxModel = model;

	if (maxOrMin)
	{
		maxGains = INT_MIN;
		for (int i = 0; i < validMoves.size(); i++)
		{
			if (recParams.maxNodes > 0)
			{
				treeNode* childNode = new treeNode;
				node.nextBoards.push_back(childNode);
				playMove(auxModel, validMoves[i]);

				gains = miniMax(auxModel, *node.nextBoards[0], recParams, depth - 1, !maxOrMin, alpha, beta, false);

				auxModel = model;
				delete node.nextBoards[0];
				node.nextBoards.erase(node.nextBoards.begin());
				maxGains = max(maxGains, gains);
				alpha = max(alpha, gains);
				if (beta <= alpha)
					break;
			}
		}
		if (isFirstIteration)
		{
			int index = 0;
			while (recParams.secondLevelGains[index] != maxGains)
				index++;
			recParams.index = index;
		}
		return maxGains;
	}
	else
	{
		minGains = INT_MAX;
		for (int i = 0; i < validMoves.size(); i++)
		{
			if (recParams.maxNodes > 0)
			{
				treeNode* childNode = new treeNode;
				node.nextBoards.push_back(childNode);

				playMove(auxModel, validMoves[i]);

				gains = miniMax(auxModel, *node.nextBoards[0], recParams, depth - 1, !maxOrMin, alpha, beta, false);

				auxModel = model;
				delete node.nextBoards[0];
				node.nextBoards.erase(node.nextBoards.begin());
				minGains = min(minGains, gains);
				beta = min(beta, gains);
				if (beta <= alpha)
					break;
			}
		}

		if (depth == DEPTH - 1)
			recParams.secondLevelGains.push_back(minGains);
		return minGains;
	}
}

int aiPieceBalance(GameModel& model)
{
	int aiCount = 0;
	Piece currentPiece;
	Square position;
	Piece currentAIPiece = (model.humanPlayer == PLAYER_WHITE)
		? PIECE_BLACK
		: PIECE_WHITE;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			position.x = i;
			position.y = j;
			currentPiece = getBoardPiece(model, position);
			if (currentPiece != PIECE_EMPTY)
			{
				if (currentPiece == currentAIPiece)
					aiCount++;
				else
					aiCount--;
			}
		}
	}
	return aiCount;
}

int aiPieceBalanceWithWeight(GameModel& model)
{
	int aiCount = 0;

	int weightMat[8][8] = {
		{ 4, -3, 2, 2, 2, 2, -3, 4 },
		{ -3, -4, -1, -1, -1, -1, -4, -3 },
		{ 2, -1, 1, 0, 0, 1, -1, 2 },
		{ 2, -1, 0, 1, 1, 0, -1, 2 },
		{ 2, -1, 0, 1, 1, 0, -1, 2 },
		{ 2, -1, 1, 0, 0, 1, -1, 2 },
		{ -3, -4, -1, -1, -1, -1, -4, -3 },
		{ 4, -3, 2, 2, 2, 2, -3, 4 },
	};

	Piece currentPiece;
	Square position;
	Piece currentAIPiece = (model.humanPlayer == PLAYER_WHITE)
		? PIECE_BLACK
		: PIECE_WHITE;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			position.x = i;
			position.y = j;
			currentPiece = getBoardPiece(model, position);
			if (currentPiece != PIECE_EMPTY)
			{
				if (currentPiece == currentAIPiece)
					aiCount += weightMat[i][j];
				else
					aiCount -= weightMat[i][j];
			}
		}
	}
	return aiCount;
}

