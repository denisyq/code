#include <iostream>
#include <vector>


// vector: constructors, 4 ways
std::vector<int> first;                                // empty vector of ints
std::vector<int> second (4,100);                       // four ints with value 100
std::vector<int> third (second.begin(),second.end());  // iterating through second
std::vector<int> fourth (third);                       // a copy of third



// vector: iterator
first.begin()
first.end()
second.rbegin()
second.rend()

// vector: element access
first[1]
first.at(1)
first.front()
first.back()


// vector: capacity
first.size()
first.capacity()
first.empty()
first.reserve(100)
	//resize, 2 ways
	//....first.assign(5,10)    		// 10 10 10 10 10
	first.resize(3);			// 10 10 10
	first,resize(6,100)			// 10 10 10 100 100 100


// vector: element modify
	//assign, 2 ways
	first.assign(7,100);             // 7 ints with a value of 100
	second.assign(first.begin()+first.size()/2, first.end()); // assign( iterator it1, iterator it2 );

	//push_back
	first.push_back(1);
	//pop_back
	first.pop_back();

	//insert, 3 ways
    //..... first =[10 10 10 10 10]
	first.insert(first.begin(),100);			//100 10 10 10 10 10
	first.insert(first.begin(),2,99);		//99 99 100 10 10 10 10 10
	first.insert(first.begin(),second.first(),second.end()); //88 88 100 10 99 99 10 10 10 10
	
	//erase, 2 ways
    //..... first = [1,2,3,4,5,6,7,8,9,10]
	first.erase(first.begin()+3)		//erase 4..... 1,2,3,,5,6,7,8,9,10
	first.erase(first.begin(),first.begin()+3)		//5,6,7,8,9,10 erase 3 elements

	//swap
	//first = [1,2,3]
	//second = [10,10,10]
	first.swap(second)				//first=[10,10,10] second=[1,2,3]

	//clear
	first.clear();



