#ifndef _FORK_
#define _FORK_

#include <unistd.h>
#include <stdlib.h>

class Fork
{
public:
  Fork() = default;
  ~Fork() = default;
  
  static void quit(int nb)
  { exit(nb); }

  template <typename function, typename ... arguments>
  static bool	forking(function func, arguments... args)
  {
    pid_t check;

    if ((check = fork()) < 0)
      return (false);
    if (check == 0)
      func(args...);
    return (true);
  }
  
};

#endif
