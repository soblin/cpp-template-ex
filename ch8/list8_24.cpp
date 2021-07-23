#include <cstdio>
#include <memory>

using namespace std;

int main() {
  auto check_fclose = [](FILE* fp) { return fp ? fclose(fp) : 0; };
  shared_ptr<FILE> p(fopen("a.txt", "wb"), check_fclose);
  if (p)
    fwrite("abc", 3, 1, p.get());
}
