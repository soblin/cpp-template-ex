#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <iostream>

template <class T>
class my_enable_shared_from_this {
  // if this class refer to the resource as `shared_ptr`, this shared_ptr will
  // not be freed even  after other agents ceased to refer to this resource.
  boost::weak_ptr<T> weak_this_;

public:
  boost::shared_ptr<T> shared_from_this() {
    boost::shared_ptr<T> p(weak_this_);
    return p;
  }
  void setup_shared_from_this(const boost::shared_ptr<T>& p) {
    if (weak_this_.expired())
      weak_this_ = p;
  }
};

template <class T>
void print_share(boost::shared_ptr<T> p) {
  p->print();
}

class Hoge : public my_enable_shared_from_this<Hoge> {
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
  p->setup_shared_from_this(p);

  p->f();
}
