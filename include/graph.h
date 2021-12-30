#ifndef MATRIXGRAPH_GRAPH_H
#define MATRIXGRAPH_GRAPH_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

struct graphStructure {
    int** matrix;
    int size;
};
typedef struct graphStructure *graph;

graph createNewGraph(int size); //создание графа размерности size

//добавление ребра между 2 вершинами с определенным весом
int addNewEdge(int vertex1, int vertex2, int weight, graph current_graph);

//удаление ребра между 2 вершинами
void deleteEdge(int vertex1, int vertex2, graph current_graph);

//добавление вершины в граф
int addNewVertex(graph current_graph);

//удаление вершины из графа
void deleteVertex(graph current_graph, int vertex_num);

//поиск кратчайшего пути из заданной вершины
int** findMinLength(int vertex_num, graph current_graph);

//печать вывода функции printFindMinLength в выходной файл
void printFindMinLength (int start_vertex, int end_vertex, int **arr, int size, FILE *output_file);

//печать содержимого графа в файл
void printGraphFile(graph current_graph, FILE *output_file);

//освобождение памяти
void freeGraph(graph current_graph);

//получение размерности графа
int getSize(graph current_graph);

bool ifInArray (const int *arr, int size, int n);
#endif //MATRIXGRAPH_GRAPH_H

