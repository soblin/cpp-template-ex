#include <iostream>

using namespace std;

template <class Derived>
struct Base {
  void something() const {
    static_cast<const Derived*>(this)->template_method();
  }
};

struct Derived : public Base<Derived> {
  void template_method() const {
    cout << "template_method@Derivcd" << endl;
  }
};

int main() {
  Derived d;
  d.something();
}
