#include <iostream>
#include <string>
#include <vector>
class Person {
    static size_t ID;
    std::string name;
    size_t id;
    std::vector<const Person*> friends;
public:
    Person(std::string name){
        this->name = name;
        this -> id = ID++;
        friends = {};
    }

    void makeFriends(Person& p){
        p.friends.push_back(this);
        this->friends.push_back(&p);
    }

    void listOfFriends() const{
        for (auto & f: friends ) {
            std::cout << f->info() << std::endl;
        }
    }

    std::vector<const Person*> friendsOfFriends() const {
        std::vector<const Person*> fof;
        for(const Person* f : friends) {
            for( const Person* FriendsOfFriends : f->friends) {
                if (FriendsOfFriends->id != id && !isFriendsWith(FriendsOfFriends) && !std::count(fof.begin(), fof.end(), FriendsOfFriends))
                    fof.push_back(FriendsOfFriends);
            }
        }
        return fof;
    }

    std::string info() const {
        return name + "(" + std::to_string(id) + ")";
    }

    bool isFriendsWith(const Person* p) const {
        for(const Person* f : friends) {
            if (f->id == p->id)
                return true;
        }
        return false;
    }
};

size_t Person::ID{1};

int main() {
    Person john{"John"}, mary{"Mary"}, kitty{"Kitty"},
            jill{"Jill"}, bob{"Bob"}, eve{"Eve"};
    john.makeFriends(mary); john.makeFriends(bob);
    john.makeFriends(eve); bob.makeFriends(john);
    bob.makeFriends(jill); bob.makeFriends(eve);
    eve.makeFriends(mary); eve.makeFriends(kitty);
    john.listOfFriends();
    std::cout << "Friends of John's friends -> ";
    for (const Person* p : john.friendsOfFriends())
        std::cout << p->info() << " ";
    std::cout << std::endl;
}
