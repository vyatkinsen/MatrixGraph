#include "../include/graph.h"

/*
 * Функция инициализации графа размерности size
 */
graph CreateGraph(int size) {
    graph new_graph;
    new_graph = malloc(sizeof(*new_graph));
    new_graph->size = size;
    new_graph->matrix = (int **)malloc(size * sizeof(int *));
    for(int i = 0; i < size; i++) {
        new_graph->matrix[i] = (int *)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) { //Заполняем матрицу нулями
        for (int j = 0; j < size; j++) {
            new_graph->matrix[i][j] = 0;
        }
    }
    return new_graph;
}

/*
 * Функция деинициализации матрицы графа (освобождение памяти)
 */
void DeinitializeMatrix(int **current_graph, int size) {
    for (int i = 0; i < size; i++) {
        free(current_graph[i]);
    }
    free(current_graph);
}

/*
 * Функция деинициализации графа (освобождение памяти)
 */
void DeinitializeGraph(graph current_graph) {
    DeinitializeMatrix(current_graph->matrix, current_graph->size);
    free(current_graph);
}

/*
 * Функция добавления ребра между 2 вершинами (vertex1, vertex2)
 * с определенным положительным весом (weight), в определенном графе (current_graph)
 */
void AddEdge(int vertex1, int vertex2, int weight, graph current_graph) {
    if ((vertex2 < current_graph->size) && (vertex1 < current_graph->size) && (weight > 0)) {
        current_graph->matrix[vertex1][vertex2] = weight;
        current_graph->matrix[vertex2][vertex1] = weight;
    } else printf("\nIncorrect vertexes or weight\n");
}

/*
 * Функция удаления ребра между 2 вершинами (vertex1, vertex2) в определенном графе (current_graph)
 */
void RemoveEdge(int vertex1, int vertex2, graph current_graph) {
    if ((vertex2 < current_graph->size) && (vertex1 < current_graph->size)) {
        current_graph->matrix[vertex1][vertex2] = 0;
        current_graph->matrix[vertex2][vertex1] = 0;
    } else printf("\nIncorrect vertexes\n");
}

/*
 * Функция добавления вершины в определенном графе (current_graph)
 */
void AddVertex(graph current_graph) {
    int size = current_graph->size + 1;
    int **array = (int **)malloc(size * sizeof(int *));
    for(int i = 0; i < size; i++){
        array[i] = (int *)malloc(size*sizeof(int));
    }
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if ((j == size - 1) || (i == size - 1)) {
                array[i][j] = 0;
            } else array[i][j] = current_graph->matrix[i][j];
        }
    }
    DeinitializeMatrix(current_graph->matrix, current_graph->size);
    current_graph->matrix = array;
    current_graph->size = size;
}

/*
 * Функция удаления вершины (vertex) в определенном графе (current_graph)
 */
void RemoveVertex(graph current_graph, int vertex) {
    int size = current_graph->size - 1;
    int **a = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++){
        a[i] = (int *)malloc(size * sizeof(int));
    }
    int offset = 0;
    for (int i = 0; i < size; i++){
        if (i >= vertex) {
            offset = 1;
        }
        for (int j = 0; j < size; j++){
            if (j >= vertex) {
                a[i][j] = current_graph->matrix[i + offset][j + 1];
            } else a[i][j] = current_graph->matrix[i + offset][j];
        }
    }
    DeinitializeMatrix(current_graph->matrix, current_graph->size);
    current_graph->matrix = a;
    current_graph->size = size;
}

/*
 * Функция нахождения кратчайшего пути из заданной вершины (vertex)
 * в определенном графе (current_graph) с выводом в выходной файл (output_file)
 */
void FindMinLength(int vertex, graph current_graph, int *distance, bool *is_visited) {
    int index, i;
    int size = current_graph->size;
    for (i = 0; i < size; i++) {
        distance[i] = INT_MAX;
        is_visited[i] = false;
    }
    distance[vertex] = 0;
    for (int count = 0; count < size - 1; count ++) {
        int min = INT_MAX;
        for (i = 0; i < size; i++) {
            if (!is_visited[i] && distance[i] <= min) {
                min = distance[i];
                index = i;
            }
        }
        int j = index;
        is_visited[j] = true;
        for (i = 0; i < size; i++) {
            if (!is_visited[i] && current_graph->matrix[j][i] &&
                distance[j] != INT_MAX &&
                distance[j] + current_graph->matrix[j][i] < distance[i]) {
                distance[i] = distance[j] + current_graph->matrix[j][i];
            }
        }
    }
}

void PrintFindMinLength (int vertex, int *distance, int size, FILE *output_file) {
    fprintf(output_file, "\n");
    for (int i = 0; i < size; i++) {
        if (i == vertex) i++;
        if (distance[i] != INT_MAX) {
            fprintf(output_file, "Стоимость пути из %d в %d - %d;\n", vertex, i, distance[i]);
        } else {
            fprintf(output_file, "Путь из %d в %d невозможен;\n", vertex, i);
        }
    }
}

/*
 * Функция вывода определенного графа (current_graph) в виде матрицы в выходной файл (output_file)
 */
void PrintGraphFile(graph current_graph, FILE *output_file) {
    fprintf(output_file, "Matrix size %dx%d:\n\n", current_graph->size, current_graph->size);
     for (int i = 0; i < current_graph->size; i++){
        for (int j = 0; j < current_graph->size; j++){
            fprintf(output_file, " %d ", current_graph->matrix[i][j]);
        }
        fprintf(output_file, "\n");
    }
}

/*
 * Функция получения размерности определенного графа (current_graph)
 */
int GetSize(graph current_graph) {
    return current_graph->size;
}