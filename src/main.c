#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/graph.h"
#include "../include/tests.h"

/*
 * У программы следующие параметры командной строки:
 * graph_size (размер графа);
 * edges_amount (кол-во пар переходов между вершинами);
 * edges_file (текстовый файл с входными значениями);
 * output_file (текстовый файл с выходными значениями);
 * -test /optional/ (запуск тестов);
 * -way /optional/ (в выходной файл будут записаны кратчайшие пути для указанной через пробел вершины);
 */
int main(int argc, char *argv[]) {
    int graph_size, edges_amount;
    char *pntr;
    if ((argc == 2) && (*argv[1] == *"-test")) { //При указанном флаге -test запускаем тесты
        startTests();
        return 0;
    } else if ((argc < 5) || (argc > 7)) {  //argc[0] занято названием программы
        printf("\nIncorrect command line arguments\n");
        return -1;
    }
    graph_size = (int) strtol(argv[1], &pntr, 10);
    edges_amount = (int) strtol(argv[2], &pntr, 10);
//    sscanf(argv[1], "%d", &graph_size);  //Размер графа
//    sscanf(argv[2], "%d", &edges_amount);  //Кол-во пар переходов между вершинами
    edges_amount *= 3;
    int *numbers = (int *)malloc(edges_amount * sizeof(int));
    FILE *edges_file;
    FILE *output_file;
    edges_file = fopen(argv[3], "rt"); //Открываем текстовый файл для чтения
    for (int i = 0; !feof(edges_file); i++) {   //Макросом feof() контролируется указатель положения в файле, когда он доходит до конца файла, происходит выход из цикла
        fscanf(edges_file, "%d", &numbers[i]);  //В массив numbers записываются значения из файла edges
    }
    graph graph = сreateNewGraph(graph_size);         //Создаем граф
    for (int k = 0; k < edges_amount; k += 3) {
        addNewEdge(numbers[k], numbers[k + 1], numbers[k + 2], graph); //Добавляем рёбра
    }
    free(numbers); //Освобождаем память
    fclose(edges_file);
    output_file = fopen(argv[4], "w"); //Создаем текстовый файл для записи
    printGraphFile(graph, output_file); //Выводим граф в виде матрицы в файл
    if ((argc == 7) && (*argv[5] == *"-way")) { //При указанном флаге -way ищем кратчайшие пути для указанного в *argv[6] вершины
        int start_vertex;
        sscanf(argv[6], "%d", &start_vertex);  //Размер графа
        if (start_vertex < graph_size) {
            int *distance = (int *)malloc(graph_size * sizeof(int));
            bool *is_visited = (bool *)malloc(graph_size * sizeof(bool));
            findMinLength(start_vertex, graph, distance, is_visited);
            printFindMinLength(start_vertex, distance, graph_size, output_file);
            free(distance);
            free(is_visited);
        } else {
            printf("\nIncorrect command line arguments\n");
            return -1;
        }
    }
    fclose(output_file);
    freeGraph(graph); //Освобождаем память
    return 0;
}
