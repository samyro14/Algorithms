#include <bits/stdc++.h>
using namespace std;

ifstream fin("f.in");
ofstream fout("f.out");
#define p push
 //topological sort
 int n, m;
 bitset<100001> visited;
 stack<int> s;
 vector<int> a[100002];
 void read(){
     fin >> n >> m;
     for(int i = 1; i <= m; ++i){
         int x, y; fin >> x >> y;
         a[x].push_back(y);
     }
 }
 void dfs(int x){
     visited[x] = 1;
     for(auto it : a[x])
         if(!visited[it])
         dfs(it);
     s.p(x);
 }
 void solve(){
    for(int i = 1;  i <= n; ++i)
        if(!visited[i])
            dfs(i);

 }
 void display(){
     while(!s.empty())
         fout << s.top() << " ", s.pop();
 }
int main(){
    read();
    solve();
    display();
    return 0;
}