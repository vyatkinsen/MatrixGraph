#include "../include/graph.h"

/*
 * Функция инициализации графа размерности size
 */
graph createNewGraph(int size) {
    graph new_graph;
    new_graph = malloc(sizeof(struct graphStructure));
    new_graph->size = size;
    new_graph->matrix = (int **)malloc(size * sizeof(int *));
    for(int i = 0; i < size; i++) new_graph->matrix[i] = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) { //Заполняем матрицу нулями
        for (int j = 0; j < size; j++)
            new_graph->matrix[i][j] = 0;
    }
    return new_graph;
}

/*
 * Функция деинициализации матрицы графа (освобождение памяти)
 */
void freeMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) free(matrix[i]);
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
    if ((vertex2 < current_graph->size) && (vertex1 < current_graph->size) && (weight >= 0)) {
        current_graph->matrix[vertex1][vertex2] = weight;
        current_graph->matrix[vertex2][vertex1] = weight;
//        printf("v1 = %d, v2 = %d;\n", vertex1, vertex2);
    } else {
        printf("\nIncorrect vertexes or weight\n");
        return -1;
    }
    return 0;
}

/*
 * Функция удаления ребра между 2 вершинами (vertex1, vertex2) в определенном графе (current_graph)
 */
int deleteEdge(int vertex1, int vertex2, graph current_graph) {
    if ((vertex2 < current_graph->size) && (vertex1 < current_graph->size)) {
        current_graph->matrix[vertex1][vertex2] = 0;
        current_graph->matrix[vertex2][vertex1] = 0;
    } else {
        printf("\nIncorrect vertexes\n");
        return -1;
    }
    return 0;
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
        for (int j = size - 1; j < size; j++) current_graph->matrix[i][j] = 0;
    }
    for (int i = size - 1; i < size; i++) {
        for (int j = 0; j < size; j++) current_graph->matrix[i][j] = 0;
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
 * Рекурсивная функция восстановления пути
 */
int findPath(const int *parent, int end_vertex, int start_vertex, int *path_array, int counter) {
    if (end_vertex < 0) return 0;
    counter = findPath(parent, parent[end_vertex], start_vertex, path_array, counter);
    path_array = (int *) realloc(path_array, (counter + 1) * sizeof (int));
    path_array[counter] = end_vertex;
    counter++;
    return counter;
}

/*
 * Функция нахождения кратчайшего пути из заданной вершины (start_vertex) в определенную вершину (end_vertex).
 * Функция возвращает количество вершин, через которое необходимо пройти.
 */
int findMinLength(int start_vertex, int end_vertex, graph graph, int string_counter, int size, int **to_return_distance, int *path_array) {
    int *distance = (int *)malloc(size * sizeof(int));
    int *parent = (int *)malloc(size * sizeof(int));
    int counter = 0;

    for (int i = 0; i < size; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }
    distance[start_vertex] = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int weight = graph->matrix[j][i];
            if (weight == 0) continue;
            if (distance[j] != INT_MAX && distance[j] + weight < distance[i]) {
                distance[i] = distance[j] + weight;
                parent[i] = j;
            }
        }
    }
    if (end_vertex != start_vertex && distance[end_vertex] < INT_MAX)
        counter = findPath(parent, end_vertex, start_vertex, path_array, counter);
    *to_return_distance = distance;
    free(parent);
    return counter;
}


/*
 * Функция вывода результата функции findMinLength в выходной файл (output_file)
 */
void printFindMinLength (int start_vertex, int end_vertex, int parents_count, FILE *output_file, const int *distance_array, int *path_array) {
    if (end_vertex != start_vertex) {
        if (distance_array[end_vertex] != INT_MAX) {
            fprintf(output_file, "\nСтоимость пути из %d в %d - %d;\n", start_vertex, end_vertex, distance_array[end_vertex]);
            if (distance_array[end_vertex] != 0) {
                fprintf(output_file, "Перемещения из %d в %d: ", start_vertex, end_vertex);
                for (int x = 0; x < parents_count; x++) {
                    fprintf(output_file, "%d", path_array[x]);
                    if (x != parents_count - 1) fprintf(output_file, " -> ");
                }
            }
        } else fprintf(output_file, "Путь из %d в %d невозможен;\n", start_vertex, end_vertex);
    } else fprintf(output_file, "Стоимость пути из %d в %d - 0;\n", start_vertex, end_vertex);
}

/*
 * Функция вывода определенного графа (current_graph) в виде матрицы в выходной файл (output_file)
 */
void printGraphFile(graph current_graph, FILE *output_file) {
    fprintf(output_file, "Matrix size %d:\n\n", current_graph->size);
    for (int i = 0; i < current_graph->size; i++) {
        for (int j = 0; j < current_graph->size; j++)
            fprintf(output_file, " %d ", current_graph->matrix[i][j]);
        fprintf(output_file, "\n");
    }
}

/*
 * Функция получения размерности определенного графа (current_graph)
 */
int getSize(graph current_graph) {
    return current_graph->size;
}
