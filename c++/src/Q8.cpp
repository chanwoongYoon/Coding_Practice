#include <iostream>
#include <vector>

using namespace std;

int INF = 1215752192;

// 방향: 0=up, 1=right, 2=down, 3=left
const int dr[4] = {-1, 0, 1, 0};
const int dc[4] = { 0, 1, 0, -1};

struct MinHeap {
    vector<int> data;            // 상태 index들 (cell*4 + dir)
    vector<vector<int>>& dist;   // 비교 기준 (cell별 {up,right,down,left})

    MinHeap(vector<vector<int>>& dist) : dist(dist) {}

    // 상태 index s가 가리키는 거리값
    int cost(int s){
        return dist[s / 4][s % 4];
    }

    bool empty(){
        return data.empty();
    }

    void push(int idx){
        data.push_back(idx);
        int i = data.size() - 1;

        while(i > 0){
            int parent = (i - 1) / 2;
            if(cost(data[i]) < cost(data[parent])){
                swap(data[i], data[parent]);
                i = parent;
            } else {
                break;
            }
        }
    }

    int pop(){
        int top = data[0];

        data[0] = data[data.size() - 1];
        data.pop_back();

        int i = 0;
        int n = data.size();
        while(true){
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if(left < n && cost(data[left]) < cost(data[smallest])) smallest = left;
            if(right < n && cost(data[right]) < cost(data[smallest])) smallest = right;

            if(smallest == i) break;

            swap(data[i], data[smallest]);
            i = smallest;
        }

        return top;
    }
};

vector<int> nodeChild(const vector<int>& grid,int my_node,vector<vector<int>>& dist,int n,int m){
    vector<int> result_vec;
    int r = my_node / m;
    int c = my_node % m;

    // 어느 방향으로 '도착'한 상태인지 확인
    for(int ad = 0; ad < 4; ad++){
        if(dist[my_node][ad] >= INF) continue;

        // 세로(up/down)로 왔으면 다음은 가로(right/left), 가로로 왔으면 다음은 세로
        int d1, d2;
        if(ad == 0 || ad == 2){ d1 = 1; d2 = 3; } // 가로
        else                  { d1 = 0; d2 = 2; } // 세로

        for(int nd : {d1, d2}){
            int sum = 0;
            for(int k = 1; k <= 7; k++){
                int nr = r + dr[nd] * k;
                int nc = c + dc[nd] * k;
                if(nr < 0 || nr >= n || nc < 0 || nc >= m) break; // 경계 넘으면 더 못 감

                sum += grid[nr * m + nc];   // 시작 다음 칸부터 지나온 칸들의 합
                if(k < 4) continue;         // 4칸부터 착지 가능 (4~7)

                int target = nr * m + nc;
                int cand = dist[my_node][ad] + sum;
                if(cand < dist[target][nd]){
                    dist[target][nd] = cand;
                    result_vec.push_back(target * 4 + nd); // 상태 index 리턴
                }
            }
        }
    }
    return result_vec;
}

void Dijkstra(vector<int>grid,int n,int m){
    vector<vector<int>> dist(n*m, vector<int>(4, INF));// {up,right,down,left}
    MinHeap waiting_queue(dist);

    // TODO: 시작 상태(시작 노드 + 도착 방향) dist 0으로 두고 push 후 루프
    while(!waiting_queue.empty()){
        int state = waiting_queue.pop();
        int node = state / 4;
        for(int child : nodeChild(grid, node, dist, n, m)){
            waiting_queue.push(child);
        }
    }
}

int main(){
    int n = 13;
    int m = 13;

    vector<int> grid = {
        2, 4, 1, 3, 4, 3, 2, 3, 1, 1, 3, 2, 3,
        3, 2, 1, 5, 4, 5, 3, 5, 3, 5, 6, 2, 3,
        3, 2, 5, 5, 2, 4, 5, 6, 5, 4, 2, 5, 4,
        3, 4, 4, 6, 5, 8, 5, 8, 4, 5, 4, 5, 2,
        4, 5, 4, 6, 6, 5, 7, 8, 6, 7, 5, 3, 6,
        1, 4, 3, 8, 5, 9, 8, 7, 9, 8, 4, 5, 4,
        4, 4, 5, 7, 8, 7, 6, 9, 8, 7, 7, 6, 6,
        3, 6, 3, 7, 8, 7, 7, 9, 7, 9, 6, 5, 3,
        4, 6, 5, 4, 9, 6, 7, 9, 8, 6, 8, 8, 7,
        4, 5, 6, 4, 6, 7, 9, 9, 8, 6, 4, 5, 3,
        1, 2, 2, 4, 6, 8, 6, 8, 6, 5, 5, 6, 3,
        2, 5, 4, 6, 5, 4, 8, 8, 8, 7, 7, 3, 5,
        4, 3, 2, 2, 6, 7, 4, 6, 5, 5, 5, 3, 3
    };

    return 0;
}