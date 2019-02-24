#ifndef IGraph_h
#define IGraph_h

#include <vector>
using std::vector;

class IGraph {
public:
	virtual ~IGraph() {}

	virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const = 0;

	virtual void GetNextVertices(int vertex, vector<int> &vertices) const = 0;
	virtual void GetPrevVertices(int vertex, vector<int> &vertices) const = 0;
};

#endif
