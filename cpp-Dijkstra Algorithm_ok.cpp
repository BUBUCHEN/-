#include<algorithm>
#include<windows.h>
#include <iostream>
#include <string>
#include<vector>
#include<fstream>
#define inf 9999999;
using namespace std;
struct pair_s{//自製pair
		int nxt;//下一個節點
		int value;//權重
};
struct node_struct{
	int now_value;
	int on_fire_t;
	int x;
	int y;
	int from;
	int was_father;
	vector<pair_s> child;
	vector<pair_s> father;
};
node_struct node[200000];
int n,s,e,yourdad[200000]={};
void bfs_fire_out(int,int);
string int2str(int num){
	string a;
	while(num){
		a+=(char)((num%10)+'0');
		num/=10;
	}
	string reversed(a);
	reverse(reversed.begin(),reversed.end());	
	return reversed;
}
void init();
void input_data(){
	int x,a,b,o,f_in;
	pair_s tmp;
	ifstream f_data,f_xy;
	string read_in;
	f_data.open("input.txt");
	f_data>>n;
	init();
	for(int i=1;i<=n;i++){//逐一輸入每個node的資訊
		f_data>>x;
		for(int v=0;v<x;v++){
			f_data>>a>>b;
			tmp.nxt=a,tmp.value=b;
			node[i].child.push_back(tmp);
			tmp.nxt=i;
			node[a].father.push_back(tmp);
		}
	}
	f_data>>s>>e>>o;
	for(int v=0;v<o;v++){
		f_data>>f_in;
		// cout<<f_in;
		node[f_in].on_fire_t=0;
		// bfs_fire_out(f_in,0);
	}
}
void bfs_fire_out(int pos,int t){
	t*=2;
	if(t<=node[pos].on_fire_t){
		node[pos].on_fire_t=t;
		for(int i=0;i<node[pos].child.size();i++){
			bfs_fire_out(node[pos].child[i].nxt,t+node[pos].child[i].value);
		}
		for(int i=0;i<node[pos].father.size();i++){
			bfs_fire_out(node[pos].father[i].nxt,t+node[pos].father[i].value);
		}
	}
	else{
		return ;
	}
}
void dijkstra(int u){
	int start=u,min=inf;
	node[start].now_value=0;
	for(int i=0;i<n;i++){
		min=inf;
		for(int j=1;j<=n;j++){
			if (min> node[j].now_value and node[j].was_father==0)
			{
				min = node[j].now_value;
				start = j;
			}
		}
		node[start].was_father=1;
		for (int k=0; k<node[start].child.size(); k++)
		{
				if (node[node[start].child[k].nxt].now_value >node[start].now_value + node[start].child[k].value && node[start].now_value+node[start].child[k].value<node[node[start].child[k].nxt].on_fire_t)
				{
					node[node[start].child[k].nxt].now_value = node[start].now_value + node[start].child[k].value;
					node[node[start].child[k].nxt].from = start;
				}
		}
	}
}
int tot_path;
string complete_path (int v, int j)
{
  string p;
  if(v==j)
  {
    return "";
  }
  p = int2str(node[j].from);
  for(int i=0;i<node[node[j].from].child.size();i++){
  	if(node[node[j].from].child[i].nxt==j){
  		tot_path+=node[node[j].from].child[i].value;
		break;
	  }
  }
  return p+" "+complete_path(v,node[j].from);
}
void init(){
	for(int i=1;i<=n;i++){
		node[i].from=0;
		node[i].now_value=inf;
		node[i].on_fire_t=inf;
		node[i].was_father=0;
	}
}
int main(){
	DWORD star_time = GetTickCount();
input_data();
dijkstra(1);
// cout<<"!";
string result=int2str(e)+' ';
result+=complete_path(s,e);
//result+=int2str(e);
ofstream opt("output.txt");
DWORD end_time = GetTickCount();
  cout<<"\n run_time= "<<end_time - star_time;
cout<<result<<tot_path;
opt<<result<<" "<<tot_path<<" "<<end_time - star_time;
return 0;
}
