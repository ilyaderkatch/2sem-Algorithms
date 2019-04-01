#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
#include <cmath>
#include <stack>

using std::stack;
using std::cin;
using std::vector;
using std::cout;
using std::endl;
using std::pair;
using std::set;
using std::min;

class State{
private:
    unsigned long long number;

public:
    State() {number = 0x123456789ABCDEF0;}
    State(unsigned long long s) {number = s;}
    vector <pair <State, char> > GetNextVerticles() const;
    friend bool operator==(const State &a, const State &b){return a.number == b.number;}
    friend bool operator<(const State &a, const State &b){return a.number < b.number;}
    void Print() const {cout << std::hex << " " << number << endl;}
    unsigned long long Heuristic() const;
    unsigned long long Linear() const;
};

//start of graph's implementation
vector <pair <State, char> > State::GetNextVerticles() const //get next vertices like in previous task, but with bitwise operators
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
        num >>= 4;
    }
    unsigned long long res = number;
    if (zero != 0 && zero != 1 && zero != 2 && zero != 3)
    {
        unsigned long long a = (number >> (4 * zero)) % 16;
        unsigned long long b = (number >> (4 * (zero - 4))) % 16;
        res += ((b - a) << (4 * zero)) + ((a - b) << (4 * (zero - 4)));
        Result.push_back({State(res), 'U'});
        res = number;
    }
    if (zero != 12  && zero != 13 && zero != 14 && zero != 15)
    {
        unsigned long long a = (number >> (4 * zero)) % 16;
        unsigned long long b = (number >> (4 * (zero + 4))) % 16;
        res += ((b - a) << (4 * zero)) + ((a - b) << (4 * (zero + 4)));
        Result.push_back({State(res), 'D'});
        res = number;
    }
    if (zero != 0 && zero != 4 && zero != 8 && zero != 12)
    {
        unsigned long long a = (number >> (4 * zero)) % 16;
        unsigned long long b = (number >> (4 * (zero - 1))) % 16;
        res += ((b - a) << (4 * zero)) + ((a - b) << (4 * (zero - 1)));
        Result.push_back({State(res), 'L'});
        res = number;
    }
    if (zero != 3 && zero != 7 && zero != 11 && zero != 15)
    {
        unsigned long long a = (number >> (4 * zero)) % 16;
        unsigned long long b = (number >> (4 * (zero + 1))) % 16;
        res += ((b - a) << (4 * zero)) + ((a - b) << (4 * (zero + 1)));
        Result.push_back({State(res), 'R'});
        res = number;
    }
    return Result;
}

pair <int, int>  GetCoordinates(unsigned int n)
{
    return {(n - 1) % 4, (n - 1) >> 2};
}

unsigned long long State::Linear() const //linear hueristic
{
    unsigned long long res = 0;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            for (int k = j + 1; k < 4; ++k)
            {
                int place1 = 4 * i + j;
                int place2 = 4 * i + k;
                int num1 = (number >> (4 * (15 - place1))) % 16;
                int num2 = (number >> (4 * (15 - place2))) % 16;
                if (((num1 - 1) >> 2) == ((num2 - 1) >> 2) && ((num1 - 1) >> 2) == i && num1 > num2 && num2 != 0)
                {
                    res += 2;
                }
                int place3 = (j << 2) + i;
                int place4 = (k << 2) + i;
                int num3 = (number >> (4 * (15 - place3))) % 16;
                int num4 = (number >> (4 * (15 - place4))) % 16;
                if ((num3 - 1) % 4 == (num4 - 1) % 4 && (num3 - 1) % 4 == i && num3 > num4 && num4 != 0)
                {
                    res += 2;
                }
            }
        }
    }
    return res;
}

unsigned long long State::Heuristic() const //new heuristic: Manhattan + linear
{
    unsigned long long res = 0;
    unsigned long long num = number;
    for (int i = 0; i < 16; ++i)
    {
        if (num % 16 != 0)
        {
            res += abs(GetCoordinates(num % 16).first - GetCoordinates(16 - i).first) + abs(GetCoordinates(num % 16).second - GetCoordinates(16 - i).second);
        }
        num >>= 4;
    }
    return Linear() + res;
}

bool IsFinished(const State &current)
{
    State right;
    return right == current;
}

int search(const State &current, int current_depth, int depth, stack <char> &S, set<State> &Old)
{
    int distance = current_depth + current.Heuristic(); // projected distance
    if (IsFinished(current)) //solution founded
    {
        return -1;
    }
    if (distance > depth) //we couldn't go farther
    {
        return distance;
    }
    vector <pair <State, char> > Children;
    Children = current.GetNextVerticles();
    int mini = 1000000000;
    for (int i = 0; i < Children.size(); ++i)
    {
        if (Old.find(Children[i].first) == Old.end()) // vertex is unvisited
        {
            S.push(Children[i].second); //update stack
            Old.insert(Children[i].first); //update way
            int t = search(Children[i].first, current_depth + 1, depth, S, Old); //finder recursion
            if (t == -1)
            {
                return -1;
            }
            S.pop(); //update stack
            mini = min(mini, t); //find min new depth
            Old.erase(Children[i].first); //update way
        }
    }
    return mini;
}



void Solve(const State &start)      //IDA* algorithm
{
    int depth = start.Heuristic();     //max depth dfs
    int t = 0;
    stack <char> S;       //answer_chars
    set <State> Old;    //visited vertex on the way from start to current
    Old.insert(start);
    while(t != -1) //while there is no solution
    {
        t = search(start, 0, depth, S, Old); //find new max depth for search or find solution
        depth = t;
    }
    vector <char> answer; //reverse answer  stack
    while(S.size() != 0)
    {
        answer.push_back(S.top());
        S.pop();
    }
    cout << answer.size() << endl;
    for (int i = 0; i < answer.size(); ++i)
    {
        cout << answer[answer.size() - i - 1];
    }
}

unsigned long long InputGraph()   //input in hex number
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
    Solve(State(InputGraph()));
    return 0;
}
