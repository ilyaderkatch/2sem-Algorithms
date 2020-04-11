#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;


struct CTreapNode
{
    string name;
    int value = 0;
    CTreapNode* left = NULL;
    CTreapNode* right = NULL;
    CTreapNode* parent = NULL;
    CTreapNode(string _name){name = _name, value = 1;};
};

void UpdateValue(CTreapNode* A)
{
    A->value = 1;
    if (A->left != NULL)
    {
        A->value += A->left->value;
    }
    if (A->right != NULL)
    {
        A->value += A->right->value;
    }
}

class Treap
{
private:
    CTreapNode* first;
    void Split(int key, CTreapNode* first, CTreapNode*& left_tree, CTreapNode*& right_tree);
    CTreapNode* Merge(CTreapNode* left_tree, CTreapNode* right_tree);
    void Delete(CTreapNode* node);
public:
    Treap();
    ~Treap();
    void InsertAt(int x, string name);
    void DeleteAt(int k1, int k2);
    string GetAt(int pos);
};

string Treap::GetAt(int pos)
{
    int LeftValue;
    CTreapNode* new_node = first;
    int sum = 0;
    while(true)
    {
        if (new_node->left == NULL)
        {
            LeftValue = 0;
        }
        else
        {
            LeftValue = new_node->left->value;
        }

        //cout << new_node->name << " " << new_node->value << " " << LeftValue << endl;

        if(pos == LeftValue + sum)
        {
            break;
        }
        else if (pos < LeftValue + sum)
        {
            new_node = new_node->left;
        }
        else {
            new_node = new_node->right;
            sum += LeftValue + 1;
        }

    }

    return new_node->name;
}

void Treap::DeleteAt(int k1, int k2)
{
    CTreapNode* left = NULL;
    CTreapNode* right = NULL;
    CTreapNode* left2 = NULL;
    CTreapNode* right2 = NULL;
    Split(k1, first, left, right);
    Split(k2 - k1, right, left2, right2);

    Delete(left2);
    first = Merge(left, right2);

}

void Treap::InsertAt(int position, string name)
{
    CTreapNode* element = new CTreapNode(name);
    if (first == NULL)
    {
        first = element;
        return;
    }
    Split(position, first, element->left, element->right);
    first = element;
    UpdateValue(first);
}

void Treap::Split(int k, CTreapNode* first, CTreapNode*& left_tree, CTreapNode*& right_tree )
{
    if(first == NULL)
    {
        left_tree = NULL;
        right_tree = NULL;
        return;
    }

    int l;
    if (left_tree == NULL)
    {
        l = 0;
    }
    else
    {
        l = left_tree->value;
    }

    if(l >= k)
    {
        Split(k, first->left, left_tree, first->left);
        UpdateValue(first);
        right_tree = first;
    }
    else
    {
        Split(k - l - 1, first->right, first->right, right_tree );
        UpdateValue(first);
        left_tree = first;
    }
}

CTreapNode* Treap::Merge(CTreapNode* left_tree, CTreapNode* right_tree)
{
    if (left_tree == NULL)
    {
        return right_tree;
    }
    if (right_tree == NULL)
    {
        return left_tree;
    }
    if (left_tree->value > right_tree->value)
    {
        left_tree->right = Merge(left_tree->right, right_tree);
        UpdateValue(left_tree);
        return left_tree;
    }
    else
    {
        right_tree->left = Merge(left_tree, right_tree->left);
        UpdateValue(right_tree);
        return right_tree;
    }
}

Treap::Treap()
{
    first = NULL;
}

void Treap::Delete(CTreapNode* node)
{
    if (node == NULL)
    {
        return;
    }
    Delete(node->right);
    Delete(node->left);
    delete node;
}

Treap::~Treap()
{
    Delete(first);
}

int main()
{
    Treap A;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        char s;
        cin >> s;
        if (s == '+')
        {
            int position;
            string S;
            cin >> position >> S;
            A.InsertAt(position, S);
            //cout << 1 << endl;
        }
        else if (s == '?')
        {
            int position;
            cin >> position;
            cout << A.GetAt(position) << endl;
            //cout << 2 << endl;
        }
        else
        {
            int k1, k2;
            cin >> k1 >> k2;
            A.DeleteAt(k1, k2);
            //cout << 3 << endl;
        }
    }
    return 0;
}
