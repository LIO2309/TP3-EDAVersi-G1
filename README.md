# EDAversi

## Integrantes del grupo y contribución al trabajo de cada integrante

* Colugnatti, Luciano E.: 
* Riverós, Santiago A.:
* Yiu, Leandro A.:

[completar]

## Parte 1: Generación de movimientos válidos y algoritmo de jugada

*getValidMoves()* analiza el entorno de cada posición del tablero. Identifica la posición de las piezas del oponente que tiene en sus cercanías, y avanza en la dirección necesaria (dentro de las ocho posibles) hasta encontrar una pieza propia, un casillero vacío, o el fin del tablero. Luego de esta validación, se guardan las coordenadas de los movimientos válidos y se cargan en el vector validMoves con el que se llamó a la función.

El algoritmo de jugada se implementa con , //COMPLETAR

Para probar el correcto funcionamiento de estos algoritmos, se realizaron las siguientes pruebas:
* En distintas jugadas de prueba se verificó analíticamente paso por paso que el programa habilitara sólo las posiciones válidas, y, luego de la selección de una posición, pintara las piezas correspondientes a la jugada escogida.
* Se realizaron jugadas "en espejo" en nuestro tablero y en un juego de reversi online [https://playpager.com/othello-reversi/] para chequear que, ante una misma jugada, el tablero se modifique de igual manera. El juego online fue utilizado en el modo "persona vs. persona" para poder cargar manualmente los movimientos de la IA de nuestro programa.
* Se probaron jugadas límite, como los movimientos cerca de los límites del tablero o de casilleros vacíos para verificar la validación de casos de los algoritmos.


## Parte 2: Implementación del motor de IA

[Enumera aquí las consideraciones que tomaste a la hora de implementar el algoritmo minimax.]

## Parte 3: Poda del árbol

[Justifica por qué el algoritmo minimax de la parte anterior no se completa. Consejo: determina la complejidad computacional.]

## Documentación adicional

[Aquí.]

## Bonus points

[Aquí.]