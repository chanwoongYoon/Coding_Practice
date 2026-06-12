#include <iostream>
#include <vector>

using namespace std;


struct MinHeap {
    vector<int> data;   
    vector<int> grid;

    MinHeap(vector<int> grid){
        this->grid = grid;
    }

    bool empty(){
        return data.empty();
    }

    void push(int idx){
        data.push_back(idx);
        int i = data.size() - 1;

        while(i > 0){
            int parent = (i - 1) / 2;
            if(grid[data[i]] < grid[data[parent]]){
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

            if(left < n && grid[data[left]] < grid[data[smallest]]) smallest = left;
            if(right < n && grid[data[right]] < grid[data[smallest]]) smallest = right;

            if(smallest == i) break;

            swap(data[i], data[smallest]);
            i = smallest;
        }

        return top;
    }
};

int main(){
    vector<int> grid = {5, 2, 8, 1, 9, 3, 7};

    MinHeap heap(grid);

    for(int i = 0; i < (int)grid.size(); i++){
        heap.push(i);
    }

    cout << "value 작은 순서대로 index 꺼내기:" << endl;
    while(!heap.empty()){
        int idx = heap.pop();
        cout << "index " << idx << " (value " << grid[idx] << ")" << endl;
    }

    return 0;
}
