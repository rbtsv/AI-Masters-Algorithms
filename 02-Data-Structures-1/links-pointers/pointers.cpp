#include<iostream>

using namespace std;

void print_anything(void * any){
	//int* thing = (int*) any; 
	cout << "any:" << *((int*) any) << endl;
}

template <typename C> void p_anything(C *any){
	//int* thing = (int*) any; 
	cout << "any:" << *any << endl;
}

// -> 

void int_p_anything(int *any){
	//int* thing = (int*) any; 
	cout << "any:" << *any << endl;
}

int main (int argc, char const *argv[]){
	int x, y, *px, * py;	
	int &lx = x;
    const int &ly = y;
    
	x = 7;
	y = -1;
    
    cout << y << " " << ly << endl;
    //ly += 1; //error
    y += 1;
    cout << y << " " << ly << endl;
    
    return 0;
    
    px = &x;
    py = &y;
    
    // x = y; content of y is copying to x
    
    cout << x << " " << *px << " " << lx << endl;
    
    *px += 1;
    px = py;
    lx += 1;
    
    cout << x << " " << *px << endl;
    
    int ** ppx;
    ppx = &px;
    //*ppx += 1; //undefined behaviour
        
    cout << **ppx << endl;
    
    print_anything(px);
    p_anything<int>(&y);
        
	//system("open link-pointer.jpeg");
	//system("open pointer-pointer.jpeg");
	//system("open int_star.jpeg");
	//system("open void_star.jpeg"); 			
    
	return 0;
}