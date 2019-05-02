#include <iostream>
#include <vector>
#include <set>
#include <queue>

using std::queue;
using std::vector;
using std::set;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::min;
using std::max;

int INFINITY = 1000000001;

class MatrixGraph{
private:
    int n = 0; //Параметры графа. n - колво работников, m - колво сортов чая
    int m = 0; //
    vector <vector <int> > Table;
    bool OpportunityToUpgrade(int start, int finish, const MatrixGraph &flow, vector <int> &distance) const;
    int FindBlockWay(int vertex, int result, int finish, MatrixGraph &flow, vector <int> &nondelete, vector <int> &distance) const;
    void AddEdge(int from, int to, int weight);
    void resize(int size);

public:
    MatrixGraph(int n);
    MatrixGraph(){}

    void MakeGraph(int m, int n);
    int VerticesCount() const;
    void GetNextVertices(int vertex, vector<int> &vertices) const;
    int Dinic(int start, int finish) const;
    void UpdateGraph(int z);
    int GetN() const {return n;}
};

void MatrixGraph::resize(int size)
{
    if (Table.size() != 0)
    {
        Table.resize(0);
    }
    Table.resize(size, vector <int>(size, 0));
}

MatrixGraph::MatrixGraph(int n)
{
    Table.resize(n, vector <int>(n, 0));
}

void MatrixGraph::AddEdge(int from, int to, int weight)
{
    Table[from - 1][to - 1] = weight;
}

int MatrixGraph::VerticesCount() const
{
    return Table.size();
}

void MatrixGraph::GetNextVertices(int vertex, vector<int> &vertices) const
{
    vertices = Table[vertex];
}

bool MatrixGraph::OpportunityToUpgrade(int start, int finish, const MatrixGraph &flow, vector <int> &distance) const
{
    distance = vector<int>(this->VerticesCount(), INFINITY);
    distance[start] = 0;
    queue <int> Q;
    Q.push(start);
    while(Q.size() != 0)
    {
        int vertex = Q.front();
        Q.pop();
        for (int i = 0; i < this->VerticesCount(); ++i)
        {
            if (flow.Table[vertex][i] < this->Table[vertex][i] && distance[i] == INFINITY)
            {
                distance[i] = distance[vertex] + 1;
                Q.push(i);
            }
        }
    }
    return distance[finish] != INFINITY;
}

int MatrixGraph::FindBlockWay(int vertex, int result, int finish, MatrixGraph &flow, vector <int> &nondelete, vector <int> &distance) const
{
    if (vertex == finish || result == 0)
    {
        return result;
    }
    for (int i = nondelete[vertex]; i < this->VerticesCount(); ++i)
    {
        if (distance[i] == distance[vertex] + 1)
        {
            int delta = this->FindBlockWay(i, min(result, this->Table[vertex][i] - flow.Table[vertex][i]), finish, flow, nondelete, distance);
            if (delta != 0)
            {
                flow.Table[vertex][i] += delta;
                flow.Table[i][vertex] -= delta;
                return delta;
            }
        }
        ++nondelete[vertex];
    }
    return 0;
}

int MatrixGraph::Dinic(int start, int finish) const //поик максимального потока
{
    MatrixGraph flow (this->VerticesCount());
    vector <int> distance(this->VerticesCount(), INFINITY);
    int result = 0;
    while(this->OpportunityToUpgrade(start, finish, flow, distance))
    {
        vector <int> nondelete(this->VerticesCount(), 0);
        int delta = this->FindBlockWay(start, INFINITY, finish, flow, nondelete, distance);
        while(delta != 0)
        {
            result += delta;
            delta = this->FindBlockWay(start, INFINITY, finish, flow, nondelete, distance);
        }
    }
    return result;
}

void MatrixGraph::MakeGraph(int _n, int _m) //делаем граф и сводим задачу к проверку на максимальный поток
{
    n = _n;
    m = _m;
    this->resize(m + n + 2);
    for (int i = 0; i < m; ++i)
    {
        int a;
        cin >> a;
        this->AddEdge(n + 2 + i, m + n + 2, a);
    }
    for (int i = 0; i < n; ++i)
    {
        int b;
        cin >> b;
        for (int j = 0; j < b; ++j)
        {
            int c;
            cin >> c;
            this->AddEdge(i + 2, n + c + 1, INFINITY);
        }
    }
}

void MatrixGraph::UpdateGraph(int z) //обновлене графа при поиске ответа
{
    for (int i = 0; i < this->n; ++i)
    {
        this->AddEdge(1, i + 2, z);
    }
}

int BinarySearch(MatrixGraph &A) //ищем ответ бинпоиском
{
    int min = 0;
    int max = INFINITY;
    while (min + 1!= max)
    {
        int update = (min + max) / 2;
        A.UpdateGraph(update);
        if (A.Dinic(0, A.VerticesCount() - 1) == update * A.GetN())
        {
            min = update;
        }
        else
        {
            max = update;
        }
    }
    return min;
}


int main()
{
    int n, m;
    cin >> n >> m;
    MatrixGraph A;
    A.MakeGraph(n, m);
    cout << BinarySearch(A) << endl;
    return 0;
}