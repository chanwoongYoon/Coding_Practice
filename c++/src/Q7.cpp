#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int INF = 1215752192;

int left_idx(int my_idx,int m){
    if (my_idx % m == 0) return INF;
    return my_idx - 1;
}
int right_idx(int my_idx,int m){
    if (my_idx % m == m - 1) return INF;
    return my_idx + 1;
}
int up_idx(int my_idx,int m){
    if(my_idx - m >= 0){
        return my_idx - m;
    } else{
        return INF;
    }
}
int down_idx(int my_idx,int n,int m){
    if(my_idx + m < (n * m)){
        return my_idx + m;
    } else{
        return INF;
    }
}

void Erase_node(vector<vector<int>>& Indegree,vector<int>& Length,vector<int>& path_len,stack<int>& next_stack,int node){
    //child의 진입 개수를 1개씩 빼주기
    next_stack.pop();
    if(Indegree[node].size() != 0){
        for(int i:Indegree[node]){
            if (path_len[i] < path_len[node] + 1) {
                path_len[i] = path_len[node] + 1;
            }

            Length[i] -= 1;
            if (Length[i] == 0) {
                next_stack.push(i);
            }
        }
    }
}

int main(){
    int n = 10;
    int m = 10;
    vector<int> test_lst = {6,3,7,1,2,9,2,6,1,9,4,1,2,7,7,2,4,2,9,7,1,2,4,1,7,1,4,1,9,3,5,7,3,9,2,5,9,3,2,4,6,2,9,2,1,4,8,9,7,6,8,8,6
  ,5,4,3,4,2,5,9,8,6,8,5,2,2,9,7,3,6,3,8,7,1,2,9,6,6,6,8,8,2,2,5,8,2,1,5,8,5,7,6,1,8,6,3,2,8,1,4};
    vector<vector<int>> Indegree;
    vector<int> Length;
    Length.resize(test_lst.size());
    vector<int> zero_lst;

    for (int i = 0; i < n * m; i++){
        vector<int> temp = {};

        int l = left_idx(i, m);
        int r = right_idx(i, m);
        int u = up_idx(i, m);
        int d = down_idx(i, n, m);

        if (u != INF && test_lst[i] > test_lst[u]) { 
            temp.push_back(u);
        }
        if (l != INF && test_lst[i] > test_lst[l]) { 
            temp.push_back(l);
        }
        if (r != INF && test_lst[i] > test_lst[r]) { 
            temp.push_back(r);
        }
        if (d != INF && test_lst[i] > test_lst[d]) { 
            temp.push_back(d);
        }

        if (u != INF && test_lst[i] < test_lst[u]) { 
            Length[i] += 1;
        }
        if (l != INF && test_lst[i] < test_lst[l]) { 
            Length[i] += 1;
        }
        if (r != INF && test_lst[i] < test_lst[r]) { 
            Length[i] += 1;
        }
        if (d != INF && test_lst[i] < test_lst[d]) { 
            Length[i] += 1;
        }

        if (Length[i] == 0) {
            zero_lst.push_back(i);
        }

        Indegree.push_back(temp);
    }

    vector<int> path_len(test_lst.size(), 1);
    stack<int> next_stack;

    for (int zero_node : zero_lst) {
        next_stack.push(zero_node);
    }

    while(!next_stack.empty()){
        int poped_node = next_stack.top();
        Erase_node(Indegree, Length, path_len, next_stack, poped_node);
    }

    int result = 0;
    for (int i = 0; i < (int)path_len.size(); i++) {
        result = max(result, path_len[i]);
    }

    cout << result << endl;
}