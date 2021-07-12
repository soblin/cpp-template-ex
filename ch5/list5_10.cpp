#include <type_traits>
#include <utility>

struct is_assignable_impl {
  template <typename T>
  static auto check(T*)
      -> decltype(std::declval<T&>() = std::declval<const T&>(),
                  std::true_type());

  template <typename T>
  static auto check(...) -> std::false_type;
};

template <typename T>
struct is_assignable : decltype(is_assignable_impl::check<T>(nullptr)) {};

struct A {
  A& operator=(const A&) = delete;
};

struct B {
  B& operator=(const B&) = default;
};

int main() {
  static_assert(!is_assignable<A>::value, "A is not assignable!");
  static_assert(is_assignable<B>::value, "B is assignable!");
}
