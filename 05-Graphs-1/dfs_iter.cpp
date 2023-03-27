#include<iostream>
#include<vector>
#include<queue>
#include<deque>
#include<list>
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


struct DFS{
    Graph *G;
    int n; // num of vertices
    int t; // time
    vector<int> d, f; 

    long long TC;
    int min_cur;
    
    DFS(Graph * GG){
        G = GG;
        n = G->V.size();
        t = 0;
        f = d = vector<int>(n, 0);
        
        TC = 0;
        min_cur = MAX_COST;
    }
    
    void operator()(){
        iter_search();
    }
    
    void search(){
      for(size_t v = 0; v < n; ++v){
          if(d[v] == 0){ 
              search(v);
              TC += min_cur;
              min_cur = MAX_COST;
          }                    
      }
      G->TC = TC;  
    }
    
    void search(int v){ // Stack: [... -> rec_call  ]
        d[v] = ++t;
        min_cur = min(min_cur, G->V[v].cost);
        for(auto u : G->neighbors(v)){
            if(d[u] == 0) search(u);
        }
        f[v] = ++t;
    }
    
    void iter_search(){
        vector <pair<int, int> > st;
        for(size_t u = 0; u < n; ++u){
            if(d[u] == 0){ 
                st.emplace_back(u, 0); // st.push_back({v, 0})
                while(!st.empty()){
                    auto [v, i] = st.back();
                    st.pop_back();
                    if(d[v] == 0){                    
                        d[v] = ++t;
                        min_cur = min(min_cur, G->V[v].cost);
                    }
                    
                    //vector<int> neigh = G->neighbors(v); // Quadratic!!!
                    //const vector<int> & neigh = G->neighbors(v);
                    auto & neigh = G->neighbors(v);
                    bool finished = true;
                    for(; i < neigh.size() && finished; ++i){
                        if(d[neigh[i]] == 0){ // u from rec DFS == neigh[i]
                           st.emplace_back(neigh[i], 0); 
                           st.emplace_back(v, ++i);
                           finished = false;
                        }
                    }
                    if(finished)
                       f[v] = ++t; 
                }
                TC += min_cur;
                min_cur = MAX_COST;
            }                    
        }
        G->TC = TC;          
    }
};


int main (int argc, char const *argv[]){
	//freopen("t2", "r", stdin); // open file with test data to reed and acces it through stdin
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
	//G.BFS();
	
    DFS dfs(&G);
    dfs();
    
	cout << G.TC;
	
	return 0;
}