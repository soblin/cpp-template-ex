#include <iostream>

template <class Derived>
struct base {
  void base_foo() const {
    static_cast<const Derived&>(*this).foo();
  }
};

struct derived : public base<derived> {
  void foo() const {
    std::cout << "foo@derived" << std::endl;
  }
};

int main() {
  derived d;
  d.base_foo();
}
