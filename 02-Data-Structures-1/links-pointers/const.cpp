#include<iostream>
// https://habr.com/ru/post/59558/

using std::cout, std::endl;

int main (int argc, char const *argv[]){
    const int ia = 1;
    //ia = 2; //error
    cout << ia << endl;
        
    
      
    const char * ca = "abc";
    cout << ca << endl;     
    //ca[0] = 'c'; //Error
    ca = "bcd";
    // ca[0] = 'c'; //Error
    cout << ca << endl;    
        
    
    int ib = 1, ic = 2;
    const int *cia = &ib;
    //*cia = 7; //error
    cia = & ic; 
    cout << *cia << endl;  
     
        
    int b = 3;
    int * const a = &b;
    cout << *a << endl;
    *a = 4;
    //a = &ic;
    cout << b << endl;
    
    
    return 0;
}