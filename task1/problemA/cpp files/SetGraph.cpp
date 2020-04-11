#include "SetGraph.h"

SetGraph::SetGraph(int n)
{
	ParentsList.resize(n);
	ChildrenList.resize(n);
}

bool operator= (const SetGraph &InputGraph)
{
	this->ParentsList = InputGraph.ParentsList;
	this->ChildrenList = InputGraph.ChildrenList;
}

SetGraph::SetGraph(const IGraph *InputGraph)
{
	int size = InputGraph->VerticesCount();
	ParentsList.resize(size);
	ChildrenList.resize(size);
	for (int i = 0; i < size; ++i)
	{
		vector <int> vertices;
		InputGraph->GetNextVertices(i, vertices);
		for (int j = 0; j < vertices.size(); ++j)
		{
			ChildrenList[i].AddInt(vertices[j]);
		}
		InputGraph->GetPrevVertices(i, vertices);
		for (int j = 0; j < vertices.size(); ++j)
		{
			ParentsList[i].AddInt(vertices[j]);
		}
	}
}

void SetGraph::AddEdge(int from, int to)
{
	ChildrenList[from].AddInt(to);
	ParentsList[to].AddInt(from);
}

int SetGraph::VerticesCount() const
{
	return ParentsList.size();
}

void SetGraph::GetNextVertices(int vertex, vector<int> &vertices) const
{
	HashTable A = ChildrenList[vertex];
	A.OutputTable(vertices);
}

void SetGraph::GetPrevVertices(int vertex, vector<int> &vertices) const
{
	HashTable A = ParentsList[vertex];
	A.OutputTable(vertices);
}
