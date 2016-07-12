#include <boost/noncopyable.hpp>

class FOO : boost::noncopyable {

};

class noncopyable{

protected:
  noncopyable(){}
  ~noncopyable(){}
private:
  noncopyable(const noncopyable&);
  noncopyable& operator=(const noncopyable&);
};
