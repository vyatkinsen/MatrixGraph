#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/graph.h"
#include "../include/tests.h"

/*
 * У программы следующие параметры командной строки:
 * edges_file (текстовый файл с входными значениями);
 * output_file (текстовый файл с выходными значениями);
 * -way /optional/ (в выходной файл будут записан кратчайший путь из одной до другой вершины);
 */
int main(int argc, char *argv[]) {
    if ((argc < 2) || (argc > 6)) {  //argc[0] занято названием программы
        puts("\nIncorrect command line arguments\n");
        return -1;
    }

    int graph_size = INT_MIN, string_counter = 0, counter = 0, m = 0;
    int char_in_file, last_char_in_file = EOF;
    int *numbers = (int *)malloc(3 * sizeof(int));
    FILE *edges_file, *output_file;

    edges_file = fopen(argv[1], "rt");
    if (edges_file == NULL) {
        puts("\nInput file does not exist\n");
        return -1;
    }

    while (!feof(edges_file)) {
        char_in_file = fgetc(edges_file);
        last_char_in_file = char_in_file;
        fscanf(edges_file, "%d", &numbers[counter]);
        if (m == 2) m = 0;
        else {
            if (numbers[counter] > graph_size) graph_size = numbers[counter];
            m++;
        }
        if (char_in_file == '\n' ) {
            string_counter++;
            numbers = (int *) realloc(numbers, (counter + 1) * 3 * sizeof (int));
        }
        counter++;
    }
    fclose(edges_file);
    if (last_char_in_file == EOF) {
        puts("\nFile is empty\n");
        return -1;
    } else if (last_char_in_file != '\n') string_counter++;

    graph_size++;
    graph graph = createNewGraph(graph_size);
    for (int k = 0; k < string_counter * 3; k += 3) addNewEdge(numbers[k], numbers[k + 1], numbers[k + 2], graph);

    output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        printf("\nInput file does not exist\n");
        return -1;
    }
    printGraphFile(graph, output_file);

    if ((argc == 6 ) && (*argv[3] == *"-way")) { //При указанном флаге -way ищем кратчайший путь от *argv[4] до *argv[5]
        char *pntr;
        int start_vertex = (int) strtol(argv[4], &pntr, 10);
        int end_vertex = (int) strtol(argv[5], &pntr, 10);
        if (start_vertex < graph_size) {
            int *distance;
            int *array = (int *) malloc(sizeof (int));
            int parents_count = findMinLength(start_vertex, end_vertex, graph, string_counter, graph_size, &distance, array);
            printFindMinLength(start_vertex, end_vertex, parents_count, output_file, distance, array);
            free(distance);
            free(array);
        } else {
            printf("\nIncorrect command line arguments\n");
            return -1;
        }
    }
    free(numbers);
    fclose(output_file);
    freeGraph(graph);
    return 0;
}
