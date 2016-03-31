//reverse list
Data* reverseList(Data* head){
    Data* prev=NULL;
    Data* curr=head;
    while(curr){
        Data* next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    return prev;
}

