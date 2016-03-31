#include <stack>
#include <queue>

//cons
stack<int> stack;
stack<int, vector<int> > stack(vector);

//capacity
stack.size();
stack.empty();

//element
stack.top();
stack.push();
stack.pop();

stack.swap();




#include <queue>
//cons
queue<int> queue;
queue<int, vector<int> >queue(vector);

//capacity
queue.size();
queue.empty();

//element
queue.push();
queue.pop();
queue.front();
queue.back();

queue.swap();


#include <queue>
//priority_queue

//cons
priority_queue<int> first;
priority_queue<int> second(it, it+4);
priority_queue<int, vector<int>, greater<int> > third(it, it+4);
priority_queue<int, vector<int>, comp > fourth;

typedef priority_queue<int, vector<int>, comp > pri_queue;
pri_queue fifth( comp() );
pri_queue sixth( comp(true) );
class comp{
    private:
        bool param;
    public:
        comp(const bool& i=false){ param = i;}
        bool operator()(const int& a, const int& b) const{
            if(param==false) return (a<b);
            else return (a>b);
        }
};

//other
size();
empty();

top();
push();
pop();

swap();

