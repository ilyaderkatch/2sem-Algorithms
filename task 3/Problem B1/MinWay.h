#ifndef MINWAY_H
#define MINWAY_H

#include "MatrixGraph.h"
#include "ListGraph.h"
#include "MST.h"
#include <algorithm>

using std::sort;


vector <int> operator+(const vector <int> &a, const vector <int> &b);

vector <int> DfsFromVertex(const ListGraph &A, int vertex, int parent);
vector <int> Dfs(const ListGraph &A);
double MinCycle(const MatrixGraph &A);
void swap(vector <int> &A, int i, int j);
bool NextSequence(vector <int> &A);
double CorrectMinCycle(const MatrixGraph &A);

#endif //PLANARITY_MINWAY_H
