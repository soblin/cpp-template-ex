#include <type_traits>

namespace util {
template <bool Cond, class Then, class Else>
struct if_;

template <class Then, class Else>
struct if_<true, Then, Else> {
  using type = Then;
};

template <class Then, class Else>
struct if_<false, Then, Else> {
  using type = Else;
};
} // namespace util

struct function_ptr_tag {};
struct function_obj_tag {};

template <class Func>
struct get_function_tag {
  using type = typename util::if_<std::is_pointer<Func>::value,
                                  function_ptr_tag,
                                  function_obj_tag>::type;
};

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
  static void destroy(any_pointer function_obj_ptr) {}
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

  template <class FuncPtr>
  void assign_to(FuncPtr func_ptr, function_ptr_tag) {
    clear();
    invoke_ = &function_ptr_manager<FuncPtr, R>::invoke;
    destroy_ = &function_ptr_manager<FuncPtr, R>::destroy;
    functor_.func_ptr = reinterpret_cast<void (*)()>(func_ptr);
  }

  template <class FuncObj>
  void assign_to(FuncObj& func_obj, function_obj_tag) {
    clear();
    invoke_ = &function_obj_manager<FuncObj, R>::invoke;
    destroy_ = &function_obj_manager<FuncObj, R>::destroy;
    // functor_.obj_ptr = reinterpret_cast<void*>(new Func(func_obj));
    functor_.obj_ptr = reinterpret_cast<void*>(&func_obj);
  }

  template <class Func>
  function& operator=(Func& func) {
    using func_tag = typename get_function_tag<Func>::type;
    assign_to(func, func_tag());
    return *this;
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
  f = func;
  std::cout << f() << std::endl;
  Closure c(1);
  f = c;
  std::cout << f() << std::endl;
  c.increment();
  std::cout << f() << std::endl;
}
