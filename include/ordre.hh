#ifndef ORDER_HH
#define ORDER_HH
#include <vector>

template <typename T>
using ordre = bool(*)(T x, T y);

template <typename T>
using poset = std::pair<std::vector<T>, ordre<T> >;

template <typename T>
using vector_pair = std::vector<std::pair<T, T> >;

template <typename T> 
vector_pair<T> ordre_total(const std::vector<T>& X, ordre<T> o) {
	std::vector<std::pair<T, T> > incomparable{};

	// todo: methode de complexite reduite (2 * N^2 comparaisons)
	for (size_t i = 0; i < X.size(); i++) {
		for (size_t j = 0; j < X.size(); j++) {
			T x = X.at(i);
			T y = X.at(j);

			if (!o(x, y) && !o(y, x)) {
				incomparable.push_back(std::make_pair(x, y));
			}
		}
	}
	return incomparable;
}

template <typename T>
poset<T> ext_lineaire_recursif(const std::vector<T> &X, ordre<T> o) {
	vector_pair<T> o_total = ordre_total<T>(X, o);
	if (o_total.empty()) {
		return std::make_pair(X, o);
	} else {
		// choisir un paire ordonnee uv d'elements o-incomparables
		std::pair<T, T> uv = o_total.at(0);
		// o := la cloture transitive de o augmentee de la paire uv

		// ext_lineaire_recursif(X, o);
	}
}

template <typename T>
poset<T> ext_lineaire_iteratif(const std::vector<T> &X, ordre<T> o) {
	while (true) {
		vector_pair<T> o_total = ordre_total<T>(X, o);
		if (o_total.empty()) {
			break;
		}
		// choisir un paire ordonnee uv d'elements o-incomparables
		std::pair<T, T> uv = o_total.at(0);
		// o := la cloture transitive de o augmentee de la paire uv
	}
	return std::make_pair(X, o);
}

template <typename T>
void ext_lineaire_enumeration(const std::vector<T>& X, ordre<T> o) {
	vector_pair<T> o_total = ordre_total<T>(X, o);
	if (o_total.empty()) {

	}
}

#endif