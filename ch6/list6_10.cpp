#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index_container.hpp>
#include <iostream>

using namespace boost::multi_index;

template <class T>
using SeqContainer = multi_index_container<T, indexed_by<sequenced<>>>;

template <class T>
using OrdContainer =
    multi_index_container<T, indexed_by<ordered_unique<identity<T>>>>;

int main() {
  SeqContainer<int> seq;
  seq.push_back(3);

  OrdContainer<int> ord;
  ord.insert(3);
}
