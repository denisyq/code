#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;

/* QUESTION:
 * Given a string, reverse it, while keep the word spell right
 * src: "I am a little boy"
 * Output: "boy little a am I"
 */

/* SOLUTION:
 * 1. reverse the whole string
 * 2. traverse and find word, reverse word
 */

//[2016.Aug.04] cost 1 hour to finish, not good

static const int NUM = 100;

void foo(char* buf, int lh, int rh){
	// "abc ", lh->a, rh->' '
	char tmp[NUM]={0};
	if((rh == lh) || (rh-lh==1)){
		//do_nothing
	}else{
		int j=0;
		for(int i=rh-1;i>=lh;i--){
			tmp[j++] = buf[i];
		}
		tmp[j]='\0';
		//cout<<tmp<<endl;
		strncpy(&buf[lh], tmp, rh-lh);
	}
}
int main(void){
	char src[] = "hello i am a little boy !";
	char dest[NUM];
	int size = sizeof src / sizeof(char);
	//cout<<"size:"<<size<<endl;
	int j=0;
	for(int i=size-1;i>0;i--){
		dest[j++] = src[i-1];
	}
	dest[j] = '\0';
	int lh=0,rh;
	for(int i=0;i<size-1;i++){
		if(dest[i] != ' ') continue;
		else rh = i;
		foo(dest,lh,rh);
		lh = rh +1;
	}
	foo(dest,lh,size-1);
	cout<<"Output: "<<endl<<dest<<endl;
	return 0;
}
