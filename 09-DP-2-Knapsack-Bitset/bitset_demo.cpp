#include<iostream>
#include<bitset>
using namespace std;

#define BS_MAX_SIZE 10

int	main(){
	//vector<bool> vbool;
    
    /*int c;
    cin >> c; 
    bitset<c> bss; */ //Error
    
	bitset<BS_MAX_SIZE> bs; 
				
	/*cout << bitset<BS_MAX_SIZE>(9) << endl;	
    
	return 0;*/
	
	int bs_size = 5;
	unsigned long long BS = 1 << bs_size; //BS = 2^bs_size = 1 -> 100000
	cout << "BS = " << BS << endl;
	cout << "bs = " << bs << endl;
	
    //return 0;
    
	for(unsigned long long i = 0; i < BS - 1; ++i){
        // bs initally = 0; bs -> next(bs)
        int j = 0; // # of bit to be changed
        for(; (j < bs_size) && (bs[j] == 1) ; ++j){
            bs[j] = 0;
        }
        if(j < bs_size) bs[j] = 1;

		cout << "i+1 = " << i+1 << ": " << bs << endl;
	}
	
	return 0;
}