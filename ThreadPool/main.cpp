#include <iostream>
#include "ThreadPool.hpp"
#include <iostream>


int lel (int nb)
{
  if (nb == 0)
    return 1;
  nb = nb -1;
  return (lel(nb) + lel(nb));
}

int print(int l, char a)
{
  lel(l);
  std::cout << l << a << std::endl;

  return 6;
}

int main()
{
  ThreadPool<int (int, char)> p(8);
  
  p.pushTask(print, 20, 'b');
  p.pushTask(print, 31, 'c');
  p.pushTask(print, 4, 'd');
  p.pushTask(print, 12, 'e');
  p.pushTask(print, 20, 'b');
  p.pushTask(print, 31, 'c');
  p.pushTask(print, 4, 'd');
  p.pushTask(print, 12, 'e');
  p.pushTask(print, 20, 'b');
  p.pushTask(print, 31, 'c');
  p.pushTask(print, 4, 'd');
  p.pushTask(print, 12, 'e');
  return 0;
}

//C++ 17
