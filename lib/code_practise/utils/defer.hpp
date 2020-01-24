#ifndef _DEFER_H_
#define _DEFER_H_

// 模拟golang defer
// ,不足之处是在使用defer的块中无法定义如_defered_var_name1jaeegc的变量
#include <functional>
// cleanup执行的函数
void __runDefer(std::function<void()> *func) { (*func)(); }
//给defer变量名增加一个__COUNTER__,避免重复
#define DEFER_1(x, y) x##y##jaeegc
#define DEFER_2(x, y) DEFER_1(x, y)
#define DEFER_0(x) DEFER_2(x, __COUNTER__)
//宏定义defer变量,使用GCC __attribute__ cleanup在变量离开
//作用域的时候执行__runDefer函数,具体见手册
#define defer                                                                  \
  std::function<void()> DEFER_0(_defered_var_name)                             \
      __attribute__((cleanup(__runDefer))) =

#endif
