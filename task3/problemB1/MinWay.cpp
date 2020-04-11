#include "MinWay.h"

double INFINITY = 1000000000000.0;

vector <int> operator+(const vector <int> &a, const vector <int> &b)
{
    vector <int> c = a;
    for (int i = 0; i < b.size(); ++i)
    {
        c.push_back(b[i]);
    }
    return c;
}

vector <int> DfsFromVertex(const ListGraph &A, int vertex, int parent)     //находим эйлеров цикл на удвонном мин остове
{                                                                    //по факту обычный дфс по дерево с сохранением порядка обхода
    vector <int> Result(1, vertex);
    vector <Edge> Vertices;
    A.GetNextVertices(vertex, Vertices);
    for (int i = 0; i < Vertices.size(); ++i)
    {
        if (Vertices[i].to != parent)
        {
            Result = Result + DfsFromVertex(A, Vertices[i].to, vertex);
        }
    }
    return Result;
}

vector <int> Dfs(const ListGraph &A)  //тот же поиск, только начало запуска
{
    return DfsFromVertex(A, 0, -1);
}

double MinCycle(const MatrixGraph &A)  //ищем гамильтонов цикл
{
    ListGraph C = Prim(A);   //строим мин остов
    vector <int> Path = Dfs(C); //строим обход приближенного гамильтонова пути
    double res = A.GetWeight(Path[0], Path[Path.size() - 1]);
    for (int i = 0; i < Path.size() - 1; ++i)
    {
        res += A.GetWeight(Path[i], Path[i + 1]); //находим вес
    }
    return res;
}

void swap(vector <int> &A, int i, int j)  //своп элементов
{
    int s = A[i];
    A[i] = A[j];
    A[j] = s;
}
bool NextSequence(vector <int> &A)  //генерация всех перестановок
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
    while(NextSequence(Sequence));  //обновляю перестановку
    return res;
}