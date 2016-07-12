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
/////////////////////////////////////////////////////

/* shared_ptr */
#include <boost/shared_ptr.hpp>
boost::shared_ptr<int> sp(new int(4));


/* weak_ptr */
#include <boost/weak_ptr.hpp>
boost::weak_ptr<int> wkSp;
/////////////////////////////////////////////////////

/* function */
#include <boost/function.hpp>
typedef boost::function<void ()> ThreadFunc;
ThreadFunc func_;
/////////////////////////////////////////////////////

/* ptr_container */
#include <boost/ptr_container/ptr_vector.hpp>
//in directory boost/ptr_container/*, we have \
ptr_vector.hpp \
ptr_deque.hpp \
ptr_inserter.hpp \
ptr_list.hpp \
ptr_map.hpp \
ptr_set.hpp \
ptr_unordered_map.hpp \
ptr_unordered_set.hpp

// ptr_vector stored pointer, no need to delete the pointer's memory allocated
// if vector stored pointer, we need to delete pointer's memory allocated manually.
boost::ptr_vector<int> sp;
sp.push_back(new int(1));
sp.push_back(new int(2));
cout<<sp.back()<<endl;

boost::ptr_set<int> ps;
ps.insert(new int(3));
ps.insert(new int(4));
cout<<*ps.begin()<<endl;
////////////////////////////////////////////////////////

/* boost static assert */
#include <boost/static_assert.hpp>
BOOST_STATIC_ASSERT(2>=1);
//this assert used for check in compile state \
false will cause compilation stop
//std::assert() used for running state \
false will cause system fault, compilation will pass.

//BOOST_ASSERT similar to assert
#include <boost/assert.hpp>
BOOST_ASSERT(2>1);
BOOST_ASSERT(2>1,"boost assert");
////////////////////////////////////////////////////////

