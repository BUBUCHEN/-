#include<algorithm>
#include<windows.h>
#include <iostream>
#include <string>
#include<vector>
#include<fstream>
#include<queue>
#define inf 2147483647;
using namespace std;
struct pair_s{
		int nxt;
		int value;
};
bool have_sol=0;
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
queue<int> onfy;
node_struct node[200000];
int n,s,e,yourdad[200000]={};
void bfs_fire_out();
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
	for(int i=1;i<=n;i++){
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
		node[f_in].on_fire_t=0;
		onfy.push(f_in);
	}
	bfs_fire_out();
}
void bfs_fire_out(){
	int nps;
	while(!onfy.empty()){
		nps=onfy.front();
		onfy.pop();
		for(int i=0;i<node[nps].child.size();i++){
			if(node[node[nps].child[i].nxt].on_fire_t>node[nps].child[i].value+node[nps].on_fire_t){
				node[node[nps].child[i].nxt].on_fire_t=node[nps].child[i].value+node[nps].on_fire_t;
				onfy.push(node[nps].child[i].nxt);
			}
		}
		for(int i=0;i<node[nps].father.size();i++){
			if(node[node[nps].father[i].nxt].on_fire_t>node[nps].father[i].value+node[nps].on_fire_t){
				node[node[nps].father[i].nxt].on_fire_t=node[nps].father[i].value+node[nps].on_fire_t;
				onfy.push(node[nps].father[i].nxt);
			}
		}
	}
}
int mhin=2147483647;
string qlq;
void dfs(int now,string re,int tot){
	if((tot>=node[now].on_fire_t||tot>=node[now].now_value)&&(tot!=0)){
		return ;
	}
	if(now==e){
		cout<<"yee\n";
		if(tot<mhin){
			mhin=tot;
			qlq=re;
		}
		have_sol=1;
		return ;
	}                   
	for(int i=0;i<node[now].child.size();i++){
		dfs(node[now].child[i].nxt,re+int2str(node[now].child[i].nxt)+" ",tot+node[now].child[i].value);
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
double time = 0;
double counts = 0;
LARGE_INTEGER nFreq;
LARGE_INTEGER nBeginTime;
LARGE_INTEGER nEndTime;
QueryPerformanceFrequency(&nFreq);
QueryPerformanceCounter(&nBeginTime);
input_data();
cout<<"onft ";
int ne,max=-1;
cout<<"\n";
dfs(s,int2str(s)+" ",0);
if(!have_sol){
	e=ne;
}
dfs(s,int2str(s)+" ",0);
int nmax=-1;
if(!have_sol){
		for(int i=1;i<=n;i++){
			if(node[i].on_fire_t<max&&node[i].on_fire_t>nmax){
				nmax=node[i].on_fire_t;
				ne=i;
			}
		}
		e=ne;
		dfs(s,int2str(s)+" ",0);
}
if(!have_sol){
	cout<<"QAQ...\n";
}
ofstream opt("output.txt");
QueryPerformanceCounter(&nEndTime);
time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
cout<<qlq<<" "<<mhin<<" "<<1000*time;
opt<<qlq<<" "<<mhin<<" "<<1000*time;
return 0;
}
