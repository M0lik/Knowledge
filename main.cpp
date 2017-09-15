#include "FunctionWrapper.hpp"
#include <iostream>

int print(int l, char a)
{
  std::cout << l << a << std::endl;
  return 6;
}

int main()
{
  Func	function(print, 21, 'a');
  std::cout << function() << std::endl;
  return 0;
}

//C++ 17
//result:
//21a
//6
