#include "CarteTresor.h"
#include "Carte.h"
#include <iomanip>
#include <utility>
#include <Jeu.h>

CarteTresor::CarteTresor(int id_, std::string nom_, int cost_, int value_):
Carte(id_,std::move(nom_),cost_,Type::Tresor){
  value = value_;
}
int CarteTresor::getValue() const {
  return value;
}



void CarteTresor::afficherDetail() const {

  std::cout <<std::endl<< "Carte trésor : ["<<getNom()<< "]"<< std::endl
  <<"Valeur : "<<value <<" €"<< std::endl
  <<"Coût : "<<getCost()<<" € "<<std::endl;
}

void CarteTresor::afficher() const {

  std::cout << std::endl << "\033[33m┌----------------┐" << std::endl;
  std::cout << "|    " << std::left << std::setw(11) << getNom() << " |" << std::endl;
  std::cout << "|-----┐----------|" << std::endl;
  std::cout << "| "  << getCost() << " € |          |" << std::endl;
  std::cout << "└-----┘----------┘\033[0m" << std::endl;
}


int CarteTresor::getNbAchats() {
  return 0;
}

int CarteTresor::getNbActions() {
  return 0;
}

int CarteTresor::getNbCartes() {
  return 0;
}

int CarteTresor::getNbGold() {
  return 0;
}




