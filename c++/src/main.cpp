#include <iostream>
#include <vector>
#include <map>
#include <queue>


using namespace std;

int range = 2;

int n = 2;
vector<vector<int>> test_lst = {{1,2,7},{3,6,7}};
int S = 1;
int T = 6;

struct RouteInfo{
    bool is_visited=false;
    int depth = 0;
    vector<int> stations;
};

struct StationInfo{
    stations
}

vector<RouteInfo> routes;
map<int,pair<int,vector<int>>> stations;

queue<int> waiting_queue;


int main() {
    for (vector<int> vals:test_lst){
        routes.push_back({false,vals});
    }
    // --- routes 결과 출력 코드 ---
    cout << "\n================ [ ROUTES RESULT ] ================" << endl;
    
    int route_idx = 0;
    for (const auto& route_pair : routes) {
        bool is_valid = route_pair.first;           // pair의 첫 번째: bool (방문/유효 여부)
        const vector<int>& path = route_pair.second; // pair의 두 번째: vector<int> (역 번호 목록)

        // 1. 해당 경로의 인덱스와 상태 출력
        cout << "Route #" << route_idx++ << " [Valid: " << (is_valid ? "True" : "False") << "] : ";

        // 2. 내부 vector<int> (stations_temp 데이터) 순회하며 출력
        if (path.empty()) {
            cout << "(Empty path)";
        } else {
            for (size_t k = 0; k < path.size(); k++) {
                cout << path[k];
                if (k < path.size() - 1) cout << " -> "; // 숫자 사이에 화살표 표시
            }
        }
        cout << endl;
    }
    
    cout << "===================================================" << endl;

    int route_size = (int)routes.size();
    for(int route_number=0;route_number<route_size;route_number++){
        for(int station_number : routes[route_number].second){
            stations[station_number].first = 0;
            stations[station_number].second.push_back(route_number);
        }
    }

    // --- 🌟 STATIONS 시각화 코드 🌟 ---
    cout << "\n================ [ STATIONS VISUALIZATION ] ================" << endl;
    cout << "  [역 번호] -> (방문 여부) | 연결된 경로들\n" << endl;

    // C++17 구조화된 바인딩을 사용하여 key(역 번호)와 value(정보 pair)를 깔끔하게 분리
    for (const auto& [station_num, station_info] : stations) {
        bool is_visited = station_info.first;
        const vector<int>& connected_routes = station_info.second;

        // 1. 역 번호와 방문 여부(True/False) 출력
        cout << " Station [ " << station_num << " ] -> Visited: " 
             << (is_visited ? "⭕ True " : "❌ False") << " | Routes: ";

        // 2. 해당 역을 지나는 경로 목록들을 가독성 좋게 출력
        if (connected_routes.empty()) {
            cout << "(None)";
        } else {
            for (size_t i = 0; i < connected_routes.size(); i++) {
                cout << "Route #" << connected_routes[i];
                if (i < connected_routes.size() - 1) cout << ", ";
            }
        }
        cout << endl;
    }
    cout << "=============================================================" << endl;

    waiting_queue.push(S);
    stations[S].first = 0;

    while(!waiting_queue.empty()){
        int station_number = waiting_queue.front();
        waiting_queue.pop();
        vector<int> child_routes = stations[station_number].second;
        for (int route:child_routes){
            for (int station_nums:routes[route].second){
                if(routes[route].first == false){// == if not visited
                    waiting_queue.push(route);
                    stations[station_nums].first = stations[station_nums].first + 1;
                    routes[route].first = true;
                }
            }
        }
    }

    return 0;
}
