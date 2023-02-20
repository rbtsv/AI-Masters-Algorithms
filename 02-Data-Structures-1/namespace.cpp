#include<iostream>
#include<vector>


using std::cout, std::endl;

namespace One{
    int first;
    int second;
    struct int_pair{
        int first;
        int second;
    };    
}


namespace Two{
    int first;
    int second;
    struct int_pair{
        bool flag;
        int first;
        int second;
    };    
}


using namespace Two;

int main (int argc, char const *argv[]){		        
    
    One::first = 1;
    Two::first = 3;
    
    int_pair p, p2, p3;

    p.first = 1; p.second = 2; p.flag = false;
    
    cout << p.first << " " << p.second << " " << p.flag << endl;
    
    return 0;
    
	int x=7, vector=5;
	for(size_t i = 0; i < 5; ++i){
		int x=i;
		cout << x;
		//...
	}    
	std::vector<int> v = {1, 2, 3};
	cout << endl << x << " " << vector << " " << v[0] << endl;	
}