#include <iostream>

class any {
private:
  void* data_;

public:
  any() : data_(nullptr) {}
  template <class T>
  any(const T& data) : data_(new T(data)) {}

  ~any() {
    delete data_;
  }

  template <class T>
  any& operator=(const T& data) {
    delete data_;
    data_ = new T(data);
    return *this;
  }

  template <class T>
  friend T& any_cast(any&);
};

template <class T>
T& any_cast(any& data) {
  return *static_cast<T*>(data.data_);
}

int main() {
  any data = 3;
  int m = any_cast<int>(data);
  std::cout << m << std::endl;
  double n = any_cast<double>(data);
  std::cout << n << std::endl;
}
