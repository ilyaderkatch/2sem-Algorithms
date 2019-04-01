#include <iostream>
#include <vector>
#include <map>
#include <queue>


using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::map;
using std::queue;

int DEGREE[9] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000}; //global vector of degries

class State{
private:
    int number;

public:
    State() {number = 123456780;}
    State(int a) {number = a;}
    vector <pair <State, char> > GetNextVerticles() const;
    friend bool operator==(const State &a, const State &b){return a.number == b.number;}
    friend bool operator<(const State &a, const State &b){return a.number < b.number;}
    void Print(){cout << number << endl;}
};

//start of state's implementation
vector <pair <State, char> > State::GetNextVerticles() const //print all next states
{
    vector <pair < State, char> > Result;
    int num = number;
    int zero = 0;
    for (int i = 0; i < 9; ++i)
    {
        if (num % 10 == 0)
        {
            zero = i;
            break;
        }
        num /= 10;
    }
    int res = number;
    if (zero != 0 && zero != 1 && zero != 2)                //we can move zero up
    {
        int a = number / DEGREE[zero] % 10;
        int b = number / DEGREE[zero - 3] % 10;
        res += (b - a) * DEGREE[zero] + (a - b) * DEGREE[zero - 3];
        Result.push_back({State(res), 'D'});
        res = number;
    }
    if (zero != 6 && zero != 7 && zero != 8)        //we can move zero down
    {
        int a = number / DEGREE[zero] % 10;
        int b = number / DEGREE[zero + 3] % 10;
        res += (b - a) * DEGREE[zero] + (a - b) * DEGREE[zero + 3];
        Result.push_back({State(res), 'U'});
        res = number;
    }
    if (zero != 0 && zero != 3 && zero != 6)        //we can move zero left
    {
        int a = number / DEGREE[zero] % 10;
        int b = number / DEGREE[zero - 1] % 10;
        res += (b - a) * DEGREE[zero] + (a - b) * DEGREE[zero - 1];
        Result.push_back({State(res), 'R'});
        res = number;
    }
    if (zero != 2 && zero != 5 && zero != 8)      //we can move zero right
    {
        int a = number / DEGREE[zero] % 10;
        int b = number / DEGREE[zero + 1] % 10;
        res += (b - a) * DEGREE[zero] + (a - b) * DEGREE[zero + 1];
        Result.push_back({State(res), 'L'});
        res = number;
    }
    return Result;
}

void OutRes(map <State, pair <State, char> > &AllStates, const State &start)
{
    State current; //right state
    vector <char> Ans;
    while(!(current == start))
    {
        Ans.push_back(AllStates[current].second);  //result_char in answer
        current = AllStates[current].first;
    }
    cout << Ans.size() << endl;
    for (int i = Ans.size() - 1; i >= 0; --i)
    {
        cout << Ans[i];                            //reverse answer
    }
}

void Solve(const State &start)
{
    State right;
    map <State, pair <State, char> > AllStates;     //map of parent and result_char
    queue <State> Q;                                //queue of bfs
    Q.push(start);
    AllStates[start] = {start, 'Z'};
    while (Q.size() != 0)
    {
        State S = Q.front();
        Q.pop();
        if (S == right)
        {
            OutRes(AllStates, start);
            return;
        }
        vector <pair<State, char> > Children = S.GetNextVerticles();
        for (int i = 0; i < Children.size(); ++i)
        {
            if (AllStates.count(Children[i].first) == 0)           //if state is unvisited
            {
                AllStates[Children[i].first] = {S, Children[i].second};
                Q.push(Children[i].first);                                //push in map and queue
            }
        }

    }
    cout << -1 << endl;   //we couldn't find right state
}

int InputGraph()
{
    int s = 0;
    for (int i = 0; i < 9; ++i)
    {
        int n;
        cin >> n;
        s *= 10;
        s += n;
    }
    return s;
}

//end of states's implementation

int main()
{
    Solve(State(InputGraph()));
    return 0;
}