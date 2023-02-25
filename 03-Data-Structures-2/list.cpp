#include<iostream>
#include<string>

using namespace std;

struct list_item{
    string key;
    int val;
    list_item *next; 
    list_item *prev; 
    list_item(){};
    //list_item(string k, int v){key = k; val=v; next=0; prev=0;}; // 0 <=> NULL
    list_item(string k, int v): key(k), val(v), next(0), prev(0) {};
};

class List{
    list_item *left;
    list_item *right;
public:
    List(){left=0; right=0;};
    List(list_item * li);
    ~List();
    list_item * next(list_item * li);
    list_item * prev(list_item * li);
    list_item * lbegin(){return left;} // const list_item * lbegin(){return left;}
    list_item * rbegin(){return right;}
    void insert_after(list_item *li, list_item *x); // insert x after li
    void delete_at(list_item *li);
    void print_list(){
        cout << endl;
        for(list_item * li = left; li != 0; li = next(li)){
            cout <<  "(" << li->key << ", " << li->val <<  ") ";
        }cout << endl;
    }
    
};

List::List(list_item * li){left = li; right=li;}

List::~List(){
    for(list_item * l = lbegin(); l != 0; ){
        list_item * _next = next(l);
        delete l; // *l -- error
        l = _next;
    }
}

list_item * List::next(list_item * li){
    return li->next; // li->next <=> (*li).next
}
list_item * List::prev(list_item * li){
    return li->prev;
}

void List::insert_after(list_item *li, list_item *x){
    if(li == 0 && left == 0){ // (li = 0) -> returned type (list_item *)
        left = x;
        right = x;
        return;
    }
    // [li]->[li->next]  => [li]->[x]->[old li->next]
    list_item * old_next = li->next;
    li->next = x;
    x->next = old_next;
    x->prev = li;
    if(li == right) right = x;
    else old_next->prev = x;
    //if(old_next != 0) old_next->prev = x;
}

void List::delete_at(list_item *li){
    // [li->prev]->[li]->[li->next]
    list_item * old_prev, * old_next;
    old_prev = li->prev;
    old_next = li->next;
    if(li == left){
        left = old_next;        
    }else{
        old_prev->next = old_next;    
    }
    if(li == right){
        right = old_prev;
    }else{
        old_next->prev = old_prev; // li->next->prev = li->prev
    }
    delete li;    
}

/*

    if(li == left){
        left = old_next;
        //if(old_next != 0) old_next->prev = 0;
    }else{
        old_prev->next = old_next;
        //if(old_next != 0) old_next->prev = old_prev;
    }
    if(li == right){
        right = old_prev;
        //if(old_prev != 0) old_prev->next = 0;
        //if(old_prev != 0) old_prev->next = 0;
    }else{
        old_next->prev = old_prev; // li->next->prev = li->prev
        //if(old_prev != 0) old_prev->next = old_next;
    }

*/


int main (int argc, char const *argv[])
{
    list_item * l0, * l1, * l2, * l3;

    l0 = new list_item("k0", 0);
    l1 = new list_item("k1", 1);
    l2 = new list_item("k2", 2);    
    l3 = new list_item("k3", 3);    
     
    List initially_empty_list, my_list(l1);
    
    initially_empty_list.insert_after(initially_empty_list.lbegin(), l0);
    
    cout << initially_empty_list.lbegin()->key << " " << initially_empty_list.rbegin()->key;
    
    my_list.insert_after(l1, l2);
    my_list.insert_after(l2, l3);
    my_list.print_list();
    
    my_list.delete_at(l2);
    my_list.print_list();
    
    cout << "l3->prev: " << l3->prev->key << endl; 
    cout << "l3->next: " << l3->next << endl; 

    cout << "l3 == right ? " << (l3 == my_list.rbegin()) << " " << my_list.rbegin()->key << endl; 

    //return 0;

    my_list.delete_at(l3);
    my_list.print_list();
    
    my_list.delete_at(l1);
    my_list.print_list();
    cout << "There should have been an empty list";
    
    l1 = new list_item("k1", 1);
    l2 = new list_item("k2", 2);    
    l3 = new list_item("k3", 3);
    my_list.insert_after(0, l1);
    my_list.insert_after(l1, l2);
    my_list.insert_after(l2, l3);
    my_list.print_list();
    
    my_list.delete_at(l1);
    my_list.print_list();
    
    list_item * l25 = new list_item("k2.5", 25);    
    my_list.insert_after(l2, l25); 
    my_list.print_list();
     
    return 0;
}