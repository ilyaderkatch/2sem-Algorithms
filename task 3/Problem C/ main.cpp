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

//реализация графа
class MatrixGraph{
private:
    vector <vector <int> > Table;

public:
    MatrixGraph(int n);

    void AddEdge(int from, int to, int weight);
    int VerticesCount() const;
    void GetNextVertices(int vertex, vector<int> &vertices) const;
    int Dinic(int start, int finish) const;
    bool OpportunityToUpgrade(int start, int finish, const MatrixGraph &flow, vector <int> &distance) const;
    int FindBlockWay(int vertex, int result, int finish, MatrixGraph &flow, vector <int> &nondelete, vector <int> &distance) const;
};


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

bool MatrixGraph::OpportunityToUpgrade(int start, int finish, const MatrixGraph &flow, vector <int> &distance) const //проверяем bfs'ом можно ли пройти от старта к финишу
{                                                                                                                    //заодно разбиваем на слои граф
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

int MatrixGraph::FindBlockWay(int vertex, int result, int finish, MatrixGraph &flow, vector <int> &nondelete, vector <int> &distance) const //ищем блокирующий поток
{
    if (vertex == finish || result == 0) //если дошли до финиша, то вернуть величину потока. Если величина потока ноль, то искать дальше нет смысла
    {
        return result;
    }
    for (int i = nondelete[vertex]; i < this->VerticesCount(); ++i)
    {
        if (distance[i] == distance[vertex] + 1) //если находятся на соседних слоях
        {
            int delta = this->FindBlockWay(i, min(result, this->Table[vertex][i] - flow.Table[vertex][i]), finish, flow, nondelete, distance); //насколько можно увеличить поток потом
            if (delta != 0)
            {
                flow.Table[vertex][i] += delta; //прибавляем к потоку к конкретному ребру эту дельту
                flow.Table[i][vertex] -= delta;
                return delta;
            }
        }
        ++nondelete[vertex]; //больше по этому ребенку можно не идти, тк путь заблокирован
    }
    return 0;
}

int MatrixGraph::Dinic(int start, int finish) const
{
    MatrixGraph flow (this->VerticesCount()); //максимальный поток
    vector <int> distance(this->VerticesCount(), INFINITY); // вектор расстояний до стартовой вершины в сллоистой системе
    int result = 0; // величина потока
    while(this->OpportunityToUpgrade(start, finish, flow, distance)) //пока можем найти поток из стартовой в финальную вершину
    {
        vector <int> nondelete(this->VerticesCount(), 0); //для каждой вершины храним минимальный номер ребенка, который еще не заблокирован
        int delta = this->FindBlockWay(start, INFINITY, finish, flow, nondelete, distance);
        while(delta != 0) // пока есть блокирующий поток
        {
            result += delta;
            delta = this->FindBlockWay(start, INFINITY, finish, flow, nondelete, distance);
        }
    }
    return result;
}



int main()
{
    int n, m;
    cin >> n >> m;
    MatrixGraph A(n);
    while(m != 0)
    {
        --m;
        int to, from, weight;
        cin >> to >> from >> weight;
        A.AddEdge(to, from, weight);
    }
    cout << A.Dinic(0, n - 1) << endl; //ищем макс поток в через первую и последнююю вершины
    return 0;
}
