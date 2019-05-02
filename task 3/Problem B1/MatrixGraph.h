#pragma once
#ifndef MatrixGraph_h
#define MatrixGraph_h
#include "Edge.h"
#include <fstream>

using std::ofstream;
using std::ios;

class MatrixGraph {
private:
    vector <vector <double> > Table;

public:
    MatrixGraph(int n);

    void AddEdge(int from, int to, double weight);
    int VerticesCount() const;
    void GetNextVertices(int vertex, vector<Edge> &vertices) const;
    double GetWeight(int i, int j) const;
    MatrixGraph operator+(const MatrixGraph &b);
    void Foutput(string s);
};

#endif //PLANARITY_MATRIXGRAPH_H
