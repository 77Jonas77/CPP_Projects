#include <iostream>
#include <iostream>

class BankAccount {
public:
    class Transaction {
        double value;
        Transaction* next;
    public:
        Transaction(double value, Transaction* next){
            this->value = value;
            this->next = next;
        }

        double getValue() const {
            return value;
        }

        void setValue(double value) {
            Transaction::value = value;
        }

        Transaction *getNext() const {
            return next;
        }

        void setNext(Transaction *next) {
            Transaction::next = next;
        }
    };
    BankAccount(int accountNumber, double balance){
        this->accountNumber=accountNumber;
        this->balance = balance;
        historyHead= nullptr;
    }

    virtual ~BankAccount() {

    }

private:
    int accountNumber;
    double balance;
    Transaction *historyHead;
public:
    void push(const double& d) {
        historyHead = new Transaction(d, historyHead);
        this->balance+=d;
    }

    double pop(){
        Transaction* tmp = historyHead;
        historyHead = tmp->getNext();
        double wyn = tmp->getValue();
        delete tmp;
        this->balance-=wyn;
        return wyn;
    }

    bool empty(){
        return historyHead == nullptr;
    }
    void show(){
        std::cout << accountNumber << " " << balance << std::endl;
    }
    friend void operator+(BankAccount& bankAcc, double val) {
        bankAcc.balance = bankAcc.balance + val;
        bankAcc.historyHead = new Transaction(val, bankAcc.historyHead);
    }
};

int main() {
    BankAccount acc1 = BankAccount(1,232.2);

    acc1.push(23.5);
    acc1.push(23.5);
    acc1.push(23.5);

    acc1.show();
    acc1+23;
    return 0;
}
