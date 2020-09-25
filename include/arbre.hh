#ifndef TREE_HH
#define TREE_HH
#include <vector>
#include <memory>
#include <string>
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

        std::vector<const Noeud<T>*> interieur() const {
            std::vector<Noeud<T>*> inter{};
            inter.reserve(_noeuds.size());

            for (std::shared_ptr<Noeud<T> > N : _noeuds) {
                if (noeud_interieur<T>(*N)) {
                    inter.push_back(N.get());
                }
            }
            return inter;
        }

        std::vector<const Noeud<T>*> exterieur() const {
            std::vector<Noeud*> exter{};
            exter.reserve(_noeuds.size());

            for (std::shared_ptr<Noeud<T> > N : _noeuds) {
                Noeud<T>* Ns = N.get();
                if (noeud_exterieur<T>(*Ns)) {
                    exter.push_back(Ns);
                }
            }
            return exter;
        }

        std::size_t ordre() const {
            return _noeuds.size();
        }
        
        std::size_t taille() const {
            return interieur().size(); // todo: cache results or compute on annexe()
        }

        size_t hauteur() const {
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
            auto P = _noeuds.at(pos);
            if (!noeud_exterieur<T>(*P)) {
                std::string s = "parent de position ";
                s += std::to_string(pos);
                s += " n'est pas un node exterieur";
                throw std::invalid_argument(s);
            }

            // nouveau fils gauche
            auto A = std::make_shared<Noeud<T> >(etiq_g);
            A->prof = P->prof + 1;
            P->fils_gauche = A.get();

            // nouveau fils droit
            auto B = std::make_shared<Noeud<T> >(etiq_r);
            B->prof = P->prof + 1;
            P->fils_droit = B.get();
            
            // actualiser ensemble des noeuds
            _noeuds.push_back(A);
            _noeuds.push_back(B);
        }

        void validate() const {
            // check for cycles
        }

    private:
        std::vector<std::shared_ptr<Noeud<T> > > _noeuds{};
        std::shared_ptr<Noeud<T> > _racine;
};

#endif