#ifndef MatrixGraph_h
#define MatrixGraph_h

#include "IGraph.h"

class MatrixGraph : public IGraph {
private:
	vector <vector <bool> > Table;
	
public:
	MatrixGraph(int n);
	MatrixGraph(const IGraph *InputGraph);

	void AddEdge(int from, int to);
	int VerticesCount() const;
	void GetNextVertices(int vertex, vector<int> &vertices) const;
	void GetPrevVertices(int vertex, vector<int> &vertices) const;
};

#endif