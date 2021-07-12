#include <iostream>
#include <type_traits>

template <class T,
          typename std::enable_if<std::is_class<T>::value, T>::type* = nullptr>
void check(T value) {
  std::cout << "T is class" << std::endl;
}

template <class T,
          typename std::enable_if<!std::is_class<T>::value and
                                      std::is_integral<T>::value,
                                  T>::type* = nullptr>
void check(T value) {
  std::cout << "T is not class and integral" << std::endl;
}

template <class T>
void check(...) {
  std::cout << "T is neither class nor integral" << std::endl;
}

int main() {
  check<int>(1);
  check<std::string>("str");
  check<char>('a');
}
