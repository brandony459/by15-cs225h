#include <vector>
#include <chrono>
#include <iostream>

struct Node {
    Node* next;
    long int data;
    Node(long int data_) {
        data = data_;
    }
};

int main() {

    const int size = 10000000;

    auto start{std::chrono::steady_clock::now()};
    auto end{std::chrono::steady_clock::now()};

    std::vector<long int> v;
    start = std::chrono::steady_clock::now();
    for (int i = 0; i < size; i++) {
        v.insert(v.begin(), LONG_MAX);
    }
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_vector{end - start};

    Node* head = new Node(0);
    start = std::chrono::steady_clock::now();
    for (int i = 0; i < size; i++) {
        Node* node = new Node(LONG_MAX);
        node->next = head;
        head = node;
    }
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_list{end - start};

    std::cout << "vector runs in " << elapsed_seconds_vector.count() << "s\n";
    std::cout << "list runs in " << elapsed_seconds_list.count() << "s\n";

    while (head != NULL) {
        Node* tmp = head->next;
        delete head;
        head = tmp;
    }
    return 0;
}