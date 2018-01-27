#ifndef THREADPOOL_HPP_
# define THREADPOOL_HPP_

# include <thread>
# include <mutex>
# include <vector>
# include <atomic>
# include <memory>
# include <condition_variable>

# include <utility>
# include "SafeQueue.hpp"
# include "FunctionWrapper.hpp"

template<typename T>
class ThreadPool
{};

template<typename func>
struct ThreadPool<func ()>
{
};

template<typename F, typename... ARG>
class								ThreadPool<F (ARG...)>
{
private:
  std::atomic<bool>						_istask;
  std::atomic<bool>						_state;
  std::condition_variable					_condvar;
  std::mutex							_mutex;
  SafeQueue<Func<std::function<F(ARG...)>, ARG...> >		_task;
  std::vector<std::thread >					_thread;

  std::thread							newThread()
  {
    return (std::thread([this](){this->execThread();}));
  }

  void								execTask()
  {
     if (_istask)
      {	
	auto t = _task.front();
	_task.pop();
	if (_task.isEmpty())
	  _istask = false;
	t.run();
      }
  }

  void								execThread()
  {
    while (_state)
      {
	if (!_istask)
	  {
	    std::unique_lock<std::mutex> lock(_mutex);
	    _condvar.wait_for(lock, std::chrono::milliseconds(1));
	  }
	if (_state && _istask)
	  execTask();
      }
  }

public:
  ThreadPool(int nb_thread)
  {
    _istask = false;
    _state = true;
    for (unsigned i = 0; i < nb_thread; i++)
      _thread.push_back(newThread());
  }

  virtual ~ThreadPool(void)
  {
    while (_istask);
    _state = false;
    _condvar.notify_all();
    for (auto &it: _thread)
      it.join();
  }
  
  void								pushTask(F (*func)(ARG ...), ARG&& ... arg)
  {
    std::function<F (ARG ...)> f = func;
    _task.push(Func<std::function<F(ARG ...)>, ARG...> (f, std::forward<ARG>(arg)...));
    _istask = true;
    _condvar.notify_one();
  }
};

#endif //THREADPOOL_HPP_
