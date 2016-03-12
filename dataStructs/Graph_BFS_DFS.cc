#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

int data[7][7]={
    {0,0,0,0,0,0,0},
    {0,0,1,2,0,0,0},
    {0,1,0,0,1,2,0},
    {0,2,0,0,4,0,6},
    {0,0,1,4,0,5,5},
    {0,0,2,0,5,0,1},
    {0,0,0,6,5,1,0} };

int dataDirection[7][7]={
    {0,0,0,0,0,0,0},
    {0,0,1,1,0,0,0},
    {0,0,0,0,1,1,0},
    {0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0},
};


class BFS{
public:
		BFS():n_(7){
			visited_.assign(n_,0);	//first arg is num, sec is value
		}
		void work(int start){
			if(!visited_[start]){
                //push in queue, set visited[]
                //do move visited_[start]=1 to queue.pop
                //in case duplicate in queue.
				iq_.push(start);
                visited_[start]=true;
            }
			while(iq_.size()!=0){
				int tmp=iq_.front();
				iq_.pop();
				cout<<"print  "<<tmp<<endl;
				for(int i=1;i<n_;++i){
					if(dataDirection[tmp][i]!=0 && !visited_[i]){
						iq_.push(i);
                        visited_[i]=true;//see comments at work() function begin.
                    }
				}
			}
		}
private:
		vector<int> visited_;
		queue<int> iq_;
		int n_;
};

class DFS{
public:
    DFS():n_(7),isLoop_(false){
        visited_.assign(n_,0); 
    }
    void dfsRecursive(int start){
        //print start here to get positive traverse
        //cout<<"print "<<start<<endl;
        visited_[start]=true;
        //use recursive algo to hide stack operation.
        for(int i=1;i<n_;++i){
            if(dataDirection[start][i]!=0 && !visited_[i])
                dfsRecursive(i);
        }
        //print start here to get reverse traverse
        //while this traverse could be used to topology sort.
        //cout<<"print "<<start<<endl;
    }
    void dfsNoRecursive(int start){
        visited_[start]=true;
        s_.push(start);
        while(!s_.empty()){
            int tmp=s_.top();
            s_.pop();
            //cout<<"print "<<tmp<<endl;
            for(int i=1;i<n_;++i){
                if(dataDirection[tmp][i] != 0 && !visited_[i]){
                    s_.push(i);
                    visited_[i]=true;
                }
            }
        }
    }


    //DFS can detect the loop.
    //visted_[i] == -1 and then set to true

    bool dfsCheckLoop(int start){
        visited_[start]=-1;//set -1, not true;
        for(int i=1;i<n_;++i){
            if(dataDirection[start][i] != 0){
                //NOTE: == -1 and return is only take effect on the recursive dfsCheckLoop(),
                //not the first dfsCheckLoop. Use the "if(dfsCheckLoop()) return true" to pass one by one.
                //careful about the "return" in recursive func. 
                if(visited_[i] == -1) 
                    return true;
                else if(!visited_[i])
                    if(dfsCheckLoop(i)) return true;
                    //if not return, will always return false at the end of func.
            }
        }
        visited_[start]=true;
        return false;
    }
    //set isLoop_ and create a new api to get isLoop_
    void dfsCheckLoop2(int start){
        visited_[start]=-1;//set -1, not true;
        for(int i=1;i<n_;++i){
            if(dataDirection[start][i] != 0){
                if(visited_[i] == -1){
                    isLoop_ =true;
                    break;
                }
                else if(!visited_[i])
                    dfsCheckLoop2(i);
            }
        }
        visited_[start]=true;
    }
    bool isLoop(void){
        return isLoop_;
    }
private:
    vector<int> visited_;
    stack<int> s_;//store non recursive DFS
    int n_;
    bool isLoop_;
};



int main(void){
    cout<<"------BFS"<<endl;
	//BFS bfs;
	//bfs.work(1);
    cout<<"------------"<<endl;
    DFS dfs;
    dfs.dfsCheckLoop2(1);
    cout<<dfs.isLoop()<<endl;
    return 0;
}

