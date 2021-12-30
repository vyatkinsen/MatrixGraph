#include <stdio.h>
#include <stdlib.h>
#include "../include/graph.h"
#include "../include/tests.h"

/*
 * У программы следующие параметры командной строки:
 * graph_size (размер графа);
 * edges_amount (кол-во пар переходов между вершинами);
 * edges_file (текстовый файл с входными значениями);
 * output_file (текстовый файл с выходными значениями);
 * -way /optional/ (в выходной файл будут записаны кратчайшие пути для указанной через пробел вершины);
 */
int main(int argc, char *argv[]) {
    if ((argc < 5) || (argc > 8)) {  //argc[0] занято названием программы
        printf("\nIncorrect command line arguments\n");
        return -1;
    }

    int graph_size, edges_amount;
    char *pntr;
    FILE *edges_file, *output_file;
    graph_size = (int) strtol(argv[1], &pntr, 10);
    edges_amount = (int) strtol(argv[2], &pntr, 10);
    edges_amount *= 3;
    int *numbers = (int *)malloc(edges_amount * sizeof(int));

    edges_file = fopen(argv[3], "rt"); //Открываем текстовый файл для чтения
    if (edges_file == NULL) {
        printf("\nInput file does not exist\n");
        return -1;
    }

    for (int i = 0; !feof(edges_file); i++) {   //Макросом feof() контролируется указатель положения в файле, когда он доходит до конца файла, происходит выход из цикла
         fscanf(edges_file, "%d", &numbers[i]);  //В массив numbers записываются значения из файла edges
    }
    graph graph = createNewGraph(graph_size);         //Создаем граф
    for (int k = 0; k < edges_amount; k += 3) {
        addNewEdge(numbers[k], numbers[k + 1], numbers[k + 2], graph); //Добавляем рёбра
    }
    free(numbers); //Освобождаем память
    fclose(edges_file);

    output_file = fopen(argv[4], "w"); //Создаем текстовый файл для записи
    if (output_file == NULL) {
        printf("\nInput file does not exist\n");
        return -1;
    }
    printGraphFile(graph, output_file); //Выводим граф в виде матрицы в файл
    if ((argc == 8 ) && (*argv[5] == *"-way")) { //При указанном флаге -way ищем кратчайший путь от *argv[6] до *argv[7]
        int start_vertex = (int) strtol(argv[6], &pntr, 10);
        if (start_vertex < graph_size) {
            printFindMinLength(start_vertex, (int) strtol(argv[7], &pntr, 10), findMinLength(start_vertex, graph), graph_size, output_file);
        } else {
            printf("\nIncorrect command line arguments\n");
            return -1;
        }
    }
    fclose(output_file);
    freeGraph(graph); //Освобождаем память
    return 0;
}
