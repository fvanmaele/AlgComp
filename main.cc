#include "include/noeud.hh"
#include "include/arbre.hh"
#include <iostream>
#include <string>

int main() {
	Noeud<std::string> r("A");
	std::cout << r.etiq << std::endl;

	ArbreBinaire A("A");
	std::cout << A.hauteur() << std::endl;
	std::cout << A.ordre() << std::endl;
	
	A.annexe(0, "b", "c"); // 0, 1, 2
	std::cout << A.hauteur() << std::endl;
	std::cout << A.ordre() << std::endl;

	A.annexe(1, "c", "d");
	std::cout << A.hauteur() << std::endl;
	std::cout << A.ordre() << std::endl;

	A.annexe(2, "e", "f");
	std::cout << A.hauteur() << std::endl;
	std::cout << A.ordre() << std::endl;
}