#include <iostream>

enum Banks {PKO, BGZ, BRE, BPH};

struct Account {
    Banks bank;
    int balance;
};

struct Person {
    char name[20];
    Account account;
};
struct Couple {
    Person he;
    Person she;
};
const Couple* bestClient(const Couple* cpls, int size, Banks bank) {
    int count = 0;
    int max = 0;
    const Couple* bCouple{};
    for(int i=0;i<size;i++){
        if(cpls[i].he.account.bank==bank || cpls[i].she.account.bank == bank){
            int savings = cpls[i].he.account.balance+cpls[i].she.account.balance;
            count++;
            if(savings > max){
                max = savings;
                bCouple = &cpls[i];
            }
        }
    }
    if(count==0)
        return nullptr;
    return bCouple;
}

int main() {
    using std::cout; using std::endl;

    Account acc1 = {PKO,1200};
    Account acc2 = {BGZ,1400};
    Account acc3 = {PKO,1600};
    Account acc4 = {PKO,200};
    Account acc5 = {BGZ,-1500};
    Account acc6 = {BRE,1500};
    Account acc7 = {BPH,-201};
    Account acc8 = {BRE,-201};

    Person p1 ={"Johny", acc1};
    Person p2 ={"Pet", acc2};
    Person p3 ={"Kev", acc3};
    Person p4 ={"Ken", acc4};
    Person p11 ={"Mary", acc5};
    Person p22 ={"Suz", acc6};
    Person p33 ={"Katy", acc7};
    Person p44 ={"Lucy", acc8};

    //Couple EX = {{"pi",{PKO,123}},{"an",{PKO, 12000}}};

    Couple cpls[] = {
            {p1,p11}, {p2,p22},{p3,p33}, {p4,p44}
    };

    const Couple* p = bestClient(cpls, std::size(cpls), BRE);
    if (p)
        cout << p->he.name << " and " << p->she.name
             << ": " << p->he.account.balance +
                        p->she.account.balance << endl;
    else
        cout << "No such couple ...\n";
}