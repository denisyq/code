#include <iostream>
#include <cstring>
using namespace std;

class Stack{
    
private:
    class Link{
        public:
            int data_;
            Link* next_;
            Link* prev_;
            Link(int data):data_(data){}
            Link();
    };
    Link *head_,*tail_;
    int size_;
    
public:
    Stack():size_(0){}
    ~Stack(){
        Link* ins;
        while(size_){
            ins = head_;
            head_=head_->next_;
            delete ins;
        }

    }
    const int getSize(){ return size_;}
    void push(int data){
        Link* node = new Link(data);
        if(getSize()==0)
            head_=tail_=node;
        else{
            tail_->next_ = node;
            node->prev_ = tail_;
            tail_=tail_->next_;
        }
        node->next_ = NULL;
        size_++;

    }
    bool pop(int &data){
        if(getSize()==0) return 0;
            Link* ins = tail_;
        if(getSize()>1){
            tail_ = tail_->prev_;
            tail_->next_=NULL;
        }
        size_--;
        data = ins->data_;
        delete ins;
        return 1;
    }
};

int main(void){
    Stack stack;
    int tmp;
    for(int i=1;i<=5;i++)
        stack.push(i);

    while(stack.getSize()){
        if(stack.pop(tmp))
            cout<<tmp<<endl;
    }
    return 0;
}











