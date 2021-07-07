#include <iostream>
#include <typeinfo>

namespace {
template <class T>
struct identity {
  using type = T;
};

template <class T>
struct add_pointer {
  using type = T*;
};

template <class T>
struct add_const_lvalue_reference {
  using type = const T&;
};

template <class T>
struct add_const {
  using type = const T&;
};

template <class T>
struct add_lvalue_reference {
  using type = T&;
};

template <class T>
struct add_lvalue_reference<T&> {
  using type = T&;
};
} // namespace

using std::cout;
using std::endl;

int main() {
  // list4-8
  cout << typeid(::identity<int>::type).name() << endl;
  cout << typeid(::identity<int*>::type).name() << endl;

  {
    // list4-9
    cout << typeid(::add_pointer<int>::type).name() << endl;
  }
  {
    // list4-10
    cout << typeid(::identity<double>::type).name() << endl;
    cout << typeid(::add_const_lvalue_reference<double>::type).name() << endl;
  }
  {
    // list4-11
    cout << typeid(::add_const<int>::type).name() << endl;
  }
}
