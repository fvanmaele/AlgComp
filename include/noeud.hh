#ifndef NODE_HH
#define NODE_HH
#include <stdexcept>

template <typename T>
struct Noeud {
    Noeud(T _etiq) 
        : etiq(_etiq) 
    {}
    Noeud* fils_gauche = nullptr;
    Noeud* fils_droit = nullptr;
    Noeud* parent = nullptr;

    std::size_t prof = 0;
    T etiq{};
};

template <typename T>
bool noeud_exterieur(const Noeud<T>& N) {
    return N.fils_gauche == nullptr && N.fils_droit == nullptr;
}

template <typename T>
bool noeud_interieur(const Noeud<T>& N) {
    return N.fils_gauche != nullptr && N.fils_droit != nullptr;
}

#endif