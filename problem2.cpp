#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define V vector
#define rep(i,N) for(int i=0;i<N;++i)

void chmax(ll& a,ll b){if(a<b)a=b;}

//H=W=26
V<V<ll>> prodmatrix(V<V<ll>> a,V<V<ll>> b){
  V<V<ll>> c(26,V<ll>(26,0));
  rep(j,26)rep(k,j+1)rep(i,k+1)chmax(c[i][j],a[i][k]+b[k][j]);
  return c;
}
//H=W=26
V<V<ll>> powmatrix(V<V<ll>> v,ll K){
  V<V<ll>> ans(26,V<ll>(26,0));
  while(K>0){
    if(K&1)ans=prodmatrix(ans,v);
    K>>=1;
    v=prodmatrix(v,v);
  }
  return ans;
}
void solve(){
  int N,Q;
  cin>>N>>Q;
  V<V<ll>> allcnt(26,V<ll>(26,0)),cnt(26,V<ll>(26,0));
  while(N--){
    string s;
    cin>>s;
    rep(j,26)rep(i,j+1)cnt[i][j]=0;
    for(auto x:s){
      x-='a';
      rep(i,x+1){
        ll ret=cnt[i][x];
        rep(j,x)chmax(ret,cnt[i][j]);
        cnt[i][x]=ret+1;
      }
    }
    rep(i,26)rep(j,25)chmax(cnt[i][j+1],cnt[i][j]);
    rep(i,26)rep(j,25)chmax(cnt[j][i],cnt[j+1][i]);
    rep(j,26)rep(i,j+1)chmax(allcnt[i][j],cnt[i][j]);
  }
  ll ans=0;
  for(auto v:powmatrix(allcnt,Q))chmax(ans,*max_element(v.begin(),v.end()));
  cout<<ans<<endl;
}
int main(){
  int T;cin>>T;
  while(T--)solve();
}