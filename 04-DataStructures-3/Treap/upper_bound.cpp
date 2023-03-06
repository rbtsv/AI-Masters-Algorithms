#include <iostream>
#include <set>
#include <algorithm>

using namespace std;


int main (int argc, char const *argv[]){
	std::ios::sync_with_stdio(false); std::cin.tie(0);
	//freopen("t_ub", "r", stdin);
	int n = 0;
	cin >> n;
    
    bool was_y = false;
    int y = 0;      
   
    set<int> s;
    
	for(size_t i = 0; i < n; ++i){
        char q;
		int x;
        cin >> q >> x;
        //cout << q << (q == '?') << " " << x << endl;
        if(q == '?'){
            //auto ub = lower_bound(s.begin(), s.end(), x); // WRONG USAGE!
            auto ub = s.lower_bound(x);
            if( ub == s.end()){ 
                cout << -1 << "\n";
                was_y = false;
            }
            else{ 
                cout << (y = *ub) << "\n";
                was_y = true;
            }
        }else{
            if(was_y) x = (x + y) % 1000000000;
            s.insert(x);    
            was_y = false;
        }
            
	}
	
	
	return 0;
}
