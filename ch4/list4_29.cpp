#include <iostream>

template <template <class> class Pred, class Tuple>
struct any_of_impl;

template <template <class> class Pred, class Head, class... Tail>
struct any_of_impl<Pred, std::tuple<Head, Tail...>> {
  static constexpr bool value =
      Pred<Head>::value ? true : any_of_impl<Pred, std::tuple<Tail...>>::value;
};

template <template <class> class Pred>
struct any_of_impl<Pred, std::tuple<>> {
  static constexpr bool value = false;
};

template <template <class> class Pred, class... List>
struct any_of {
  static constexpr bool value = any_of_impl<Pred, std::tuple<List...>>::value;
};

template <class T>
struct is_int {
  static constexpr bool value = false;
};

template <>
struct is_int<int> {
  static constexpr bool value = true;
};

int main() {
  using namespace std;
  auto result = any_of<is_int, char, double, int>::value;
  cout << boolalpha;
  cout << result << endl;
  result = any_of<is_int, long, string>::value;
  cout << result << endl;
  result = any_of<is_int>::value;
  cout << result << endl;
}
