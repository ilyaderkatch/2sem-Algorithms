#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::min;
using std::max;
using std::sort;
using std::set;


class LCA{
private:
    vector <long long> Parents;
    vector <vector <long long> > GrandParents;
    vector <long long> Depth;
    void Predprocess();
    void UpdateDepth(long long k);

public:
    LCA(long long n);
    void Out();
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
    long long diff = Depth[u] - Depth[v];
    long long deg = 0;
    while (diff != 0)
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
        //cout << u << " " << v << endl;
    }
    if (v == u)
    {
        return v;
    }
    for (int i = int(log2(Parents.size())); i >= 0; --i)
    {
        if (GrandParents[v][i] != GrandParents[u][i])
        {
            v = GrandParents[v][i];
            u = GrandParents[u][i];
        }
       // cout << u << " " << v << endl;
    }
    return Parents[v];
}

void LCA::Out()
{
    for (long long i = 0; i < GrandParents.size(); ++i)
    {
        for (long long j = 0; j < GrandParents[i].size(); ++j)
        {
            cout << GrandParents[i][j] << " ";
        }
        cout << endl;
    }
}

LCA::LCA(long long n)
{
    //Обновляем Родителей
    Parents.resize(0);
    Parents.push_back(0);
    for (long long i = 0; i < n - 1; ++i)
    {
        long long a;
        cin >> a;
        Parents.push_back(a);
    }
    //Обновляем глубину
    Depth.resize(0);
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

void LCA::Predprocess()
{
    long long n = Parents.size();
    GrandParents.resize(n, vector<long long>(int(log2(n))));
    for (long long i = 0; i < n; ++i)
    {
        GrandParents[i][0] = Parents[i];
    }
    for (long long i = 1; i < log2(n); ++i)
    {
        for (long long j = 1; j < n; ++j)
        {
            GrandParents[j][i] = GrandParents[GrandParents[j - 1][i - 1]][i - 1];
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
        //cout << (a + last) % n << " " << b << " " << A.FindParent((a + last) % n, b) << endl;
        last = A.FindParent((a + last) % n, b);
        result += last;
        a = (x * a + y * b + z) % n;
        b = (x * b + y * a + z) % n;
    }
    cout << result << endl;
    return 0;
}
