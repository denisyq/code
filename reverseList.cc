#include <iostream>
#include <pthread.h>
#include <cassert>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

/*
 * reverse the one direction list
 */

typedef struct data{
	int val;
	struct data* next;
}Data;
void printList(Data* head){
	while(head != NULL){
		//std::cout<<head<<std::endl;
		std::cout<<head->val<<std::endl;
		head = head->next;
	}
}
//instead of new operator,for auto release
std::vector<Data> dv;

Data* initList(void){
	int num=5,val;
	Data* head=NULL;
	Data* tail=NULL;
	dv.reserve(num);
	int i=0;
	while(i < num){
		std::cin>>val;
		//Data* tmp = new Data;
		dv[i].val  = val;
		dv[i].next = NULL;
		if(head == NULL){
			head = &dv[i];
			tail = head;
		}else{
			tail->next = &dv[i];
			tail = tail->next;	
		}
		i++;
	}/*
	std::cout<<"init print"<<std::endl;
	for(int i=0;i<5;i++){
		std::cout<<&dv[i]<<std::endl;
		std::cout<<dv[i].val<<std::endl;
	}
	std::cout<<"head "<<head<<std::endl;
	*/
	return head;
}
Data* reverse(Data* head){
	Data *a,*b,*c;
	a=NULL;
	b=head;
	c=head->next;
	
	//change b->next one time
	//and then move a,b,c
	while(b->next != NULL && c != NULL){
		b->next = a;
		a = b;
		b = c;
		c = c->next;
	}
	if(c == NULL) b->next = a;
	return b;
}
int main(){
	Data* head;
	head = initList();
	std::cout<<"print "<<std::endl;
	printList(head);
	std::cout<<"reverse"<<std::endl;
	printList(reverse(head));
	return 0;
}














