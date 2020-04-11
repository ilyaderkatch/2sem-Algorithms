#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int n)
{
	Table.resize(n, vector <bool>(n, false));
}

bool operator= (const MatrixGraph &InputGraph)
{
	this->Table = InputGraph.Table;
}

MatrixGraph::MatrixGraph(const IGraph *InputGraph)
{
	int size = InputGraph->VerticesCount();
	Table.resize(size, vector <bool>(size, false));
	for (int i = 0; i < size; ++i)
	{
		vector <int> vertices;
		InputGraph->GetNextVertices(i, vertices);
		for (int j = 0; j < vertices.size(); ++j)
		{
			Table[i][vertices[j]] = true;
		}
	}
}

void MatrixGraph::AddEdge(int from, int to)
{
	Table[from][to] = true;
}

int MatrixGraph::VerticesCount() const
{
	return Table.size();
}

void MatrixGraph::GetNextVertices(int vertex, vector<int> &vertices) const
{
	vertices.resize(0);
	int size = VerticesCount();
	for (int i = 0; i < size; ++i)
	{
		if (Table[vertex][i])
		{
			vertices.push_back(i);
		}
	}
}

void MatrixGraph::GetPrevVertices(int vertex, vector<int> &vertices) const
{
	vertices.resize(0);
	int size = VerticesCount();
	for (int i = 0; i < size; ++i)
	{
		if (Table[i][vertex])
		{
			vertices.push_back(i);
		}
	}
}
