#include "ArcGraph.h"

ArcGraph::ArcGraph(int n)
{
	NumVertices = n;
}

ArcGraph::ArcGraph(const IGraph *InputGraph)
{
	NumVertices = InputGraph->VerticesCount();
	for (int i = 0; i < NumVertices; ++i)
	{
		vector <int> vertices;
		InputGraph->GetNextVertices(i, vertices);
		for (int j = 0; j < vertices.size(); ++j)
		{
			Graph.push_back({ i, vertices[j] });
		}
	}
}

void ArcGraph::AddEdge(int from, int to)
{
	for (int i = 0; i < Graph.size(); ++i)
	{
		if (Graph[i].first == from && Graph[i].second == to)
		{
			return;
		}
	}
	Graph.push_back({ from, to });
}

int ArcGraph::VerticesCount() const
{
	return NumVertices;
}

void ArcGraph::GetNextVertices(int vertex, vector<int> &vertices) const
{
	vertices.resize(0);
	for (int i = 0; i < Graph.size(); ++i)
	{
		if (Graph[i].first == vertex)
		{
			vertices.push_back(Graph[i].second);
		}
	}
}

void ArcGraph::GetPrevVertices(int vertex, vector<int> &vertices) const
{
	vertices.resize(0);
	for (int i = 0; i < Graph.size(); ++i)
	{
		if (Graph[i].second == vertex)
		{
			vertices.push_back(Graph[i].first);
		}
	}
}
