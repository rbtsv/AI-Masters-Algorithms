#include<iostream>
#include<set>
#include<map>
#include<algorithm>
#include<string>
//#include<utility>
#include <utility>

using namespace std;

class MaxPrQueue{ // You can do both max and min
    set<pair<int, string> > queue; // pair (priority, key)
    map<string, set<pair<int, string> >::iterator > find;
public:
    MaxPrQueue(){};
    void insert(pair<int, string> vk);
    void insert(string k, int v){ insert(make_pair(v, k)); };
    pair<int, string> extract_max();
    void set_priority(pair<int, string> vk);
    void set_priority(string k, int v){ set_priority(make_pair(v, k));};
    class ExceptionAddTheSameKey{};
};

void MaxPrQueue::insert(pair<int, string> vk){
    if(find.find(vk.second) == find.end()){
      find[vk.second] = queue.insert(vk).first;
    }else{
        throw ExceptionAddTheSameKey();
    }
}

pair<int, string> MaxPrQueue::extract_max(){
    set<pair<int, string> >::iterator it = --queue.end();
    find.erase(it->second);
    pair<int, string> vk = *it;
    queue.erase(it);
    return vk;
}


void MaxPrQueue::set_priority(pair<int, string> vk){
    queue.erase(find[vk.second]);
    find.erase(vk.second);
    insert(vk);
}

int main (int argc, char const *argv[])
{
	MaxPrQueue q;
	q.insert("Z", 17);
	q.insert("C", 10);
	q.insert("A", 13);
	q.insert("B", 13);
	auto [v, k] = q.extract_max();
	cout << k << " " << v << endl;
	auto [v1, k1] = q.extract_max();
	cout << k1 << " " << v1 << endl;
	q.set_priority("A", 1);
	auto [v2, k2] = q.extract_max();
	cout << k2 << " " << v2 << endl;	
	auto [v3, k3] = q.extract_max();
	cout << k3 << " " << v3 << endl;	
	return 0;
}    
