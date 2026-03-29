#ifndef __CarteTresor_h__
#define __CarteTresor_h__
#include <iostream>
#include "Carte.h"

/**
* @class CarteTresor
* @brief représente une carte tresor
* Cette classe étend la classe abstraite 'Carte'
*/
class CarteTresor : public Carte{
private:
    int value;
public:
    CarteTresor(int id_, std::string nom_, int cost_, int value_);
    int getValue() const;

    void afficherDetail() const override;
    void afficher() const;

    int getNbCartes() override;
    int getNbActions() override;
    int getNbGold() override;
    int getNbAchats() override;
    ~CarteTresor() override = default;
  };

#endif