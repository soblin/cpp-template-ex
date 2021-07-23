#include <iostream>
#include <string>

using namespace std::string_literals;

class Base {
public:
  virtual void print() const = 0;
  virtual ~Base() {}
};

template <class T>
class Derived : public Base {
  T value_;

public:
  Derived(const T& value) : value_(value) {}
  virtual void print() const override {
    std::cout << value_ << std::endl;
  }
  virtual ~Derived() {}
};

class X {
  Base* p_;

public:
  template <class T>
  X(const T& value) {
    p_ = new Derived<T>(value);
  }
  ~X() {
    delete p_;
  }
  void print() const {
    p_->print();
  }
};

int main() {
  X x1 = X(1.0);
  x1.print();

  X x2 = X("abc"s);
  x2.print();
}
