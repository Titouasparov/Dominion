#include "../include/Deck.h"
#include "CarteRoyaume.h"
#include <algorithm>
#include <CarteTresor.h>
#include <CarteVictoire.h>
#include <random>
#include <iomanip>
#include <algorithm>
#include <Jeu.h>

Deck::Deck(std::vector<Carte*> cartes_):cartes(std::move(cartes_)){
    nbCartes = cartes.size();
}

Deck::Deck() {
    nbCartes = 0;
}

Deck::~Deck() {
    nbCartes = 0;
    for (Carte* carte : cartes) {
        delete carte;
    }
    cartes.clear();
}

Deck &Deck::operator=(const Deck & other) {
    for (Carte* carte : cartes) {
        delete carte;
    }
    cartes.clear();
    nbCartes = other.nbCartes;
    for (Carte* carte : other.cartes) {
        if (auto* cr = dynamic_cast<CarteRoyaume*>(carte)) {
            auto* cr_ =  new CarteRoyaume(*cr);
            cartes.push_back(cr_);
        }
        if (auto* ctt = dynamic_cast<CarteTresor*>(carte)) {
            auto* ctt_ =  new CarteTresor(*ctt);
            cartes.push_back(ctt_);
        }
        if (auto* cvt = dynamic_cast<CarteVictoire*>(carte)) {
            auto* cvt_ =  new CarteVictoire(*cvt);
            cartes.push_back(cvt_);
        }
    }
    return *this;
}

Deck::Deck(const Deck & other) : nbCartes(other.nbCartes){
    for (Carte* carte : other.cartes) {
        if (auto* cr = dynamic_cast<CarteRoyaume*>(carte)) {
            CarteRoyaume* cr_ =  new CarteRoyaume(*cr);
            cartes.push_back(cr_);
        }
        if (auto* ctt = dynamic_cast<CarteTresor*>(carte)) {
            CarteTresor* ctt_ =  new CarteTresor(*ctt);
            cartes.push_back(ctt_);
        }
        if (CarteVictoire* cvt = dynamic_cast<CarteVictoire*>(carte)) {
            auto* cvt_ =  new CarteVictoire(*cvt);
            cartes.push_back(cvt_);
        }
    }
}

Deck::Deck(Deck && other) noexcept : cartes(std::move(other.cartes)), nbCartes(other.nbCartes)  {
    other.nbCartes = 0;
}

Deck &Deck::operator=(Deck && other) noexcept {
    for (Carte* carte : cartes) {
        delete carte;
    }
    cartes.clear();
    cartes = std::move(other.cartes);
    nbCartes = other.nbCartes;
    other.cartes.clear();
    other.nbCartes = 0;
    return *this;
}




//mélange le deck
void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(cartes.begin(), cartes.end(), gen);
};


// Fonction de comparaison pour trier les cartes
bool comparerParType(Carte* carte1, Carte* carte2) {

    if (carte1->getType() == carte2->getType()) {
        return false;
    }

    int c1=0;
    if (carte1->getType() == Royaume)
    {c1=0;}
    else if(carte1->getType() == Tresor)
    {c1=1;}
    else if(carte1->getType() == Victoire)
    {c1=2;}

    int c2=0;
    if (carte2->getType() == Royaume)
    {c2=0;}
    else if(carte2->getType() == Tresor)
    {c2=1;}
    else if(carte2->getType() == Victoire)
    {c2=2;}


    // Ordre de tri : Royaume > Trésor > Victoire
    return c1 < c2;
}

//trie le deck
void Deck::trier() {
    std::sort(cartes.begin(), cartes.end(), comparerParType);
}



int Deck::getTaille() const {
    return cartes.size();
}

const std::vector<Carte*>& Deck::getCartes() const{
    return cartes;
}


//retire la carte passée en argument du deck et renvoie un pointeur vers cette dernière , renvoie nullptr si la carte n'a pas été trouvée dans le deck
Carte* Deck::retirerCarte(Carte* carte_) {
    std::vector<Carte*>::iterator it;
    Carte* c = nullptr;
    for (it = cartes.begin(); it != cartes.end(); ++it) {
        if ((*it)->getNom() == carte_->getNom()) {  // Vérifie si l'adresse de la carte correspond
            c = *it;
            // Retirer la carte du deck
            cartes.erase(it);
            nbCartes--;
            break;
        }
    }
    return c;

}

//pareil qu'au dessus mais avec un index
Carte *Deck::retirerCarte(int index) {
    Carte* c = cartes.at(index);
    cartes.erase(cartes.begin()+index);
    return c;
}

//pareil qu'au dessus mais avec un nom
Carte *Deck::retirerCarte(std::string nom) {
    Carte* c = nullptr;
    std::vector<Carte*>::iterator it;
    for (it = cartes.begin(); it != cartes.end(); it++) {
        if ((*it)->getNom() == nom) {
            c = *it;
            cartes.erase(it);
            nbCartes--;
            break;
        }
    }
    return c;
}

//désalloue la mémoire de toutes les cartes d'un deck et vide le paquet
void Deck::reset() {
    for (Carte* carte : cartes) {
        delete carte;
    }
    cartes.clear(); // Vide le vecteur
    nbCartes = 0;   // Réinitialise le compteur
}

Carte *Deck::getCarte(std::string nom, Type t){
    Carte * c = nullptr;
    for (Carte* carte : cartes) {
        if (carte->getNom() == nom && carte->getType() == t) {
            c = carte;
            break;
        }
    }
    return c;
}

//retourne un pointeur vers la carte de nom nom, null ptr sinon
Carte *Deck::getCarte(std::string nom){
    Carte * c = nullptr;
    for (Carte* carte : cartes) {
        if (carte->getNom() == nom) {
            c = carte;
            break;
        }
    }
    return c;
}

//retourne la liste des noms des cartes du paquet
std::vector<std::string> Deck::getNomCartes() {
    std::vector<std::string> ncartes;
    for (Carte* carte : cartes) {
        ncartes.push_back(carte->getNom());
    }
    return ncartes;
}





//retire tous les tresors d'un deck et les renvoie sous frome de vector de cartes
std::vector<Carte*> Deck::retirerTresors() {
    std::vector<Carte*> v;
    std::vector<Carte*>::iterator it;
    for (it = cartes.begin(); it != cartes.end(); it++) {
        if ((*it)->getType() == Tresor) {
            v.push_back(*it);
        }
    }
    return v;
}


void Deck::ajouterCarte(Carte* carte_) {
    cartes.push_back(carte_);
    nbCartes++;
}



void Deck::setCartes(const std::vector <Carte*> &c) {
    cartes = c;
}



bool Deck::estVide() const {return cartes.size() == 0;};

//enleve la carte du dessus et la retourne, !pas de delete
Carte* Deck::prendreTopCarte() {
    Carte* c = cartes.back();
    cartes.pop_back();
    nbCartes--;
    return c;
};
void Deck::afficher(const Jeu& jeu)  {
    std::string couleurtresor;
    std::string couleurAction;
    if (jeu.getPhase()==Treasure)
    {
        couleurtresor="\033[5m\033[33m";
    }
    else
    {
        couleurtresor="\033[33m";
    }
    if (jeu.getPhase()==Action)
    {
        couleurAction="\033[5m\033[31m";
    }
    else
    {
        couleurAction="\033[31m";
    }
    std::cout<<"                                                 ";
    for (size_t i = 0; i < cartes.size(); ++i)
    {

        std::cout<<(getCartes().at(i)->getType()==Royaume ? couleurAction+"\033[31m┌────────────────┐ \033[0m" :
             (getCartes().at(i)->getType()==Tresor  ? couleurtresor+"┌────────────────┐ \033[0m" : "\033[32m┌────────────────┐ \033[0m"));
    }
    std::cout<<std::endl;
    std::cout<<"                                                 ";
    for (size_t i = 0; i < cartes.size(); ++i)
    {

        if (getCartes().at(i)->getType() == Royaume) {
            std::cout <<couleurAction<< "\033[1m│   " << std::left << std::setw(12) << getCartes().at(i)->getNom() << " │ \033[0m" ;
        } else if (getCartes().at(i)->getType() == Tresor) {
            std::cout <<couleurtresor<< "\033[1m│    " << std::left << std::setw(11) << getCartes().at(i)->getNom() << " │ \033[0m" ;
        } else {
            std::cout << "\033[32m\033[1m│    " << std::left << std::setw(11) << getCartes().at(i)->getNom() << " │ \033[0m" ;
        }
    }
    std::cout<<std::endl;
    std::cout<<"                                                 ";
    for (size_t i = 0; i < cartes.size(); ++i)
    {

        if (getCartes().at(i)->getType() == Royaume) {
            std::cout <<couleurAction<< "│───────┐┌───────│ \033[0m" ;
        } else if (getCartes().at(i)->getType() == Tresor) {
            std::cout <<couleurtresor<< "│────────────────│ \033[0m" ;
        } else {
            std::cout << "\033[32m│────────────────│ \033[0m" ;
        }
    }
    std::cout<<std::endl;
    std::cout<<"                                                 ";
    for (size_t i = 0; i < cartes.size(); ++i)
    {

        if (getCartes().at(i)->getType() == Royaume) {
            CarteRoyaume* carteRoyaume = dynamic_cast<CarteRoyaume*>(getCartes().at(i));
            std::cout <<couleurAction<< "\033[1m│ "  << carteRoyaume ->getNbActions()<< " Act ││ "<<carteRoyaume ->getNbCartes()<<" Crt │ \033[0m";
        } else if (getCartes().at(i)->getType() == Tresor) {
            std::cout <<couleurtresor<< "\033[1m│                │ \033[0m" ;
        } else {

            std::cout << "\033[32m│                │ \033[0m" ;
        }
    }
    std::cout<<std::endl;
    std::cout<<"                                                 ";
    for (size_t i = 0; i < cartes.size(); ++i)
    {

        if (getCartes().at(i)->getType() == Royaume) {

            std::cout <<couleurAction<< "│───────││───────│ \033[0m";
        } else if (getCartes().at(i)->getType() == Tresor) {

            std::cout <<couleurtresor<< "│─────┐──────────│ \033[0m" ;
        } else {

            std::cout << "\033[32m│──────┐─────────│ \033[0m" ;
        }
    }
    std::cout<<std::endl;
    std::cout<<"                                                 ";
    for (size_t i = 0; i < cartes.size(); ++i)
    {

        if (getCartes().at(i)->getType() == Royaume) {
            CarteRoyaume* carteRoyaume = dynamic_cast<CarteRoyaume*>(getCartes().at(i));
            std::cout <<couleurAction<< "\033[1m│ "  << carteRoyaume ->getNbGold()<< "  €  ││ "<<carteRoyaume ->getNbAchats()<<" buy │ \033[0m";
        } else if (getCartes().at(i)->getType() == Tresor) {
            CarteTresor* carteTresor = dynamic_cast<CarteTresor*>(getCartes().at(i));
            std::cout <<couleurtresor<< "\033[1m│ "<<carteTresor->getValue()<<" € │          │ \033[0m" ;
        } else
        {
            CarteVictoire* carteVictoire = dynamic_cast<CarteVictoire*>(getCartes().at(i));
            std::cout << "\033[32m\033[1m│ "<<carteVictoire->getValue()<<" PV │         │ \033[0m" ;
        }
    }

    std::cout<<std::endl;
    std::cout<<"                                                 ";
    for (size_t i = 0; i < cartes.size(); ++i)
    {

        if (getCartes().at(i)->getType() == Royaume) {

            std::cout <<couleurAction<< "└───────┘└───────┘ \033[0m";
        } else if (getCartes().at(i)->getType() == Tresor) {

            std::cout <<couleurtresor<< "└─────┘──────────┘ \033[0m" ;
        } else {

            std::cout << "\033[32m└──────┘─────────┘ \033[0m" ;
        }
    }
};


//vide le deck mais ne met pas à nullptr les cartes
void Deck::vider() {
    cartes.clear();
    nbCartes = 0;
}

//ajoute les cartes d'un deck à un autre (copie les pointeurs)
void Deck::ajouterDeck(Deck & d) {
    for (Carte* c : d.cartes) {
        cartes.push_back(c);
    }
}

void Deck::afficher2(std::string nom,const char*  color, bool afficherIndex) const{
    {
        if (color == nullptr) {
            color = "";
        }
        std::cout<< color << "───────────────────────────────────────────────────────────── \033[1m"<<nom<<" ──────────────────────────────────────────────────────────────────────────────────────────"<<std::endl;
        for (size_t i=0 ; i<cartes.size() ; i++)
        {std::cout<<"\033[31m┌";
            for (std::string::size_type ii =0 ; ii<cartes.at(i)->getNom().size() ; ii++)
            {
                std::cout<<"─";
            }
            std::cout<<"┐";
        }
        std::cout<<std::endl;
        for (size_t i=0 ; i<cartes.size() ; i++)
        {std::cout<<"│";


            std::cout<<cartes.at(i)->getNom();

            std::cout<<"│";
        }
        std::cout<<std::endl;
        for (size_t i=0 ; i<cartes.size() ; i++)
        {std::cout<<"\033[31m└";
            for (std::string::size_type ii = 0 ; ii<cartes.at(i)->getNom().size() ; ii++)
            {
                if (afficherIndex && ii == cartes.at(i)->getNom().size()/2) {
                    std::cout << i;
                }else {
                    std::cout<<"─";

                }
            }
            std::cout<<"┘\033[0m";
        }
        std::cout<<std::endl;
    }
}