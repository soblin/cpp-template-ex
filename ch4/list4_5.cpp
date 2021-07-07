#include <iostream>

using namespace std;

// calculate X^N
template <int X, int N>
struct pow {
  static constexpr int value = X * pow<X, N - 1>::value;
};

template <int X>
struct pow<X, 0> {
  static constexpr int value = 1;
};

int main() {
  cout << pow<4, 3>::value << endl;
}
