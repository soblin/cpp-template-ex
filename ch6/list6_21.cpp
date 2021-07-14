#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <class T, template <class> class ComparePolicy>
class sorted_vector {
  std::vector<T> vec_;

public:
  void push_back(const T& value) {
    vec_.push_back(value);
    std::sort(std::begin(vec_), std::end(vec_), &ComparePolicy<T>::compare);
  }

  void print() {
    std::copy(std::begin(vec_),
              std::end(vec_),
              std::ostream_iterator<T>(std::cout, " "));
    std::cout << std::endl;
  }
};

template <class T>
struct less_policy {
  static bool compare(const T& a, const T& b) {
    return a < b;
  }
};

template <class T>
struct greater_policy {
  static bool compare(const T& a, const T& b) {
    return a > b;
  }
};

int main() {
  {
    sorted_vector<int, less_policy> vec;
    for (auto&& i : {3, 1, 2, 4}) {
      vec.push_back(i);
      vec.print();
    }
  }
  {
    sorted_vector<int, greater_policy> vec;
    for (auto&& i : {3, 1, 2, 4}) {
      vec.push_back(i);
      vec.print();
    }
  }
}
