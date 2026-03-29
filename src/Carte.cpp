#include "../include/Carte.h"
#include <iomanip>
#include<iostream>
Carte::Carte(int id_, std::string nom_, int cost_, Type type_):id(id_), nom(nom_), cost(cost_), type(type_){

}

bool Carte::operator==(const Carte& other) const {
	if (typeid(*this) != typeid(other)) {
		return false;
	}
	if (this->id == other.id && this->nom == other.nom && this->cost == other.cost && this->type == other.type) {
		return true;
	}
	return false;
}


const std::string& Carte::getNom() const {
	return nom;
}

int Carte::getId() const {
	return id;
}

int Carte::getCost() const {
	return cost;
}

Type Carte::getType() const {
	return type;
}

void Carte::setNom(const std::string& nom_) {
	nom = nom_;
}

void Carte::afficher() const {
	std::cout<<"\033[31m┌";
	for (std::string::size_type ii =0 ; ii<nom.size() ; ii++)
	{
		std::cout<<"─";
	}
	std::cout<<"┐";

	std::cout<<"│";


	std::cout<<nom;

	std::cout<<"│";

	std::cout<<std::endl;

	std::cout<<"└";
	for (std::string::size_type ii = 0 ; ii<nom.size(); ii++)
	{
		std::cout<<"─";
	}
	std::cout<<"┘";
}

void Carte::setId(int id_) {
	id = id_;
}

//renvoie si la carte est une attaque ou pas
bool Carte::getAttaque() const {
	return false;
}

//renvoie si la carte est une carte reaction ou pas
bool Carte::getReaction() const {
	return false;
}
std::string Carte::getDescription() const {
	return "";
}

//pour les cartes reactions, indique si elle a été jouée
bool Carte::getRevelee() const {
	return false;
}

void Carte::setRevelee(bool) {
}


