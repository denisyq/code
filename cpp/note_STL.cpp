****
 * NOTES of "Effective STL"
 * Written on May 13rd, 2016
 * Author: Dennis LU
****

#1 容器
1. 慎重选择容器类型
	- 序列容器：vector / deque / list / string
	- 关联容器：set / map / multiset / multimap
	- 非标准关联容器： hash_set / hash_map
	- 其他：stack / queue / heap / priority_queue
	
	- queue & stack 实现如果用vector，是无法事先确认其长度的，所以增加删除都不高效，只能用deque
	- priority_queue 实现用heap作为其底层数据结构（top值一直是min/max)，当然也可以用排序的vector来做
	- vector 优势：内存连续，可random visit，容器的构建sizeof不大
			 劣势：insert/erase 不高效，内存可能需要重新分配和copy，push_back/pop_back 同样如此
			 		iterator容易失效，需要reserve空间
	- deque  优势: 内存是一段段连续的，push_back/push_front等操作高效
			 劣势：容器构建的sizeof较大
	- list   优势：insert/erase 高效，因为无法用algorithm的API所以有自己的remove/sort/merge/unique
			 劣势：无法random visit, 遍历需要O(N)
	- hash VS 关联容器： HASH是精确打击，能很快找到某个元素 / 关联容器更容易区域打击，找到一片
	- heap：
		make_heap(pvec->begin(),pvec->end(),greater<int>());
		
		pvec->push_back(111);
		push_heap(pvec->begin(),pvec->end());
		
		pop_heap(pvec->begin(),pvec->end());
		pvec->pop_back();
		
		sort_heap(pvec->begin(), pvec->end());
		
3. 确保容器中的对象拷贝正确且高效
	- 如果说容器中是Widget对象，经常拷贝肯定开销较大，那就在容器中存放Widget*, 指针拷贝快
	- 如果放指针，一定要注意，在容器销毁时，不会销毁指针的malloc空间造成MemoryLeak -> 智能指针

4. 调用empty 而不是size()==0
	- 在大部分容器中，size() 不会是O(N)操作，但是在list中，因为有splice操作，size不一定是常数操作
	- list.splice(list.end(), list2, find(list2.begin(),list2.end(),5), find(...,10))
	- 这时，我们不知道两个find之间是几个元素，方法1，我们遍历一遍更新size，方法2，不遍历
	- 因为list的实现需要splice常数时间，所以size就不是常数时间了
	
5. 成员函数效率优于通用函数
	- vector.assign() VS copy(vec.begin(),vec.size()/2, back_inserter(vec2))
	- 正确的写vector的批量输入：
		for(i=0;i<NUM;i++){
			loc = vec.insert(loc,value);
			loc++;
		}//这种写法就算capacity没问题，每次insert都要移动数据，也是不高效的
		//一个个的insert进来，不如一下子insert进来所有数据
		//不如这种：vec.insert(loc, iter1, iter2)

7. 如果容器中有new出来的指针，不要忘记delete掉
	vector<Widget*> wv;
	for(){
		wv.push_back(new Widget);
	}
	wv会自动删掉，但是里面的Widget*不会，他们造成了MemoryLeak
	你需要：

	struct DeleteObject{
		template<typename T>
		void operator()(const T* ptr) const{
			delete ptr;
		}
	}
	//for_each，优于for loop, 不怕中间的异常跳出，破坏loop
	for_each(wv.begin(),wv.end(), DeleteObject());
	
	/* 最好的解决方法是用SmartPointer */
	typedef boost::shared_ptr<Widget> WSP;
	vector<WSP> vec;
	for(){
		vec.push_back(WSP(new Widget));
	}
	//shapred_ptr<Widget> ptr(new Widget);
	
9. 正确的删除容器内元素
	- 首先，用容器自己的api（erase）最有效
	- 需要用remove/remove_if，都别忘记erase-remove结构
		vec.erase(remove(vec.begin(),vec.end(),99),vec.end())
		//remove 不删除元素，只是将符合条件的元素移到最后面
	- list用自己的API：remove， 因为list不能用通用的remove（可能是list无法RandomVisit)
	- 关联容器 用 erase
	- 需要区域的删除元素：
		- vector/deque/string
			for(){
				if(badValue(*iter))
					iter = vec.erase(iter);
				else
					iter++;
			}
		
		- set/map
			for(){
				if(badValue(*iter))
					set.erase(iter++);
				else
					iter++;
			}
12. STL不完全能够做到线程安全
	- 最好还是上锁安全点
	- RAII(Resource Acquisition is initialization), 用RAII来创建LOCK
	

#2 vector && String

13. vector & string 优先动态分配的数组
	- new出来的不要忘记delete，选择正确的delete或者delete[],不要重复delete
	- 用vector等方便内存管理

14. 用reserve避免不必要的内存分配
	- 内存分配是按照2-4-8这样或者是原先size的double再double，反应在capacity
	- 涉及内存重新分配，开销很大；有重新new一块空间，拷贝原先数据，iterator失效
	
15. 注意string实现的多样性
	- 这节是说string的各个平台的实现，导致string的sizeof不一样
	- sizeof(string) == 8
	- sizeof(vector) == 24
	- sizeof(deque)  == 80
	- sizeof(list)   == 16
	- sizeof(set/map)== 48
	- 以上基于64位，sizeof(char*) == 8
	
16. 如何把vector和string传递给旧的API
	- void foo(int* array） ----- &vector[0]
	- void foo(char* ) ---------- string.c_str()	
	
17. 使用swap技巧除去多余的容量
	- vector<int>(iv).swap(iv)  ------ 去掉的是capacity-size的空间
	- vector<int>().swap(iv)    ------ 类似clear
	
18. 避免使用vector<bool>
	- 一个bool只占一个二进制位，一个字节可以容纳8个bool
	- 不是真正的容器
	- 可以使用deque<bool> 或者 bitset
	


#3 关联容器

19. 相等和等价的区别
	- 相等的概念是基于 operator==
	- 等价的概念是基于 operator<, 等价的关系是以“已排序区间中的对象值的相对顺序”为基础
	- 等价是如：Widget w1 & w2, w1和w2哪个都不在对方之前，即视为等价
	- set<Widget>的默认比较函数是less<Widget>, 在less<Widget>里是看operator<
	- 等价：!(w1 < w2) && !(w2 < w1)
	- 关联容器强调排序，pred（默认less）由用户自己定义，成功的判断返回false
	- 

20. 为包含指针的关联容器指定比较类型
	- 关联容器里放指针，首先是smartPointer比较好，其次，不会对指针自动排序，要指定比较函数
	- set<string*, less<string*> > stringSet;
	- 或者这样
		struct StringPtrLess : 
			public binary_function<const string*,
									const string*,
									bool> {
			bool operator() (const string* ps1, const string* ps2) const {
				return *ps1 < *ps2;
			}								
		};
		//加入template
		struct StringPtrLess {
			template<typename T>
			bool operator() (T pt1, T pt2) const{
				return *pt1 < *pt2;
			}	
		};
		typedef set<string*, StringPtrLess> StringSet;
		StringSet ssp;
		//然后可以遍历
		for(StringSet::const_iterator it=ssp.begin(); i!=ssp.end();i++)
			cout<<**i<<endl;
		//说过用for loop不是个good idea，选择用for_each
		void print(const string* sp){
			cout<< *sp <<endl;	
		}
		for_each(ssp.begin(),ssp.end(),print);
		//这样写出来的print不够好，再改下
		struct PRINT{
			template<typename T>
			void operator() (const T* t) const{
				cout<< *t <<endl;
			}	
		};
		for_each(ssp.begin(),  ssp.end(), PRINT());
		//最后需要注意的是：
		//你可能会想给set添加个bool比较函数就行，其实这样编译不过
		bool StringLess (const string* s1, const string* s2) const{
			return *s1 < *s2;
		}//这种比较函数在set<string*, StringLess >会编译不过

21. 总是让比较函数在等值的情况下返回False
	- 在关联容器做比较函数时，不要用小于等于 或 大于等于，就只用小于 或者 大于。

22. 不要直接修改关联容器的键
	- 关联容器是按照RBTree来排序的，直接改变其中的键，对排序就乱了
	- map的设计者已经把键设计成const，所以修改键，会引起报错
	- 但是set的设计者并没有设计成const，因为set<Person_Info>，若Person_Info类中的比较类型是
		以Person的age大小，如果设计成const，在后面的代码中将无法修改Person_Info类中的其他信息
		同样的map不存在这样的问题。所以set无法使用const键
	- 说道const，我们梳理下const概念：
		1. const int a = 100; 这个可以写在全局只读数据段，申明的是全局int a; 也可以是在函数类，是
			写在堆栈里面。
		2. 在全局的const的修改，可以用 const_cast<int*>, 编译没问题，运行就段错误
		3. 所以只能修改在堆栈里的const变量：
			const int *a = new int(10);
			int* p = const_cast<int*>(a);
			const int a = 100;
			int* p = const_cast<int*>(&a);
			这两种方法，a和*p都被修改
			const int a =100;
			int* p = (int*)(&a);
			*p修改了，但是cout<<a 时，a还是原值
			
23. 考虑用排序的vector来代替关联容器
	- 关联容器的优势是insert和erase速度快，RBTree结构的查找
	- 如果数据量一下子全了，然后操作只有查找，用排序后的vector就比关联容器更好
	- 排序后的vector，用binary_search/equal_range/lower_bound/upper_bound,都可以
	- 最后书中说，关联容器的内存空间不连续，相对连续的vector，更造成页面置换，影响效率
	- 类似代码如：
		vector<Widget> vw;
		sort(vw.begin(),vw.end(),pred);
		Widget w;
		if(binary_search(vw.begin(),vw.end(),w)){
			pair<vector<Widget>::iterator, vector<Widget>::iterator> ret = 
				equal_range(vw.begin(), vw.end(),w);
			if(ret.first != ret.second){
				//found
				//这个地方又牵涉到 ret.second - ret.first 能不能用的问题
				//如果是连续内存，如vector,可以用ret.second-ret.first来确定有几个
				//那如果是list这种不连续内存，只能用遍历的方法得到
				//for(list<int>::iterator it=ret.first; it!=ret.end();it++){
				//	num++;
				//}
				//或者distance(list.begin(),list.end())
			}
		}

24. 在效率至关重要时，分辨map::operator[] 和 map::insert的区别
	- map::operator[] 在调用后，先去找是否存在：Key存在，改变value、
		若key不存在，则调用map::insert来创建Key::value
	- map::insert 在键值不存在的时候，创建它
						
25. 熟悉非标准的散列容器
	- hash_set
	- hash_map
	

#4 迭代器 Iterator

26. iterator 优先于 const_iterator & reverse_iterator & const_reverse_iterator
	- insert/erase 入参不能使用除iterator外的迭代器
	- iterator = reverse_iterator.base() //NOT the same element point
	- const_iterator = const_reverse_iterator.base()
	- iterator = advance(i, distance<vector<int>::const_iterator>(i,ci));
	- 尽量用iterator，将const转化过来需要时间：连续的要O(1),list等需要O(n) 
	
27. const_iterator 转化成 iterator (使用advance & distance)
	- demo代码：
		typedef vector<int>::iterator Iter;
		typedef vector<int>::const_iterator ConstIter;
		vector<int> iv;
		ConstIter ci; 
		...
		Iter i(iv.begin());
		advance(i, distance<ConstIter>(i,ci));
	- 解释：先将iter定义在begin()上，然后通过计算ci和begin()的距离，再由advance累加
	
28. 正确理解由reverse_iterator的base()所产生的iterator
	- 由find(vector.rbegin(),vector.rend(),value) 返回的必须是reverse_iterator
	- vector<int>::reverse_iterator re_iter = find(iv.rbegin(),iv.rend(),value)
	- 但是这个reverse_iterator 不能用于insert和erase: iv.erase(re_iter)//NOT work
	- 必须是iterator才行，所以，reverse_iterator 得转变成iterator
	- iterator = reverse_iterator.base()
	- 问题来了：iterator 不是指向reverse_iterator的值
	- vector<int> = {1，2，3，4，5}， find(rbegin,rend,3), riter -> 3
	- iter(riter.base()) -> 3后面的4
	


#5 算法

30. 确保目标区间足够大
	- demo代码：
		int add5(int x);
		vector<int> values, results;
		transform(values.begin(),values.end(),
					back_inserter(results),add5);
	- back_inserter() 调用push_back。若front_inserter调用push_front，确保容器支持
	- 这样的元素拷贝对string、vector等顺序容器不理想，他们需要reserve且最好保证一次性
		全部拷贝进去，transform这样的一个个元素insert进来的，需要频繁移动数据。
		
31. 了解各种排序
	- 序列容器：nth_element > partial_sort > sort > stable_sort
	- list不可以random visit，所以不能用上述api，list有成员函数sort
	- 关联容器自身就是有序的
	- partition/stable_partition 根据某个条件分段，速度快
	- 根据某个条件，但具体不知道几个 ------ partition
	- 知道具体几个，如前75%         ------ nth_element 
	- 前75%也是要排序的             ------ partial_sort
	- 全排序                       ----—- sort  
	- 等值的不改变前后顺序           ------ stable_sort
	
32. vector.erase(remove(),end())
	- remove 操作是将符合条件的移到最后，并没有实际删除掉
	- 用erase+remove操作才能真正删除
	
33. remove包含指针的容器
	- 因为容器的放的是指针，而指针指向的空间并没有delete，可能会造成内存泄漏
	- 除了记得删掉指针的内存，也可以用智能指针来代替
	
34. 需要先排好序的api
	- binary_search/equal_range/lower_bound/upper_bound
	- unique: 只会寻找前一个后一个是否相同.ababab就发现不了
	- 如果sort是按照greater<int>来排序，binary_search也得加上，因为
		binary_search是按照<来默认排序的
		binary_search(iv.begin(),iv.end(),value, greater<int>())
		

		
#7 在程序中使用STL

43. 算法调用优于手写的循环
	- for_each比for要好，能捕捉异常并释放资源

44. 容器的成员函数优于同名算法函数
	- set.find VS. find()
	
45. 区分count/find/binary_search/lower_bound/upper_bound/equal_range
	- find 存在性测试, 无序空间
	- 排序过的，对数时间的bianry_search,它只回答在不在，返回bool值
	- lower_bound：返回value值在的地方或value不在，他应该被插入的地方
	- lower_bound返回的iterator，不要直接iter!=end() && *iter == value
	- lower_bound更适合用于找到某个条件的左值，在一个位置上进行删除
	- iv.erase(lower_bound(),iv.end)
	- 推荐使用equal_range, distance(p.first,p.second)确定几个元素
	
46. 使用函数对象 而不是函数 作为STL算法的参数
	- 自己写的函数，即使申明inline，最后编译的时候可能没有inline，所以效率
		上没有函数对象好
