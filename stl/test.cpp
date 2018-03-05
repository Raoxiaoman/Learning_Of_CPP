#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits.h>
using namespace std;

/** 请完成下面这个函数，实现题目要求的功能 **/
 /** 当然，你也可以不按照这个模板来作答，完全按照自己的想法来 ^-^  **/
int minCost(vector<vector<int>>& costs)
{    
    int minCost = 0;
    for (size_t i = 0;i< costs.size();i++){
        vector<int> cost = costs[i];
        for(size_t j = 0;j<cost.size();j++){
            minCost += cost[j];
        }
    }
    return minCost;
}

int main()
{
    int N,K;
    int cost;
    vector<vector<int> > costs;
    string s;
    istringstream is;

    getline(cin, s);
    is.str(s);
    is>>N>>K;
    for(int i =0 ; i < N; i++)
    {
        vector<int> t;
        getline(cin, s);
        is.clear();
        is.str(s);
        for(int j = 0; j < K; j++) {
            is >> cost;
            t.push_back(cost);
        }
        costs.push_back(t);
    }
    cout<<minCost(costs)<<endl;
    return 0;
}
