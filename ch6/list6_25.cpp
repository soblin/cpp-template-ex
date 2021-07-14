#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index_container.hpp>
#include <iostream>

using namespace boost::multi_index;

typedef multi_index_container<
    int,
    indexed_by<ordered_unique<identity<int>>, sequenced<>>>
    Container;

int main() {
  Container c;
  c.insert(3);
  c.insert(1);
  c.insert(4);

  // in lexical order
  for (int x : c.get<0>())
    std::cout << x << ' ';
  std::cout << std::endl;

  for (int x : c.get<1>())
    std::cout << x << ' ';
  std::cout << std::endl;
}
