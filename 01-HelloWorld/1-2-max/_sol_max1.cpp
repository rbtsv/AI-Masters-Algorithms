#include <iostream>
#include <algorithm>

int main (){
    //freopen("t1", "r", stdin);
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    int n, max1;
    std::cin >> n >> max1;
    for(int i = 1; i < n; ++i){ // ++i == i += 1 == (i = i + 1)
        int c;
        std::cin >> c;        
        //if( c > max1) max1 = c; 
        max1 = std::max(c, max1);
    }    
    std::cout << max1 << "\n"; // << std::endl;
    return 0;
}