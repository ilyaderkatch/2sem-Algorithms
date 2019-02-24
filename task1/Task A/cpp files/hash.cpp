#include "hash.h"

void HashTable::Resize()
{
    Table.resize(Table.size() * 2);
}

bool HashTable::DeleteInt(int key)
{
    int h = Hash(key);
    vector <int>::iterator it = Table[h].begin();
    while(it != Table[h].end())
    {
        if (*it == key)
        {
            Table[h].erase(it);
            return true;
        }
        ++it;
    }
    return false;
}

bool HashTable::AddInt(int key)
{
    if (num == Table.size())
    {
        Resize();
    }
    int h = Hash(key);
    Table[h].push_back(key);
    return true;
}

bool HashTable::Has(int key)
{
    int h = Hash(key);
    vector<int>::iterator it = Table[h].begin();
    while (it != Table[h].end())
    {
        if (*it == key)
        {
            return true;
        }
        ++it;
    }
    return false;
}

int HashTable::Hash(int key)
{
    int result = 0;
    while (key != 0)
    {
        result += key % 10;
        key /= 10;
    }
    return result % Table.size();
}

HashTable::HashTable()
{
    Table.resize(8);
}

HashTable::~HashTable()
{
    Table.clear();
}

bool HashTable::OutputTable(vector <int> &Output)
{
    Output.resize(0);
    for (int i = 0; i < Table.size(); ++i)
    {
        for (int j = 0; j < Table[i].size(); ++j)
        {
            Output.push_back(Table[i][j]);
        }
    }
}