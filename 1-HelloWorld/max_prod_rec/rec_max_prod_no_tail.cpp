#include <iostream>
#include <algorithm>

//using namespace std;

int read_int(){
    int c = 0;
    std::cin >> c;
    return c;
}

std::pair<int, int> max12(int n, std::pair<int, int> m12){
    if(n == 0) return m12;
    int c = read_int();  
     std::pair<int, int> p = c > m12.first ? std::make_pair(c, m12.first) 
                               : std::make_pair(m12.first, std::max(m12.second, c));
    return max12(n-1,p); 
             //pair <int, int> p;
             /*if(c > m12.first){
                 p = make_pair(c, m12.first)
             }else{ p = make_pair(m12.first, max(m12.second, c)) } */                
}

int main (){
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    //freopen("tm2", "r", stdin);    
    int n, a, b;
    std::cin >> n >> a >> b;
    std::pair<int, int> answ = max12(n-2, std::make_pair(std::max(a,b), std::min(a,b)));            
       
    //long long prod;
    //prod = max1*max2;
    std::cout << (long long) answ.first*answ.second << "\n"; // << endl;
    return 0;
}