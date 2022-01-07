#include <stdio.h>
#include <stdlib.h>
#include "../include/graph.h"
#include "../include/tests.h"

/*
 * У программы следующие параметры командной строки:
 * -fo /optional/ (граф будет построен из выходного файла)
 * edges_file (текстовый файл с входными значениями);
 * output_file (текстовый файл с выходными значениями);
 * -way /optional/ (в выходной файл будут записан кратчайший путь из одной до другой вершины);
 */
int main(int argc, char *argv[]) {
    if ((argc < 3) || (argc > 7)) {  //argc[0] занято названием программы
        puts("\nIncorrect command line arguments\n");
        return -1;
    }

    int output_index, graph_size = INT_MIN;
    int** numbers = (int **)malloc(3 * sizeof(int**));
    FILE *edges_file, *output_file;
    graph graph;

    if (*argv[1] == *"-fo") {
        output_index = 3;
        edges_file = fopen(argv[2], "rt");
        if (edges_file == NULL) {
            puts("\nInput file does not exist\n");
            return -1;
        }
        graph_size = createNewGraphFromOutputFile(edges_file, numbers);
    }
    else {
        output_index = 2;
        edges_file = fopen(argv[1], "rt");
        if (edges_file == NULL) {
            puts("\nInput file does not exist\n");
            return -1;
        }
        graph_size = createNewGraphFromEdgesFile(edges_file, numbers);
        graph_size++;
    }
    graph = createNewGraph(graph_size);
    for (int k = 0; k < 3 * graph_size * graph_size - 1; k += 3) addNewEdge((*numbers)[k], (*numbers)[k + 1], (*numbers)[k + 2], graph);
    fclose(edges_file);
    free(numbers);

    output_file = fopen(argv[output_index], "w");
    if (output_file == NULL) {
        printf("\nInput file does not exist\n");
        return -1;
    }
    printGraphFile(graph, output_file);

    if ((argc >= 6 ) && (*argv[output_index + 1] == *"-way")) { //При указанном флаге -way ищем кратчайший путь от *argv[4] до *argv[5]
        char *pntr;
        int start_vertex = (int) strtol(argv[output_index + 2], &pntr, 10);
        int end_vertex = (int) strtol(argv[output_index + 3], &pntr, 10);
        if (start_vertex < graph_size) {
            int *distance;
            int *array = (int *) malloc(sizeof (int));
            int parents_count = findMinLength(start_vertex, end_vertex, graph, graph_size, &distance, array);
            printFindMinLength(start_vertex, end_vertex, parents_count, output_file, distance, array);
            free(distance);
            free(array);
        } else {
            printf("\nIncorrect command line arguments\n");
            return -1;
        }
    }
    fclose(output_file);
    freeGraph(graph);
    return 0;
}
