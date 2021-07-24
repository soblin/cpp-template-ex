#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

template <class T>
void print_share(boost::shared_ptr<T> p) {
  p->print();
}

class Hoge : public boost::enable_shared_from_this<Hoge> {
public:
  void f() {
    print_share(shared_from_this());
  }
  void print() {
    std::cout << "Hoge" << std::endl;
  }
};

int main() {
  boost::shared_ptr<Hoge> p(new Hoge());
  p->f();
}
