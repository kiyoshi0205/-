#include<bits/stdc++.h>
using namespace std;

#ifndef ATCODER_SEGTREE_HPP
#define ATCODER_SEGTREE_HPP 1

#include <algorithm>
#include <cassert>
#include <vector>

#ifndef ATCODER_INTERNAL_BITOP_HPP
#define ATCODER_INTERNAL_BITOP_HPP 1

#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace atcoder {

namespace internal {

// @param n `0 <= n`
// @return minimum non-negative `x` s.t. `n <= 2**x`
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
constexpr int bsf_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x))) x++;
    return x;
}

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
int bsf(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

}  // namespace internal

}  // namespace atcoder

#endif  // ATCODER_INTERNAL_BITOP_HPP

namespace atcoder {

template <class S, S (*op)(S, S), S (*e)()> struct segtree {
  public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = internal::ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

}  // namespace atcoder

#endif  // ATCODER_SEGTREE_HPP


using ll =long long;
struct S{
  ll lp,lm,ans,rp,rm,all;
  bool len;
};
constexpr S op(const S l,const S r){
  S res=l;
  res.ans=max({l.ans,r.ans,l.rp+r.lm,l.rm+r.lp});
  if(l.len){
    res.lp=max(l.lp,l.all+r.lm);
    res.lm=max(l.lm,-l.all+r.lp);
    res.all=l.all-r.all;
  }else{
    res.lp=max(l.lp,l.all+r.lp);
    res.lm=max(l.lm,-l.all+r.lm);
    res.all=l.all+r.all;
  }
  if(r.len){
    res.rp=max(r.rp,l.rm+r.all);
    res.rm=max(r.rm,l.rp-r.all);
  }else{
    res.rp=max(r.rp,l.rp-r.all);
    res.rm=max(r.rm,l.rm+r.all);
  }
  res.len=l.len^r.len;
  return res;
}
constexpr ll inf=1LL<<60;
constexpr S e(void){
  return {-inf,-inf,-inf,-inf,-inf,0,false};
}
using segtree=atcoder::segtree<S,op,e>;

vector<int> input(void){
  vector<int> res;
  string s;
  getline(cin,s);
  if(s.size())s.pop_back();
  while(s.size()){
    string t;
    while(s.size()&&(isdigit(s.back())||s.back()=='-')){
      t+=s.back();
      s.pop_back();
    }
    reverse(t.begin(),t.end());
    if(s.size())s.pop_back();
    res.emplace_back(stoll(t));
  }
  reverse(res.begin(),res.end());
  return res;
}

int main(){
  auto A=input();
  vector<S> init(A.size());
  for(size_t i=0;i<A.size();++i)init[i]=S({A[i],-A[i],A[i],A[i],-inf,A[i],true});
  segtree tree(init);
  vector<int> ans;
  while(1){
    auto Q=input();
    if(Q.empty())break;
    if(Q[0]==1){
      tree.set(--Q[1],S({Q[2],-Q[2],Q[2],Q[2],-inf,Q[2],true}));
    }else{
      assert(Q[0]==2);
      ans.emplace_back(tree.prod(--Q[1],Q[2]).ans);
    }
  }
  for(size_t i=0;i<ans.size();++i)cout<<ans[i]<<" \n"[i+1==ans.size()];
}