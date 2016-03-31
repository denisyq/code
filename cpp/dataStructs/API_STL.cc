/***********/
// vector //
/**********/

void vector_api(void){
//cons
	vector<int> iv;
	vector<int> iv(n,value);
	vector<int> iv(iv2);
	vector<int> iv(iv2.iter1, iv2.iter2);

//iterator
	iv.begin();
	iv.end();
	iv.rbegin();
	iv.rend();

//element
	iv[1];
	iv.at(1);
	iv.front();
	iv.end();

//capacity
	size();
	capacity();
	empty();
	reserve(n);

//modify
	iv.assign(n,value);
	iv.assign(iv2.begin(),iv2.begin()+2);

	iv.insert(iter,value);
	iv.insert(iter,n,value);
	iv.insert(iter, iv2.begin(),iv2.end());

	iv.erase(iter);
	iv.erase(iter1,iter2);

	iv.push_back();
	iv.pop_back();
	
	iv.swap();
	iv.clear();
}


/*********/
// Deque //
/*********/
//deque has minor different from vector
//	no api "capacity" and "reserve"
void deque_api(void){

//cons
	deque<int> id;
	deque<int> id(n,value);
	deque<int> id(id2);
	deque<int> id(iter1, iter2);

//iter
	id.begin();//rbegin
	id.end();//rend

//element
	id.front();
	id.back()
	id.at(1);
	id[1];

//capacity
	id.size();
	id.empty();
	//deque has NO "capacity" nor "reserve" api

//modify
	id.assign(n, value);
	id.assign(iter1, iter2);
	
	id.insert(id.begin(), value);
	id.insert(id.begin(), n, value);
	id.insert(id.begin(), iter1, iter2);	
	
	id.erase(iter);
	id.erase(iter1, iter2);

	id.push_back();
	id.push_front();
	id.pop_back();
	id.pop_front();

	id.swap(id2);
	id.clear();	
		
}


/**********/
// list //
/**********/
void list(void){

//cons
	list<int> il;
	list<int> il(n, value);
	list<int> il(iter1, iter2)
	list<int> il(list2);

//iter
	list.begin();
	list.end();

//element
	list.front();
	list.back();

//capacity
	list.size();
	list.empty();

//modify
	list.assign(n, value);
	list.assign(iter1, iter2);

	list.insert(list.begin(), n, value);
	list.insert(list.begin(), value);
	list.insert(list.begin(), iter1, iter2);

	list.erase(iter);
	list.erase(iter1, iter2);

	list.push_back();
	list.pop_back();
	list.push_front();
	list.pop_front();

	list.swap(list2);
	list.clear()

//more -- 7 items
	//splice
	list.splice(list.begin(), list2);
	list.splice(list.begin(), list2, list2.begin()+2);
	list.splice(list.begin(), list2, list2.iter1, list2.iter2);
	//merge
	list.merge(second);
	bool compare(const double a, const double b){
		return ( int(a) < int(b) );
	}
	list.merge(second, compare);
	//remove
	list.remove(99);
	//remove_if(pred);
	//sort(pred);
	//unique(pred);
	//reverse();
}












