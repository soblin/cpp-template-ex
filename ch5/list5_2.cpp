#include <iostream>
#include <vector>

template <class T>
struct is_void {
  static constexpr bool value = false;
};

template <>
struct is_void<void> {
  static constexpr bool value = true;
};

template <class T>
constexpr bool has_iterator_impl(typename T::iterator*) {
  return true;
}

template <class T>
constexpr bool has_iterator_impl(...) {
  return false;
}

template <class T>
constexpr bool has_iterator() {
  return has_iterator_impl<T>(nullptr);
}

using namespace std;

int main() {
  static_assert(::has_iterator<std::vector<int>>(), "vector has iterator type");
  static_assert(!::has_iterator<int>(), "int does not have iterator type");
  cout << boolalpha;
  cout << ::is_void<void>::value << endl;
  cout << ::is_void<int>::value << endl;
}
