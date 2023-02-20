#include <iostream>
#include <algorithm>

using namespace std;

int main (){
    //freopen("t4", "r", stdin);
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    
    int n, cur, prev, max_len=1, cur_len=1;
    
    cin >> n >> prev;
    cout << 1 << "\n";    
    
    for(size_t i = 1; i < n; ++i){
        cin >> cur;
        if(cur >= prev){
            cur_len += 1;
        }else{
            cur_len = 1;
        }
        max_len = max(max_len, cur_len);
        cout << max_len << "\n";
        prev = cur; 
    }
        
    return 0;
}