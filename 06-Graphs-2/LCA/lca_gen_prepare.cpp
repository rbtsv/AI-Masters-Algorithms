#include <iostream>
#include <vector>
#include <cassert>
#include <string>

#define MAXH 20



	#define SUBMIT true
//	#define SUBMIT false
//	#define DEBUG  true
	#define DEBUG  false

using namespace std;

void print_vec(vector<int> v);
void print_vertrex_vec(vector<int> v);

struct vertex{
	int id;
	int depth;
	vector<int> powancesters;
	int name(){return id+1;}
	
	vertex(int i){id = i; powancesters = vector<int>(MAXH, -1);}
	vertex(){}
};


class Graph{	
public: 
	int n; // Number of vertices ≤ 10^5
	long long TC; // total cost;
	vector<vertex> V;
	vector<vector<int> > adj_list;
	virtual void add_edge(pair<int, int> p){ 
		adj_list[p.first-1].push_back(p.second-1); adj_list[p.second-1].push_back(p.first-1); 
	}
	Graph(int nn);
	Graph(){*this = Graph(1); }
	void printV();
	//void printE();
	vector<int> neighbours(int v){ return adj_list[v]; };
};

Graph::Graph(int nn){
	n = nn;
	TC = 0;
	vector<vertex> VV(n, vertex());
	V=VV;
	vector<vector<int> > al(n);
	adj_list = al;
}


class Tree : public Graph{
	vector<int> Powers={1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288};
//	int MaxH = 20;	
	
	
public:	
	vector<int> parent;	
	
	Tree(){		
		V[0].id=0;		
		V[0].powancesters = vector<int>(MAXH, -1);
		V[0].powancesters[0] = 0;		
		V[0].depth = 1;		
		parent.resize(1);
	}	
	
	void enlarge_graph(int nn){
		for(size_t i = n; i < nn; ++i){
			V.push_back(vertex(i));
		}
		n = nn;
		parent.resize(n);		
	}
	
	
	int lca(int iu, int iv){		        
		int answ = 0;
		for(int i = MAXH-1; i >= 0 && iv != iu; --i){
            if(V[iv].powancesters[i] != V[iu].powancesters[i] ){
		        if(V[iv].powancesters[i] != -1){
		            iv = parent[V[iv].powancesters[i]];
		        }
		        if(V[iu].powancesters[i] != -1){
		            iu = parent[V[iu].powancesters[i]];
		        }
            }else{
                if(V[iv].powancesters[i] != -1) answ = V[iv].powancesters[i];
            }
		}
        if(iu == iv) return iv;
        return answ;
	}
	
	
	
	void compute_powancesters(int iv){
		int iu = parent[iv]; 
		vertex & u = V[iu], & v = V[iv]; //links are important!
		if(DEBUG){
			cout << "compute_powancesters for " << iv << " depth:" << v.depth << endl;
		}
		long long d = 0; // current depth of an ancestor
        for(int i = MAXH - 1; i >= 0; --i){
            if(v.depth >= d + Powers[i]){
                d += Powers[i];
                if(u.depth >= d){
                    v.powancesters[i] = u.powancesters[i];
                }else{
                    //if(v.depth == d) v.powancesters[i] = v;
                    v.powancesters[i] = iv;
                    break;
                }
            }
                
        }
	}
	
	
	void add_edge(pair<int, int> p){ 
			if(p.second > n){ enlarge_graph(p.second); }
			int iu, iv;
			iu = p.first-1; iv = p.second-1;
			assert(iu < iv);
			parent[iv] = iu;
            vertex & v = V[iv], & u = V[iu];
            v.depth = u.depth + 1;                        
			compute_powancesters(iv);			
		}
};




int main (int argc, char const *argv[]){
	
	std::ios::sync_with_stdio(false); std::cin.tie(0);
	if(SUBMIT){		
	}else{ 	freopen("./testsA/01", "r", stdin); }
	
	
	int k;
	cin >> k;
	
	Tree T;
	
	for(size_t i = 0; i < k; ++i){
		string q; int iu, iv;
		cin >> q >> iu >> iv;		
		if( q == "ADD" ) {  T.add_edge(make_pair(iu, iv)); 
			if(DEBUG){ --iu; --iv; 
				cout << "ADD("<< iu << "," << iv << ")\n";
				cout << "powancesters iu == " << iu << ":";
				print_vec(T.V[iu].powancesters);
				cout << "powancesters iv == " << iv << ":";
				print_vec(T.V[iv].powancesters);
			}
		}
		if( q == "GET" ){			
			if(DEBUG)
				cout << "LCA("<< iu-1 << "," << iv-1 << ")\n";
			cout << (T.lca(iu-1,iv-1)+1) << "\n"; 
		}
	}
	
	return 0;
}




void print_vec(vector<int> v){
	cout <<"print_vec: ";
	for(vector<int>::iterator it=v.begin(); it != v.end(); ++it){
		cout << *it << " ";
	}
	cout << "\n";
}
