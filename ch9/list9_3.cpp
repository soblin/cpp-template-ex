#include <iostream>

using namespace std;

class Base {
  virtual void template_method() const = 0;

public:
  void something() const {
    template_method();
  }
};

class Derived : public Base {
  virtual void template_method() const override {
    cout << "template_method()@Derived" << endl;
  }
};

int main() {
  Derived d;
  d.something();
}
