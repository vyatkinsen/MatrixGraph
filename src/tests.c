#include <assert.h>
#include "../include/graph.h"

void configTest() {
    int size = 4;
    graph newGraph = сreateNewGraph(size);
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
    graph newGraph = сreateNewGraph(size);
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
    graph newGraph = сreateNewGraph(size);
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
    graph newGraph = сreateNewGraph(size);
    addNewEdge(0, 1, 1152, newGraph);
    addNewEdge(1, 2, 14343, newGraph);
    addNewEdge(1, 3, 563451, newGraph);
    addNewVertex(newGraph);
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
    graph newGraph = сreateNewGraph(size);
    addNewEdge(0, 1, 1241, newGraph);
    addNewEdge(0, 3, 14234, newGraph);
    addNewEdge(1, 2, 15433, newGraph);
    addNewEdge(2, 3, 1534335, newGraph);
    deleteVertex(newGraph, 2);
    assert(getSize(newGraph) == 3);
    assert(newGraph->matrix[0][2] == 14234);
    assert(newGraph->matrix[2][0] == 14234);
    assert(newGraph->matrix[1][2] == 0);
    assert(newGraph->matrix[2][1] == 0);
    freeGraph(newGraph);
}

void findMinLengthTest() {
    int size = 4;
    graph newGraph = сreateNewGraph(size);
    int *distance = (int *)malloc(size * sizeof(int));
    bool *is_visited = (bool *)malloc(size * sizeof(bool));
    addNewEdge(1, 2, 23, newGraph);
    addNewEdge(0, 1, 33, newGraph);
    addNewEdge(0, 3, 44, newGraph);
    findMinLength(1, newGraph, distance, is_visited);
    assert(distance[0] == 33);
    assert(distance[2] == 23);
    assert(distance[3] == 77);
    free(distance);
    free(is_visited);
}

int startTests() {
    configTest();
    addNewEdgeTest();
    deleteEdgeTest();
    addNewVertexTest();
    deleteVertexTest();
    findMinLengthTest();
    return 0;
}
