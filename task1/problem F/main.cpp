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

    void DfsForTGraph(int vertex, vector <int> &visited, int &leave_time) const;
    void DfsForGraph(int vertex, vector <int> &Result, int marker) const;
    ListGraph MakeTGraph() const;
    void Kosarau(vector <int> &Result, int &marker) const;
    ListGraph MakeCondensat() const;

public:
    ListGraph(int n);

    void AddEdge(int from, int to);
    int VerticesCount() const;
    void GetNextVertices(int vertex, vector<int> &vertices) const;
    void GetPrevVertices(int vertex, vector<int> &vertices) const;

    int Result() const;
};

//start of graph's implementation


ListGraph::ListGraph(int n)
{
    ParentsList.resize(n);
    ChildrenList.resize(n);
}

void ListGraph::AddEdge(int from, int to)
{
    from = from - 1;
    to = to - 1;
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

//end of graph's implementation

void ListGraph::DfsForTGraph(int vertex, vector <int> &visited, int &leave_time) const //DFS for transposed graph with leave time for all vertexes
{
    if (visited[vertex] == 0)
    {
        visited[vertex] = -1;
        for (int i = 0; i < ChildrenList.size(); ++i)
        {
            for (int j = 0; j < ChildrenList[i].size(); ++j)
            {
                this->DfsForTGraph(ChildrenList[i][j], visited, leave_time);
            }
        }
        visited[vertex] = leave_time;
        ++leave_time;
    }
}

void ListGraph::DfsForGraph(int vertex, vector <int> &Result, int marker) const //DFS for normal graph
{
    if (Result[vertex] == 0)
    {
        Result[vertex] = marker;
        for (int j = 0; j < ChildrenList[vertex].size(); ++j)
        {
            this->DfsForGraph(ChildrenList[vertex][j], Result, marker);
        }
    }
}

ListGraph ListGraph::MakeTGraph() const //Make transposed Graph
{
    ListGraph TGraph(this->VerticesCount());
    for (int i = 0; i < this->VerticesCount(); ++i)
    {
        vector <int> children;
        this->GetNextVertices(i, children);
        for (int j = 0; j < children.size(); ++j)
        {
            TGraph.AddEdge(children[j], i);
        }
    }
    return TGraph;
}

void ListGraph::Kosarau(vector <int> &Result, int &marker) const  //Kosarau algorithm
{
    ListGraph TGraph = this->MakeTGraph();
    int n = this->VerticesCount();
    vector <int> visited(n, 0);
    int leave_time = 1;
    for (int i = 0; i < n; ++i)
    {
        if (visited[i] == 0)
        {
            TGraph.DfsForTGraph(i, visited, leave_time);   //take order
        }
    }
    vector <int> Order(n);
    for (int i = 0; i < n; ++i)
    {
        Order[n - visited[i]] = i;
    }
    for (int i = 0; i < Order.size(); ++i)
    {
        if (Result[Order[i]] == 0)
        {
            this->DfsForGraph(Order[i], Result, marker);     //make dfs with special order
            ++marker;
        }
    }
}

ListGraph ListGraph::MakeCondensat() const   // Make Condensat from graph
{
    vector <int> Kos(this->VerticesCount(), 0);
    ListGraph TGraph = this->MakeTGraph();  //take TGraph
    int n = 1;
    this->Kosarau(Kos, n);                  //divide to components
    ListGraph Condensat(n);
    for (int i = 0; i < this->VerticesCount(); ++i)
    {
        vector <int> Children;
        this->GetNextVertices(i, Children);
        for (int j = 0; j < Children.size(); ++j)
        {
            Condensat.AddEdge(Kos[i], Kos[Children[j]]);
        }
    }
    return Condensat;
}

int ListGraph::Result() const       //take a result of the problem
{
    int grand_child = 0;
    int grand_parent = 0;
    ListGraph Condensat = this->MakeCondensat();
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
        Graph.AddEdge(a, b);
    }
    cout << Graph.Result() << endl;
    return 0;
}
