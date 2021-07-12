#include <iostream>
#include <list>
#include <type_traits>

struct has_sort_member_impl {
  // must use std::true_type() here because declval takes an instantiated
  // variable as its argument
  template <class T>
  static auto check(T*) -> decltype(std::declval<T>().sort(), std::true_type());

  template <class T>
  static auto check(...) -> std::false_type;
};

template <class T>
struct has_sort_member
  : public decltype(has_sort_member_impl::check<T>(nullptr)) {};

int main() {
  std::cout << std::boolalpha;
  std::cout << has_sort_member<std::list<int>>::value << std::endl;
}
