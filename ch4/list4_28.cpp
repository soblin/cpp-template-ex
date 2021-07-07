#include <iostream>

template <template <class> class Pred, class Head, class... Tail>
struct any_of {
  static constexpr bool value =
      Pred<Head>::value ? true : any_of<Pred, Tail...>::value;
};

template <template <class> class Pred, class Head>
struct any_of<Pred, Head> {
  static constexpr bool value = Pred<Head>::value;
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
}
