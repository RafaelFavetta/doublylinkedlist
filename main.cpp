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
    int size = 0;

public:
    void push_back(T value) {
        Node *node = new Node(value);
        if (!head) {
            head = tail = node;
            head->next = head;
            head->prev = head;
        } else {
            tail->next = node;
            node->prev = tail;
            node->next = head;
            head->prev = node;
            tail = node;
        }
        size++;
    }

    void push_front(T value) {
        Node *node = new Node(value);
        if (!head) {
            head = tail = node;
            head->next = head;
            head->prev = head;
        } else {
            node->next = head;
            head->prev = node;
            node->prev = tail;
            tail->next = node;
            head = node;
        }
        size++;
    }

    void print_forward() {
        if (!head) {
            cout << "Empty!\n";
            return;
        }
        cout << "Front -> Back: ";
        Node *n = head;
        for (int i = 0; i < size; i++) {
            cout << n->data << " <-> ";
            n = n->next;
        }
        cout << "(back to head)\n";
    }

    void print_backward() {
        if (!tail) {
            cout << "Empty!\n";
            return;
        }
        cout << "Back -> Front: ";
        Node *n = tail;
        for (int i = 0; i < size; i++) {
            cout << n->data << " <-> ";
            n = n->prev;
        }
        cout << "(back to tail)\n";
    }

    ~DoublyLinkedList() {
        while (size > 0) {
            Node *temp = head;
            if (size == 1) {
                head = tail = nullptr;
            } else {
                head = head->next;
                head->prev = tail;
                tail->next = head;
            }
            delete temp;
            size--;
        }
    }

    void pop_front() {
        if (!head) {
            cout << "List is empty!\n";
            return;
        }
        Node *temp = head;
        if (size == 1) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = tail;
            tail->next = head;
        }
        delete temp;
        size--;
        cout << "Popped from the front\n";
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty!\n";
            return;
        }
        Node *temp = tail;
        if (size == 1) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = head;
            head->prev = tail;
        }
        delete temp;
        size--;
        cout << "Popped from the back\n";
    }

    void insert_at(int index, T value) {
        if (index < 0 || index > size) {
            cout << "Index out of bounds!\n";
            return;
        }
        if (index == 0) {
            push_front(value);
            return;
        }
        if (index == size) {
            push_back(value);
            return;
        }

        Node *node = new Node(value);
        Node *current = get_node(index);

        node->next = current;
        node->prev = current->prev;
        current->prev->next = node;
        current->prev = node;

        size++;
        cout << "Inserted at " << index << "\n";
    }

    void remove_at(int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of bounds!\n";
            return;
        }
        if (index == 0) {
            pop_front();
            return;
        }
        if (index == size - 1) {
            pop_back();
            return;
        }

        Node *current = get_node(index);
        current->prev->next = current->next;
        current->next->prev = current->prev;

        delete current;
        size--;
        cout << "Removed at " << index << "\n";
    }

    bool search(T value) {
        if (!head) {
            cout << "Not found!\n";
            return false;
        }
        Node *current = head;
        for (int position = 0; position < size; position++) {
            if (current->data == value) {
                cout << "Found at position " << position << "\n";
                return true;
            }
            current = current->next;
        }
        cout << "Not found!\n";
        return false;
    }

    int count() {
        return size;
    }

private:
    Node *get_node(int index) {
        Node *current;
        if (index < size / 2) {
            current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        } else {
            current = tail;
            for (int i = size - 1; i > index; i--) {
                current = current->prev;
            }
        }
        return current;
    }
};

// agora é MAIN
int main() {
    DoublyLinkedList<string> playlist;
    int option, position;
    string value;

    while (true) {
        cout << "-------MENU-------" << endl;
        cout << "1. Insert at the beginning" << endl;
        cout << "2. Insert at the end" << endl;
        cout << "3. Insert at specific position" << endl;
        cout << "4. Remove from the beginning" << endl;
        cout << "5. Remove from the end" << endl;
        cout << "6. Remove from specific position" << endl;
        cout << "7. Search for a value" << endl;
        cout << "8. Display from front to back" << endl;
        cout << "9. Display from back to front" << endl;
        cout << "10. Count elements" << endl;
        cout << "0. Exit" << endl;

        cin >> option;

        switch (option) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                playlist.push_front(value);
                break;
            case 2:
                cout << "Enter value: ";
                cin >> value;
                playlist.push_back(value);
                break;
            case 3:
                cout << "Enter position and value: ";
                cin >> position >> value;
                playlist.insert_at(position, value);
                break;
            case 4:
                playlist.pop_front();
                break;
            case 5:
                playlist.pop_back();
                break;
            case 6:
                cout << "Enter position: ";
                cin >> position;
                playlist.remove_at(position);
                break;
            case 7:
                cout << "Enter value: ";
                cin >> value;
                playlist.search(value);
                break;
            case 8:
                playlist.print_forward();
                break;
            case 9:
                playlist.print_backward();
                break;
            case 10:
                cout << "Count: " << playlist.count() << endl;
                break;
            case 0:
                return 0;
            default:
                cout << "Invalid option!\n";
        }
    }
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
