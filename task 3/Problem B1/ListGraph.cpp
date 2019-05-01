#include "ListGraph.h"

vector <Edge> operator+(const vector <Edge> &a, const vector <Edge> &b)
{
    vector <Edge> c = a;
    for (int i = 0; i < b.size(); ++i)
    {
        c.push_back(b[i]);
    }
    return c;
}

ListGraph::ListGraph(int n)
{
    ChildrenList.resize(n);
}

void ListGraph::AddEdge(int from, int to, double weight)
{
    if (to != from)
    {
        ChildrenList[from].push_back(Edge(from, to, weight));
        ChildrenList[to].push_back(Edge(to, from, weight));
    }
}

int ListGraph::VerticesCount() const
{
    return ChildrenList.size();
}

void ListGraph::GetNextVertices(int vertex, vector<Edge> &vertices) const
{
    vertices = ChildrenList[vertex];
}

void ListGraph::Output()
{
    for (int i = 0; i < ChildrenList.size(); ++i)
    {
        for (int j = 0; j < ChildrenList[i].size(); ++j)
        {
            cout << i << " " << ChildrenList[i][j].to  << " " << ChildrenList[i][j].weight << endl;
        }
    }
}

int ListGraph::ExtentVertex(int vertex) const
{
    return ChildrenList[vertex].size();
}

ListGraph ListGraph::operator+(const ListGraph &B)
{
    ListGraph C(this->VerticesCount());
    for (int i = 0; i < this->VerticesCount(); ++i)
    {
        C.ChildrenList[i] = this->ChildrenList[i] + B.ChildrenList[i];

    }
    return C;
}