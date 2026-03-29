#include <utility>

#include "../include/Joueur.h"

#include <CarteTresor.h>
#include <Jeu.h>

// Retourne le nombre d'achats disponibles pour ce joueur.
int Joueur::getNbAchats() const {
  return nbAchats;
}

// Retourne le nombre de pièces disponibles pour ce joueur.
int Joueur::getNbPieces() const {
  return nbPieces;
}

// Retourne le nombre d'actions restantes pour ce joueur.
int Joueur::getNbActions() const {
  return nbActions;
}

// Retourne si le joueur est actuellement un marchand.
bool Joueur::getMarchand() {
  return marchand;
}

// Définit si le joueur est un marchand.
void Joueur::setMarchand(bool b) {
  marchand = b;
}

// Constructeur de Joueur, initialisant le nom du joueur et les valeurs par défaut des autres attributs.
Joueur::Joueur(std::string nom_): nom(std::move(nom_)), marchand(false),protege(false) {
  std::string nom; // Variable inutilisée, probablement un oubli.
  nbActions = 1;
  nbPieces = 0;
  nbAchats = 1;
}

// Constructeur par défaut de Joueur.
Joueur::Joueur() {}

// Définit le nom du joueur.
void Joueur::setNom(std::string n) {
  nom = std::move(n);
}

// Modifie le nombre d'achats disponibles pour ce joueur.
void Joueur::setNbAchats(int n) {
  nbAchats = n;
}

// Modifie le nombre de pièces disponibles pour ce joueur.
void Joueur::setNbPieces(int n) {
  nbPieces = n;
}

void Joueur::setProtege(bool p) {
  protege = p;
}

// Modifie le nombre d'actions disponibles pour ce joueur.
void Joueur::setNbActions(int n) {
  nbActions = n;
}

// Modifie les points de victoire du joueur.
void Joueur::setNbPV(int n) {
  pv = n;
}

// Définit les cartes achetées par ce joueur.
void Joueur::setCartesAchetes(Deck & d) {
  cartesAchetees = d;
}

bool Joueur::estProtege() {
  return protege;
}


// Retourne le nom du joueur.
std::string Joueur::getNom() const {
  return nom;
}

// Retourne le nombre de points de victoire du joueur.
int Joueur::getPv() const {
  return pv;
}

// Ajoute un nombre d'actions au joueur.
void Joueur::ajouterActions(int n){
  nbActions += n;
}

// Ajoute un nombre de pièces au joueur.
void Joueur::ajouterPieces(int n){
  nbPieces += n;
}

// Ajoute un nombre d'achats au joueur.
void Joueur::ajouterAchats(int n){
  nbAchats += n;
}

// Ajoute un nombre de points de victoire au joueur.
void Joueur::ajouterPV(int n){
  pv += n;
}

// Retourne le deck des cartes jouées par ce joueur.
Deck& Joueur::getCartesJouees() {
  return cartesJouees;
}

// Retourne le deck des cartes en main du joueur.
Deck& Joueur::getHand() {
  return hand;
}

// Retourne le deck des cartes achetées par ce joueur.
Deck& Joueur::getCartesAchetes() {
  return cartesAchetees;
}

// Retourne le deck des cartes à piocher.
Deck& Joueur::getPioche() {
  return pioche;
}

// Retourne le deck des cartes dans la défausse.
Deck& Joueur::getDefausse() {
  return defausse;
}

// Retourne l'ensemble des cartes à défausser, incluant la main, les cartes achetées et les cartes jouées.
Deck Joueur::getCartesAdefausser() {
  Deck d = Deck();
  d.ajouterDeck(hand);
  d.ajouterDeck(cartesAchetees);
  d.ajouterDeck(cartesJouees);
  return d;
}

// Définit les cartes jouées par ce joueur.
void Joueur::setCartesJouees(Deck& deck) {
  cartesJouees = deck;
}

// Définit la main de ce joueur.
void Joueur::setHand(Deck& deck) {
  hand = deck;
}

// Définit la pioche de ce joueur.
void Joueur::setPioche(Deck& deck) {
  pioche = deck;
}

// Définit la défausse de ce joueur.
void Joueur::setDefausse(Deck& deck) {
  defausse = deck;
}

// Défausse toutes les cartes de la main, des cartes achetées et des cartes jouées dans la défausse.
void Joueur::defausser() {
  defausse.ajouterDeck(hand);
  defausse.ajouterDeck(cartesAchetees);
  defausse.ajouterDeck(cartesJouees);
  cartesAchetees.vider();
  cartesJouees.vider();
  hand.vider();
}

// Défausse les cartes d'un deck spécifique dans la défausse.
void Joueur::defausser(Deck & d) {
  defausse.ajouterDeck(d);
  d.vider();
}

// Pioche un nombre donné de cartes et les ajoute à la main.
void Joueur::piocher(int nombre) {
  for (int i = 0; i < nombre; i++) {
    if (pioche.estVide()) {
      defausseToPioche(); // Si la pioche est vide, on recharge la pioche à partir de la défausse.
      pioche.shuffle();
    }
    //si la pioche est tjr vide c'est que le joueur n'a pas d'autres cartes
    if (!pioche.estVide()) {
      hand.ajouterCarte(pioche.prendreTopCarte()); // Pioche une carte du dessus de la pioche.
    }
  }
  hand.trier();
}


void Joueur::oblitererCarte(Carte& carte) {
  hand.retirerCarte(&carte); // Retire la carte de la main.
  delete &carte; // Supprime la carte de la mémoire.
}

// Recharge la pioche à partir de la défausse et vide cette dernière.
void Joueur::defausseToPioche() {
  pioche = defausse;
  defausse.vider();
}

// Achète une carte et l'ajoute aux cartes achetées du joueur.
void Joueur::acheterCarte(Carte& c) {
    cartesAchetees.ajouterCarte(&c);
}

// Joue une carte spécifique de la main et l'ajoute aux cartes jouées.
void Joueur::jouerCarte(Carte& carte) {
  if (carte.getType() == Tresor) {
    if (marchand && carte.getNom() == "Argent") {
      nbPieces += carte.getValue() + 1; // Si le joueur est marchand, il gagne +1 pièce avec argent
      marchand = false; // Le joueur perd son statut de marchand après avoir joué un argent
    }
    nbPieces += carte.getValue(); // Ajoute la valeur de la carte trésor aux pièces du joueur.
  }
  cartesJouees.ajouterCarte(&carte);
  hand.retirerCarte(&carte);
}

// Joue une carte spécifiée par son nom à partir de la main du joueur.
void Joueur::jouerCarte(std::string nom) {
  Carte* c = hand.retirerCarte(nom); // Retire la carte spécifiée de la main.
  if (c->getType() == Tresor) {
    if (marchand && c->getNom() == "Argent") {
      nbPieces += 1; // Si le joueur a un  marchand, il gagne +1 pièce avec "Argent".
      marchand = false;
    }
    nbPieces += c->getValue(); // Ajoute la valeur de la carte trésor aux pièces du joueur.
  }else {
    nbActions-=1;
  }
  cartesJouees.ajouterCarte(c); // Ajoute la carte aux cartes jouées.
}

// Joue toutes les cartes trésor présentes dans la main du joueur.
void Joueur::jouerTresor() {
  std::vector<Carte*> carteTresors = hand.retirerTresors(); // Récupère toutes les cartes trésor de la main.
  for (Carte* c : carteTresors) {
    jouerCarte(*c); // Joue chaque carte trésor.
  }
}

// Vérifie si le joueur possède un trésor spécifié par son nom.
bool Joueur::hasTresor(std::string nom) {
  for (auto c : hand.getCartes()) {
    if (c->getType() == Tresor && c->getNom() == nom) {
      return true;
    }
  }
  return false;
}

// Vérifie si le joueur possède au moins un trésor.
bool Joueur::hasTresor() {
  for (auto c:hand.getCartes()) {
    if (c->getType() == Tresor) {
      return true;
    }
  }
  return false;
}
// Vérifie si le joueur possède au moins un trésor.
bool Joueur::hasVictoire() {
  for (auto c:hand.getCartes()) {
    if (c->getType() == Victoire) {
      return true;
    }
  }
  return false;
}

// Vérifie si le joueur possède une action.
bool Joueur::hasActions() {
  for (auto c:hand.getCartes()) {
    if (c->getType() == Royaume) {
      return true;
    }
  }
  return false;
}

// Vérifie si le joueur possède une action spécifique par son nom.
bool Joueur::hasActions(std::string nom) {
  for (auto c : hand.getCartes()) {
    if (c->getType() == Royaume && c->getNom() == nom) {
      return true;
    }
  }
  return false;
}

// Met à jour les points de victoire du joueur en fonction des cartes de victoire dans son deck.
void Joueur::updatePV() {
  pv = 0;
  int nbCartes = getNbCartes();
  for (Deck* d : getDeck()) {
    for (Carte* c: d->getCartes()) {
      if (c->getType() == Victoire) {
        pv += c->getValue(); // Ajoute la valeur des cartes de victoire.
      }
      if (c->getNom() == "Jardin") {
        pv += nbCartes / 10; // Les Jardins rapportent des points de victoire en fonction du nombre total de cartes.
      }
    }
  }
}

// Retourne le nombre total de cartes que possède le joueur (main, cartes achetées, cartes jouées, défausse, pioche).
int Joueur::getNbCartes() {
  return hand.getTaille() + cartesAchetees.getTaille() + cartesJouees.getTaille() + defausse.getTaille() + pioche.getTaille();
}

// Retourne tous les decks associés au joueur.
std::vector<Deck*> Joueur::getDeck() {
  std::vector<Deck*> decks;
  decks.push_back(&hand);
  decks.push_back(&cartesAchetees);
  decks.push_back(&cartesJouees);
  decks.push_back(&defausse);
  decks.push_back(&pioche);
  return decks;
}


// Réinitialise le joueur pour le prochain tour (remet les actions, achats et pièces à zéro, défausse toutes les cartes).
void Joueur::nextTour() {
  marchand = false;
  nbAchats = 1;
  nbPieces = 0;
  nbActions = 1;
  //on derevele les cartes revelees
  for (Deck* d : getDeck()) {
    for (Carte* c: d->getCartes()) {
      c->setRevelee(false);
    }
  }
  defausser(); // Défausse toutes les cartes avant le prochain tour.
  piocher(5);
}

// Réinitialise complètement le joueur, y compris ses decks et attributs.
void Joueur::reset() {
  hand.reset();
  cartesAchetees.reset();
  cartesJouees.reset();
  defausse.reset();
  pioche.reset();

  marchand = false;
  nbActions = 1;
  nbPieces = 0;
  nbAchats = 1;
  pv = 3;
}

bool Joueur::seDefend() {
  std::string douve ="Douve";
  std::string choix;
  Carte* c = hand.getCarte(douve,Royaume);
  if (c==nullptr) return false;

  while (choix != "oui" or choix !="non") {
    std::cout << "Joueur " << nom << ", voulez vous jouer douve (oui ou non) ? ";
    std::cin >> choix;
    if (choix == "oui" or choix !="non") {
      break;
    }else {
      std::cout << "Entrée invalide réessayez : ";
    }
  }
  return choix == "oui";
}
