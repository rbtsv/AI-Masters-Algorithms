#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cstdint>


#define DEBUG true

using namespace std;

struct Fenwick{    
    int n;
    vector<int64_t> t;
    
    int F(int i){
        return i & (i+1);
    }
    
    Fenwick(const vector<int> & inp){
        n = inp.size();        
        t = vector<int64_t>(n+1,0);
        
        //vector<int64_t> s(n+1,0);
    	for(size_t i = 0; i < n; ++i){
            /*s[i+1] = s[i] + inp[i];
            t[i+1] = s[i+1] - s[F(i+1)-1];*/
            //t[i+1] = inp[i] + sum(i) - sum(F(i+1)-1);  
            modify(i, inp[i]);
    	} 
    }
    
    int64_t sum(int i){
        int64_t answ = 0;
        for(;i > 0; i = F(i) - 1){
            answ += t[i]; 
        }
        return answ;
    }
    
    int64_t rsq(int l, int r){
        return sum(r) - sum(l-1);
    }    
    
    void modify(int i, int d){
        for(; i <= n; i = i | (i+1)){
            t[i] += d;
        }
    }
    
};


int main ( ){
	std::ios::sync_with_stdio(false); std::cin.tie(0);
	if(DEBUG) freopen("t0", "r", stdin);	
	
	
	int64_t n;	
	cin >> n;
	vector<int> inp(n, 0);
    vector<int64_t> s(n+1,0);
	
	for(size_t i = 0; i < n; ++i){
		cin >> inp[i];
        if(DEBUG) s[i+1] = s[i]+inp[i];
   	}  

    Fenwick fw(inp);
		
	int m;
    cin >> m;	
	for(int64_t i = 0; i < m; ++i){
		int l, r;
		cin >> l >> r;
        if(DEBUG) cout << s[r] - s[l-1] << endl;
        cout << fw.rsq(l,r) << endl;
	}
	
	return 0;
}