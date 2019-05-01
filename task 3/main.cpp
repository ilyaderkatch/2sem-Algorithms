#include <iostream>
#include <vector>
#include <set>

using std::vector;
using std::set;
using std::cin;
using std::cout;
using std::endl;
using std::pair;

//реализация реба графа

struct Edge
{
    Edge(int _to, int _weight) {to = _to; weight = _weight;}
    int to = 0;
    int weight = 0;
    friend bool operator==(const Edge &a, const Edge &b){return (a.to == b.to) && (a.weight == b.weight);}
    friend bool operator<(const Edge &a, const Edge &b){return (a.weight < b.weight) || ((a.weight == b.weight) && (a.to < b.to));}
    bool Out(){cout << to << " " << weight << endl;}
};

//реализация графа через список смежности

class ListGraph{
private:
    vector <vector <Edge> > ChildrenList;

public:
    ListGraph(int n);

    void AddEdge(int from, int to, int weight);
    int VerticesCount() const;
    void GetNextVertices(int vertex, vector<Edge> &vertices) const;
    int Prim() const;
};


ListGraph::ListGraph(int n)
{
    ChildrenList.resize(n);
}

void ListGraph::AddEdge(int from, int to, int weight)
{
    ChildrenList[from - 1].push_back(Edge(to - 1, weight));
    ChildrenList[to - 1].push_back(Edge(from - 1, weight));
}

int ListGraph::VerticesCount() const
{
    return ChildrenList.size();
}

void ListGraph::GetNextVertices(int vertex, vector<Edge> &vertices) const
{
    vertices = ChildrenList[vertex];
}

int ListGraph::Prim() const  //поиск мин остова
{
    int result = 0;
    vector <bool> IsVisited(this->VerticesCount(), false);
    set <Edge> NotVisitedPairs;
    NotVisitedPairs.insert(Edge(0, 0));
    while (NotVisitedPairs.size() != 0)    //почти дейкстра, взяли очередь с приориетом
    {
        Edge NewVertex = *NotVisitedPairs.begin();    //достали минимальное по весу ребро
        NotVisitedPairs.erase(NotVisitedPairs.begin());
        while (IsVisited[NewVertex.to] == true && NotVisitedPairs.size() != 0)  //берем новое, если вторая вершина уже посещена
        {
            NewVertex = *NotVisitedPairs.begin();
            NotVisitedPairs.erase(NotVisitedPairs.begin());
        }
        if (IsVisited[NewVertex.to] == false)   //добавляем ребро и вершину в мин остов
        {
            IsVisited[NewVertex.to] = true;
            result += NewVertex.weight;
            vector <Edge> Children;
            this->GetNextVertices(NewVertex.to, Children);
            for (int i = 0; i < Children.size(); ++i)  //всех непосещенных детей новой вершины отправляем в стек
            {
                if (!IsVisited[Children[i].to])
                {
                    NotVisitedPairs.insert(Children[i]);
                }
            }
        }

    }
    return result;
}


int main()
{
    int n, m;
    cin >> n >> m;
    ListGraph A(n);
    while(m != 0)
    {
        --m;
        int to, from, weight;
        cin >> to >> from >> weight;
        A.AddEdge(to, from, weight);
    }
    cout << A.Prim() << endl;
    return 0;
}