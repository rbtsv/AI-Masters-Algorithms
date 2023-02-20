#include<iostream>

using namespace std;


int main (int argc, char const *argv[]){
	int *ar; // Python: [1, 2.0, (-1,1), "s"]
	//char * s; // C string
	//cin >> n;
	int n = 10;
	ar = new int[n];
	int br[n]; // br's type is (almost) int * (with restrictions)
	for(size_t i = 0; i < n; ++i){
		br[i] = -i;
		ar[i] = i;
	}
	for(int i = 0; i < n; ++i){
		// ar[i] == *(ar+i) == i[ar]
		cout << *(ar+i) << "," << br[i] << "," << i[ar] << endl;
	}
	return 0;
}
