#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <type_traits>
#include <vector>

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

template <class Sortable,
          typename std::enable_if<has_sort_member<Sortable>::value,
                                  Sortable>::type* = nullptr>
void sort(Sortable& x) {
  x.sort();
}

template <class Sortable,
          typename std::enable_if<not has_sort_member<Sortable>::value,
                                  Sortable>::type* = nullptr>
void sort(Sortable& x) {
  std::sort(std::begin(x), std::end(x));
}

int main() {
  std::vector<int> v({3, 1, 4});
  std::list<int> ls({3, 1, 4});

  ::sort(v);
  ::sort(ls);

  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::copy(ls.begin(), ls.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
}
