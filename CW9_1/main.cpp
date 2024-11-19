#include <iostream>

template <typename E>
class MyStack {
private:
    class Node{
        E data;
        Node* next;
    public:
        Node(E data, Node* next){
            this->data = data;
            this->next=next;
        }
        E getData(){ return this->data;}
        void setData(E data){this->data = data;}
        Node* getNext(){return this->next;}
        void setNext(Node* next){this->next = next;}
    };
    Node* head;
public:
    void push(const E& d) {
        head = new Node(d, head);
    }

    E pop(){
//        E tmpData = head->getData();
//        Node* tmpNext = head->getNext();
//        delete head;
//        head=tmpNext;
//        return tmpData;
        Node* tmp = head;
        head = tmp->getNext();
        E wyn = tmp->getData();
        delete tmp;
        return wyn;
    }

    bool empty(){
        return head == nullptr;
    }
};

int main() {
    using std::cout; using std::endl; using std::string;
    MyStack<string> stS;
    MyStack<double> stD;

    for (int i = 5; i > 0; --i) {
        stS.push(std::to_string(double(i)));
        stD.push(double(i));
    }

    for (int i = 5; i > 0; --i) {
        cout << "string: " << stS.pop() << " " << "double: " << stD.pop() << endl;
    }
}