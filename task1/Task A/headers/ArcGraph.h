#ifndef ArcGraph_h
#define ArcGraph_h

#include "IGraph.h"

using std::pair;

class ArcGraph : public IGraph {
private:
	vector <pair<int, int> > Graph;
	int NumVertices = 0;

public:
	ArcGraph(int n);
	ArcGraph(const IGraph *InputGraph);
	ArcGraph(const ArcGraph *InputGraph);
	
        friend bool operator= (const ArcGraph &InputGraph);

	void AddEdge(int from, int to);
	int VerticesCount() const;
	void GetNextVertices(int vertex, vector<int> &vertices) const;
	void GetPrevVertices(int vertex, vector<int> &vertices) const;
};

#endif
