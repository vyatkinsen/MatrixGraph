#include <assert.h>
#include "../include/graph.h"

void Config_Test() {
    int size = 4;
    graph newGraph = CreateGraph(size);
    assert(GetSize(newGraph) == size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            assert(newGraph->matrix[i][j] == 0);
        }
    }
    DeinitializeGraph(newGraph);
}

void AddEdge_Test() {
    int size = 4;
    graph newGraph = CreateGraph(size);
    AddEdge(0, 1, 1, newGraph);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (((i == 0) && (j == 1)) || ((i == 1) && (j == 0))) assert(newGraph->matrix[i][j] == 1);
            else assert(newGraph->matrix[i][j] == 0);
        }
    }
    AddEdge(1, 2, 23, newGraph);
    AddEdge(1, 3, 10, newGraph);
    assert(newGraph->matrix[1][2] == 23);
    assert(newGraph->matrix[2][1] == 23);
    assert(newGraph->matrix[1][3] == 10);
    assert(newGraph->matrix[3][1] == 10);
    DeinitializeGraph(newGraph);
}

void RemoveEdge_Test() {
    int size = 4;
    graph newGraph = CreateGraph(size);
    AddEdge(0, 1, 33, newGraph);
    AddEdge(1, 2, 2, newGraph);
    AddEdge(1, 3, 55, newGraph);
    RemoveEdge(0, 1, newGraph);
    assert(newGraph->matrix[0][1] == 0);
    assert(newGraph->matrix[1][0] == 0);
    assert(newGraph->matrix[1][2] == 2);
    assert(newGraph->matrix[2][1] == 2);
    assert(newGraph->matrix[1][3] == 55);
    assert(newGraph->matrix[3][1] == 55);
    DeinitializeGraph(newGraph);
}

void AddVertex_Test() {
    int size = 4;
    graph newGraph = CreateGraph(size);
    AddEdge(0, 1, 1152, newGraph);
    AddEdge(1, 2, 14343, newGraph);
    AddEdge(1, 3, 563451, newGraph);
    AddVertex(newGraph);
    AddEdge(2, 4, 1444, newGraph);
    assert(GetSize(newGraph) == 5);
    assert(newGraph->matrix[1][4] == 0);
    assert(newGraph->matrix[4][1] == 0);
    assert(newGraph->matrix[2][4] == 1444);
    assert(newGraph->matrix[4][2] == 1444);
    assert(newGraph->matrix[0][1] == 1152);
    assert(newGraph->matrix[1][0] == 1152);
    DeinitializeGraph(newGraph);
}

void RemoveVertex_Test() {
    int size = 4;
    graph newGraph = CreateGraph(size);
    AddEdge(0, 1, 1241, newGraph);
    AddEdge(0, 3, 14234, newGraph);
    AddEdge(1, 2, 15433, newGraph);
    AddEdge(2, 3, 1534335, newGraph);
    RemoveVertex(newGraph, 2);
    assert(GetSize(newGraph) == 3);
    assert(newGraph->matrix[0][2] == 14234);
    assert(newGraph->matrix[2][0] == 14234);
    assert(newGraph->matrix[1][2] == 0);
    assert(newGraph->matrix[2][1] == 0);
    DeinitializeGraph(newGraph);
}

void FindMinLength_Test() {
    int size = 4;
    graph newGraph = CreateGraph(size);
    int *distance = (int *)malloc(size * sizeof(int));
    bool *is_visited = (bool *)malloc(size * sizeof(bool));
    AddEdge(1, 2, 23, newGraph);
    AddEdge(0, 1, 33, newGraph);
    AddEdge(0, 3, 44, newGraph);
    FindMinLength(1, newGraph, distance, is_visited);
    assert(distance[0] == 33);
    assert(distance[2] == 23);
    assert(distance[3] == 77);
    free(distance);
    free(is_visited);
}

int StartTests() {
    Config_Test();
    AddEdge_Test();
    RemoveEdge_Test();
    AddVertex_Test();
    RemoveVertex_Test();
    FindMinLength_Test();
    return 0;
}
