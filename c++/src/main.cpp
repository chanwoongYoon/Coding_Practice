#include <iostream>
#include <vector>
#include <map>
#include <queue>


using namespace std;

int n = 3;
vector<vector<int>> test_lst = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 1000},
    {1000, 2000},
    {2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021, 2022, 2023, 2024, 2025, 2026, 2027, 2028, 2029, 2030, 2031, 2032, 2033, 2034, 2035, 2036, 2037, 2038, 2039, 2040, 2041, 2042, 2043, 2044, 2045, 2046, 2047, 2048, 2049}
};
int S = 0;
int T = 2049;


struct RouteInfo{
    bool is_visited=false;
    int depth = 0;
    vector<int> stations_r;
    RouteInfo(vector<int> new_station) { stations_r = new_station;};
};

vector<RouteInfo> routes;
map<int,vector<int>> stations;

queue<int> waiting_queue;


int main() {
    //route 리스트 만들기
    for (vector<int> stations_in_route:test_lst){
        RouteInfo new_route(stations_in_route);
        routes.push_back(new_route);
    }

    //station 리스트 만들기
    for (int route_num=0;route_num<(int)routes.size();route_num++){
        for (int station_ind : routes[route_num].stations_r){
            stations[station_ind].push_back(route_num);
        }
    }
    
    //start algorithm
    waiting_queue.push(S);

    int current_depth = 0;

    while(!waiting_queue.empty()){
        int q_size = waiting_queue.size();
        for (int i=0;i<q_size;i++){
            int front_station = waiting_queue.front();
            waiting_queue.pop();

            if(front_station == T){
                cout << "\n🎯 목적역 " << T << "번까지의 최소 환승 횟수: " << current_depth << "회" << endl;
                return 0; 
            }

            for (int child_routes:stations[front_station]){
                if (!routes[child_routes].is_visited){
                    for(int child_station : routes[child_routes].stations_r){
                        waiting_queue.push(child_station);
                    }
                    routes[child_routes].is_visited = true;
                    routes[child_routes].depth = current_depth;
                }
            }
        }
        current_depth ++;
    }

    return -1;
}
