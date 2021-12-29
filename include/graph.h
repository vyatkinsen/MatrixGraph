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
void addNewEdge(int vertex1, int vertex2, int weight, graph current_graph); //добавление ребра между 2 вершинами с определенным весом
void deleteEdge(int vertex1, int vertex2, graph current_graph); //удаление ребра между 2 вершинами
void addNewVertex(graph current_graph); //добавление вершины в граф
void deleteVertex(graph current_graph, int vertex_num); //удаление вершины из графа
void findMinLength(int vertex_num, graph current_graph, int *distance, bool *is_visited); //поиск кратчайшего пути из заданной вершины
void printFindMinLength (int vertex, int *distance, int size, FILE *output_file); //печать вывода функции printFindMinLength в выходной файл
void printGraphFile(graph current_graph, FILE *output_file); //печать содержимого графа в файл
void freeGraph(graph current_graph); //освобождение памяти
int getSize(graph current_graph); //получение размерности графа
#endif //MATRIXGRAPH_GRAPH_H
