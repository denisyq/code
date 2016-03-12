#include <deque>

//deque constructor

/*1.default*/   std::deque<int> first;                                // empty deque of ints
/*2.fill*/      std::deque<int> second (4,100);                       // four ints with value 100
/*3.range*/     std::deque<int> third (second.begin(),second.end());  // iterating through second
/*4.copy*/      std::deque<int> fourth (third);                       // a copy of third


//iterator
first.begin();
first.end();
first.rbegin();
first.rend();


//capacity
first.size();
first.empty();
/*error,deque has no capacity*/ first.capacity();wrong statement;
    //resize
    first = [1,2,3,4,5,6,7]
    first.resize(3);       //[1,2,3]
    first.resize(5,100);    //[1,2,3,100,100]



//element access
first[1];
first.at(1);
deque.front();
deque.back();


//element modify
    //assign
    deque.assign(first.begin(),first.begin()+4);
    deque.assign(4,100)     [100,100,100,100]

    //push_back
    deque.push_back(100);
    //push_front
    deque.push_front(100);
    //pop_back,pop_front
    deque.pop_back();
    deque.pop_front();

    //insert, 3 ways
    deque = [1,2,3]
    deque.insert(deque.begin(),10);         //[10,1,2,3]
    deque.insert(deque.begin(),4,10)        //[10,10,10,10,1,2,3]
    deque.insert(deque.begin(),first.begin(),first.end())       //insert iterator

    //erase, 2 ways
    deque.erase(deque.begin())          //erase certain iterator
    deque.erase(deque.begin(),deque.begin()+3)      //erase iterator, 3 elements


    //swap
    first.swap(second);
    //clear
    deque.clear()



