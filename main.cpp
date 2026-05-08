#include <iostream>
using namespace std;

template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node *next;
        Node *prev;

        Node(T value) : data(value), next(nullptr), prev(nullptr) {
        }
    };

    Node *head = nullptr;
    Node *tail = nullptr;

public:
    void push_back(T value) {
        Node *node = new Node(value);
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    void push_front(T value) {
        Node *node = new Node(value);
        if (!head) {
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
    }

    void print_forward() {
        cout << "Forward: ";
        for (Node *n = head; n; n = n->next)
            cout << n->data << " <-> ";
        cout << "null\n";
    }

    void print_backward() {
        cout << "Backward: ";
        for (Node *n = tail; n; n = n->prev)
            cout << n->data << " <-> ";
        cout << "null\n";
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head -> next;
            delete temp;
        }
    }
};

// agora é MAIN
int main() {
    DoublyLinkedList<string> playlist;

    playlist.push_back("SMASH!");
    playlist.push_back("Circle");
    playlist.push_back("XIX");
    playlist.push_back("The Trooper");
    playlist.push_back("Praise The Lord");

    playlist.print_forward();
    playlist.print_backward();

    return 0;
}
// inserir no inicio
// inserir no final
// inserir em posicao especifica
// remover no inicio
// remover no final
// remover em posicao especifica
// buscar valor
// exibir inicio -> fim
// exibir fim -> inicio
// contar elementos
// sair
