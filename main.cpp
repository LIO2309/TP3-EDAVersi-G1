/**
 * @brief Reversi game
 * @author Marc S. Ressl
 * Luciano E. Colugnatti; Santiago A. Riverós; Leandro A. Yiu.
 * Estructuras de Datos y Algoritmos (25.03).
 * @copyright Copyright (c) 2023-2024
 */

#include "model.h"
#include "view.h"
#include "controller.h"

int main()
{
    GameModel model;

    initModel(model);
    initView();

    while (updateView(model))
        ;

    freeView();
}
