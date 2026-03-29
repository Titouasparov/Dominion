#include "../include/Util.h"
#include <algorithm>
#include "CarteRoyaume.h"
#include "CarteTresor.h"
#include "CarteVictoire.h"
#include <sstream>
#include <climits>
#include "../include/Jeu.h"
#include <fstream>


// Fonction qui transforme une ligne de texte en objet Carte
Carte* Util::strToCarte(std::string& line) {
    Carte* carte = nullptr;
    std::string nom, description;
    int cout = 0, nbCartes = 0, nbActions = 0, nbGold = 0, nbAchats = 0, valeur = 0;
    bool attaque = false, reaction = false;
    std::string t;

    std::string word;
    std::stringstream s = std::stringstream(line);

    // Extraction du nom de la carte
    std::getline(s, word, ';');  
    nom = word;

    std::getline(s, word, ';');
    t = word;

    // Extraction du coût si disponible
    if (std::getline(s, word, ';')) {
        cout = std::stoi(word);
    }

    // Si la carte est de type "Royaume", extraction des propriétés spécifiques
    if (t == "Royaume") {
        if (std::getline(s, word, ';')) {  
            description = word;
        }
        if (std::getline(s, word, ';')) {
            nbCartes = std::stoi(word);
        }
        if (std::getline(s, word, ';')) {
            nbActions = std::stoi(word);
        }
        if (std::getline(s, word, ';')) {
            nbGold = std::stoi(word);
        }
        if (std::getline(s, word, ';')) {
            nbAchats = std::stoi(word);
        }
        if (std::getline(s, word, ';')) {
            attaque = (word == "1");
        }
        if (std::getline(s, word, ';')) {
            reaction = (word == "1");
        }
    } else {  // Si la carte est de type "Victoire" ou "Tresor", on récupère la valeur
        if (std::getline(s, word, ';')) {
            valeur = std::stoi(word);
        }
    }

    // Création de l'objet Carte en fonction du type
    if (t == "Royaume") {
        carte = new CarteRoyaume(Jeu::getNextIdCarte(), nom, cout, nbCartes, nbActions, nbGold, nbAchats, attaque, reaction, description);
    } else {
        if (t == "Victoire") {
            carte = new CarteVictoire(Jeu::getNextIdCarte(), nom, cout, valeur);
        }
        if (t == "Tresor") {
            carte = new CarteTresor(Jeu::getNextIdCarte(), nom, cout, valeur);
        }
    }

    return carte;
}

// Fonction qui convertit un objet Carte en une chaîne de caractères
std::string Util::carteToStr(Carte* carte) {
    std::string result;
    std::string nom, description, valeur, cout, nbCartes, nbActions, nbGold, nbAchats, attaque, reaction;

    // Récupération du nom et du coût de la carte
    nom = carte->getNom();
    cout = std::to_string(carte->getCost());

    result.append(nom);
    result.append(";");

    // Si la carte est de type "Royaume", extraction des propriétés supplémentaires
    if (carte->getType() == Royaume) {
        nbCartes = std::to_string(carte->getNbCartes());
        nbActions = std::to_string(carte->getNbActions());
        nbGold = std::to_string(carte->getNbGold());
        nbAchats = std::to_string(carte->getNbAchats());
        description = carte->getDescription();
        attaque = carte->getAttaque() ? "1" : "0";
        reaction = carte->getReaction() ? "1" : "0";

        result.append("Royaume");
        result.append(";");
        result.append(cout);
        result.append(";");
        result.append(description);
        result.append(";");
        result.append(nbCartes);
        result.append(";");
        result.append(nbActions);
        result.append(";");
        result.append(nbGold);
        result.append(";");
        result.append(nbAchats);
        result.append(";");
        result.append(attaque);
        result.append(";");
        result.append(reaction);
    } else {  // Pour les cartes "Victoire" ou "Tresor", extraction de la valeur
        valeur = std::to_string(carte->getValue());

        if (carte->getType() == Victoire) {
            result.append("Victoire;");
        }
        if (carte->getType() == Tresor) {
            result.append("Tresor;");
        }
        result.append(cout);
        result.append(";");
        result.append(valeur);
    }

    return result;
}

// Convertit les informations d'un joueur en chaîne de caractères
std::string Util::joueurToStr(const Joueur& j) {
    std::string result;
    result.append(j.getNom());
    result.append(";");
    result.append(std::to_string(j.getNbActions()));
    result.append(";");
    result.append(std::to_string(j.getNbPieces()));
    result.append(";");
    result.append(std::to_string(j.getNbAchats()));
    result.append(";");
    result.append(std::to_string(j.getPv()));
    result.append(";");

    // Information sur les différents decks du joueur
    result.append("hand_");
    result.append(j.getNom());
    result.append(";");

    result.append("defausse_");
    result.append(j.getNom());
    result.append(";");

    result.append("pioche_");
    result.append(j.getNom());
    result.append(";");

    result.append("cartesJouees_");
    result.append(j.getNom());
    result.append(";");

    result.append("cartesAchetees_");
    result.append(j.getNom());

    return result;
}

// Convertit les informations d'un jeu en chaîne de caractères
std::string Util::jeuToStr(Jeu& j) {
    std::string result;

    std::string nextId = std::to_string(j.getNextIdCarte());
    std::string numTour = std::to_string(j.getNumTour());
    std::string quiJoue = j.getQuiJoue().getNom();
    std::string phase = (j.getPhase() == Action ? "Action" : "Achat");

    result.append(nextId);
    result.append(";");
    result.append(numTour);
    result.append(";");
    result.append(phase);
    result.append(";");
    result.append(quiJoue);
    return result;
}

// Calcule la distance de Levenshtein (différence minimale) entre deux chaînes de caractères
int Util::diff(std::string a, std::string b) {
    std::transform(a.begin(), a.end(), a.begin(), ::tolower);
    std::transform(b.begin(), b.end(), b.begin(), ::tolower);

    // Création d'une matrice pour stocker les valeurs intermédiaires
    std::vector<std::vector<int>> tab;
    for (size_t i = 0; i < a.size() + 1; i++) {
        std::vector<int> tmp;
        for (size_t j = 0; j < b.size() + 1; j++) {
            if (i == 0) {
                tmp.push_back(j);  // Si la première chaîne est vide, la distance est la longueur de la seconde chaîne
            } else if (j == 0) {
                tmp.push_back(i);  // Si la seconde chaîne est vide, la distance est la longueur de la première chaîne
            } else {
                tmp.push_back(-1);  // Sinon, la distance est encore inconnue
            }
        }
        tab.push_back(tmp);
    }

    // Calcul de la distance avec la fonction récursive
    diffRec(a.size(), b.size(), a, b, tab);
    return tab[a.size()][b.size()];
}

// Fonction récursive utilisée par diff() pour calculer la distance entre 2 chaines
int Util::diffRec(int i, int j, std::string& a, std::string& b, std::vector<std::vector<int>>& tab) {
    if ((tab[i][j] == -1)) {
        if (a.at(i - 1) == b.at(j - 1)) {
            tab[i][j] = diffRec(i - 1, j - 1, a, b, tab);
        } else {
            tab[i][j] = std::min(1 + diffRec(i - 1, j, a, b, tab), 1 + diffRec(i, j - 1, a, b, tab));
        }
    }
    return tab[i][j];
}

// Vérifie si un élément est présent dans un vecteur
bool Util::isInVector(std::string p, std::vector<std::string> v) {
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] == p) {
            return true;
        }
    }
    return false;
}

// Trouve l'élément le plus proche dans une liste par rapport à une chaîne donnée
std::string Util::closestEl(const std::string &el, const std::vector<std::string> &list) {
    std::string meilleurMatch;
    int diffMin = INT_MAX;

    // Pour chaque élément de la liste, calcule la différence et trouve le plus proche
    for (const auto& nom : list) {
        int ecart = diff(nom, el);
        if (ecart < diffMin) {
            diffMin = ecart;
            meilleurMatch = nom;
        }
    }
    return meilleurMatch;
}

std::vector <std::string> Util::getCartesRoyaumesFromCsv() {
    std::fstream file;
    std::string line;
    std::vector<std::string> toutesLesCartes;
    file.open("cartesRoyaumes.csv", std::ios::in);

    if (!file.is_open()){
        std::cout << "Erreur ou open";
        exit(1);
    }
    std::getline(file, line);
    while (std::getline(file, line)){
        toutesLesCartes.push_back(line);
    }
    return toutesLesCartes;
}