#include <iostream>
#include <algorithm>

int main (){
    //freopen("tm2-f", "r", stdin);
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    int n, a, b;
    std::cin >> n >> a >> b;
    
    //1 1 1 3 2 
    int max1, max2;
    max1 = std::max(a,b);
    max2 = std::min(a,b);    
    for(int i = 2; i < n; ++i){ // ++i == i += 1 == (i = i + 1)
        //long long c;
        int c;
        std::cin >> c;
        if(c > max1){
            max2 = max1;
            max1 = c;            
        }else{
            max2 = std::max(c, max2);
        }        
    }    
    //long long prod;
    //prod = max1*max2;
    std::cout << (long long) max1*max2 << "\n"; // << std::endl;
    return 0;
}