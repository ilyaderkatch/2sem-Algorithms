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

int GetTheSecond(int a1, int a2, int a3, int a4, const vector <int> &Array)  //индекс, элемент которого второй по возрастанию
{
    set <pair<int, int> > A;
    A.insert({Array[a1], a1});
    A.insert({Array[a2], a2});
    A.insert({Array[a3], a3});
    A.insert({Array[a4], a4});
    A.erase(A.begin());
    return A.begin()->second;
}

int GetTheFirst(int a1, int a2, const vector <int> &Array) //индекс, элемент которого первый по возрастанию
{
    vector <pair<int, int> > A;
    A.push_back({Array[a1], a1});
    A.push_back({Array[a2], a2});
    sort(A.begin(), A.end());
    return A[0].second;
}

class SparseTable{
private:
    vector <int> Numbers;
    vector <vector <pair <int, int> > > Table;

public:
    SparseTable(int n){Table.resize((int)log2(n) + 1);}
    void InsertValues(const vector <int> &A);
    int GetResult(int i, int j) const;
    void Out1() const;
    void Out2() const;
};

void SparseTable::Out1() const {
    for (int i = 0; i < Table.size(); ++i)
    {
        for (int j = 0; j < Table[i].size(); ++j)
        {
            cout << Numbers[Table[i][j].first] << " ";
        }
        cout << endl;
    }
}

void SparseTable::Out2() const {
    for (int i = 0; i < Table.size(); ++i)
    {
        for (int j = 0; j < Table[i].size(); ++j)
        {
            cout << Numbers[Table[i][j].second] << " ";
        }
        cout << endl;
    }
}

void SparseTable::InsertValues(const vector<int> &A)
{
    Numbers = A;
    vector <pair <int, int> > NewA;
    for (int i = 0; i < A.size(); ++i)
    {
        NewA.push_back({i, i});
    }
    Table[0] = NewA;
    int limit = 1;
    for (int k = 1; k < log2(A.size()); ++k)
    {
        for (int i = 0; i <= A.size() - limit * 2; ++i)
        {
            Table[k].push_back({GetTheFirst(Table[k - 1][i].first, Table[k - 1][i + limit].first, A), GetTheSecond(Table[k - 1][i].first, Table[k - 1][i + limit].first, Table[k - 1][i].second, Table[k - 1][i + limit].second, A)});
        }
        limit *= 2;
    }
}

int SparseTable::GetResult(int i, int j) const
{
    int k = log2(j - i);
    return Numbers[GetTheSecond(Table[k][i - 1].first, Table[k][i - 1].second, Table[k][j - Degree(2, k)].first, Table[k][j - Degree(2, k)].second, Numbers)];
}


int main()
{
    vector <int> A;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        int a;
        cin >> a;
        A.push_back(a);
    }
    SparseTable S(n);
    S.InsertValues(A);
    //S.Out1();
    //S.Out2();
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        cout << S.GetResult(a, b) << endl;
    }
}