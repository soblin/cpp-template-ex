#include <tuple>
#include <type_traits>

template <template <class> class Func, class... List>
struct my_transform {
  using type = std::tuple<typename Func<List>::type...>;
};

using result = my_transform<std::add_pointer, int, char, double>::type;

int main() {
  int x = 1;
  char y = 'a';
  double z = 0.1;
  result var = std::make_tuple(&x, &y, &z);
}
