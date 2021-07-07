#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;

template <bool Cond, class Then, class Else>
struct if_;

template <class Then, class Else>
struct if_<true, Then, Else> {
  using type = Then;
};

template <class Then, class Else>
struct if_<false, Then, Else> {
  using type = Else;
};

int main() {
  if_<true, int, long>::type value;
  cout << typeid(decltype(value)).name() << endl;
}
