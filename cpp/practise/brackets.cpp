#include <iostream>
#include <stack>
#include <string>
using namespace std;
int checkNotRight(string);
int process(string, int&, int&);

int main(void){
	string s;
	int first_end=0,num_swap=0;
	cin>>s;
	if(process(s,first_end,num_swap) == -1)
		cout<<"brackets are not coupled"<<endl;
	else
		cout<<"first_end="<<first_end<<"  "<<"num_swap="<<num_swap<<endl;
}
int process(string s, int& first_end, int& num_swap){
	if(checkNotRight(s) == false)
		return -1;
	stack<char> stackMain;
	stack<char> stackSub;
	int firstEnd=0,numSwap=0;//first_end,num_swap are for output
	int firstEndFlag=false;
	for(int i=0;i<s.length();i++){
		if(s[i] == '(' && stackSub.empty() ) 
			stackMain.push(s[i]);
		else if(s[i]=='(' && !stackSub.empty()) {
			//has ')" in stackSub,
			if(!firstEndFlag) firstEnd +=2;
			numSwap += stackSub.size();
			stackSub.pop();
		}
		else if(s[i] == ')' && !stackMain.empty() ){
			//case 1, stackMain has '(', so stackMain pop
			stackMain.pop(); 
			if(!firstEndFlag) firstEnd += 2;
		}
		else if(s[i]==')' && stackMain.empty()){
			stackSub.push(s[i]);
		}
		if(stackMain.empty() && stackSub.empty()){ 
			//such as () or (())
			firstEndFlag = true;
			firstEnd -= 1;
		}
	}
	if(s[0] == ')') {
		firstEnd=1;
		//firstEndFlag=true;
	}
	first_end = firstEnd;
	num_swap  = numSwap;
	return 0;
}
int checkNotRight(string s){
	int length = s.length();
	if(length % 2==1)
		return false;//error
	int num_left=0, num_right=0;
	int index=0;
	while(length--){
		if(s[index] == '(') num_left++;
		else if(s[index] == ')') num_right++;
		else cout<<"error"<<endl;
		index++;
	}
	if(num_left != num_right) return false;
	else return true;
}





