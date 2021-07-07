#include <iostream>
#include <vector>

template <class T>
class has_iterator {
  // to define another template function in template class,
  // I need to use another template parameter
  // because T is not a free variable
  template <class U>
  static constexpr bool check(typename U::iterator*) {
    return true;
  }

  template <class U>
  static constexpr bool check(...) {
    return false;
  }

public:
  static constexpr bool value = check<T>(nullptr);
};

int main() {
  static_assert(::has_iterator<std::vector<int>>::value, "vector has iterator");
  static_assert(!::has_iterator<int>::value, "int does not have iterator");
}
