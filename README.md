# EDAversi

## Integrantes del grupo y contribución al trabajo de cada integrante

* Colugnatti, Luciano E.: 
* Riverós, Santiago A.:
* Yiu, Leandro A.:

[completar]

## Parte 1: Generación de movimientos válidos y algoritmo de jugada

Para la generación de movimientos válidos se implementó *getValidMoves()*. Ésta analiza el entorno de cada 
posición del tablero, identifica la posición de las piezas del oponente que tiene en sus cercanías, y avanza 
en la dirección necesaria (dentro de las ocho posibles) hasta encontrar una pieza propia, un casillero vacío, 
o el fin del tablero. Luego de esta validación, se guardan las coordenadas de los movimientos válidos y se cargan 
en el vector validMoves con el que se llamó a la función.

Para el algoritmo de jugada, se implementó *playMove()*. Ésta recibe un movimiento (coordenada) y verifica y valida 
las condiciones de su entorno. Luego, se "mueve" en cada dirección necesaria incrementando el contador *paintCount*, 
que almacena la cantidad de piezas del oponente que deben ser "pintadas" regresando a la coordenada escogida.

Para probar el correcto funcionamiento de estos algoritmos, se realizaron las siguientes pruebas:
* En distintas jugadas de prueba se verificó analíticamente paso por paso que el programa habilitara sólo las posiciones 
válidas, y, luego de la selección de una posición, pintara las piezas correspondientes a la jugada escogida.
* Se realizaron jugadas "en espejo" en nuestro tablero y en un juego de reversi online [https://playpager.com/othello-reversi/]
para chequear que, ante una misma jugada, el tablero se modifique de igual manera. El juego online fue utilizado en el modo 
"persona vs. persona" para poder cargar manualmente los movimientos de la IA de nuestro programa.
* Se probaron jugadas límite, como los movimientos cerca de los límites del tablero o de casilleros vacíos para verificar 
la validación de casos de los algoritmos.


## Parte 2: Implementación del motor de IA

A la hora de implementar el algoritmo minimax se tomaron las siguientes consideraciones:
* Se creó la clase *RecursiveParams* para el pasaje de estados y parámetros de la recursión, evitando pasar tantas cosas 
en la llamada recursiva. Ésta contiene un *vector* de *int* (*secondLevelGains*) para almacenar las ganancias de cada nodo 
hijo, un *int*  para accederlo (*index*), y un *int* con el máximo de nodos (*maxNodes*).
* Se implementó el flag *isFirstIteration*, que permite, luego de la recursión, al llegar al segundo nivel del árbol, acceder 
a los parámetros recursivos y devolver la mejor jugada para realizar.
* Se controlaron los turnos en los cuales la ganancia se debe maximizar o minimizar según juegue la IA o su oponente, 
accediendo a distintos ciclos según el estado de la variable booleana *maxOrMin*.
* Se modularizó el cálculo de las ganancias netas que implica cada jugada en la función *aiPieceBalanceWithWeight*, que es 
llamada por *minimax*.


## Parte 3: Poda del árbol

El algoritmo minimax posee una complejidad computacional de O(b^d), siendo b un factor de tablero constante relacionado con 
su tamaño, y d la profundidad de búsqueda [https://zzutk.github.io/docs/reports/2014.04%20-%20Searching%20Algorithms%20in%20Playing%20Othello.pdf].
Como Reversi puede llegar a tener hasta 60 movimientos en una partida [https://sites.google.com/site/elreversista/preguntas-y-curiosidades-sobre-el-reversi], 
el factor exponencial d alcanzaría este valor, haciendo que el tiempo de ejecución sea excesivamente alto.
Frente a esto, se tomaron las siguientes decisiones:
* Se agregó la variable *int* *depht*, que determina la profundidad máxima (en niveles) hasta donde se analizará el árbol de juego.
* Se implementó la **poda alpha-beta**, que evalúa las etiquetas alpha y beta de cada nodo intermedio y elimina ramas del árbol cuyo análisis es innecesario, ahorrando recursos computacionales y tiempo.


## Documentación adicional

* Para implementación de la poda alpha-beta en el algoritmo minimax se estudió el siguiente video: 
[https://www.youtube.com/watch?v=l-hh51ncgDI&ab_channel=SebastianLague].

* La elección de la altura máxima de búsqueda en el árbol fue seleccionada considerando el siguiente gráfico presente en un 
*paper* de la Universidad de Washington [https://zzutk.github.io/docs/reports/2014.04%20-%20Searching%20Algorithms%20in%20Playing%20Othello.pdf]:

![Pesos para cada posición en el tablero de Reversi](/TP3-EDAVersi-G1/Images/Weights__table.png)


## Bonus points

* Como se indicó anteriormente, se implementó la poda alpha-beta.
* Para mejorar el desempeño de la IA, agregó un criterio de decisión basado en una tabla con puntajes fijos para cada posición del tablero, ponderando las posiciones que aseguran una mejor jugada (como las esquinas, por ejemplo). Se estudiaron y compararon distintas tablas de distintas publicaciones de trabajos similares en Internet, y finalmente se seleccionó la siguiente