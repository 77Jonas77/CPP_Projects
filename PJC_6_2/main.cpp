#include <iostream>

struct Node {
    int data;
    Node *next;
};

bool add(Node*& head, int data);

size_t size(const Node *head);

void clear(Node *&head);

void printList(const Node *head);

int main() {
    using std::cout;
    using std::endl;

    int tab[] = {1, 4, 1, 3, 5};

    Node* head = nullptr;

    for (size_t i = 0, e = std::size(tab); i != e; ++i) {
        bool b = add(head, tab[i]);
        cout << tab[i] << (b ? " " : " NOT ")
             << "added" << endl;
    }
    cout << "Size of the list: " << size(head) << endl;
    printList(head);
    clear(head);
}

void printList(const Node* head) {
    const Node* tmp = head;
    while(tmp != nullptr){
        std::cout << tmp->data << std::endl;
        tmp = tmp->next;
    }
}

size_t size(const Node *head) {
    const Node* tmp = head;
    size_t listSize=0;
    while(tmp != nullptr){
        listSize++;
        tmp = tmp->next;
    }
    return listSize;
}

bool add(Node*& head, int data) {
    const Node* tmp = head;
    if(head== nullptr){
        head = new Node{data, nullptr};
        return true;
    }else {
        while (tmp != nullptr) {
            if (tmp->data == data)
                return false;
            tmp = tmp->next;
        }
        Node* tmp2 = new Node{data, head};
        head = tmp2;
    }
    return true;
}

void clear(Node *&head) {
    while (head != nullptr) {
        Node* tmp = head;
        head=head->next;
        delete tmp;
    }
}

