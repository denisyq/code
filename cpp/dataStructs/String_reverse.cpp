#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;

void swap(char& a, char& b){
    char tmp = a;
    a = b;
    b = tmp;
}
/*
 * 简单的反转字符串，利用原空间，i=0 和 i=N-1 进行swap, 需要进行O(N/2)
 */
void reverse(char* str){
    int len = sizeof(str)/sizeof(char);
    cout<<"len:"<<len<<endl;
    for(int i=0;i<len/2;i++){
        //中间的元素，作为分界点。如果是奇数，中间的元素不要动，偶数，正好全部反转
        swap(str[i], str[len-1-i]);
    }
}

int main(int argc, char** argv){
    string base("abcdefghijk");

    //简单的字符反转
    cout<<"String simple reverse:"<<endl;
    cout<<"Orig :"<<base<<endl;
    reverse((char*)base.c_str());
    cout<<"After:"<<base<<endl;
}

