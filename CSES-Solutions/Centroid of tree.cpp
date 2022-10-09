#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
typedef long long ll;
#define pb push_back
#define ff first
#define ss second
const int N=3e5+7;
const int mod=1e9+7;
const double eps=1e-6;
const double pi=    3.14159265358979323846;
using namespace std;  
using namespace __gnu_pbds;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    op_set;
 
struct CentroidDecomposition{
    int N;
    vector<vector<int>>G;
    vector<vector<int>>T;
    vector<int>used,sz,par;
    int r;
    void set(int n){
        N=n;
        G.resize(N);
        T.resize(N);
        par.resize(N);
        fill(par.begin(),par.end(),-1);
    }
    void addEdge(int a,int b){
        G[a].push_back(b);
        G[b].push_back(a);
    }
 
    int calcSubtreeSize(int v,int p){
        sz[v]=1;
        for(auto u:G[v]){
            if(u==p||used[u])continue;
            sz[v]+=calcSubtreeSize(u,v);
        }
        return sz[v];
    }
 
    pair<int,int>findCentroid(int v,int p,int ov){
        pair<int,int>ret(N,-1);
        int mx=ov-sz[v];
        for(auto u:G[v]){
            if(u==p||used[u])continue;
            ret=min(ret,findCentroid(u,v,ov));
            mx=max(mx,sz[u]);
        }
        ret=min(ret,pair<int,int>(mx,v));
        return ret;
    }
 
    void dfs(int v,int p){
        calcSubtreeSize(v,-1);
        v=findCentroid(v,-1,sz[v]).second;
        used[v]=true;
        if(p==-1)r=v;
        else{
            par[v]=p;
            T[p].push_back(v);
        }
        for(auto u:G[v])if(!used[u])dfs(u,v);
    }
 
    void decompose(int v){
        used.resize(N);
        sz.resize(N);
        dfs(v,-1);
    }
 
    inline int root()const{
        return r;
    }
    vector<int>&operator[](int i){
        return T[i];
    }
};
 
int32_t main() 
{
   ios_base::sync_with_stdio(false);
   cin.tie(0);
 
   int n;
   cin >> n;
   CentroidDecomposition cd;
   cd.set(n);
   for(int i=1;i<n;i++)
   {
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        cd.addEdge(a,b);
   }
 
   cd.decompose(0);
   cout << cd.root()+1 << "\n";
}
