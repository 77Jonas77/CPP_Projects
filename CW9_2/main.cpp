#include <iostream>
#include <fstream>

class Resistor {
private:
    double opor;
public:
    Resistor() {
        opor = 0;
    }

    Resistor(double arg) {
        this->opor = arg;
    }

    double r() const {
        return this->opor;
    }

    void r(double arg) {
        this->opor = arg;
    }

    friend std::ostream& operator<<(std::ostream& os, const Resistor& resistor) {
        os << resistor.r();
        return os;
    }
};

Resistor operator+(const Resistor& x, const Resistor& y) {
    return Resistor(x.r() + y.r());
}

Resistor operator*(const Resistor& x, const Resistor& y) {
    return Resistor(1.0 / (1 / x.r() + 1 / y.r()));
}

int main() {
    Resistor r1, r2{6};
    r1.r(3);
    std::cout << (r1 + r2) << " " << (r1 * r2) << std::endl;
    return 0;
}
