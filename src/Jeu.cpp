#include "../include/Jeu.h"
#include "../include/CarteTresor.h"
#include "../include/CarteVictoire.h"
#include "../include/Carte.h"
#include "../include/Util.h"

int Jeu::nextIdCarte = 0;

Jeu::Jeu(){
  numTour = 0;
  phase = Achat;
  joueurAttaque = nullptr;
};

void Jeu::setJoueurAttaque(Joueur* j) {
  joueurAttaque = j;
}

//renvoie le joueur devant réagir à une attaque
Joueur* Jeu::getJoueurAttaque() {
  return joueurAttaque;
}

//On cree une liste avec tous les noms de carte du jeu
void Jeu::initNomCartes() {
  for (auto* d : plateau.getPlateau()) {
    for (auto* c : d->getCartes()) {
      if (!(Util::isInVector(c->getNom(),nomCartesJeu))) {
        nomCartesJeu.push_back(c->getNom());
      }
    }
  }
}

// initialise le jeu
void Jeu::init(bool restoringSave){
  //valeurs de base
  int nbProvince=0;
  int nbDuchy=0;
  int nbEstate=0;
  int nbCurse=0;
  int nbGold=0;
  int nbSilver=0;
  int nbCopper=0;

  int nbCopperHand = 7;
  int nbEstateHand = 3;
  //selon le nombre de joueurs
  switch (joueurs.size()) {
    case 2:
      nbCartesRoyaumes = 10;
      nbDeckRoyaumes = 10;
      //Quantités de cartes autre que royaumeint nbProvince = 8;
      nbProvince = 8;
      nbDuchy = 8;
      nbEstate = 8;
      nbCurse = 10;
      nbGold = 30;
      nbSilver=40;
      nbCopper = 47;
      break;
    default:
      nbCartesRoyaumes = 12;
      nbDeckRoyaumes = 10;
      //Quantités de cartes autre que royaumeint nbProvince = 8;
      nbProvince = 12;
      nbDuchy = 12;
      nbEstate = 12;
      nbCurse = 20;
      nbGold = 30;
      nbSilver=40;
      nbCopper = 39;
  }
  //si on restaure une sauvegarde
  if (restoringSave) {

  }else {
    //sinon on initialise les cartes de gauche du plateau et les mains des joueurs
    if (!(joueurs.empty())){
      quiJoue = &joueurs.at(0);
    }
    //Creation des provinces
    for (int i = 0; i<nbProvince; i++) {
      plateau.addProvince(new CarteVictoire(nextIdCarte,"Province",8,6));
      nextIdCarte+=1;
    }
    //Creation des golds
    for (int i = 0; i<nbGold; i++) {
      plateau.addGold(new CarteTresor(nextIdCarte,"Or",6,3));
      nextIdCarte+=1;
    }
    //Creation des silver
    for (int i = 0; i<nbSilver; i++) {
      plateau.addSilver(new CarteTresor(nextIdCarte,"Argent",3,2));
      nextIdCarte+=1;
    }
    //Creation des copper
    for (int i = 0; i<nbCopper; i++) {
      plateau.addCopper(new CarteTresor(nextIdCarte,"Cuivre",0,1));
      nextIdCarte+=1;
    }
    //Creation des duchy
    for (int i = 0; i<nbDuchy; i++) {
      plateau.addDuchy(new CarteVictoire(nextIdCarte,"Duche",5,3));
      nextIdCarte+=1;
    }
    //Creation des estates
    for (int i = 0; i<nbEstate; i++) {
      plateau.addEstate(new CarteVictoire(nextIdCarte,"Domaine",2,1));
      nextIdCarte+=1;
    }
    //Creation des curses
    for (int i = 0; i<nbCurse; i++) {
      plateau.addCurse(new CarteVictoire(nextIdCarte,"Malediction",0,-1));
      nextIdCarte+=1;
    }

    //Création main des joueurs
    auto* copper_ = new CarteTresor(getNextIdCarte(),"Cuivre",0,1);
    auto* estate_ = new CarteVictoire(getNextIdCarte(),"Domaine",2,1);
    for (Joueur& j : joueurs) {
      for (int i = 0; i < nbCopperHand; i++) {
        j.getPioche().ajouterCarte(copper_);
        copper_ = new CarteTresor(*copper_);
        copper_->setId(getNextIdCarte());
      }
      for (int i = 0; i < nbEstateHand; i++) {
        j.getPioche().ajouterCarte(estate_);
        estate_ = new CarteVictoire(*estate_);
        estate_->setId(getNextIdCarte());
      }
      j.getPioche().shuffle();
    }
  }

}

void Jeu::afficher() const{
}

void Jeu::addNextIdCarte() {
  nextIdCarte++;
}


//retourne la liste des nom de cartes royaumes
const std::vector<std::string>& Jeu::getNomCartesJeu() const {
  return nomCartesJeu;
}

//ajoute le deck deck au decksRoyaumes du plateau
void Jeu::ajouterDeckRoyaume(Deck& deck) {
  plateau.addDeckRoyaume(deck);
}

Phase Jeu::getPhase() const{
  return phase;
  }
std::vector<Joueur>& Jeu::getJoueurs(){
  return joueurs;
  }

int Jeu::getNumTour() const{
  return numTour;
  }


int Jeu::getNextIdCarte() {
  nextIdCarte++;
  return nextIdCarte;
}

int Jeu::getNbDeckRoyaumes() const {
  return nbDeckRoyaumes;
}
int Jeu::getNbCartesRoyaumes() const {
  return nbCartesRoyaumes;
}

//Si le joueur à les sous et le bn d'achats > 0, deplace la carte choisie du plateau à la main du joueur. Renvoie vraie si l'opération a réussi faux sinon.
bool Jeu::acheterCarte(std::string& nom) {
  Carte* c = plateau.getCarte(nom);
  if (c==nullptr){ return false;}
  if (quiJoue->getNbPieces()>= c->getCost() && quiJoue->getNbAchats() > 0) {
    plateau.prendreCarte(nom);
    quiJoue->acheterCarte(*c);
    quiJoue->ajouterAchats(-1);
    quiJoue->ajouterPieces(-c->getCost());
    //La transaction s'est bien effectuée
    return true;
  }
  else {
    return false;
  }
}


void Jeu::setNumTour(int n){
  numTour = n;
  }

void Jeu::setJoueur(Joueur& j){
  quiJoue = &j;
  }

void Jeu::setPhase(Phase p){
  phase = p;
  }
void Jeu::setJoueurs(std::vector<Joueur>& j){
  joueurs = j;
  }

void Jeu::setQuiJoue(Joueur& j) {
  quiJoue =&j;
}

void Jeu::ajouterJoueur(Joueur & j) {
  joueurs.push_back(j);
}

Joueur& Jeu::getQuiJoue() {
  return *quiJoue;
}

// On augmente le num du tour, on reinitialise la phase et les actions,achats... des joueurs, on passe la main au joueur d'après
//On remplit les mains et on recalcule les pv
void Jeu::lancerTour() {
  //on re remplit la main du joueur qui vient de jouer

  //tour suivant
  numTour++;
  //phase initial
  phase = Action;
  //pas de joueur attaqué au début d'une phase
  joueurAttaque = nullptr;

  //premier tour tout le monde pioche et le premier inscrit commence
  if (numTour == 1) {
    quiJoue = &joueurs[0];
    for (Joueur& j : joueurs) {
      j.piocher(5);
    }

  }else {
    //on met à jour l'état du joueur ayant joué
    quiJoue->nextTour();
    //on passe au joueur suivant
    nextPlayer();

  }

  //on remplit les decks et update les pv
  for (auto &j : joueurs) {
    j.updatePV();
  }

}

void Jeu::setNextId(int n) {
  nextIdCarte = n;
}



Deck& Jeu::getProvinces(){ return plateau.getProvinces();}
Deck& Jeu::getGold(){return plateau.getGold();}
Deck& Jeu::getSilver(){return plateau.getSilver();}
Deck& Jeu::getDuchy(){return plateau.getDuchy();}
Deck& Jeu::getEstate(){return plateau.getEstate();}
Deck& Jeu::getCopper(){return plateau.getCopper();}
Deck& Jeu::getCurse(){return plateau.getCurse();}
std::vector<Deck>& Jeu::getDecksRoyaume() {
  return plateau.getDecksRoyaume();
}
Plateau& Jeu::getPlateau() {
  return plateau;
}

//determine le prochain joueur à jouer et le met dans quiJoue
void Jeu::nextPlayer() {
  for (size_t i = 0; i < joueurs.size(); i++) {
    if (quiJoue->getNom() == joueurs.at(i).getNom()) {
      if (i==joueurs.size()-1) {
        quiJoue = &joueurs.at(0);
        break;
      }else {
        quiJoue = &joueurs.at(i+1);
        break;
      }
    }
  }
}


void Jeu::nextPhase() {
  switch (phase) {
    case Achat:
      phase = Action;
      break;
    case Action:
      phase = Treasure;
      break;
    case Treasure:
      phase = Achat;
      break;
  }

}

//verifie les conditions de fin de jeu
bool Jeu::fin() {
  if(plateau.getProvinces().estVide() || plateau.getNbVide() >= 3) {
    return true;
  }
  return false;
}

//met à jour les points de victoire
void Jeu::updatePV() {
  for (Joueur& j: joueurs) {
    j.updatePV();
  }
}
Joueur Jeu::getJoueurGagnant()
{
  Joueur gagnant= getJoueurs().at(0);

  for (size_t i=1;i<getJoueurs().size();i++)
  {
    if (getJoueurs().at(i).getPv()>=gagnant.getPv())
    {
      gagnant=getJoueurs().at(i);
    }
  }
  return gagnant;
}

void Jeu::reset() {
  numTour = 0;
  quiJoue = nullptr;
  for (Joueur &j : joueurs) {
    j.reset();
  }
  plateau.clear();
}