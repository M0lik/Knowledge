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
