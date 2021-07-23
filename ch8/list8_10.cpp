#include <iostream>

class drawable {
  struct vtable {
    void (*draw)(void*);
  };
  template <class T>
  struct vtable_initializer {
    static vtable vtbl_; // store the following `draw` function

    static void draw(void* this_) {
      //  if T has .draw or not is checked at compile time, because the compiler
      //  knows what is `T`
      static_cast<T*>(this_)->draw();
    }
  };
  void* this_;
  vtable* vptr_; // the pointer to vtable that corresponds to current type T

public:
  template <class T>
  drawable(T& other) : this_(&other), vptr_(&vtable_initializer<T>::vtbl_) {}

  void draw() const {
    vptr_->draw(this_);
  }
};

template <class T>
drawable::vtable drawable::vtable_initializer<T>::vtbl_ = {
    &drawable::vtable_initializer<T>::draw};

struct circle {
  void draw() const {
    std::cout << "Draw a circle" << std::endl;
  }
};

struct circle2 {
  void draw() const {
    std::cout << "Draw a circle2" << std::endl;
  }
};

int main() {
  circle c;
  circle2 c2;
  drawable a = c;
  a.draw();
  a = c2;
  a.draw();
}
