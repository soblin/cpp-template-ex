#include <iostream>
#include <type_traits>
#include <vector>

namespace cpp {

struct has_iterator_impl {
  template <class T>
  static std::true_type check(typename T::iterator*);

  template <class T>
  static std::false_type check(...);
};

template <class T>
class has_iterator : public decltype(has_iterator_impl::check<T>(nullptr)) {};
} // namespace cpp

int main() {
  static_assert(cpp::has_iterator<std::vector<int>>::value,
                "vector has iterator");

  static_assert(!cpp::has_iterator<int>::value, "int does not have iterator");
}
