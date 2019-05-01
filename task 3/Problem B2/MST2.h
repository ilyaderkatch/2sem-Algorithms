#ifndef MST2_H
#define MST2_H

#include "MatrixGraph.h"
#include "ListGraph.h"
#include <stack>
#include <algorithm>

using std::stack;
using std::sort;

vector <int> EulerCycle(const ListGraph &A);
double MinCycle(const MatrixGraph &A);
ListGraph MinMatching(const MatrixGraph &G, const vector <int> &A);
vector <int> FindOddVertices(const ListGraph &G);
bool NextSequence(vector <int> &A);
void swap(vector <int> &A, int i, int j);
ListGraph Prim(const MatrixGraph &A);
double CorrectMinCycle(const MatrixGraph &A);


#endif
