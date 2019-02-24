//find number of different the shortest ways in graph
#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::cin;
using std::cout;
using std::endl;
using std::pair;

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

int FindWay(int start, int finish, const ListGraph &A)
{
	vector <pair<int, int> > Combinations(A.VerticesCount(), { 0, 0 }); //The first argument is num of the shortest ways to the vertex, the second is depth in BFS too
	queue <int> Q;
	Q.push(start);
	Combinations[start] = { 1, 0 };
	while (Q.size()) //cycle of bfs
	{
		int v = Q.front();
		Q.pop();
		vector <int> vertices;
		A.GetNextVertices(v, vertices);
		for (int i = 0; i < vertices.size(); ++i)
		{
			if (Combinations[vertices[i]].first == 0)
			{
				Combinations[vertices[i]].first = Combinations[v].first;
				Combinations[vertices[i]].second = Combinations[v].second + 1;
				Q.push(vertices[i]);
			}
			else if (Combinations[vertices[i]].second == Combinations[v].second + 1) // if it is one of the shortest way
			{
				Combinations[vertices[i]].first += Combinations[v].first;
			}
		}
	}
	return Combinations[finish].first;
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
	int start, finish;
	cin >> start >> finish;
	cout << FindWay(start, finish, A) << endl;
	return 0;
}
