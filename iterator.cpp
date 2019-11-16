#include <iostream>
#include <vector>
#include <list>
#include <map>

template <class Container>
void printContainer(Container& c){
	for (typename Container::iterator it = c.begin(); it != c.end(); ++it){
		std::cout << *it << ", ";
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[]){
	std::vector<int> a;
	std::vector<int>::iterator it3;
	for (int i = 1; i <= 5; ++i){
		a.push_back(i);
	}
	std::cout << "before erase vector" << std::endl;
	for (std::vector<int>::iterator it = a.begin(); it != a.end(); ++it){
		std::cout << *it << ", ";
		if (*it == 3){
			it3 = it;
		}
	}
	a.erase(it3);
	std::cout << std::endl;
	std::cout << "after erase vector" << std::endl;
	printContainer(a);

	std::list<int> b;
	std::list<int>::iterator it9;
	for (int i = 6; i <= 10; ++i){
		b.push_back(i);
	}
	std::cout << "before erase list" << std::endl;
	for (std::list<int>::iterator it = b.begin(); it != b.end(); ++it){
		std::cout << *it << ", ";
		if (*it == 9){
			it9 = it;
		}
	}
	b.erase(it9);
	std::cout << std::endl;
	std::cout << "after erase list" << std::endl;
	printContainer(b);

	std::map<int, int> c;
	std::map<int, int>::iterator it13;
	for (int i = 11; i <= 15; ++i){
		c.insert(std::make_pair<int, int>(i, i));
	}
	std::cout << "before earse map" << std::endl;
	for (std::map<int, int>::iterator it = c.begin(); it != c.end(); ++it){
		std::cout << "(" << it->first << "," << it->second << "), ";
		if (it->first == 13){
			it13 = it;
		}
	}
	c.erase(it13);
	std::cout << std::endl << "after erase map" << std::endl;
	for (std::map<int, int>::iterator it = c.begin(); it != c.end(); ++it){
		std::cout << "(" << it->first << "," << it->second << "), ";
	}
	std::cout << std::endl;
	
	return 0;
}
