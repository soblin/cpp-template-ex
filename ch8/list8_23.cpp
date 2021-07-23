#include <iostream>

namespace mine {

class shared_deleter_base {
public:
  shared_deleter_base() {}
  virtual ~shared_deleter_base() {}
  virtual void destroy() = 0;
};

template <class T, class D>
class shared_deleter : public shared_deleter_base {
  T* object_;
  D deleter_;

public:
  shared_deleter(T* object, D deleter) : object_(object), deleter_(deleter) {}
  virtual void destroy() {
    deleter_(object_);
  }
};

template <class T>
class shared_ptr {
  T* object_;
  shared_deleter_base* deleter_;

public:
  explicit shared_ptr(T* object) : object_(object), deleter_(nullptr) {}
  template <class D>
  shared_ptr(T* object, D deleter) : object_(object) {
    deleter_ = new shared_deleter<T, D>(object_, deleter);
  }
  ~shared_ptr() {
    if (deleter_ != nullptr) {
      deleter_->destroy();
      delete deleter_;
    } else {
      delete object_;
    }
  }
  T* operator->() const {
    return object_;
  }
};
} // namespace mine

using namespace std;

struct hoge {
  hoge() {
    cout << "ctor" << endl;
  }
  ~hoge() {
    cout << "dtor" << endl;
  }
  void something() const {
    cout << "something" << endl;
  }
};

void delete_hoge(hoge* p) {
  delete p;
  cout << "deleted a hoge" << endl;
}

int main() {
  mine::shared_ptr<hoge> p(new hoge(), &delete_hoge);
  p->something();
}
