#include<iostream>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<map>

using namespace std;

struct CmpSecond{
	bool operator( )(const pair<string, int> & x, const pair<string, int> &y  ) const {
		if( x.second < y.second ) return true;
		if( x.second > y.second ) return false;
		return x.first < y.first;
	}
};


struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
 
        if (hash1 != hash2) {
            return hash1 ^ hash2;             
        }
         
        // If hash1 == hash2, their XOR is zero.
          return hash1;
    }
};




int main (int argc, char const *argv[])
{
    std::unordered_map<string, int> h; // h: string -> int   

    std::map<pair<string, int>, int> m; // m : (string, int) -> int
    //std::map<pair<string, int>, int, CmpSecond> m; // m : (string, int) -> int
    std::unordered_map<pair<string, int>, int, hash_pair> hh;
    
    pair<string, int> pp1, pp2;
    pp1 = make_pair("Z", 17);
    pp2 = make_pair("Z", 17);
    hh[pp1] = 1; m[pp1] = 1;
    cout << hh[pp1] << " " << m[pp1] << endl;
    hh[pp2] = 2; m[pp2] = 2; 
    cout << hh[pp1] << " " << m[pp1] << endl;
    cout << hh[pp2] << " " << m[pp2] << endl;
    
    return 0;
}