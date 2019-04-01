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
    Vertex(int a, double b){to = a; weight = b;}   //vertex with weight
    int to = 0;
    double weight = 0;
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
    virtual void AddEdge(int from, int to, double weight) = 0;

    virtual int VerticesCount() const  = 0;

    virtual void GetNextVertices(int vertex, std::vector<Vertex>& vertices) const = 0;
    virtual void AddEdge(int from, int to) {}
    virtual void InputGraph() = 0;
    virtual bool Ford() const = 0;

    void GetNextVertices(int vertex, std::vector<int>& vertices) const {}
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const {}
};


class ListGraph: public IGraphW{                  //weight ListGraph
private:
    vector <vector <Vertex > > Table;

public:
    ~ListGraph(){}
    ListGraph(int n);

    void InputGraph();
    bool Ford() const;
    int VerticesCount() const;
    bool Out() const;
    void AddEdge(int from, int to, double weight);
    void GetNextVertices(int vertex, vector <Vertex> &vertices) const;
};

//start of graph's implementation
void ListGraph::AddEdge(int from, int to, double weight)
{
    Table[from].push_back(Vertex(to, weight));
    Table[to].push_back(Vertex(from, weight));
}

int ListGraph::VerticesCount() const
{
    return Table.size();
}

void ListGraph::GetNextVertices(int vertex, vector<Vertex> &vertices) const
{
    vertices = Table[vertex];
}

bool ListGraph::Out() const
{
    for (int i = 0; i < Table.size(); ++i)
    {
        for (int j = 0; j < Table[i].size(); ++j)
        {
            cout << Table[i][j].to << "--" <<Table[i][j].weight << "  ";
        }
        cout << endl;
    }
}

ListGraph::ListGraph(int n)
{
    Table.resize(n);
}

void ListGraph::InputGraph()       //input graph for ford's algorithm
{
    for (int i = 0; i < Table.size(); ++i)
    {
        for (int j = 0; j < Table.size(); ++j)
        {
            if (i == j)
            {
                continue;
            }
            double weight = 0;
            cin >> weight;
            if (weight > 0)
            {
                Table[i].push_back({j, weight});
            }
        }
    }
}


bool ListGraph::Ford() const             //ford algorithm
{
    vector <double> Result(Table.size(), 0);
    Result[0] = 1;
    for (int c = 0; c < Table.size() - 1; ++c)
    {
        for (int i = 0; i < Table.size(); ++i)
        {
            for (int j = 0; j < Table[i].size(); ++j)
            {
                if (Result[Table[i][j].to] < Result[i] * Table[i][j].weight)
                {
                    Result[Table[i][j].to] = Result[i] * Table[i][j].weight;     //dynamic update graph
                }
            }
        }
    }
    bool result = false;
    for (int i = 0; i < Table.size(); ++i)
    {
        for (int j = 0; j < Table[i].size(); ++j)
        {
            if (Result[Table[i][j].to] < Result[i] * Table[i][j].weight)
            {
                result = true;                           // opportunity to update graph again -> we have sub-zero cycle
            }
        }
    }
    return result;
}

//end of graph's implementation

int main() {
    int n;
    cin >> n;
    IGraphW* A = new ListGraph(n);
    A->InputGraph();
    if (A->Ford())
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
    return 0;
}
