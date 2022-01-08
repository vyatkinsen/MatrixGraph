#include <assert.h>
#include "../include/graph.h"

void configTest() {
    int size = 4;
    graph newGraph = createNewGraph(size);
    assert(getSize(newGraph) == size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            assert(newGraph->matrix[i][j] == 0);
        }
    }
    freeGraph(newGraph);
}

void addNewEdgeTest() {
    int size = 4;
    graph newGraph = createNewGraph(size);
    addNewEdge(0, 1, 1, newGraph);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (((i == 0) && (j == 1)) || ((i == 1) && (j == 0))) assert(newGraph->matrix[i][j] == 1);
            else assert(newGraph->matrix[i][j] == 0);
        }
    }
    addNewEdge(1, 2, 23, newGraph);
    addNewEdge(1, 3, 10, newGraph);
    assert(newGraph->matrix[1][2] == 23);
    assert(newGraph->matrix[2][1] == 23);
    assert(newGraph->matrix[1][3] == 10);
    assert(newGraph->matrix[3][1] == 10);
    freeGraph(newGraph);
}

void deleteEdgeTest() {
    int size = 4;
    graph newGraph = createNewGraph(size);
    addNewEdge(0, 1, 33, newGraph);
    addNewEdge(1, 2, 2, newGraph);
    addNewEdge(1, 3, 55, newGraph);
    deleteEdge(0, 1, newGraph);
    assert(newGraph->matrix[0][1] == 0);
    assert(newGraph->matrix[1][0] == 0);
    assert(newGraph->matrix[1][2] == 2);
    assert(newGraph->matrix[2][1] == 2);
    assert(newGraph->matrix[1][3] == 55);
    assert(newGraph->matrix[3][1] == 55);
    freeGraph(newGraph);
}

void addNewVertexTest() {
    int size = 4;
    graph newGraph = createNewGraph(size);
    addNewEdge(0, 1, 1152, newGraph);
    addNewEdge(1, 2, 14343, newGraph);
    addNewEdge(1, 3, 563451, newGraph);
    int new_index = addNewVertex(newGraph);
    assert(new_index == 4);
    addNewEdge(2, 4, 1444, newGraph);
    assert(getSize(newGraph) == 5);
    assert(newGraph->matrix[1][4] == 0);
    assert(newGraph->matrix[4][1] == 0);
    assert(newGraph->matrix[2][4] == 1444);
    assert(newGraph->matrix[4][2] == 1444);
    assert(newGraph->matrix[0][1] == 1152);
    assert(newGraph->matrix[1][0] == 1152);
    freeGraph(newGraph);
}

void deleteVertexTest() {
    int size = 4;
    graph newGraph = createNewGraph(size);
    addNewEdge(0, 1, 1241, newGraph);
    addNewEdge(0, 3, 14234, newGraph);
    addNewEdge(2, 0, 1534335, newGraph);
    addNewEdge(2, 1, 32432, newGraph);
    addNewEdge(3, 2, 4432, newGraph);
    deleteVertex(newGraph, 2);
    assert(newGraph->matrix[0][2] == 0);
    assert(newGraph->matrix[2][0] == 0);
    assert(newGraph->matrix[1][2] == 0);
    assert(newGraph->matrix[2][3] == 0);
    assert(newGraph->matrix[2][1] == 0);
    freeGraph(newGraph);
}

void findMinLengthTest() {
    int size = 3;
    graph graph = createNewGraph(size);
    int a[] = {1, 0, 22, 0, 2, 33, 1, 2, 60};
    for (int x = 0; x < 3 * size; x += 3) addNewEdge(a[x], a[x + 1], a[x + 2], graph);
    int *distance;
    int *array = (int *) malloc(sizeof (int));
    int count = findMinLength(1, 2, graph, size, &distance, array);
    assert(distance[0] == 22);
    assert(distance[1] == 0);
    assert(distance[2] == 55);
    assert(count == 3);
    assert(array[0] == 1);
    assert(array[1] == 0);
    assert(array[2] == 2);
    free(array);
    free(distance);
}

int main() {
    configTest();
    addNewEdgeTest();
    deleteEdgeTest();
    addNewVertexTest();
    deleteVertexTest();
    findMinLengthTest();
    return 0;
}
