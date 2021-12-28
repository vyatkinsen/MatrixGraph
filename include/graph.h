#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

struct GraphStructure {
    int** matrix;
    int size;
};

typedef struct GraphStructure *graph;
graph CreateGraph(int size); //создание графа размерности size
void AddEdge(int vertex1, int vertex2, int weight, graph current_graph); //добавление ребра между 2 вершинами с определенным весом
void RemoveEdge(int vertex1, int vertex2, graph current_graph); //удаление ребра между 2 вершинами
void AddVertex(graph current_graph); //добавление вершины в граф
void RemoveVertex(graph current_graph, int vertex); //удаление вершины из графа
void FindMinLength(int vertex, graph current_graph, int *distance, bool *is_visited); //поиск кратчайшего пути из заданной вершины
void PrintFindMinLength (int vertex, int *distance, int size, FILE *output_file); //печать вывода функции PrintFindMinLength в выходной файл
void PrintGraphFile(graph current_graph, FILE *output_file); //печать содержимого графа в файл
int GetSize(graph current_graph); //получение размерности графа
void DeinitializeGraph(graph current_graph); //освобождение памяти