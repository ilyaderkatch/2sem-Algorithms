#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
#include <map>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::set;
using std::min;
using std::map;

unsigned long long DEGREE[16] = {0x1, 0x10, 0x100, 0x1000, 0x10000, 0x100000, 0x1000000, 0x10000000, 0x100000000, 0x1000000000, 0x10000000000, 0x100000000000, 0x1000000000000, 0x10000000000000, 0x100000000000000, 0x1000000000000000};

class State{     //state
private:
    unsigned long long number;  //table in hex

public:
    State() {number = 0x123456789ABCDEF0;}
    State(unsigned long long s) {number = s;}
    vector <pair <State, char> > GetNextVerticles() const;
    friend bool operator==(const State &a, const State &b){return a.number == b.number;}
    friend bool operator<(const State &a, const State &b){return a.number < b.number;}
    void Print() const {cout << std::hex << " " << number << endl;}
    unsigned long long Heuristic() const;
};

//start of state's implementation
vector <pair <State, char> > State::GetNextVerticles() const     //get next vertices like in previous task but in hex
{
    vector <pair < State, char> > Result;
    unsigned long long num = number;
    int zero = 0;
    for (int i = 0; i < 16; ++i)
    {
        if (num % 16 == 0)
        {
            zero = i;
            break;
        }
        num /= 16;
    }
    unsigned long long res = number;
    if (zero != 0 && zero != 1 && zero != 2 && zero != 3)
    {
        unsigned long long a = number / DEGREE[zero] % 16;
        unsigned long long b = number / DEGREE[zero - 4] % 16;
        res += (b - a) * DEGREE[zero] + (a - b) * DEGREE[zero - 4];
        Result.push_back({State(res), 'U'});
        res = number;
    }
    if (zero != 12  && zero != 13 && zero != 14 && zero != 15)
    {
        unsigned long long a = number / DEGREE[zero] % 16;
        unsigned long long b = number / DEGREE[zero + 4] % 16;
        res += (b - a) * DEGREE[zero] + (a - b) * DEGREE[zero + 4];
        Result.push_back({State(res), 'D'});
        res = number;
    }
    if (zero != 0 && zero != 4 && zero != 8 && zero != 12)
    {
        unsigned long long a = number / DEGREE[zero] % 16;
        unsigned long long b = number / DEGREE[zero - 1] % 16;
        res += (b - a) * DEGREE[zero] + (a - b) * DEGREE[zero - 1];
        Result.push_back({State(res), 'L'});
        res = number;
    }
    if (zero != 3 && zero != 7 && zero != 11 && zero != 15)
    {
        unsigned long long a = number / DEGREE[zero] % 16;
        unsigned long long b = number / DEGREE[zero + 1] % 16;
        res += (b - a) * DEGREE[zero] + (a - b) * DEGREE[zero + 1];
        Result.push_back({State(res), 'R'});
        res = number;
    }
    return Result;
}

pair <int, int>  GetCoordinates(unsigned int n) //number's coordinates in the table
{
    return {(n - 1) % 4, (n - 1) / 4};
}

unsigned long long State::Heuristic() const //manhattan heuristic
{
    unsigned long long res = 0;
    unsigned long long num = number;
    for (int i = 0; i < 16; ++i)
    {
        if (num % 16 != 0)
        {
            res += abs(GetCoordinates(num % 16).first - GetCoordinates(16 - i).first) + abs(GetCoordinates(num % 16).second - GetCoordinates(16 - i).second);
        }
        num /= 16;
    }
    return res;
}

void OutRes(map <State, pair <State, char> > &AllStates, const State &start) //print result like in the previous problem
{
    State current;
    vector <char> Ans;
    while(!(current == start))
    {
        Ans.push_back(AllStates[current].second);
        current = AllStates[current].first;
    }
    cout << std::dec << Ans.size() << endl;
    for (int i = Ans.size() - 1; i >= 0; --i)
    {
        cout << Ans[i];
    }
}


void Solve(const State &start) //A* algorithm
{
    State right;
    map <State, pair <State, char> > AllStates;   //map with parent and result_char
    set <pair <int, State> > Q;    //priority queue with min state
    Q.insert({0, start});
    AllStates[start] = {start, 'Z'};
    while (Q.size() != 0)
    {
        State S = Q.begin()->second;
        Q.erase(Q.begin());
        if (S == right)   //find solution
        {
            OutRes(AllStates, start);
            return;
        }
        vector <pair<State, char> > Children = S.GetNextVerticles();
        for (int i = 0; i < Children.size(); ++i)
        {
            if (AllStates.count(Children[i].first) == 0) //find unvisited vertex
            {
                AllStates[Children[i].first] = {S, Children[i].second};
                Q.insert({Children[i].first.Heuristic(), Children[i].first});
            }
        }

    }
    cout << -1 << endl;    //we couldn't find solution
}

unsigned long long InputGraph()
{
    unsigned long long s = 0;
    for (int i = 0; i < 16; ++i)
    {
        unsigned long long n;
        cin >> n;
        s *= 16;
        s += n;
    }
    return s;
}

//end of state's implementation

int main()
{
    Solve(InputGraph());
    return 0;
}