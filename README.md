# Matematica Discreta II (Famaf 2023)

## Integrantes 
	- Nacho Cuevas
	- Tomas Marmay 

## Grafos

En este proyecto se va a estar trabajando sobre procesamiento y algoritmos en grafos en el lenguaje de C. 
Basicamente se basa en dos partes. La primera parte se trata sobre procesar un grafo dado en formato DIMACS (con leve modificaciones) y construir funciones basicas.
Y la segunda parte se trata sobre ...


### Primera parte

Debido a que los nombres de los vertices pueden ser cualquier numero entero entre 0 y 2<sup>32</sup> decidimos usar una funcion de hash para "mapear" cada nodo i con un nuevo nombre j:
$$
\begin{align}
has(i) = j\\
\end{align}
$$
para despues manejarse internamente con los nuevos nombres.
La parte mas costosa en cuanto a complejidad es en poder mapear los nodos con un nuevo nombre. Dada nuestra implementacion sabemos que nuestro algoritmo es muy eficiente para los casos en los que los nodos de entrada no son multiplos de la cantidad de `vertices`. Y nuestro peor caso sucede cuendo lo anterior pasa ya que se incrementa el numero de coaliciones y es costoso resolverlas.

#### Archivos

- `APIG23.h` : Prototipo de funciones sobre el grafo
- `APIG23.c` : Implementacion de procesamiento de grafo y funciones
- `EstructuraGrafo23.h` : Estructura interna del grafo
- `rbt.h` : Prototipo de funciones de red-black-tree
  - Se encargar de resolver problema de coaliciones
- `rbt.c` : Implementacion de red-black-tree
- `vector.h` : Estructura de vector y funcions
- `vector.c` : Implementacion de vector y funciones
- `Makefile` : Para simplificar la compilacion del proyecto
  
#### Tiempos de referencia

Nuestro algoritmo tienen los siguientes tiempos en peor y mejor caso, hablando sobre grafos significativamente importantes:

|Grafo                |Vertices-Aristas                          |Tiempo                         |
|----------------|-------------------------------|-----------------------------|
|Gf12345_12111222|`221651-12528006 `            |27 seg            |
|R1999999_10123123          |`2000000-7196008`            |1,6 seg            |

#### Posibles mejoras

- Si se cambiara la funcion de hash por una mas compleja, lo que significa que va a haber menos coliciones el tiempo de ejecucion del peor caso bajaria drasticamente, sin contar que no seria de falta el uso de rbt y el over-head que produce
- Todo el proyecto seria mejor diseñado y con mas rendimiento si fuera implementado en C++


