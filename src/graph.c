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
    } else {
        printf("\nIncorrect vertexes or weight\n");
        return -1;
    }
    return 0;
}

/*
 * Функция создания графа из output файла
 */
graph extractGraphFromOutputFile(char *input_file_name) {
    FILE *edges_file = fopen(input_file_name, "rt");
    if (edges_file == NULL) {
        puts("\nInput file does not exist\n");
        exit(-1);
    }
    int graph_size = INT_MIN, full_num = 0, src = 0, direction = 0, index = -1;
    int char_in_file, previous_char_in_file;
    int *numbers = (int *)malloc(sizeof(int*));

    while (!feof(edges_file)) {
        char_in_file = fgetc(edges_file);
        if (isdigit(char_in_file)) full_num = full_num * 10 + (char_in_file - 48);
        else {
            if (isdigit(previous_char_in_file)) {
                if (index == -1) {
                    graph_size = full_num;
                    numbers = (int *) realloc(numbers, 3 * graph_size * graph_size * sizeof (int));
                } else {
                    numbers[index - 2] = src;
                    numbers[index - 1] = direction;
                    numbers[index] = full_num;
                    direction++;
                    if (direction == graph_size) {
                        direction = 0;
                        src++;
                    }
                }
                if (index == 3 * graph_size * graph_size - 1) break;
                index += 3;
            }
            full_num = 0;
        }
        previous_char_in_file = char_in_file;
    }
    fclose(edges_file);
    graph graph = createNewGraph(graph_size);
    for (int k = 0; k < 3 * graph_size * graph_size - 1; k += 3) addNewEdge(numbers[k], numbers[k + 1], numbers[k + 2], graph);
    free(numbers);
    return graph;
}

/*
 * Функция создания графа из input файла
 */
graph extractGraphFromEdgesFile(char *input_file_name) {
    FILE *edges_file = fopen(input_file_name, "rt");
    if (edges_file == NULL) {
        puts("\nInput file does not exist\n");
        exit(-1);
    }
    int char_in_file, last_char_in_file = EOF, graph_size = INT_MIN, counter = 0, m = 0;
    int *numbers = (int*) malloc(3 * sizeof(int*));
    while (!feof(edges_file)) {
        char_in_file = fgetc(edges_file);
        last_char_in_file = char_in_file;
        fscanf(edges_file, "%d", &numbers[counter]);
        if (m == 2) m = 0;
        else {
            if (numbers[counter] > graph_size) graph_size = numbers[counter];
            m++;
        }
        if (char_in_file == '\n' ) numbers = (int *) realloc(numbers, (counter + 1) * 3 * sizeof (int*));
        counter++;
        if (last_char_in_file == EOF) {
            puts("\nFile is empty\n");
            exit(-1);
        }
    }
    fclose(edges_file);
    ++graph_size;
    graph graph = createNewGraph(graph_size);
    for (int k = 0; k < 3 * graph_size * graph_size - 1; k += 3) addNewEdge(numbers[k], numbers[k + 1], numbers[k + 2], graph);
    free(numbers);
    return graph;
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
int findMinLength(int start_vertex, int end_vertex, graph graph, int **to_return_distance, int *path_array) {
    int size = graph->size;
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
void printFindMinLength (int start_vertex, int end_vertex, int parents_count, char *output_file_name, const int *distance_array, int *path_array) {
    FILE *output_file = fopen(output_file_name, "at");
    if (output_file == NULL) {
        printf("\nOutput file name incorrect\n");
        return;
    }
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
    fclose(output_file);
}

/*
 * Функция вывода определенного графа (current_graph) в виде матрицы в выходной файл (output_file)
 */
void printGraphInFile(graph current_graph, char *output_file_name) {
    FILE *output_file = fopen(output_file_name, "w");
    if (output_file == NULL) {
        printf("\nOutput file name incorrect\n");
        return;
    }
    fprintf(output_file, "Matrix size %d:\n\n", current_graph->size);
    for (int i = 0; i < current_graph->size; i++) {
        for (int j = 0; j < current_graph->size; j++)
            fprintf(output_file, " %d ", current_graph->matrix[i][j]);
        fprintf(output_file, "\n");
    }
    fclose(output_file);
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
    current_graph->matrix = (int**) realloc(current_graph->matrix, size * sizeof(int*));

    for (int i = 0; i < size; i++) {
        current_graph->matrix[i] = (int *) realloc(current_graph->matrix[i], size * sizeof(int));
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
 * Функция получения размерности определенного графа (current_graph)
 */
int getSize(graph current_graph) {
    return current_graph->size;
}
