#include <vector>
#include <chrono>
#include <iostream>

struct Node
{
    int data;
    Node *next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedListQueue
{
public:
    LinkedListQueue() : head(nullptr), tail(nullptr) {}

    void push(int val)
    {
        Node *newNode = new Node(val);
        if (tail)
        {
            tail->next = newNode;
        }
        else
        {
            head = newNode;
        }
        tail = newNode;
    }

    void pop()
    {
        if (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            if (!head)
            {
                tail = nullptr;
            }
        }
    }

    int front()
    {
        return head->data;
    }

    bool empty()
    {
        return head == nullptr;
    }

private:
    Node *head;
    Node *tail;
};

void bfs_linked_list(const std::vector<std::vector<int>> &graph, int start, std::vector<int> &visited)
{
    LinkedListQueue q;
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        for (int neighbor : graph[node])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main()
{
    int n = 10000; // Larger graph
    std::vector<std::vector<int>> graph(n);
    std::vector<int> visited(n, false);

    // Adding edges to the graph
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n && j < i + 10; ++j)
        {
            graph[i].push_back(j);
            graph[j].push_back(i);
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    bfs_linked_list(graph, 0, visited);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Linked List BFS with size " << n << ": " << duration.count() << " s" << std::endl;

    return 0;
}
