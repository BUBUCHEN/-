#include<windows.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#define on_fire_para 1
#define out_speed 2
#define inf 2147483647
using namespace std;
struct pair_s{
	int nxt;
	int value;
};
struct node_s{
	int x;
	int y;
	int from;
	int was_f;
	int now_min;
	int on_fire_t;
	vector<pair_s> child;
	vector<pair_s> father;
};
	int n;
	int s,e;
	node_s node[200];	
void bfs_fire_spread(int tot,int now){
	
	if(node[now].on_fire_t>=tot){
		node[now].on_fire_t=tot*2;
		for(int i=0;i<node[now].child.size();i++){
			bfs_fire_spread(tot+node[now].child[i].value,node[now].child[i].nxt);
		}
		for(int i=0;i<node[now].father.size();i++){
			bfs_fire_spread(tot+node[now].father[i].value,node[now].father[i].nxt);
		}
	}
	return ;
}
void algo_safe(int u){
	int start =u; 
	node[start].now_min=node[start].on_fire_t;
	for(int i=1;i<=n;i++){
		int safe=0;
		for(int j=1;j<=n;j++){
			if(safe<node[j].on_fire_t&&node[j].was_f==0){
				safe=node[j].on_fire_t;
				start=j;
			}
		}
		node[start].was_f=1;
		for(int k=0;k<node[start].child.size();k++){
			node[node[start].child[k].nxt].now_min=node[node[start].child[k].nxt].now_min;
			node[node[start].child[k].nxt].from=start; 
		}
	}
} 
void input(){
	pair_s tmp;
	int count,nxt,val,o,of;
	ifstream ifs;
	ifs.open("input.txt");
	ifs>>n;
	for(int i=1;i<=n;i++){
  		node[i].on_fire_t=inf;
  	}
	for(int i=1;i<=n;i++){
		ifs>>count;
		for(int v=0;v<count;v++){
			ifs>>nxt>>val;
			tmp.nxt=nxt;
			tmp.value=val;
			node[i].child.push_back(tmp);
			tmp.nxt=i;
			node[nxt].father.push_back(tmp);		
		}
	}
	ifs>>s>>e>>o;
	for(int i=0;i<o;i++){
		ifs>>of;
		node[of].on_fire_t=0;
//		bfs_fire_spread(0,of);
	}
}
string int2str(int num){
	string a;
	while(num){
		a+=(char)((num%10)+'0');
		a+=' ';
		num/=10;
	}
	string reversed(a);
//	reverse(reversed.begin(),reversed.end());	
	return reversed;
}
int tot_path=0;
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
  return p+complete_path(v,node[j].from);
}
int main()
{
  DWORD star_time = GetTickCount();
  input();
  for (int i=1; i<=n; i++)
  {
  	node[i].was_f=0;
//  	cout<<node[i].on_fire_t<<" ";
  	node[i].now_min=inf;
    node[i].from=-1;
  }
  algo_safe(1);
  string result=int2str(e);
  result+=complete_path(s,e);
  ofstream ofs("output.txt");
  DWORD end_time = GetTickCount();
  cout<<"\n run_time= "<<end_time - star_time;
  cout<<result<<tot_path;
  ofs<<result<<tot_path<<" "<<end_time - star_time;
  
}
