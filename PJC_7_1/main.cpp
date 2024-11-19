#include <iostream>

struct Animal{
    virtual void makeSound(){
        std::cout << "klasa bazowa" << std::endl;
    }
};

struct Dog : Animal {
    void makeSound() override{
        std::cout << "hau " << std::endl;
    }
};

struct Cat : Animal {
    void makeSound() override{
        std::cout << "miau " << std::endl;
    }
};

int main(){
    Animal *arr[] = {new Dog, new Cat};

    for(Animal *x :arr){
        x->makeSound();
    }

    return 0;
}
