#ifndef TEST_H
#define TEST_H

#include <random>
#include <ctime>
#include "MatrixGraph.h"
#include "ListGraph.h"

using std::random_device;
using std::mt19937;
using std::normal_distribution;

MatrixGraph Generate(int vertices_count);

#endif //PLANARITY_TEST_H
