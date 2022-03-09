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
	int now_min;
	int on_fire_t;
	vector<pair_s> child;
	vector<pair_s> father;
};
	int n;
	int s,e;
	node_s node[200];	
void bellmanford(int s)
{
  int start = s;
  node[start].now_min = 0;
  bool change =true;
  for (int i=1; i<=n; i++)
  {
  	node[i].now_min=inf;
  	node[i].from=-1;
  }
  for(int i=0;i<node[start].child.size();i++){
  	node[node[start].child[i].nxt].from=start;
  }
  for(int i=0; i<n-2 && change;  i++)
  {
    change = false;
    for (int j=1; j<=n; j++)
    {
      if(j!= start)
      {
      	for(int g=0;g<node[j].child.size();g++){
      		if(node[node[j].child[g].nxt].now_min>node[j].now_min+node[j].child[g].value && node[j].now_min+node[j].child[g].value<node[node[j].child[g].nxt].on_fire_t)
            {
              node[node[j].child[g].nxt].now_min = node[j].now_min+node[j].child[g].value;
              node[node[j].child[g].nxt].from=j;
              change = true;
            }		
		} 
      }
    }
  }
}
void bfs_fire_spread(int tot,int now){
	
	if(node[now].on_fire_t>=tot){
		node[now].on_fire_t=tot;
		for(int i=0;i<node[now].child.size();i++){
			bfs_fire_spread(tot+node[now].child[i].value,node[now].child[i].nxt);
		}
		for(int i=0;i<node[now].father.size();i++){
			bfs_fire_spread(tot+node[now].father[i].value,node[now].father[i].nxt);
		}
	}
	return ;
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
  input();
  for (int i=1; i<=n; i++)
  {
  	cout<<node[i].on_fire_t<<" ";
  	node[i].now_min=inf;
    node[i].from=-1;
  }
  bellmanford(s);
  string result;
  result+=complete_path(s,e);
  ofstream osf;
  osf.open("output.txt");
  reverse(result.begin(),result.end());
  result+=' ';
  result+=int2str(e);
  cout<<result;
  osf<<result<<" "<<tot_path;
  return 0;
}
