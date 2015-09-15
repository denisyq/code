#include <list>
cons 4
capacity size/empty/resize
iterator begin/end/rbegin/rend
element access front/back
element assign/insert/erase/swap/clear
more    splice/merge/remove_if/sort/unique/reverse


//cons
std::list<int> first;                                // empty list of ints
std::list<int> second (4,100);                       // four ints with value 100
std::list<int> third (second.begin(),second.end());  // iterating through second
std::list<int> fourth (third);                       // a copy of third

//iterator
list.begin()
list.end()
list.rbegin()
list.rend()

//capacity
list.size()
list.empty()
list.resize()

//element access
//list has no [] or at(n) usage
list.front()
list.back()

//element modify
    //assign
    list.assign(7,10)
    list.assign(second.begin(),second.end())
    
    //push_back pop_back
    //push_front pop_front
    list.push_back()
    list.push_front()
    list.pop_back()
    list.pop_front()

    //insert
    list.insert(list.begin(),10)
    list.insert(list.begin(),9,10)
    list.insert(list.begin(), second.begin(), second.end())

    //erase
    list.erase(list.begin());
    list.erase(list.begin(),list.begin()+3);

    //swap
    list.swap(first);

    //clear
    list.clear();

//more
    //splice - 3 ways
    list.splice(list.begin(),first);                            //copy the whole list
    list.splice(list.begin(),first, first.begin()+3);           //copy the single iterator
    list.splice(list.begin(),first, first.begin(),first.end()); //copy range iter1 --iter2

    //merge
    list.merge(second);
    bool comp(const double a, const double b){
        return ( int(a)<int(b) );
    }
    list.merge(second,comp);
    //list = [1.1, 2.2, 3.3]
    //second=[2.1]
    //then will be [1.1, 2.2, 2.1, 3.3]
    //remove
    list.remove(89);

    //remove_if(pred)
    //pred - 2 ways
    bool single_value(const int& value){ return (value<10);}
    struct is_odd{
        bool operator() (const int& value) { return (value%2)==1; }
    };
    list.remove_if(single_value);
    list.remove_if(is_odd());



    //sort
    list.sort();            //small -> big
    list.sort(comp);
    bool comp(int a, int b){ return a>b;}

    //unique
    //list = [1.11,1.22,1.22,2.22,6.11]
    list.unique();      //erase 1.22
    bool same_int(double a, double b){ return (int(a)==int(b));}
    struct is_near{
        bool operator() (double a, double b) { return (fabs(a-b)<2.0);}
    };
    //[1.11, 1.22, 2.22, 6.11]
    list.unique(same_int);      //erase 1.22
    list.unique(is_near());     //erase 2.22

    //reverse
    list.reverse();



