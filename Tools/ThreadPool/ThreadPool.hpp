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



class								ThreadPool
{
private:
  std::atomic<bool>						_istask;
  std::atomic<bool>						_state;
  std::condition_variable					_condvar;
  std::mutex							_mutex;
  SafeQueue<void(*)(void)>					_task;
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
	t();
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
  static void lel(){};
  template < typename F, typename... ARG >
  void								pushTask(F (*func)(ARG ...), ARG&& ... arg)
  {
    std::function<F (ARG ...)> f = func;
    Func<std::function<F(ARG ...)>, ARG...> functmp(f, std::forward<ARG>(arg)...);


    void (*lbda)(void);
    lbda = [functmp](){
      functmp.run();
    };

    std::cout << ((typeid(lbda)).name() == typeid(lel).name() ? "oui" : "Non") << std::endl;
    //    _task.push(lbda);
    
    //    _istask = true;
    //    _condvar.notify_one();
  }
};

#endif //THREADPOOL_HPP_
