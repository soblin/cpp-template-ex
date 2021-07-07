#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;

template <class Head, class... Tail>
struct g {
  using head = Head;
  using tail = std::tuple<Tail...>;
};

template <class... List>
struct f {
  using head = typename g<List...>::head;
  using tail = typename g<List...>::tail;
};

int main() {
  typedef f<int, char, long, double> list;
}
