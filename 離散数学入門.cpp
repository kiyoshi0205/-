#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
template<class T>
inline bool chmax(T& a,const T b){bool x=a<b;if(x)a=b;return x;}
template<class T>
inline bool chmin(T& a,const T b){bool x=a>b;if(x)a=b;return x;}
using P=pair<long long,int>;

//日数(手計算時は10にするとよい)
constexpr int M=10;
int main(){
  int N,K;
  cin>>N>>K;
  vector<int> L(N),R(N),W(N);
  vector<int> g[M+2];
  //入力とグラフの構築(案件のindexをもつように)
  for(int i=0;i<N;++i){
    cin>>L[i]>>R[i]>>W[i];
    R[i]+=K;
    chmax(L[i],K);
    chmin(R[i],M+1);
    g[L[i]].emplace_back(i);
  }
  //dijkstra 色々楽をしたのでO((E+V)log(E+V))
  vector<long long> dist(M+2,numeric_limits<long long>::max()/3);
  vector<pair<int,int>> bf(M+2);
  priority_queue<P,vector<P>,greater<P>> que;
  que.emplace(dist[K]=0,K);
  while(!que.empty()){
    auto [y,x]=que.top();que.pop();
    if(dist[x]!=y)continue;
    //案件の辺
    for(auto i:g[x]){
      if(chmin(dist[R[i]],W[i]+y)){
        que.emplace(W[i]+y,R[i]);
        bf[R[i]].first=L[i];
        bf[R[i]].second=i;
      }
    }
    //コスト0の辺
    if(x&&chmin(dist[x-1],y)){
      que.emplace(y,x-1);
      bf[x-1].first=x;
      bf[x-1].second=-1;
    }
  }
  //答えとなる案件選択の最小値
  cout<<dist[M+1]<<'\n';
  //逆辺を辿り案件選択の復元
  vector<int> ans;
  int now=M+1;
  while(bf[now].first>0){
    if(bf[now].second>=0)ans.emplace_back(bf[now].second+1);
    now=bf[now].first;
  }
  sort(ans.begin(),ans.end());
  //案件の選択
  for(size_t i=0;i<ans.size();++i)cout<<ans[i]<<" \n"[i+1==ans.size()];
}