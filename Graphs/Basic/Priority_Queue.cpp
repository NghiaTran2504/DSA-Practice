#include <iostream>

using std::cin;
using std::cout;
using std::swap;
using ll = long long;

bool greater (int a, int b) {return a > b; }
bool less (int a, int b) {return a < b; }
struct priority_queue{
    int* heap;
    int size, capacity;
    bool (*cmp) (int, int);

    priority_queue (){};
    priority_queue (int cap, bool (*func) (int, int )){
        capacity = cap;
        heap = new int [cap + 5];
        cmp = func;
        size = 0;
    }

    void push (int x){
        heap[size++] = x;
        heapifyUp (size - 1);
    }

    void heapifyUp (int i){
        int node = i;
        while (node > 0){
            int parent = (node - 1) / 2;
            if (cmp (heap[node], heap[parent])){
                swap (heap[node], heap[parent]);
                node = parent;
            }

            else break;
        }
    }

    void pop(){
        heap[0] = heap[size - 1];
        size--;
        heapifyDown (0);
    }

    void heapifyDown (int i){
        int node = i;
        while (1){
            int left= 2 * node + 1;
            int right = 2 * node + 2;
            int largest = node;

            if (left < size && cmp (heap[left], heap[largest])){
                largest = left;
            }
            if (right < size && cmp (heap[right], heap[largest])){
                largest = right;
            }

            if (largest == node)
                return;
            swap (heap[largest], heap[node]);
            node = largest;
        }
    }

    bool empty(){
        return size == 0;
    }

    int top(){
        return heap[0];
    }

    ~priority_queue(){
        delete[] heap;
        heap = nullptr;
    }
};

int main()
{
    priority_queue pq (100, less);
    int n;
    while (cin >> n){
        pq.push (n);
    }

    while (!pq.empty()){
        cout << pq.top() << " ";
        pq.pop();
    }
    return 0;
}