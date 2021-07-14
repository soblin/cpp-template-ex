#include <cmath>
#include <iostream>
#include <utility>

// This function must be declared **before** the below one!!!
double pow2sum() {
  return 0.0;
}

template <class D1, class... DN>
double pow2sum(D1 d1, DN... dn) {
  return d1 * d1 * 1.0 + pow2sum(dn...);
}

template <class D1, class... DN>
double hypot(D1 d1, DN... dn) {
  return std::sqrt(pow2sum(d1, dn...));
}

int main() {
  std::cout << hypot(1, 2, 3) << std::endl;
}
