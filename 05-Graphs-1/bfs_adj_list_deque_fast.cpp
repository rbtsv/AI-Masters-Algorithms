#include<iostream>
#include<vector>
#include<queue>
#include<deque>
#include<algorithm>

using namespace std;

#define MAX_COST 1000000001

struct vertex{
	int cost;	
	//vertex(int c){cost = c;}
	vertex(int c) : cost{c} {};
	//vertex(int c, int aa) : cost{c}, a{aa} {};
	vertex(){}
};

class Graph{
	int n; // Number of vertices ≤ 10^5
    vector<vector<int> > adj_list;    
public:
	long long TC; // Total cost
	vector<vertex> V;
	void add_edge(pair<int, int> p){adj_list[p.second-1].push_back(p.first-1); 
                                    adj_list[p.first-1].push_back(p.second-1);}
	/*vector<vector<bool> > E; //T — есть ребро, F — нет ребра
	void add_edge(pair<int, int> p){ E[p.first-1][p.second-1] = true; 
                                     E[p.second-1][p.first-1] = true; }*/
	Graph(int nn);
	void BFS();
	const vector<int> & neighbors(int v);	
	void printV();
	void printE();	
};

const vector<int> & Graph::neighbors(int v){
    return adj_list[v];
}

/*vector<int> Graph::neighbors(int v){
    vector<int> neigh;
    for(size_t u = 0; u < n; ++u){
        if(E[v][u]) neigh.push_back(u);  
    }
    return neigh;
}*/

Graph::Graph(int nn){
	n = nn;
	TC = 0;
	V = vector<vertex>(n, vertex());
    adj_list = vector<vector<int> >(n, vector<int>());
	//E = vector<vector<bool> >(n, vector<bool>(n, false) );
}

void Graph::BFS(){
	//queue<int> q;
    //vector<int> q;
    deque<int> q;
    vector<bool> touched(n, false);
    for(size_t i = 0; i < n; ++i){
        if(!touched[i]){
            int min_cost = V[i].cost;
            q.push_back(i);
            touched[i] = true;
            while(q.size() > 0){ // BFS itself
                min_cost = min(min_cost, V[q.front()].cost);
                for(auto u : neighbors(q.front())){
                    if(!touched[u]){ q.push_back(u); touched[u] = true;}
                }
                //q.pop();
                //q.erase(q.begin());
                q.pop_front();
            } // BFS
         TC += min_cost;   
        }// New Connected Component
    }
}


void Graph::printV(){
	for(size_t i = 0; i < n; ++i){
		cout << V[i].cost << " ";
	}
	cout << endl << endl;
}

/*void Graph::printE(){
	for(size_t i = 0; i < n; ++i){
		for(size_t j = 0; j < n; ++j){
			cout << (E[i][j] ? 1 : 0);
			cout << " ";
		}
		cout << "\n";
	}
}*/


int main (int argc, char const *argv[])
{
	//freopen("t1", "r", stdin); // open file with test data to reed and acces it through stdin
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    
	int n, m; // n — V, E — 
	
	cin >> n; cin >> m;
	
	Graph G(n);
	
	for(size_t i = 0; i < n; ++i){
		int cost;
		cin >> cost;
		vertex v(cost);
		G.V[i] = v;
	}
	
	//G.printV();
	
	for(size_t i = 0; i < m; ++i){
		pair<int, int> p;
		cin >> p.first; cin >> p.second;
		G.add_edge(p);
	}
	//G.printE();
	G.BFS();
	
	cout << G.TC;
	
	return 0;
}