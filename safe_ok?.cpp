#include<algorithm>
#include<windows.h>
#include <iostream>
#include <string>
#include<vector>
#include<fstream>
#define inf 2147483647;
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
int n,s,e;
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
		 bfs_fire_out(f_in,0);
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
int n_min=-1*inf;
string ph;
void dfs(int pos,int tot,string recoder,int actual_val){
	if(node[pos].on_fire_t==0||actual_val>node[pos].on_fire_t){
		return ;
	}
	if(pos==e){
//	cout<<recoder<<"\n";	
		if(n_min<tot){
//			cout<<n_min;
			n_min=tot;
			ph=recoder;	
		}
	return ;
	}
	for(int i=0;i<node[pos].child.size();i++){
		dfs(node[pos].child[i].nxt,tot+node[node[pos].child[i].nxt].on_fire_t,recoder+" "+int2str(node[pos].child[i].nxt),actual_val+node[pos].child[i].value);
	}
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
double time = 0;
double counts = 0;
LARGE_INTEGER nFreq;
LARGE_INTEGER nBeginTime;
LARGE_INTEGER nEndTime;
QueryPerformanceFrequency(&nFreq);
QueryPerformanceCounter(&nBeginTime);
input_data();
for(int i=1;i<=n;i++){
	cout<<node[i].on_fire_t<<" ";
}
cout<<"\n";
dfs(s,0,int2str(s),0);
cout<<ph;
ofstream opt("output.txt");
QueryPerformanceCounter(&nEndTime);//停止計時  
time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
//cout<<result<<tot_path<<" "<<1000*time;
opt<<ph<<" "<<n_min<<" "<<1000*time;
return 0;
}
