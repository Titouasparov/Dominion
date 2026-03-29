#include "../include/Plateau.h"
#include "../include/Util.h"
#include<fstream>

Plateau::Plateau()
    : provinces(), gold(), silver(), duchy(), estate(), copper(), curse(), decksRoyaume() {
}

Deck& Plateau::getProvinces() {
    return provinces;
}

Deck& Plateau::getGold() {
    return gold;
}

Deck& Plateau::getSilver(){
    return silver;
}

Deck& Plateau::getDuchy() {
    return duchy;
}

Deck& Plateau::getEstate() {
    return estate;
}

Deck& Plateau::getCopper() {
    return copper;
}

Deck& Plateau::getCurse() {
    return curse;
}

std::vector<Deck>& Plateau::getDecksRoyaume(){
    return decksRoyaume;
}

void Plateau::setDecksRoyaume(std::vector<Deck> decks) {
    decksRoyaume =decks;
}

void Plateau::addDeckRoyaume(Deck& deck) {
    // Ajoute un Deck à la liste decksRoyaume
    decksRoyaume.push_back(deck);
}

void Plateau::addGold(Carte* carte) {
    // Ajoute une carte au deck Gold
    gold.ajouterCarte(carte);  // La méthode ajouterCarte de Deck doit accepter un pointeur Carte*
}

void Plateau::addSilver(Carte* carte) {
    // Ajoute une carte au deck Silver
    silver.ajouterCarte(carte);  // La méthode ajouterCarte de Deck doit accepter un pointeur Carte*
}

void Plateau::addDuchy(Carte* carte) {
    // Ajoute une carte au deck Duchy
    duchy.ajouterCarte(carte);  // La méthode ajouterCarte de Deck doit accepter un pointeur Carte*
}

void Plateau::addCopper(Carte* carte) {
    // Ajoute une carte au deck Copper
    copper.ajouterCarte(carte);  // La méthode ajouterCarte de Deck doit accepter un pointeur Carte*
}

void Plateau::addCurse(Carte* carte) {
    // Ajoute une carte au deck Curse
    curse.ajouterCarte(carte);  // La méthode ajouterCarte de Deck doit accepter un pointeur Carte*
}

void Plateau::addEstate(Carte *carte) {
    estate.ajouterCarte(carte);
}


void Plateau::addProvince(Carte* carte) {
    // Ajoute une carte au deck Provinces
    provinces.ajouterCarte(carte);  // La méthode ajouterCarte de Deck doit accepter un pointeur Carte*
}

void Plateau::setProvinces(Deck& deck) {
    provinces = deck;  // Remplace le deck provinces par celui passé en argument
}

void Plateau::setGold(Deck& deck) {
    gold = deck;  // Remplace le deck gold par celui passé en argument
}

void Plateau::setSilver(Deck& deck) {
    silver = deck;  // Remplace le deck silver par celui passé en argument
}

void Plateau::setDuchy(Deck& deck) {
    duchy = deck;  // Remplace le deck duchy par celui passé en argument
}

void Plateau::setEstate(Deck& deck) {
    estate = deck;  // Remplace le deck estate par celui passé en argument
}

void Plateau::setCopper(Deck& deck) {
    copper = deck;  // Remplace le deck copper par celui passé en argument
}

void Plateau::setCurse(Deck& deck) {
    curse = deck;  // Remplace le deck curse par celui passé en argument
}

//retire la carte nommée nom du plateau et la renvoie sous forme de pointeur
Carte* Plateau::prendreCarte(std::string nom) {
    Carte* c = nullptr;
    if (nom == "Province") {
        c = provinces.prendreTopCarte();
    } else if (nom == "Or") {
        c = gold.prendreTopCarte();
    } else if (nom == "Argent") {
        c = silver.prendreTopCarte();
    } else if (nom == "Duche") {
        c = duchy.prendreTopCarte();
    } else if (nom == "Domaine") {
        c = estate.prendreTopCarte();
    } else if (nom == "Cuivre") {
        c = copper.prendreTopCarte();
    } else if (nom == "Malediction") {
        c = curse.prendreTopCarte();
    } else {
        for (auto& d : decksRoyaume) {
            if (!d.getCartes().empty()) {
                if (d.getCartes().at(0)->getNom() == nom) {
                    c = d.prendreTopCarte();
                    break; // Exit the loop once the card is found
                }
            }
        }
    }
    return c;
}

//renvoie true si la carte nommée nom est sur le plateau, false sinon
bool Plateau::isCardOnBoard(std::string nom) {
    bool res = false;

    // Vérification de la première carte dans chaque deck
    if (!provinces.estVide() && nom == provinces.getCartes().at(0)->getNom()) {
        res = true;
    }

    if (!gold.estVide() && nom == gold.getCartes().at(0)->getNom()) {
        res = true;
    }

    if (!silver.estVide() && nom == silver.getCartes().at(0)->getNom()) {
        res = true;
    }

    if (!duchy.estVide() && nom == duchy.getCartes().at(0)->getNom()) {
        res = true;
    }

    if (!estate.estVide() && nom == estate.getCartes().at(0)->getNom()) {
        res = true;
    }

    if (!copper.estVide() && nom == copper.getCartes().at(0)->getNom()) {
        res = true;
    }

    if (!curse.estVide() && nom == curse.getCartes().at(0)->getNom()) {
        res = true;
    }

    // Vérification de la première carte dans les decks royaume
    for (const auto& deck : decksRoyaume) {
        if (!deck.estVide() && nom == deck.getCartes().at(0)->getNom()) {
            res = true;
            break;  // Arrêter dès qu'une carte est trouvée
        }
    }

    return res;
}

//renvoie le pointeur vers une carte nommée nom sur le plateau, nullptr sinon
Carte *Plateau::getCarte(std::string &nom) {
    if (!provinces.estVide()) {
        if (nom == provinces.getCartes().at(0)->getNom()) {
            return provinces.getCartes().at(0);
        }
    }
    if (!gold.estVide()) {
        if (nom == gold.getCartes().at(0)->getNom()) {
            return gold.getCartes().at(0);
        }
    }
    if (!silver.estVide()) {
        if (nom == silver.getCartes().at(0)->getNom()) {
            return silver.getCartes().at(0);
        }
    }
    if (!duchy.estVide()) {
        if (nom == duchy.getCartes().at(0)->getNom()) {
            return duchy.getCartes().at(0);
        }
    }
    if (!estate.estVide()) {
        if (nom == estate.getCartes().at(0)->getNom()) {
            return estate.getCartes().at(0);
        }
    }
    if (!copper.estVide()) {
        if (nom == copper.getCartes().at(0)->getNom()) {
            return copper.getCartes().at(0);
        }
    }
    if (!curse.estVide()) {
        if (nom == curse.getCartes().at(0)->getNom()) {
            return curse.getCartes().at(0);
        }
    }
    for (Deck& d : decksRoyaume) {
        if (!d.estVide()) {
            if (nom == d.getCartes().at(0)->getNom()) {
                return d.getCartes().at(0);
            }
        }
    }
    return nullptr;
}

//retourne la lsite de pointeurs vers tous les decks du plateau
std::vector<Deck *> Plateau::getPlateau() {
    std::vector<Deck*> decks;
    decks.push_back(&gold);
    decks.push_back(&silver);
    decks.push_back(&duchy);
    decks.push_back(&estate);
    decks.push_back(&copper);
    decks.push_back(&curse);
    decks.push_back(&provinces);
    for (Deck& d : decksRoyaume) {
        decks.push_back(&d);
    }

    return decks;
}

void Plateau::clear() {
    for (Deck* d : getPlateau()) {
        d->reset();
    }
    decksRoyaume.clear();
}

//renvoie le nombre de piles vides du plateau
int Plateau::getNbVide() {
    int nbVide = 0;
    for (Deck* d:getPlateau()) {
        if(d->estVide()) {
            nbVide++;
        }
    }
    return nbVide;
}

