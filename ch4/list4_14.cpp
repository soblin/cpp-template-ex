#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;

namespace {
template <class T>
struct remove_const {
  using type = T;
};

template <class T>
struct remove_const<const T> {
  using type = T;
};
} // namespace

int main() {
  cout << typeid(remove_const<const int>::type).name() << endl;
  cout << typeid(remove_const<int>::type).name() << endl;
}
