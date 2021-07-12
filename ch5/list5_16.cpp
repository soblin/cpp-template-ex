#include <iostream>
#include <type_traits>
#include <utility>

struct has_add_member_impl {
  template <class T, class U>
  static auto check(T*, U*)
      -> decltype(std::declval<T>().add(std::declval<U>()), std::true_type());
  template <class T, class U>
  static auto check(...) -> std::false_type;
};

template <class T, class U>
struct has_add_member
  : decltype(has_add_member_impl::check<T, U>(nullptr, nullptr)) {};

template <class T, class U>
typename std::enable_if<has_add_member<T, U>::value, T>::type
operator+(const T& a, const U& b) {
  return a.add(b);
}

class X {
  int value;

public:
  X(int value) : value(value) {}
  X add(const X& x) const {
    return X(value + x.value);
  }

  int getValue() const {
    return value;
  }
};

class Y {
  int value;

public:
  Y(int value) : value(value) {}
  Y add(const X& x) const {
    return Y(value + x.getValue());
  }

  int getValue() const {
    return value;
  }
};

int main() {
  X a(1);
  X b(2);

  X r = a + b;

  Y c(3);
  Y d = c + r;

  std::cout << r.getValue() << std::endl;
}
