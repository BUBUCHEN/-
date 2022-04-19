#include<iostream>
#include<windows.h>
#include<fstream>
#include<vector>
#include<algorithm>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
struct pair_s{//??pair 
		int nxt;//????? 
		int value;//?? 
};
struct node_struct{
	int now_value;
	long long on_fire_t; 
	int x;
	int y;
	vector<pair_s> child;
	vector<pair_s> father; 
};
int n,s,e;
node_struct node[200000];
void bfs_fire_out(int pos,int t){
	t*=2;
	if(t<node[pos].on_fire_t){
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
void input_data(){
	ifstream fst;
	int m,a,b,on_f,o;
	pair_s tmp;
	fst.open("input.txt");
	fst>>n;
//	cout<<n;
	for(int i=1;i<=n;i++){
		fst>>m;
		for(int c=0;c<m;c++){
			fst>>a>>b;
			tmp.nxt=a,tmp.value=b;
			node[i].child.push_back(tmp);
			tmp.nxt=i;
			node[a].father.push_back(tmp);
		}
	}
	for(int i=1;i<=n;i++){
		node[i].on_fire_t=99999;
		node[i].now_value=9999;
	}
	fst>>s>>e>>o;
	for(int j=0;j<o;j++){
		fst>>on_f;
		bfs_fire_out(on_f,0);
	}
}
int mhin=2147483647;
string qlq;
void dfs(int now,string re,double tot){

	if(now==e){
		if(tot<mhin){
			mhin=tot;
			qlq=re;
		}
//		cout<<re<<" "<<tot<<"!\n";
		return ;
	}
	if((tot>=node[now].on_fire_t||tot>=node[now].now_value)&&(tot!=0)){
		return ;
	}                    
	for(int i=0;i<node[now].child.size();i++){
		dfs(node[now].child[i].nxt,re+int2str(node[now].child[i].nxt)+" ",tot+node[now].child[i].value);
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
	ofstream ofs;
	long long pos,max=-1;
	for(int i=1;i<=n;i++){
		if(node[i].on_fire_t>max){
			pos=i;
			max=node[i].on_fire_t;
		}
	}
	e=pos;
	ofs.open("output.txt");
	dfs(s,int2str(s)+" ",0);
	cout<<qlq<<mhin;
QueryPerformanceCounter(&nEndTime);
time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
cout<<qlq<<mhin;
	ofs<<qlq<<mhin<<" "<<1000*time;
  cout<<"\n run_time= "<<1000*time;
} 
