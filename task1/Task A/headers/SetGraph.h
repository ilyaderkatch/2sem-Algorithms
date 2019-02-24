#ifndef SetGraph_h
#define SetGraph_h

#include "IGraph.h"
#include "hash.cpp"

class SetGraph : public IGraph {
private:
	vector <HashTable> ParentsList;
	vector <HashTable> ChildrenList;

public:
	SetGraph(int n);
	SetGraph(const IGraph *InputGraph);

	void AddEdge(int from, int to);
	int VerticesCount() const;
	void GetNextVertices(int vertex, vector<int> &vertices) const;
	void GetPrevVertices(int vertex, vector<int> &vertices) const;
};


#endif