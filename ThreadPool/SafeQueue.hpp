//
// SafeQueue.hpp for plazza in /home/margue_m/rendu/cpp_plazza
//
// Made by Mattéo Margueritte
// Login   <margue_m@epitech.net>
//
// Started on  Fri Apr 28 14:39:43 2017 Mattéo Margueritte
// Last update Fri Sep 22 17:49:40 2017 molik
//

#ifndef SAFEQUEUE_HPP_
# define SAFEQUEUE_HPP_

# include <queue>
# include <mutex>

template<class T>
class				SafeQueue
{
  std::queue<T>			_queue;
  std::mutex			_mutex;

public:
  SafeQueue(void)
  {
  }
  ~SafeQueue(void)
  {
  }

  T				front()
  {
    _mutex.lock();
    auto front = _queue.front();
    _mutex.unlock();
    return front;
  }
  
  void				push(T elem)
  {
    _mutex.lock();
    _queue.push(elem);
    _mutex.unlock();
  }

    void				pop()
  {
    _mutex.lock();
    _queue.pop();
    _mutex.unlock();
  }

  bool				tryPop(T &value)
  {
    _mutex.lock();
    if (_queue.empty())
      {
	_mutex.unlock();
	return (false);
      }
    value = _queue.front();
    _queue.pop();
    _mutex.unlock();
    return (true);
  }

  bool				isEmpty(void)
  {
    bool			status;
    _mutex.lock();
    status = _queue.empty();
    _mutex.unlock();
    return (status);
  }
};

#endif //SAFEQUEUE_HPP_
