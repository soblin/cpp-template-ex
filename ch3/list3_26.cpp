#include <iostream>

using namespace std;

class Plain {
public:
  string convert(const string& str) const {
    return str;
  }
};

template <class Base>
class Bold : public Plain {
public:
  string convert(const string& str) const {
    return "<b>" + Base::convert(str) + "</b>";
  }
};

template <class Base>
class Italic : public Base {
public:
  string convert(const string& str) const {
    return "<i>" + Base::convert(str) + "</i>";
  }
};

int main() {
  Bold<Plain> b;
  string s1 = b.convert("Hello");

  Italic<Plain> i;
  string s2 = i.convert("Hello");

  Italic<Bold<Plain>> ib;
  string s3 = ib.convert("Hello");

  cout << s1 << endl;
  cout << s2 << endl;
  cout << s3 << endl;
}
