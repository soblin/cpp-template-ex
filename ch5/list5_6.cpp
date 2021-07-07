#include <type_traits>

namespace cpp {

struct is_class_impl {
  template <class T>
  static std::true_type check(int T::*);
  template <class T>
  static std::false_type check(...);
};

template <class T>
struct is_class : public decltype(is_class_impl::check<T>(nullptr)) {};
} // namespace cpp

struct X {};

int main() {
  static_assert(cpp::is_class<X>::value, "X is a class");

  static_assert(!cpp::is_class<int>::value, "int is not class");
}
