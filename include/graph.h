#ifndef MATRIXGRAPH_GRAPH_H
#define MATRIXGRAPH_GRAPH_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>

struct graphStructure {
    int** matrix;
    int size;
};
typedef struct graphStructure *graph;

//создание графа размерности size
graph createNewGraph(int size);

//добавление ребра между 2 вершинами с определенным весом
int addNewEdge(int vertex1, int vertex2, int weight, graph current_graph);

//Функция создания графа из output файла
int extractGraphFromOutputFile(char *input_file_name, int **numbers);

//Функция создания графа из input файла
int extractGraphFromEdgesFile(char *input_file_name, int **numbers);

//удаление ребра между 2 вершинами
int deleteEdge(int vertex1, int vertex2, graph current_graph);

//добавление вершины в граф
int addNewVertex(graph current_graph);

//удаление вершины из графа
void deleteVertex(graph current_graph, int vertex_num);

//Рекурсивная функция восстановления пути
int findPath(const int *parent, int end_vertex, int start_vertex, int *path_array, int counter);

//поиск кратчайшего пути из заданной вершины в определенную
int findMinLength(int start_vertex, int end_vertex, graph graph, int size, int **to_return_distance, int *path_array);

//печать вывода функции printFindMinLength в выходной файл
void printFindMinLength(int start_vertex, int end_vertex, int parents_count, char *output_file_name, const int *distance_array, int *path_array);

//печать содержимого графа в файл
void printGraphInFile(graph current_graph, char *output_file_name);

//освобождение памяти
void freeGraph(graph current_graph);

//получение размерности графа
int getSize(graph current_graph);
#endif //MATRIXGRAPH_GRAPH_H
