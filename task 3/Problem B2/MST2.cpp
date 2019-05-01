#include "MST2.h"

double INFINITY = 10000000000.0;

ListGraph Prim(const MatrixGraph &A)              //Ищем минимальный остов
{
    ListGraph result(A.VerticesCount());
    vector <bool> IsVisited(A.VerticesCount(), false);
    set <Edge> NotVisitedPairs;
    NotVisitedPairs.insert(Edge(0, 0, 0));
    while (NotVisitedPairs.size() != 0)
    {
        Edge NewVertex = *NotVisitedPairs.begin();
        NotVisitedPairs.erase(NotVisitedPairs.begin());
        while (IsVisited[NewVertex.to] == true && NotVisitedPairs.size() != 0)
        {
            NewVertex = *NotVisitedPairs.begin();
            NotVisitedPairs.erase(NotVisitedPairs.begin());
        }
        if (IsVisited[NewVertex.to] == false)
        {
            IsVisited[NewVertex.to] = true;
            result.AddEdge(NewVertex.from, NewVertex.to, NewVertex.weight);
            vector <Edge> Children;
            A.GetNextVertices(NewVertex.to, Children);
            for (int i = 0; i < Children.size(); ++i)
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

void swap(vector <int> &A, int i, int j)   //свап элементов массива
{
    int s = A[i];
    A[i] = A[j];
    A[j] = s;
}
bool NextSequence(vector <int> &A)         //генерация всех возможных перестановок
{
    int j = A.size() - 2;
    while (j != -1 && A[j] >= A[j + 1])
    {
        --j;
    }
    if (j == -1)
    {
        return false;
    }
    int k = A.size() - 1;
    while (A[j] >= A[k])
    {
        --k;
    }
    swap(A, j, k);
    int l = j + 1, r = A.size() - 1;
    while (l<r)
    {
        swap(A, l++, r--);
    }
    return true;
}

vector <int> FindOddVertices(const ListGraph &G)    //Ищем вершины с нечетными степенями, добавляем их в массив
{
    vector <int> res;
    for (int i = 0; i < G.VerticesCount(); ++i)
    {
        if (G.ExtentVertex(i) % 2 != 0)
        {
            res.push_back(i);
        }
    }
    sort(res.begin(), res.end());
    return res;
}

ListGraph MinMatching(const MatrixGraph &G, const vector <int> &A)     //в поисках минимального покрытия нечетных вершин
{
    vector <int> Sequence = A;  //какая-то перестановка ---- разбиение на пары
    double res = INFINITY;
    ListGraph ans(G.VerticesCount());
    do
    {
        double new_res = 0;
        ListGraph new_ans(G.VerticesCount());
        for (int i = 0; i < Sequence.size(); i += 2)
        {
            new_res += G.GetWeight(Sequence[i], Sequence[i + 1]);    //находим вес нового разбиения на пары
            new_ans.AddEdge(Sequence[i], Sequence[i + 1], G.GetWeight(Sequence[i], Sequence[i + 1]));
        }
        if(new_res < res)  //нашли более маленькое разбиение
        {
            res = new_res;
            ans = new_ans;
        }
    }
    while(NextSequence(Sequence));   //обновляем разбиение на пары
    return ans;
}

vector <int> EulerCycle(const ListGraph &A)   //находим эйлеров цикл
{
    vector <int> result;
    stack <int> S;
    int vertex = 0;
    while(vertex < A.VerticesCount() && A.ExtentVertex(vertex) == 0)
    {
        ++vertex;
    }
    S.push(vertex);
    set <Edge> VisitedEdges;
    while (!S.empty())
    {
        int current_vertex = S.top();
        vector <Edge> vertices;
        A.GetNextVertices(current_vertex, vertices);
        for (int i = 0; i < vertices.size(); ++i)
        {
            if (VisitedEdges.find(vertices[i]) == VisitedEdges.end())
            {
                S.push(vertices[i].to);
                VisitedEdges.insert(vertices[i]);
                VisitedEdges.insert(vertices[i].Reverse());
                break;
            }
            if (i == vertices.size() - 1)
            {
                S.pop();
                result.push_back(current_vertex);
            }
        }

    }
    return result;
}

double MinCycle(const MatrixGraph &A)   //наш гамильтонов цикл
{
    ListGraph C = Prim(A); //нашли мин.остов
    vector <int> OddVertices = FindOddVertices(C);  //выделили нечетные вершины из мин остова
    ListGraph Min = MinMatching(A, OddVertices);
    C = C + Min;    //добавили мин покрытие нечетных вершин
    vector <int> Path = EulerCycle(C);   //наш путь - эйлеров цикл
    set <int> VisitedVertices;
    int last_index = 0;
    double result = 0;
    VisitedVertices.insert(Path[0]);
    for (int i = 1; i < Path.size(); ++i)
    {
        if (VisitedVertices.find(Path[i]) == VisitedVertices.end())  //если вершина еще не встречалась, добавляем ее в наш гамильтонов цикл
        {
            result += A.GetWeight(Path[last_index], Path[i]);
            last_index = i;
            VisitedVertices.insert(Path[i]);
        }
    }
    result += A.GetWeight(Path[last_index], Path[0]);
    return result;
}

double CorrectMinCycle(const MatrixGraph &A)  //поиск корректного минимального цикла плолным перебором за факториал
{
    vector <int> Sequence; //перестановка
    for (int i = 0; i < A.VerticesCount(); ++i)
    {
        Sequence.push_back(i);
    }
    double res = INFINITY;
    do
    {
        bool WasBroken = false;
        double new_res = 0;
        int current_vertex = 0;
        set <int> used_vertices;
        for (int i = 0; i < Sequence.size(); ++i)
        {
            if (current_vertex == Sequence[current_vertex]) //проверка на корректность, нельзя прийти в посещенную вершину слишком рано
            {
                WasBroken = true;
                break;
            }
            used_vertices.insert(current_vertex);
            new_res += A.GetWeight(current_vertex, Sequence[current_vertex]);  //обновляем вес конкретного гамильтоного цикла
            current_vertex = Sequence[current_vertex];

        }
        if(new_res < res && !WasBroken && used_vertices.size() == A.VerticesCount())  //проверка на минимальность и корректность перестановк
        {
            res = new_res;
        }
    }
    while(NextSequence(Sequence));
    return res;
}
