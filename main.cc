#include "include/noeud.hh"
#include "include/arbre.hh"
#include "include/ordre.hh"
#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>

template <typename T>
void info_arbre(ArbreBinaire<T> A, size_t pos) {
	std::cout << "Arbre d'ordre: " << std::to_string(A.ordre()) << std::endl
		<< "Hauteur: " << std::to_string(A.hauteur()) << std::endl;
	
	auto v = A.cdr(pos);
	std::cout << "Chemin de recherche (" << std::to_string(pos) << "):" << std::endl;
	for (const auto& c : v) {
		std::cout << c.etiq << " ";
	}
	std::cout << std::endl;
}

void test_arbre() {
	Noeud<std::string> r("A");
	std::cout << r.etiq << std::endl;

	std::cout << "Arbre d'ordre 1" << std::endl;
	ArbreBinaire<std::string> A("A");
	info_arbre(A, 0);
	std::cout << std::endl;

	A.annexe(0, "b", "c"); // 0, 1, 2
	info_arbre(A, 1);
	std::cout << std::endl;

	A.annexe(1, "c", "d");
	info_arbre(A, 3);
	std::cout << std::endl;

	A.annexe(2, "e", "f");
	info_arbre(A, 5);
	std::cout << std::endl;
}

bool o_divisible(int x, int y) {
	return x % y == 0;
}

bool o_less_equal(int x, int y) {
	return x <= y;
}

int main() {
	test_arbre();
	std::vector<int> v(9);
	
	std::iota(v.begin(), v.end(), 1);
	for (auto c : v) {
		std::cout << c;
	}
	std::cout << std::endl;
	std::cout << std::boolalpha << ordre_total(v, o_less_equal).empty() << std::endl;
	
	std::sort(v.begin(), v.end(), o_divisible);
	for (auto c : v) {
		std::cout << c;
	}
	std::cout << std::endl;
	std::cout << std::boolalpha << ordre_total(v, o_divisible).empty() << std::endl;
}