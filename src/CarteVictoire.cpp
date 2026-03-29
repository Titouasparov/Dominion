#include "../include/CarteVictoire.h"
#include "../include/Carte.h"
#include <iomanip>
CarteVictoire::CarteVictoire(int id_, std::string nom_, int cost_, int value_):
Carte(id_,nom_,cost_,Type::Victoire){
  value = value_;
}


int CarteVictoire::getValue() const {
  return value;
}

void CarteVictoire::afficherDetail() const {
  std::cout <<std::endl<< "Carte Victoire : ["<<getNom()<< "]"<< std::endl
  <<"Valeur : "<<value <<" PV"<< std::endl
  <<"Coût : "<<getCost()<<" € "<<std::endl;
}

void CarteVictoire::afficher() const {

  std::cout << std::endl << "\033[32m┌----------------┐" << std::endl;
  std::cout << "|    " << std::left << std::setw(11) << getNom() << " |" << std::endl;
  std::cout << "|-----┐----------|" << std::endl;
  std::cout << "| "  << getCost() << " € |          |" << std::endl;
  std::cout << "└-----┘----------┘\033[0m" << std::endl;
}


int CarteVictoire::getNbAchats() {
  return 0;
}

int CarteVictoire::getNbActions() {
  return 0;
}

int CarteVictoire::getNbCartes() {
  return 0;
}

int CarteVictoire::getNbGold() {
  return 0;
}




