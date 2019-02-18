//Ќайти цикл минимальной длины(задача2)

#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::cin;
using std::cout;
using std::endl;
using std::pair;

//реализаци€ графа

class ListGraph{
private:
	vector <vector <int> > ChildrenList;

public:
	ListGraph(int n);

	void AddEdge(int from, int to);
	int VerticesCount() const;
	void GetNextVertices(int vertex, vector<int> &vertices) const;
};


ListGraph::ListGraph(int n)
{
	ChildrenList.resize(n);
}

void ListGraph::AddEdge(int from, int to)
{
	for (int i = 0; i < ChildrenList[from].size(); ++i)
	{
		if (ChildrenList[from][i] == to)
		{
			return;
		}
	}
	ChildrenList[from].push_back(to);
	ChildrenList[to].push_back(from);
}

int ListGraph::VerticesCount() const
{
	return ChildrenList.size();
}

void ListGraph::GetNextVertices(int vertex, vector<int> &vertices) const
{
	vertices = ChildrenList[vertex];
}

//конец реализации графа

int CycleFromVertix(int vertex, const ListGraph &A)
{
	vector <pair <int, int> > Visited(A.VerticesCount(), {0,0}); //первое поле глубина, второе поле номер родител€(все значени€ определ€ютс€ в пор€дке обхода bfs
	queue <int> Q;
	Q.push(vertex);
	Visited[vertex] = { 1, -1 };
	while (Q.size())
	{
		int v = Q.front();
		Q.pop();
		vector <int> vertices;
		A.GetNextVertices(v, vertices);
		for (int i = 0; i < vertices.size(); ++i)
		{
			if (Visited[vertices[i]].first == 0)
			{
				Visited[vertices[i]].first = Visited[v].first + 1;
				Visited[vertices[i]].second = v;
				Q.push(vertices[i]);
			}
			else if (Visited[v].second != vertices[i])
			{
				return Visited[v].first + Visited[vertices[i]].first - 1; //если пришли уже в хоженую вершину(не родитель), то нашли цикл
			}
		}
	}
	return -1;
}

int MinCycle(const ListGraph &A) // находим минимальный цикл - проходимс€ от каждой вершины
{
	int mincycle = -1;
	for (int i = 0; i < A.VerticesCount(); ++i)
	{
		int x = CycleFromVertix(i, A);
		if (mincycle == -1 || (x > 0 && x < mincycle))
		{
			mincycle = x;
		}
	}
	return mincycle;
}



int main()
{
	int v, n;
	cin >> v >> n;
	ListGraph A(v);
	while (n != 0)
	{
		--n;
		int a, b;
		cin >> a >> b;
		A.AddEdge(a, b);
	}
	cout << MinCycle(A) << endl;
	return 0;
}
