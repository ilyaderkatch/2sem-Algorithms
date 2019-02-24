//is graph dicotyledonous
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

bool IsTwoPartGraph(const ListGraph &A)
{
	vector <int> Visited(A.VerticesCount(), 0); //color of vertex
	for (int i = 0; i < A.VerticesCount(); ++i)
	{
		if (Visited[i] == 0)
		{
			queue <int> Q;
			Q.push(i);
			Visited[i] = 1;
			while (Q.size())
			{
				int v = Q.front();
				Q.pop();
				vector <int> vertices;
				A.GetNextVertices(v, vertices);
				for (int i = 0; i < vertices.size(); ++i)
				{
					if (Visited[vertices[i]] == 0)
					{
						Visited[vertices[i]] = -Visited[v]; //paint another color than parent's color
						Q.push(vertices[i]);
					}
					else
					{
						if (Visited[vertices[i]] == Visited[v])
						{
							return false; 
						}
					}
				}
			}
		}
	}
	return true;
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
	if (IsTwoPartGraph(A))
	{
		cout << "YES" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}
	return 0;
}

