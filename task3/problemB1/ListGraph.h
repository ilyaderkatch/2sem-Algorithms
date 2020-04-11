#pragma once
#ifndef PLANARITY_LISTGRAPH_H
#define PLANARITY_LISTGRAPH_H

#include "Edge.h"

vector <Edge> operator+(const vector <Edge> &a, const vector <Edge> &b);

class ListGraph{
private:
    vector <vector <Edge> > ChildrenList;

public:
    ListGraph(int n);

    void AddEdge(int from, int to, double weight);
    int VerticesCount() const;
    void GetNextVertices(int vertex, vector<Edge> &vertices) const;
    void Output();
    int ExtentVertex(int vertex) const;
    ListGraph operator+(const ListGraph &b);
};

#endif //PLANARITY_LISTGRAPH_H
