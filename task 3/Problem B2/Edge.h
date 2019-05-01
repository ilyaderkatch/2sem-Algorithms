#ifndef PLANARITY_EDGE_H
#define PLANARITY_EDGE_H

#include <iostream>
#include <vector>
#include <set>

using std::vector;
using std::set;
using std::cin;
using std::cout;
using std::endl;
using std::pair;

struct Edge
{
    Edge(int _from, int _to, double _weight) {from = _from; to = _to; weight = _weight;}
    int from = 0;
    int to = 0;
    double weight = 0;
    friend bool operator==(const Edge &a, const Edge &b){return (a.to == b.to) && (a.weight == b.weight) && (a.from == b.from);}
    friend bool operator<(const Edge &a, const Edge &b){return (a.weight < b.weight) || ((a.weight == b.weight) && (a.to < b.to)) || ((a.weight == b.weight) && (a.to == b.to) && (a.from < b.from));}
    bool Out(){cout << from << " " << to << " " << weight << endl;}
    Edge Reverse() const {return Edge(to, from, weight);}
};


#endif //PLANARITY_EDGE_H
