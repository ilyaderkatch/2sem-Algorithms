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

int Degree(int a, int n)
{
    if (n == 0)
    {
        return 1;
    }
    return Degree(a, n - 1) * a;
}

class LCA{
private:
    vector <int> Parents;
    vector <vector <int> > GrandParents;
    vector <int> Depth;
    void Predprocess();
    void UpdateDepth(int k);

public:
    LCA(int n);
    void Out();
    int FindParent(int u, int v) const;

};

void LCA::UpdateDepth(int k)
{
    if (Depth[Parents[k]] == -1)
    {
        UpdateDepth(Parents[k]);
    }
    Depth[k] = Depth[Parents[k]] + 1;
}

int LCA::FindParent(int u, int v) const
{
    if (Depth[u] < Depth[v])
    {
        int t = u;
        u = v;
        v = t;
    }
    int diff = Depth[u] - Depth[v];
    int deg = 0;
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
    for (int i = 0; i < GrandParents.size(); ++i)
    {
        for (int j = 0; j < GrandParents[i].size(); ++j)
        {
            cout << GrandParents[i][j] << " ";
        }
        cout << endl;
    }
}

LCA::LCA(int n)
{
    //Обновляем Родителей
    Parents.resize(0);
    Parents.push_back(0);
    for (int i = 0; i < n - 1; ++i)
    {
        int a;
        cin >> a;
        Parents.push_back(a);
    }
    //Обновляем глубину
    Depth.resize(0);
    Depth.resize(n, -1);
    Depth[0] = 0;
    for (int i = 0; i < Depth.size(); ++i)
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
    int n = Parents.size();
    GrandParents.resize(n, vector<int>(int(log2(n))));
    for (int i = 0; i < n; ++i)
    {
        GrandParents[i][0] = Parents[i];
    }
    for (int i = 1; i < log2(n); ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            GrandParents[j][i] = GrandParents[GrandParents[j - 1][i - 1]][i - 1];
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    LCA A(n);
    int a, b;
    cin >> a >> b;
    int x, y, z;
    cin >> x >> y >> z;
    int result = 0;
    int last = 0;
    for (int i = 0; i < m; ++i)
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