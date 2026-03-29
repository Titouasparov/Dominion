#ifndef __CarteVictoire_h__
#define __CarteVictoire_h__
#include <iostream>
#include "Carte.h"

/**
* @class CarteVictoire
* @brief  représente une Carte Victoire
*
* Cette classe étend la classe 'Carte'
*/
class CarteVictoire : public Carte{
private:
    int value;
public:
    CarteVictoire(int id_, std::string nom_, int cost_, int value_);
    int getValue() const;
    void afficherDetail() const;
    void afficher() const;

    int getNbCartes() override;
    int getNbActions() override;
    int getNbGold() override;
    int getNbAchats() override;
    ~CarteVictoire() override = default;
};

#endif