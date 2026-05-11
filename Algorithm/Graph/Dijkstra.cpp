#include <iostream>

using std::cin;
using std::cout;
using ll = long long;

// ADJACENCY LIST

/*Discription: self - built pair container
members: vertex, weight
*/
struct pair
{
    int vertex;
    int weight;

    pair() {};
    pair(int v, int w)
    {
        vertex = v;
        weight = w;
    }
};

/*Discription: A node to store value for adjacency list
members: the data is pair (adj_vertex, weight)*/
struct Node
{
    pair data;
    Node *next;

    Node() {};
    Node(pair p)
    {
        data = p;
        next = NULL;
    }
};

/*Description: Struct to store adjancency list
members: 2 con trỏ cấp 2 (đầu và cuối).
        Mỗi phần từ là một Node - là một pair chứa đỉnh kề và trọng số
        Gồm các hàm: addNode*/
struct Graph
{
    Node **adj_list;
    Node **tail;
    int n;

    Graph(int num)
    {
        n = num;
        adj_list = new Node *[n + 5]{};
        tail = new Node *[n + 5]{};
    }

    void addNode(int dinh, pair data)
    {
        Node *newNode = new Node(data);
        if (adj_list[dinh] == NULL)
        {
            adj_list[dinh] = tail[dinh] = newNode;
        }
        else
        {
            tail[dinh]->next = newNode;
            tail[dinh] = newNode;
        }
    }

    ~Graph()
    {
        for (int i = 0; i <= n; ++i)
        {
            Node *curr = adj_list[i];
            while (curr != NULL)
            {
                Node *tmp = curr;
                curr = curr->next;
                delete tmp;
                tmp = NULL;
            }
        }
        delete[] adj_list;
        delete[] tail;
    }
};

// PRIORITY QUEUE

/* Điều kiện để build min heap cho priority queue, so sánh 2 pair */
bool minHeap(pair a, pair b)
{
    return a.weight < b.weight;
}

/* Description: priority_queue tự build
Members: mỗi phần tử là 1 pair
Các hàm: constructor (capacity, điều kiện minHeap), push, pop (trả về phần tử đầu),
empty*/
struct priority_queue
{
    pair *heap;
    int size, capacity;
    bool (*cmp)(pair, pair);

    priority_queue() {};
    priority_queue(int cap, bool (*func)(pair, pair))
    {
        capacity = cap;
        heap = new pair[cap + 5];
        cmp = func;
        size = 0;
    }

    void push(int dinh, int trong_so)
    {
        heap[size].vertex = dinh;
        heap[size].weight = trong_so;
        size++;
        heapifyUp(size - 1);
    }

    void heapifyUp(int i)
    {
        int node = i;
        while (node > 0)
        {
            int parent = (node - 1) / 2;
            if (cmp(heap[node], heap[parent]))
            {
                std::swap(heap[node], heap[parent]);
                node = parent;
            }
            else break;
        }
    }

    pair pop()
    {
        pair returnVal = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);

        return returnVal;
    }

    void heapifyDown(int i)
    {
        int node = i;
        while (1)
        {
            int left = 2 * node + 1;
            int right = 2 * node + 2;
            int largest = node;

            if (left < size && cmp(heap[left], heap[largest]))
                largest = left;
            if (right < size && cmp(heap[right], heap[largest]))
            {
                largest = right;
            }

            if (largest == node)
                return;
            std::swap(heap[largest], heap[node]);
            node = largest;
        }
    }

    bool empty()
    {
        return size == 0;
    }
};

// dijkstra
int n, m, s;
const int INF = 2e9;
Graph *g;

void nhap()
{
    cin >> n >> m >> s;
    g = new Graph(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        pair data;
        data.vertex = v; data.weight = w;
        g -> addNode (u, data);
    }
}

// DIJKSTRA LOGIC
void dijkstra ()
{
    int best_dist[n + 5];
    for (int i = 0; i <= n; ++i){
        best_dist[i] = INF;
    }
    best_dist[s] = 0;

    priority_queue pq (m + 5, minHeap);
    pq.push (s, 0);

    while (!pq.empty()){
        pair top = pq.pop(); // Lấy đỉnh có trọng số bé nhất hiện tại để xét (gọi là đỉnh u)
        
        // Nếu mà trọng số từ s -> u trong pair mới được pop từ priority queue lớn hơn
        // so với khoảng cách tốt nhất s -> u, thì skip
        if (top.weight > best_dist[top.vertex]) continue;


        // Duyệt qua tất cả đỉnh kề của đỉnh u vừa pop ra
        Node* curr = g -> adj_list[top.vertex];
        while (curr != NULL){
            int dinh_hien_tai = (curr -> data).vertex;
            int trong_so_hien_tai = (curr -> data).weight;
            if (best_dist[dinh_hien_tai] > trong_so_hien_tai + best_dist[top.vertex]){
                best_dist[dinh_hien_tai] = trong_so_hien_tai + best_dist[top.vertex];
                pq.push (dinh_hien_tai, best_dist[dinh_hien_tai]);
            }
            curr = curr -> next;
        }
    }

    for (int i = 1; i <= n; ++i){
        if (best_dist[i] >= 2e9) cout << -1 << " ";
        else cout << best_dist[i] << " ";
    }

}

int main()
{
    std::ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    nhap();
    dijkstra();

    return 0;
}