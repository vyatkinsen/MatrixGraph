#include <stddef.h>

struct graphStruct {
    int** matrix; //матрица смежности размером size * size, меняется динамически
    int size; //размер нашей матрицы == количеству вершин
    };

typedef struct graphStruct *graph;

graph CreateGraph(int size); //создание графа с количеством вершин и размером size
void AddEdge(int vertex1, int vertex2, int weight, graph current_graph); //добавление ребра между 2 вершинами
void RemoveEdge(int vertex1, int vertex2, graph current_graph); //удаление ребра между 2 вершинами
void AddVertex(graph current_graph); //добавление вершины в граф
void RemoveVertex(graph current_graph, int vertex); //удаление вершины из графа
void PrintGraphFile(graph current_graph, FILE *output_file); //печать содержимого графа в файл
int GetSize(graph current_graph); //получение размера(количества вершин) графа
void DeinitializeGraph(graph current_graph); //освобождение памяти
void FindMinLength(int start_vertex,graph current_graph, FILE *output_file);