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
    int index_for_way, graph_size = INT_MIN;
    int** numbers = (int **)malloc(3 * sizeof(int**));
    graph graph;
    if (*argv[1] == *"-fo") {  //Для случая, когда нужно создать граф из выходного файла
        index_for_way = 3;
        graph_size = extractGraphFromOutputFile(argv[2], numbers);
    }
    else {  //Для случая, когда нужно создать граф из текстового файла, в котором описаны номера вершин для ребра и его вес
        index_for_way = 2;
        graph_size = extractGraphFromEdgesFile(argv[1], numbers);
    }
    graph = createNewGraph(graph_size);
    for (int k = 0; k < 3 * graph_size * graph_size - 1; k += 3) addNewEdge((*numbers)[k], (*numbers)[k + 1], (*numbers)[k + 2], graph);
    free(numbers);
    printGraphInFile(graph, argv[index_for_way]);
    if ((argc >= 6 ) && (*argv[index_for_way + 1] == *"-way")) { //При указанном флаге -way ищем кратчайший путь между указанными вершинами
        char *ptr;
        int start_vertex = (int) strtol(argv[index_for_way + 2], &ptr, 10);
        int end_vertex = (int) strtol(argv[index_for_way + 3], &ptr, 10);
        if (start_vertex < graph_size) {
            int *distance;
            int *array = (int *) malloc(sizeof (int));
            int parents_count = findMinLength(start_vertex, end_vertex, graph, graph_size, &distance, array);
            printFindMinLength(start_vertex, end_vertex, parents_count, argv[index_for_way], distance, array);
            free(distance);
            free(array);
        } else {
            printf("\nIncorrect command line arguments\n");
            return -1;
        }
    }
    freeGraph(graph);
    return 0;
}
