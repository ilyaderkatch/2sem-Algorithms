#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

int log(int n) {   //считаем двоичный логорифм
    if (n == 1) {
        return 0;
    }
    return log(n / 2) + 1;
}

class LCA{
private:
    vector <long long> Parents; //список родителей
    vector <vector <long long> > GrandParents; //список родитлей со степенным шагом
    vector <long long> Depth;  //глубина для каждой вершины
    void Predprocess();
    void UpdateDepth(long long k);

public:
    LCA(long long n);
    long long FindParent(long long u, long long v) const;
};

void LCA::UpdateDepth(long long k)
{
    if (Depth[Parents[k]] == -1)
    {
        UpdateDepth(Parents[k]);
    }
    Depth[k] = Depth[Parents[k]] + 1;
}

long long LCA::FindParent(long long u, long long v) const
{
    if (Depth[u] < Depth[v])
    {
        long long t = u;
        u = v;
        v = t;
    }
    long long diff = Depth[u] - Depth[v];  //разница глубин
    long long deg = 0;
    while (diff != 0)   //устраняем разницу, делая степенные полъемы
    {
        if (diff % 2 == 1)
        {
            u = GrandParents[u][deg];
            diff -= 1;
        }
        else
        {
            diff /= 2;
            deg += 1;
        }
    }
    if (v == u)
    {
        return v;
    }
    for (int i = int(log(Parents.size())); i >= 0; --i)  //ищем разных предков на одном уровне - если таких нет, то мы нашли ответ
    {
        if (GrandParents[v][i] != GrandParents[u][i])
        {
            v = GrandParents[v][i];
            u = GrandParents[u][i];
        }
    }
    return Parents[v];  //ответ - их общий предок
}

LCA::LCA(long long n)
{
    //Обновляем Родителей
    Parents.push_back(0);
    for (long long i = 0; i < n - 1; ++i)
    {
        long long a;
        std::cin >> a;
        Parents.push_back(a);
    }
    //Обновляем глубину
    Depth.resize(n, -1);
    Depth[0] = 0;
    for (long long i = 0; i < Depth.size(); ++i)
    {
        if (Depth[i] == -1)
        {
            this->UpdateDepth(i);
        }
    }
    //Обновляем родителей с степенным шагом
    this->Predprocess();
}

void LCA::Predprocess() // динамическое заполнение списка родителей со степенным шагом
{
    long long n = Parents.size();
    GrandParents.resize(n, vector<long long>(log(n) + 1));
    for (long long i = 0; i < n; ++i)
    {
        GrandParents[i][0] = Parents[i];
    }
    for (long long i = 1; i < log(n); ++i)
    {
        for (long long j = 1; j < n; ++j)
        {
            GrandParents[j][i] = GrandParents[GrandParents[j][i - 1]][i - 1];
        }
    }
}

int main()
{
    long long n, m;
    cin >> n >> m;
    LCA A(n);
    long long a, b;
    cin >> a >> b;
    long long x, y, z;
    cin >> x >> y >> z;
    long long result = 0;
    long long last = 0;
    for (long long i = 0; i < m; ++i)
    {
        last = A.FindParent((a + last) % n, b);
        result += last;
        a = (x * a + y * b + z) % n; //генерация новых запросов
        b = (x * b + y * a + z) % n;
    }
    cout << result << endl;
    return 0;
}
