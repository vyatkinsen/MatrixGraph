#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/graph.h"

graph CreateGraph(int size) {
    graph new_graph;
    new_graph = malloc(sizeof(*new_graph));
    new_graph->size = size;                                                   //Присваиваем матрице размер
    new_graph->matrix = (int **)malloc(size * sizeof(int *));            //Выделяем место в памяти под матрицу размером size
    for(int i = 0; i < size; i++) {
        new_graph->matrix[i] = (int *)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {                                          //Заполняем матрицу нулями
        for (int j = 0; j < size; j++) {
            new_graph->matrix[i][j] = 0;
        }
    }
    return new_graph;
}

void DeinitializeMatrix(int **graph, int size) {
    for(int i = 0; i < size; i++) {
        free(graph[i]);
    }
    free(graph);
}

void AddEdge(int vertex1, int vertex2, int weight, graph current_graph) {              //Откуда, куда, какой вес, в каком графе
    if ((vertex2 < current_graph->size) && (vertex1 < current_graph->size) && (weight > 0)) {  //Проверка на то, что номер вершины не выходит за границы предела матрицы
        current_graph->matrix[vertex1][vertex2] = weight;
        current_graph->matrix[vertex2][vertex1] = weight;
    } else printf("\nWrong vertexes\n");
}

void RemoveEdge(int vertex1, int vertex2, graph current_graph) {
    if ((vertex2 < current_graph->size) && (vertex1 < current_graph->size)) {
        current_graph->matrix[vertex1][vertex2] = 0;
        current_graph->matrix[vertex2][vertex1] = 0;
    } else printf("\nWrong vertexes\n");
}

void AddVertex(graph current_graph) {
    int size = current_graph->size + 1;
    int **array = (int **)malloc(size * sizeof(int *));
    for(int i = 0; i < size; i++){
        array[i] = (int *)malloc(size*sizeof(int));
    }
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if ((j == size - 1) || (i == size - 1)) array[i][j] = 0;
            else array[i][j] = current_graph->matrix[i][j];
        }
    }
    DeinitializeMatrix(current_graph->matrix, current_graph->size);
    current_graph->matrix = array;
    current_graph->size = size;
}

void RemoveVertex(graph current_graph, int vertex) {
    int size = current_graph->size - 1;
    int **array = (int **)malloc(size * sizeof(int *));
    for(int i = 0; i < size; i++){
        array[i] = (int *)malloc(size*sizeof(int));
    }
    int offsetI = 0;
    for (int i = 0; i < size; i++){
        if (i >= vertex) offsetI = 1;
        for (int j = 0; j < size; j++){
            if (j >= vertex) {
                array[i][j] = current_graph->matrix[i + offsetI][j + 1];
            } else array[i][j] = current_graph->matrix[i + offsetI][j];
        }
    }
    DeinitializeMatrix(current_graph->matrix, current_graph->size);
    current_graph->matrix = array;
    current_graph->size = size;
}

void FindMinLength(int start_vertex, graph current_graph, FILE *output_file) {
    int index;
    int size = current_graph->size;
    int *distance = (int *)malloc(size * sizeof(int));
    bool *is_visited = (bool *)malloc(size * sizeof(bool));
    for (int i = 0; i < size; i++) {
        distance[i] = 2147483647;
        is_visited[i] = false;
    }
    distance[start_vertex] = 0;
    for (int count = 0; count < size - 1; count ++) {
        int min = 2147483647;
        for (int i = 0; i < size; i++) {
            if (!is_visited[i] && distance[i] <= min) {
                min = distance[i];
                index = i;
            }
        }
        int u = index;
        is_visited[u] = true;
        for (int i = 0; i < size; i++) {
            if (!is_visited[i] && current_graph->matrix[u][i] &&
            distance[u] != 2147483647 &&
            distance[u] + current_graph->matrix[u][i] < distance[i]) {
                distance[i]=distance[u]+current_graph->matrix[u][i];
            }
        }
    }
    free(is_visited);
    fprintf(output_file, "\n");
    for (int i = 0; i < current_graph->size; i++) {
        if (distance[i] != 2147483647) {
            fprintf(output_file, "Стоимость пути из %d в %d - %d;\n", start_vertex, i, distance[i]);
        } else {
            fprintf(output_file, "Путь из %d в %d невозможен;\n", start_vertex, i);
        }
    }
    free(distance);
}

void PrintGraphFile(graph current_graph, FILE *output_file) {
    fprintf(output_file, "Matrix size %dx%d:\n\n", current_graph->size, current_graph->size);
     for (int i = 0; i < current_graph->size; i++){
        for (int j = 0; j < current_graph->size; j++){
            fprintf(output_file, " %d ", current_graph->matrix[i][j]);
        }
        fprintf(output_file, "\n");
    }
}

int GetSize(graph current_graph) {
    return current_graph->size;
}

void DeinitializeGraph(graph current_graph) {
    DeinitializeMatrix(current_graph->matrix, current_graph->size);
    free(current_graph);
}