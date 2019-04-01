#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::max;
using std::set;
using std::min;

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
    void AddEdge(int from, int to) {}

    virtual int VerticesCount() const  = 0;

    virtual void InputTable() = 0;
    virtual void Floid() = 0;
    virtual void OutputTable() const = 0;

    void GetNextVertices(int vertex, std::vector<int>& vertices) const {}
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const {}
};

class MatrixGraph: public IGraphW{    //weight MatrixGraph
private:
    vector <vector <int> > Table;

public:
    ~MatrixGraph(){}
    MatrixGraph(int n);

    int VerticesCount() const {return Table.size();}
    void InputTable();
    void Floid();
    void OutputTable() const;
};

//start of graph's implementation

MatrixGraph::MatrixGraph(int n)
{
    Table.resize(n, vector <int>(n, 0));
}

void MatrixGraph::InputTable()     //In Graph
{
    for (int i = 0; i < Table.size(); ++i)
    {
        for (int j = 0; j < Table[i].size(); ++j)
        {
            int weight = 0;
            cin >> weight;
            Table[i][j] = weight;
        }
    }
}

void MatrixGraph::Floid()
{
    for (int i = 0; i < Table.size(); ++i)
    {
        for (int a = 0; a < Table.size(); ++a)
        {
            for (int b = 0; b < Table.size(); ++b)
            {
                Table[a][b] = min(Table[a][b], Table[a][i] + Table[i][b]);  //dynamic update
            }
        }
    }
}

void MatrixGraph::OutputTable() const       //Out graph
{
    for (int i = 0; i < Table.size(); ++i)
    {
        for (int j = 0; j < Table.size(); ++j)
        {
            cout << Table[i][j] << " ";
        }
        cout << endl;
    }
}

//end of graph's implementation



int main() {
    int n;
    cin >> n;
    IGraphW* A = new MatrixGraph(n);
    A->InputTable();
    A->Floid();
    A->OutputTable();
    return 0;
}