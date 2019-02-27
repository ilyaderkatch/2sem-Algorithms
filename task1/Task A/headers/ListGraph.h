#ifndef ListGraph_h
#define ListGraph_h

#include "IGraph.h"

class ListGraph: public IGraph{
private:
	vector <vector <int> > ParentsList;
	vector <vector <int> > ChildrenList;

public:
	ListGraph(int n);
	ListGraph(const IGraph *InputGraph);
	ListGraph(const ListGraph *InputGraph);
	
        friend bool operator= (const ListGraph &InputGraph);

	void AddEdge(int from, int to);
        int VerticesCount() const;
        void GetNextVertices(int vertex, vector<int> &vertices) const;
	void GetPrevVertices(int vertex, vector<int> &vertices) const;
};


#endif
