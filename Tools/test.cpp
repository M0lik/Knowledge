#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <tuple>
#include <utility>
#include <functional>

class genericFunc {
  
  class interface {
  public:
    virtual ~interface(){}
    virtual void run()=0;
  };
  
  template <class f, class... arg>
  class Func : public interface {
  private:
    std::tuple<arg...>    _arg;
    f                     funct;

  public:
    Func(f func, arg&& ... a): interface(), funct(func)
    {
      _arg = std::tuple<arg...>(std::forward<arg>(a)...);
    };

    ~Func(){};

    void operator()()
    {
      run();
    };
    
    void run()
    {
      std::apply(funct, _arg);
    };
  };
  
public:
  std::shared_ptr<interface> data;
  
  template < typename T, typename... Arg >
  void setOther( T other, Arg&&... a)
  {
    data.reset(new Func<T, Arg...>(other, std::forward<Arg>(a)...));
  }

  template < typename T, typename... Arg >
  genericFunc( T other, Arg&&... a)
  {
    data.reset(new Func<T, Arg...>(other, std::forward<Arg>(a)...));
  }

  genericFunc(){}
  
  genericFunc(const genericFunc& g)
  {

    data =  g.data;
  }
  
  void run() {
    data->run();
  }
};



void print(int a)
{
  std::cout << "data: "<< a << std::endl;
}

void prout(std::string str)
{
  std::cout << "data: "<< str << std::endl;
}

int main()
{
  std::vector<genericFunc> vec;

  genericFunc f(print, 3);
  genericFunc g(prout, std::string("Je nik le game")); 
  
  vec.push_back(f);
  vec.push_back(g);


  (vec[0]).run();
  (vec[1]).run();

}
