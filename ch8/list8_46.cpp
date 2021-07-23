union any_pointer {
  void (*func_ptr)();
  void* obj_ptr;
};

template <class Func, class R>
struct function_ptr_manager {
  static R invoke(any_pointer function_ptr) {
    Func func = reinterpret_cast<Func>(function_ptr.func_ptr);
    return func();
  }
  static void destroy(any_pointer) {}
};

template <class Func, class R>
struct function_obj_manager {
  static R invoke(any_pointer func_obj) {
    Func* func = reinterpret_cast<Func*>(func_obj.obj_ptr);
    return (*func)();
  }
  static void destroy(any_pointer function_obj_ptr) {
    // Func* func = reinterpret_cast<Func*>(function_obj_ptr.obj_ptr);
    // delete func;
  }
};

template <class Signature>
class function;

template <class R>
class function<R()> {
  R (*invoke_)(any_pointer);
  void (*destroy_)(any_pointer);
  any_pointer functor_;

public:
  function() : invoke_(nullptr), destroy_(nullptr) {}
  ~function() {
    clear();
  }

  template <class Func>
  void set_function_ptr(Func func_ptr) {
    clear();
    invoke_ = &function_ptr_manager<Func, R>::invoke;
    destroy_ = &function_ptr_manager<Func, R>::destroy;
    functor_.func_ptr = reinterpret_cast<void (*)()>(func_ptr);
  }

  template <class Func>
  void set_function_obj(Func* func_obj) {
    clear();
    invoke_ = &function_obj_manager<Func, R>::invoke;
    destroy_ = &function_obj_manager<Func, R>::destroy;
    // functor_.obj_ptr = reinterpret_cast<void*>(new Func(func_obj));
    functor_.obj_ptr = reinterpret_cast<void*>(func_obj);
  }

  R operator()() {
    return invoke_(functor_);
  }

private:
  void clear() {
    if (destroy_)
      destroy_(functor_);

    destroy_ = nullptr;
  }
};

int func() {
  return 3;
}

class Closure {
  int n;

public:
  explicit Closure(int n) : n(n) {}
  void increment() {
    n++;
  }
  int operator()() {
    return n;
  }
};

#include <iostream>

int main() {
  function<int()> f;
  f.set_function_ptr(&func);
  std::cout << f() << std::endl;
  Closure c(1);
  f.set_function_obj(&c);
  std::cout << f() << std::endl;
  c.increment();
  std::cout << f() << std::endl;
}
