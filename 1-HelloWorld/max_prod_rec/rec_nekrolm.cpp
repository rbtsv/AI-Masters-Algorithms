// https://godbolt.org/z/Y9T6zrK84
// https://twitter.com/Nekrolm/status/1610062514032615427?s=20&t=gqdepj3YKKkDE3pO7YaHow
#include <iostream>
#include <algorithm>
#include <vector>

struct Maximums {
    int first;
    int second;
};


struct Reader {
    virtual int read_int() = 0;
};

struct StdIOReader : Reader {
    int read_int() override {
        int n = 0;
        std::cin >> n;
        return n;
    }
};

Maximums max_two(size_t n, Maximums m12, Reader& reader){
	if(n == 0) return m12;		
    int c = reader.read_int();
	Maximums p = (c > m12.first) ? Maximums{c, m12.first}
						: Maximums{m12.first, std::max(c, m12.second)};
	return max_two(n-1, p, reader);
}

int main (int argc, char const *argv[])
{
	std::ios::sync_with_stdio(false); std::cin.tie(0);
	int n, a, b;
	
	std::cin >> n >> a >> b;
	Maximums m12 = Maximums{std::max(a, b), std::min(a, b)};
    
    StdIOReader reader;
	m12 = max_two(n-2, m12, reader);
		
	std::cout << ((long long) m12.first) * ((long long) m12.second) << "\n";
	
	return 0;
}