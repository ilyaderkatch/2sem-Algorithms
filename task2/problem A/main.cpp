#include <iostream>
#include <vector>
#include <cmath>
#include <set>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::max;
using std::set;

const int BIG_INT = 4294967295; // unsigned int a; (a - 1) = 4294967295

struct Vertex{
    Vertex(int a, unsigned int b){to = a; weight = b;}   //vertex with weight
    int to = 0;
    unsigned int weight = 0;
};

struct IGraph {                                  //abstract graph
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0;
};

struct IGraphW: public IGraph{                  //abstract weight graph
    virtual ~IGraphW(){}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to, unsigned int weight) = 0;

    virtual int VerticesCount() const  = 0;

    virtual void GetNextVertices(int vertex, std::vector<Vertex>& vertices) const = 0;
    virtual void AddEdge(int from, int to) {}
    void GetNextVertices(int vertex, std::vector<int>& vertices) const {}
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const {}
};


class ListGraph: public IGraphW{                 //weight ListGraph
private:
    vector <vector <Vertex> > ChildrenList;

public:
    ListGraph(int n);
    ~ListGraph(){};

    void AddEdge(int from, int to, unsigned int weight);
    int VerticesCount() const;
    void GetNextVertices(int vertex, vector<Vertex> &vertices) const;
};

//start of graph's implementation

ListGraph::ListGraph(int n)
{
    ChildrenList.resize(n);
}

void ListGraph::AddEdge(int from, int to, unsigned int weight)
{
    ChildrenList[from].push_back(Vertex(to, weight));
    ChildrenList[to].push_back(Vertex(from, weight));
}

int ListGraph::VerticesCount() const
{
    return ChildrenList.size();
}

void ListGraph::GetNextVertices(int vertex, vector<Vertex> &vertices) const
{
    vertices = ChildrenList[vertex];
}

//end of graph's implementation

unsigned int FindShortWay(const IGraphW* Graph, int start, int finish) //dejkstra algorithm
{
    vector <unsigned int> Ans(Graph->VerticesCount(), BIG_INT);     //current weight of vertex
    vector <bool> Finished(Graph->VerticesCount(), false);          //finished vertices with correct length
    Ans[start] = 0;
    set <pair <unsigned int, int> > Q;    // priority queue of vertices
    Q.insert({0, start});
    while (Q.size() != 0 && Q.begin()->second != finish)
    {
        int vertex = Q.begin()->second;
        unsigned int weight = Q.begin()->first;
        Q.erase(Q.begin());
        if (!Finished[vertex])
        {
            Finished[vertex] = true;
            vector <Vertex> Children;
            Graph->GetNextVertices(vertex, Children);
            for (int i = 0; i < Children.size(); ++i)
            {
                if (Children[i].weight + weight < Ans[Children[i].to])     //find shorter way
                {
                    Ans[Children[i].to] = Children[i].weight + weight;
                    Q.insert({Ans[Children[i].to], Children[i].to});
                }
            }
        }
    }
    return Ans[finish];
}



int main() {
    int n;
    cin >> n;
    IGraphW* A = new ListGraph(n);
    int m;
    cin >> m;
    while(m != 0)
    {
        --m;
        int a, b;
        unsigned int w;
        cin >> a >> b >> w;
        A->AddEdge(a, b, w);
    }
    int start, finish;
    cin >> start >> finish;
    cout << FindShortWay(A, start, finish) << endl;
    return 0;
}
