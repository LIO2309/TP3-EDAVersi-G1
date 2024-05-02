# EDAversi

## Integrantes del grupo y contribución al trabajo de cada integrante

* **Colugnatti, Luciano E.**: Generación de movimientos válidos y algoritmo de jugada, implementación del motor de IA, poda
del árbol, bonus points y pruebas.
* **Riverós, Santiago A.**: Generación de movimientos válidos y algoritmo de jugada, investigación de profundidades de búsqueda, 
complejidad computacional y tablas pesadas, pruebas y documentación.
* **Yiu, Leandro A.**: Generación de movimientos válidos y algoritmo de jugada, implementación del motor de IA, poda
del árbol, bonus points y pruebas.


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

A la hora de implementar el algoritmo *minimax* se tomaron las siguientes consideraciones:
* Se creó la clase *RecursiveParams* para el pasaje de estados y parámetros de la recursión, evitando pasar tantas cosas 
en la llamada recursiva. Ésta contiene un *vector* de *int* (*secondLevelGains*) para almacenar las ganancias de cada nodo 
hijo, un *int*  para accederlo (*index*), y un *int* con el máximo de nodos (*maxNodes*).
* Se implementó el flag *isFirstIteration*, que permite, luego de la recursión, al llegar al segundo nivel del árbol, acceder 
a los parámetros recursivos y devolver la mejor jugada para realizar.
* Se controlaron los turnos en los cuales la ganancia se debe maximizar o minimizar según juegue la IA o su oponente, 
accediendo a distintos ciclos según el estado de la variable booleana *maxOrMin*.
* Se modularizó el cálculo de las ganancias netas que implica cada jugada en las funciones *aiPieceBalance* o 
*aiPieceBalanceWithWeight* (según corresponda), que son llamadas por *minimax*.


## Parte 3: Poda del árbol

El algoritmo *minimax* posee una complejidad computacional de O(b^d), siendo b un factor de tablero constante relacionado con 
su tamaño, y d la profundidad de búsqueda 
[https://zzutk.github.io/docs/reports/2014.04%20-%20Searching%20Algorithms%20in%20Playing%20Othello.pdf].
Como Reversi puede llegar a tener hasta 60 movimientos en una partida 
[https://sites.google.com/site/elreversista/preguntas-y-curiosidades-sobre-el-reversi], 
el factor exponencial d alcanzaría este valor, haciendo que el tiempo de ejecución sea excesivamente alto.
Frente a esto, se tomaron las siguientes decisiones:
* Se agregó la variable *int* *depth*, que determina la profundidad máxima (en niveles) hasta donde se analizará el árbol 
de juego.
* Se implementó la **poda alpha-beta**, que evalúa las etiquetas alpha y beta de cada nodo intermedio y elimina ramas del 
árbol cuyo análisis es innecesario, ahorrando recursos computacionales y tiempo.
* Para mejorar la complejidad computacional, se limitó la cantidad de nodos a analizar con el *#define* *MAX_NODES*.
Se determinó un límite de 50000 nodos de manera heurística.


## Documentación adicional

* Para implementación de la poda alpha-beta en el algoritmo minimax, se estudió el siguiente video: 
[https://www.youtube.com/watch?v=l-hh51ncgDI&ab_channel=SebastianLague].

* La altura máxima de búsqueda en el árbol se reguló considerando el siguiente gráfico presente en un 
*paper* de *Oregon State University*:

![Tiempo computacional para distintas profundidades de búsqueda](/Images/Computation_times.png)
[https://zzutk.github.io/docs/reports/2014.04%20-%20Searching%20Algorithms%20in%20Playing%20Othello.pdf]

## Bonus points

* Como se indicó anteriormente, se implementó la poda alpha-beta.

* Para mejorar el desempeño de la IA, agregó un criterio de decisión basado en una tabla con puntajes fijos para cada posición
del tablero, ponderando las posiciones que aseguran una mejor jugada (como las esquinas, por ejemplo). Se estudiaron y 
compararon distintas tablas de distintas publicaciones de trabajos similares en Internet, y finalmente se seleccionó, de
un *paper* de *University of Washington*, la siguiente:

![Pesos para cada posición en el tablero de Reversi](/Images/Weights_table.png)
[https://courses.cs.washington.edu/courses/cse573/04au/Project/mini1/RUSSIA/Final_Paper.pdf]

Se comparó el desempeño del algoritmo con los dos tipos de evaluación de jugadas implementados: 
a) Diferencia neta entre las potenciales piezas perdidas y ganadas en cada jugada.
b) Diferencia neta entre las potenciales piezas perdidas y ganadas en cada jugada con la adición de un factor de peso propio
de cada posición del tablero.

Con una cantidad de nodos constante (50000), y probando todas las profundidades de búsqueda desde 5 hasta 15 (siempre haciendo
coincidir la profundidad de un método con la del otro), se realizaron 22 pruebas enfrentado a ambos métodos de evaluación.
Los resultados fueron contundentes: el 90,9% de las partidas fueron ganadas por la IA que empleaba el método b (con tabla
de pesos). Así, se seleccionó este método.
Sin embargo, se puede seleccionar el método de evaluación de la IA definiendo en *ai.cpp* la *DIFFERENCE* para el primer caso, 
y *WEIGHTED* para el segundo.


