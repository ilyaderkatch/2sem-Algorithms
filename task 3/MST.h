#ifndef MST_H
#define MST_H

#include "MatrixGraph.h"
#include "ListGraph.h"
#include <algorithm>

using std::sort;


vector <int> operator+(const vector <int> &a, const vector <int> &b);

ListGraph Prim(const MatrixGraph &A);
vector <int> DfsFromVertex(const ListGraph &A, int vertex, int parent);
vector <int> Dfs(const ListGraph &A);
double MinCycle(const MatrixGraph &A);
void swap(vector <int> &A, int i, int j);
bool NextSequence(vector <int> &A);
double CorrectMinCycle(const MatrixGraph &A);

#endif //PLANARITY_MST_H
