#include <iostream>

using namespace std;

template <int N>
struct square {
  static constexpr int value = N * N;
};

int main() {
  cout << square<3>::value << endl;
}
