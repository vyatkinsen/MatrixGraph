#include <stdio.h>
#include <stdlib.h>
#include "../include/graph.h"
#include "../include/tests.h"

/*Демонстрационная программа создаёт граф размера N (задается первым аргументом конмадной строки)
 * затем прочтём K (второй аргумент) пар переходов между вершинами из файла edges.txt (3 аргумент)
 * и после этого заполним матрицу смежности. Напечатаем содержимое графа в файл out.txt (4 аргумет).
 * Чтобы запустить тесты необходимао передать флаг -t.
 */
int main(int argc, char *argv[]) {
    int graph_size, edges_amount;
    if ((argc < 5) || (argc > 7)) {  //argc[0] занято названием программы
        printf("\nWrong command line arguments\n");
        return -1;
    }
    if ((argc == 6) && (*argv[5] == *"-t")) { //При указанном флаге -t запускаем тесты
        runAllTests();
    }
    sscanf(argv[1], "%d", &graph_size);  //Размер графа
    sscanf(argv[2], "%d", &edges_amount);  //Кол-во пар переходов между вершинами
    edges_amount *= 3;

    int *numbers = (int *)malloc(edges_amount * sizeof(int));
    FILE *edges_file;
    FILE *output_file;

    edges_file = fopen(argv[3], "rt"); //Открываем текстовый файл для чтения
    for (int i = 0; !feof(edges_file); i++) {   //Макросом feof() контролируется указатель положения в файле, когда он доходит до конца файла, происходит выход из цикла
        fscanf(edges_file, "%d", &numbers[i]);  //В массив numbers записываются значения из файла edges
    }

    graph graph = CreateGraph(graph_size);         //Создаем граф

    for (int k = 0; k < edges_amount; k += 3) {
        AddEdge(numbers[k], numbers[k + 1], numbers[k + 2], graph); //Добавляем рёбра
    }

    free(numbers);
    fclose(edges_file);

    output_file = fopen(argv[4], "w"); //Создаем текстовый файл для записи
    PrintGraphFile(graph, output_file);

    if ((argc == 7) && (*argv[5] == *"-way")) { //При указанном флаге -way ищем кратчайшие пути для указанного в *argv[6] вершины
        int start_vertex;
        sscanf(argv[6], "%d", &start_vertex);  //Размер графа
        if (start_vertex < graph_size) {
            FindMinLength(start_vertex, graph, output_file);
        } else {
            printf("\nWrong command line arguments\n");
            return -1;
        }
    }
    fclose(output_file);
    DeinitializeGraph(graph);
    return 0;
}