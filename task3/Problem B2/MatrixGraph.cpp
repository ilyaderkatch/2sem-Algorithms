#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int n)
{
    Table.resize(n, vector <double>(n, 0));
}

void MatrixGraph::AddEdge(int from, int to, double weight)
{
    Table[from][to] = weight;
    Table[to][from] = weight;
}

int MatrixGraph::VerticesCount() const
{
    return Table.size();
}

void MatrixGraph::GetNextVertices(int vertex, vector<Edge> &vertices) const
{
    int size = VerticesCount();
    for (int i = 0; i < size; ++i)
    {
        if (Table[vertex][i] > 0.0000001)
        {
            vertices.push_back(Edge(vertex, i, Table[vertex][i]));
        }
    }
}

double MatrixGraph::GetWeight(int i, int j) const
{
    return Table[i][j];
}

MatrixGraph MatrixGraph::operator+(const MatrixGraph &B)
{
    MatrixGraph C(this->VerticesCount());
    for (int i = 0; i < this->VerticesCount(); ++i)
    {
        for (int j = 0; j < this->VerticesCount(); ++j)
        {
            C.Table[i][j] = GetWeight(i, j) + B.GetWeight(i, j);
        }
    }
    return C;
}

void MatrixGraph::Foutput(string s)
{
    ofstream out;
    out.open(s, ios::app);
    for (int i = 0; i < Table.size(); ++i)
    {
        for (int j = 0; j < Table.size(); ++j)
        {
            out << Table[i][j] << " ";
        }
        out << endl;
    }
    out << endl;
}
