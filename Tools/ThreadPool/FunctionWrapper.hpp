#ifndef FUNC
#define FUNC

#include <tuple>
#include <utility>
#include <functional>

template <class f, class... arg>
class Func
{
private:
  std::tuple<arg...>	_arg;
  f			funct;
public:
  Func(f func, arg&& ... a): funct(func)
  {
    _arg = std::tuple<arg...>(std::forward<arg>(a)...);
  };
  ~Func(){};
  decltype(auto) operator()()
  {
    return run();
  };
  decltype(auto) run()
  {
    return std::apply(funct, _arg);
  };
};
#endif
