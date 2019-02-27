#include "ListGraph.h"

ListGraph::ListGraph(int n)
{
	ParentsList.resize(n);
	ChildrenList.resize(n);
}

bool operator= (const ListGraph &InputGraph)
{
	this->ParentsList = InputGraph.ParentsList;
	this->ChildrenList = InputGraph.ChildrenList;
}

ListGraph::ListGraph(const IGraph *InputGraph)
{
	int size = InputGraph->VerticesCount();
	ParentsList.resize(size);
	ChildrenList.resize(size);
	for (int i = 0; i < size; ++i)
	{
		InputGraph->GetNextVertices(i, ChildrenList[i]);
		InputGraph->GetPrevVertices(i, ParentsList[i]);
	}
}

void ListGraph::AddEdge(int from, int to)
{
	for (int i = 0; i < ChildrenList[from].size(); ++i)
	{
		if (ChildrenList[from][i] == to)
		{
			return;
		}
	}
	ChildrenList[from].push_back(to);
	ParentsList[to].push_back(from);
}

int ListGraph::VerticesCount() const
{
	return ParentsList.size();
}

void ListGraph::GetNextVertices(int vertex, vector<int> &vertices) const
{
	vertices = ChildrenList[vertex];
}

void ListGraph::GetPrevVertices(int vertex, vector<int> &vertices) const
{
	vertices = ParentsList[vertex];
}
