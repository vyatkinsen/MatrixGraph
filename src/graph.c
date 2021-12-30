#include "../include/graph.h"

/*
 * Функция инициализации графа размерности size
 */
graph createNewGraph(int size) {
    graph new_graph;
    new_graph = malloc(size * sizeof(int *));
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
void freeMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

/*
 * Функция деинициализации графа (освобождение памяти)
 */
void freeGraph(graph current_graph) {
    freeMatrix(current_graph->matrix, current_graph->size);
    free(current_graph);
}

/*
 * Функция добавления ребра между 2 вершинами (vertex1, vertex2)
 * с определенным положительным весом (weight), в определенном графе (current_graph)
 */
int addNewEdge(int vertex1, int vertex2, int weight, graph current_graph) {
    if ((vertex2 < current_graph->size) && (vertex1 < current_graph->size) && (weight > 0)) {
        current_graph->matrix[vertex1][vertex2] = weight;
        current_graph->matrix[vertex2][vertex1] = weight;
    } else {
        printf("\nIncorrect vertexes or weight\n");
        return -1;
    }
    return 0;
}

/*
 * Функция удаления ребра между 2 вершинами (vertex1, vertex2) в определенном графе (current_graph)
 */
void deleteEdge(int vertex1, int vertex2, graph current_graph) {
    if ((vertex2 < current_graph->size) && (vertex1 < current_graph->size)) {
        current_graph->matrix[vertex1][vertex2] = 0;
        current_graph->matrix[vertex2][vertex1] = 0;
    } else printf("\nIncorrect vertexes\n");
}

/*
 * Функция добавления вершины в определенном графе (current_graph)
 */
int addNewVertex(graph current_graph) {
    int size = current_graph->size + 1;
    int new_Number_Of_Vertex = current_graph->size;
    current_graph->matrix = (int**) realloc(current_graph->matrix, size * sizeof(*current_graph->matrix));

    for (int i = 0; i < size; i++) {
        current_graph->matrix[i] = (int *) realloc(current_graph->matrix[i], (size + 1) * sizeof(int));
        for (int j = size - 1; j < size; j++){
            current_graph->matrix[i][j] = 0;    //Заполняем нулями последние пустые ячейки в новой матрице
        }
    }
    for (int i = size - 1; i < size; i++){
        for (int j = 0; j < size; j++){
            current_graph->matrix[i][j] = 0;    //Заполняем нулями последние пустые ячейки в новой матрице
        }
    }
    current_graph->size = size;
    return new_Number_Of_Vertex;
}

/*
 * Функция удаления вершины (vertex_num) в определенном графе (current_graph)
 */
void deleteVertex(graph current_graph, int vertex_num) {
    int size = current_graph->size;
    for (int i = 0; i < size; i++) {
        current_graph->matrix[vertex_num][i] = 0;
        current_graph->matrix[i][vertex_num] = 0;
    }
}

/*
 * Функция нахождения кратчайшего пути из заданной вершины (vertex_num) в определенном графе (current_graph)
 */
int** findMinLength(int vertex_num, graph current_graph) {
    int index, i, x = 1;
    int size = current_graph->size;
    int *distance = (int *)malloc(size * sizeof(int));
    int *arr = (int *)malloc(sizeof(int));
    bool *is_visited = (bool *)malloc(size * sizeof(bool));
    int **toReturn = (int **)malloc(size * sizeof(int *));
    for (i = 0; i < size; i++) {
        distance[i] = INT_MAX;
        is_visited[i] = false;
    }
    distance[vertex_num] = 0;
    for (int count = 0; count < size + 1; count++) {
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
            if (!is_visited[i] && current_graph->matrix[j][i] && distance[j] != INT_MAX && distance[j] + current_graph->matrix[j][i] < distance[i]) {
                distance[i] = distance[j] + current_graph->matrix[j][i];
                if ((vertex_num == 0 && x == 1) || !ifInArray(arr, size, j)) {
                    arr[x] = j;
                    x++;
                    arr = (int*) realloc(arr, x * sizeof(*arr));
                }
            }
         }
    }
    x--;
    arr[0] = x;
    free(is_visited);
    toReturn[0] = distance;
    toReturn[1] = arr;
    return toReturn;
}

bool ifInArray (const int *arr, int size, int n) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == n) return true;
    }
    return false;
}

/*
 * Функция вывода результата функции findMinLength в выходной файл (output_file)
 */
void printFindMinLength (int start_vertex, int end_vertex, int **arr, FILE *output_file) {
    int distance = arr[0][end_vertex];
    if (end_vertex != start_vertex) {
        if (distance != INT_MAX) {
            fprintf(output_file, "\nСтоимость пути из %d в %d - %d;\n", start_vertex, end_vertex, distance);
            if (distance != 0) {
                fprintf(output_file, "Перемещения из %d в %d: ", start_vertex, end_vertex);
                for (int x = 0; x < arr[1][0]; x++) {
                    fprintf(output_file, "%d", arr[1][x + 1]);
                    if (x != arr[1][0] - 1) fprintf(output_file, " -> ");
                }
            }
        } else {
            fprintf(output_file, "Путь из %d в %d невозможен;\n", start_vertex, end_vertex);
        }
    } else {
        fprintf(output_file, "Стоимость пути из %d в %d - 0;\n", start_vertex, end_vertex);
    }
    free(arr);
}

/*
 * Функция вывода определенного графа (current_graph) в виде матрицы в выходной файл (output_file)
 */
void printGraphFile(graph current_graph, FILE *output_file) {
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
int getSize(graph current_graph) {
    return current_graph->size;
}
