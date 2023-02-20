#include<iostream>
#include<stdexcept>

using std::cout, std::endl;

template <class T> class Stack{
    size_t size;
    size_t head;
    T * stack_content; 
    //class Overflow{};   
    class Underflow{};
    
    public:
        void push(T x);
        T pop();
        bool is_empty();
        
        Stack(){// constructor
            size = 10;
            head = 0;
            stack_content = new T[size];
        }
        
        Stack(T s){// constructor
            size = s;
            head = 0;
            stack_content = new T[size];
        }
        
        ~Stack(){ delete[] stack_content; }
        
        
        //Stack(Stack other){ // No-No-No
        Stack(const Stack & other){ // Stack b = a; 
        			cout << "Copy Constructor\n";			
        			size = other.size;
        			stack_content = new T[size];
        			head = other.head;
        			for(size_t i = 0; i < size; ++i){
        				if( i < head)				
        					stack_content[i] = other.stack_content[i]; 
        				else
        					stack_content[i] = -1; 
        			}
        }
		
        void operator = (const Stack & other){ // *this	
        			// https://ru.wikipedia.org/wiki/Правило_трёх_(C%2B%2B)
        			cout << "operator =\n";
        			// Guard self assignment
        		    if (this == &other) // s = s;
        		        return;
			
        			delete[] stack_content;
			
        			size = other.size;
        			stack_content = new T[size];
        			head = other.head;
        			for(size_t i = 0; i < head; ++i){
        				this->stack_content[i] = other.stack_content[i];
        				// this->stack_content ==  (*this).stack_content
        			}
			
        }
        
        void tst_print(){
        			for(size_t i = 0; i < size; ++i){
        				cout << stack_content[i] << " ";
        			}
        			cout << endl;
        		}

};


template <class T> void Stack<T>::push(T x){ //++head;  // <=> head += 1;
    if(head < size){ stack_content[head++] = x;} // head++ <=> ++head, head-1
    //else{ throw Overflow(); }
    else{ throw std::length_error("Stack overflow!111"); }
}

template <class T> T Stack<T>::pop(){
    if(head > 0){ return stack_content[--head]; }
    else{ throw Underflow(); }
}

template <class T> bool Stack<T>::is_empty(){
    return (head == 0);
}



int main (int argc, char const *argv[]){
	Stack<char> s1, s2(20);
	for(size_t i = 0; i < 11; ++i){
		try{s1.push('A' + i);}
		catch(std::length_error){ cout << "Stack Overflow!111" << endl; }
		s2.push('A' + i);
	}
	
	s2.tst_print();
    
    //return 0;
	
	if(!s1.is_empty()){
		Stack<char> s3 = s2, s4;
		cout << "s3:";
		s3.tst_print();
		s1.pop();		
		s4 = s1;
		cout << "s4:";
		s4.tst_print();
	}
	cout << "s1:";
	s1.tst_print();
	cout << "s2:";
	s2.tst_print();


    return 0; 
}