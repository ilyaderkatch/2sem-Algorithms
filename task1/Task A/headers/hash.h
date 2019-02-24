#ifndef hash_h
#define hash_h

#include <vector>

using std::vector;

class HashTable
{
private:
    vector <vector <int> > Table;
    int num = 0;
    int Hash(int a);
    void Resize();

public:
    HashTable();
    ~HashTable();
    bool DeleteInt(int a);
    bool AddInt(int a);
    bool Has(int a);
    bool OutputTable(vector <int> &A)
};


#endif
