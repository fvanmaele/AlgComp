#ifndef TREE_HH
#define TREE_HH
#include <vector>
#include <list>
#include <memory>
#include <string>
#include <iostream>
#include <unordered_map>
#include "noeud.hh"

template <typename T>
class ArbreBinaire {
    public:
        ArbreBinaire(T etiq) {
            _racine = std::make_shared<Noeud<T> >(Noeud<T>(etiq));
            _noeuds.push_back(_racine);
        }
        Noeud<T> racine() const {
            return _racine.get();
        }       

        std::vector<Noeud<T> > interieur() const {
            std::vector<std::weak_ptr<Noeud<T> > > inter{};
            inter.reserve(_noeuds.size());

            for (std::shared_ptr<Noeud<T> > N : _noeuds) {
                if (noeud_interieur<T>(*N)) {
                    inter.push_back(*N);
                }
            }
            return inter;
        }

        std::vector<Noeud<T> > exterieur() const {
            std::vector<std::weak_ptr<Noeud<T> > > exter{};
            exter.reserve(_noeuds.size());

            for (std::shared_ptr<Noeud<T> > N : _noeuds) {
                if (noeud_exterieur<T>(*N)) {
                    exter.push_back(*N);
                }
            }
            return exter;
        }

        std::size_t find(T label) const {
            // return position of label (handle ambiguities)
        }
        
        std::list<Noeud<T> > cdr(std::size_t pos, std::size_t limit = 500) const {
            // chemin de recherche
            Noeud<T>* x = _noeuds.at(pos).get();
            std::list<Noeud<T> > cdr = { *x };
            std::size_t i = 0;

            while (x->parent != nullptr) {
                x = x->parent;
                if (i > limit) {
                    std::string s = "limite pour cdr de position ";
                    s += std::to_string(pos);
                    s += " excedee";

                    std::cerr << s << std::endl;
                    break;
                }
                cdr.push_front(*x);
                i++;
            }
            return cdr;
        }
        
        ArbreBinaire sous_arbre(std::size_t pos) const {
            // deep copy
        }

        std::size_t ordre() const {
            return _noeuds.size();
        }

        std::size_t taille() const {
            return interieur().size(); // todo: cache results or compute on annexe()
        }

        size_t hauteur() const { // todo: cache results or compute on annex()
            std::size_t max_prof = 0;

            for (const std::shared_ptr<Noeud<T> > N : _noeuds) {
                if (N->prof > max_prof) {
                    max_prof = N->prof;
                }
            }
            return max_prof;
        }

        // TODO: check if labels are unique
        void annexe(size_t pos, T etiq_g, T etiq_r) {
            // parent
            Noeud<T>* P = _noeuds.at(pos).get();
            if (!noeud_exterieur<T>(*P)) {
                std::string s = "parent de position ";
                s += std::to_string(pos);
                s += " n'est pas un node exterieur";
                throw std::invalid_argument(s);
            }

            // nouveau fils gauche
            auto A = std::make_shared<Noeud<T> >(etiq_g);
            A->prof = P->prof + 1;
            A->parent = P;
            P->fils_gauche = A.get();

            // nouveau fils droit
            auto B = std::make_shared<Noeud<T> >(etiq_r);
            B->prof = P->prof + 1;
            B->parent = P;
            P->fils_droit = B.get();
            
            // actualiser ensemble des noeuds
            _noeuds.push_back(A);
            _noeuds.push_back(B);
        }

        void validate() const {
            // check for cycles
        }

    private:
        // use shared_ptr for RAII. Noeud uses pointers directly to avoid
        // possible issues with cycles (alternative: weak_ptr)
        std::vector<std::shared_ptr<Noeud<T> > > _noeuds{};
        std::shared_ptr<Noeud<T> > _racine;
};

#endif