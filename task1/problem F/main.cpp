#include <iostream>
#include <vector>
#include <cmath>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::max;

class ListGraph{
private:
    vector <vector <int> > ParentsList;
    vector <vector <int> > ChildrenList;

public:
    ListGraph(int n);

    void AddEdge(int from, int to);
    int VerticesCount() const;
    void GetNextVertices(int vertex, vector<int> &vertices) const;
    void GetPrevVertices(int vertex, vector<int> &vertices) const;
};


ListGraph::ListGraph(int n)
{
    ParentsList.resize(n);
    ChildrenList.resize(n);
}

void ListGraph::AddEdge(int from, int to)
{
    if (from == to)
    {
        return;
    }
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

void Out(vector <int> A)
{
    for (int i = 0; i < A.size(); ++i)
    {
        cout << A[i] << " ";
    }
    cout << endl;
}

void DfsForTGraph(int vertex, const ListGraph &Graph, vector <int> &visited, int &leave_time)
{
    if (visited[vertex] == 0)
    {
        visited[vertex] = -1;
        vector <int> ChildrenOfVertex;
        Graph.GetNextVertices(vertex, ChildrenOfVertex);
        for (int i = 0; i < ChildrenOfVertex.size(); ++i)
        {
            DfsForTGraph(ChildrenOfVertex[i], Graph, visited, leave_time);
        }
        visited[vertex] = leave_time;
        ++leave_time;
    }
}

void DfsForGraph(int vertex, const ListGraph &Graph, vector <int> &Result, int marker)
{
    if (Result[vertex] == 0)
    {
        Result[vertex] = marker;
        vector <int> ChildrenOfVertex;
        Graph.GetNextVertices(vertex, ChildrenOfVertex);
        for (int i = 0; i < ChildrenOfVertex.size(); ++i)
        {
            DfsForGraph(ChildrenOfVertex[i], Graph, Result, marker);
        }
    }
}

int Kosarau(const ListGraph &Graph, const ListGraph &TGraph, vector <int> &Result)
{
    int n = Graph.VerticesCount();
    vector <int> visited(n, 0);
    int leave_time = 1;
    for (int i = 0; i < n; ++i)
    {
        if (visited[i] == 0)
        {
            DfsForTGraph(i, TGraph, visited, leave_time);
        }
    }
    vector <int> Order(n);
    for (int i = 0; i < n; ++i)
    {
        Order[n - visited[i]] = i;
    }
    int marker = 0;
    for (int i = 0; i < Order.size(); ++i)
    {
        if (Result[Order[i]] == 0)
        {
            DfsForGraph(Order[i], Graph, Result, marker);
            ++marker;
        }
    }
    return marker;
}

ListGraph MakeCondensat(const ListGraph &Graph, const ListGraph &TGraph)
{
    vector <int> Kos(Graph.VerticesCount(), 0);
    int n = Kosarau(Graph, TGraph, Kos);
    ListGraph Condensat(n);
    for (int i = 0; i < Graph.VerticesCount(); ++i)
    {
        vector <int> Children;
        Graph.GetNextVertices(i, Children);
        for (int j = 0; j < Children.size(); ++j)
        {
            Condensat.AddEdge(Kos[i], Kos[Children[j]]);
        }
    }
    return Condensat;
}

int Result(const ListGraph &Graph, const ListGraph &TGraph)
{
    int grand_child = 0;
    int grand_parent = 0;
    ListGraph Condensat = MakeCondensat(Graph, TGraph);
    if (Condensat.VerticesCount() == 1)
    {
        return 0;
    }
    vector <int> parents;
    vector <int> children;
    for (int i = 0; i < Condensat.VerticesCount(); ++i)
    {
        Condensat.GetNextVertices(i, children);
        Condensat.GetPrevVertices(i, parents);
        if (children.size() == 0)
        {
            ++grand_child;
        }
        if (parents.size() == 0)
        {
            ++grand_parent;
        }
    }
    return max(grand_child, grand_parent);
}

int main() {
    int n;
    cin >> n;
    ListGraph Graph(n);
    ListGraph TGraph(n);
    int m;
    cin >> m;
    int a, b;
    while(m != 0)
    {
        --m;
        cin >> a >> b;
        Graph.AddEdge(a - 1, b - 1);
        TGraph.AddEdge(b - 1, a - 1);
    }
    cout << Result(Graph, TGraph) << endl;
    return 0;
}
