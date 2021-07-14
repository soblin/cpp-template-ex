#include <cstring>
#include <iostream>
#include <list>

#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>

template <class Iterator,
          typename std::enable_if<
              std::is_pointer<Iterator>::value and
              boost::has_trivial_assign<typename std::iterator_traits<
                  Iterator>::value_type>::value and
              boost::has_trivial_destructor<typename std::iterator_traits<
                  Iterator>::value_type>::value>::type* = nullptr>
Iterator copy(Iterator first, Iterator last, Iterator out) {
  std::cout << "memomove" << std::endl;
  std::memmove(out, first, (last - first) * sizeof(decltype(*first)));
  return out + (last - first);
}

template <class InputIterator, class OutputIterator>
OutputIterator
copy(InputIterator first, InputIterator last, OutputIterator out) {
  std::cout << "loop copy" << std::endl;
  for (; first != last; ++out, ++first) {
    *out = *first;
  }

  return out;
}

int main() {
  int ar1[3] = {3, 1, 4};
  int ar2[3] = {};

  ::copy(std::begin(ar1), std::end(ar1), std::begin(ar2));
  for (int x : ar2) {
    std::cout << x << std::endl;
  }

  std::list<int> ls1 = {3, 1, 4};
  std::list<int> ls2(3);

  ::copy(std::begin(ls1), std::end(ls1), std::begin(ls2));
  for (int x : ls2) {
    std::cout << x << std::endl;
  }
}
