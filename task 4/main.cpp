#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::max;

struct Vertex{
public:
    int suf = 0;
    int pref = 0;
    int len = 1;
    bool all_one = false;
    int max = 0;
    Vertex(int _pref, int _suf, int _len, bool _all_one, int _max) {pref = _pref; suf = _suf; len = _len; all_one = _all_one; max = _max;}
    Vertex() {}
};

vector <Vertex> IntToVertex(vector <int> A)
{
    int new_size = 1;
    while(A.size() > new_size)
    {
        new_size *= 2;
    }
    vector <Vertex> NewA(new_size);
    for (int i = 0; i < A.size(); ++i)
    {
        NewA[i] = Vertex(A[i], A[i], 1, A[i], A[i]);
    }
    return NewA;
}

Vertex Merge(Vertex v1, Vertex v2)
{
    Vertex ans;
    ans.len = v1.len + v2.len;
    ans.max = max(v1.suf + v2.pref, max(v1.max, v2.max));
    ans.all_one = v1.all_one && v2.all_one;
    if (v1.all_one)
    {
        ans.pref = v1.pref + v2.pref;
    }
    else
    {
        ans.pref = v1.pref;
    }
    if (v2.all_one)
    {
        ans.suf = v1.suf + v2.suf;
    }
    else
    {
        ans.pref = v2.suf;
    }
    return ans;
}

class SegmentTree{
private:
    vector <Vertex> Tree;
    void TreeBuild(const vector <Vertex> &A, int a, int b, int i);
    Vertex UpToDown(int l, int r, int x, int lx, int rx) const;

public:
    SegmentTree(const vector <Vertex> &A);
    int FindAnswer(int i, int j) const;
};

void SegmentTree::TreeBuild(const vector<Vertex> &A, int a, int b, int i)
{
    if (a == b)
    {
        return;
    }
    if (b - a == 1)
    {
        Tree[i] = A[i];
    }
    else
    {
        int m = (a + b) / 2;
        TreeBuild(A, 2 * i + 1, a, m);
        TreeBuild(A, 2 * i + 2, m, b);
        Tree[i] = Merge(Tree[2 * i + 1], Tree[2 * i + 2]);
    }
}

Vertex SegmentTree::UpToDown(int l, int r, int x, int lx, int rx) const
{
    if (l <= lx && r >= rx)
    {
        return Tree[x];
    }
    if (l >= rx || r <= lx)
    {
        return Vertex(0, 0, 0, 0, 0);
    }
    int mx = (lx + rx) / 2;
    return Merge(UpToDown(l, r, 2 * x + 1, lx, mx), UpToDown(l, r, 2 * x + 2, mx, rx));

}

int SegmentTree::FindAnswer(int i, int j) const
{
    return UpToDown(i, j, 0, 0, (Tree.size() + 1) / 2).max;
}

SegmentTree::SegmentTree(const vector <Vertex> &A)
{
    Tree.resize(A.size() * 2 - 1);
    TreeBuild(A, 0, A.size(), 0);
}

int main()
{
    int n, m;
    vector <int> A;
    for (int i = 0; i < n; ++i)
    {
        int a;
        cin >> a;
        A.push_back(a);
    }
    SegmentTree T(IntToVertex(A));
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        cout << T.FindAnswer(a, b) << endl;
    }
    return 0;
}