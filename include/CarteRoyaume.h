#ifndef __CarteRoyaume__
#define __CarteRoyaume__

#include <iostream>
#include "Carte.h"

class Jeu; // Déclaration avant usage de la classe Jeu pour éviter les dépendances circulaires.

/**
 * @class CarteRoyaume
 * @brief Classe représentant une carte de type Royaume.
 * 
 * Cette classe étend la classe abstraite `Carte` et ajoute des attributs et 
 * méthodes spécifiques aux cartes de type Royaume, telles que des actions,
 * de l'or supplémentaire, et des interactions d'attaque ou de réaction.
 */
class CarteRoyaume : public Carte {
private:
    int nbCartes;         ///< Nombre de cartes supplémentaires à piocher.
    int nbActions;        ///< Nombre d'actions supplémentaires offertes.
    int nbGold;           ///< Nombre de pièces supplémentaires offertes.
    int nbAchats;         ///< Nombre d'achats supplémentaires offerts.
    bool attaque;         ///< Indique si la carte est une carte d'attaque.
    bool reaction;        ///< Indique si la carte est une carte de réaction.
    std::string description;
    bool effet;           ///< Indique si la carte a un effet spécial.
    bool revelee;         ///< Indique si la carte est révélée.

public:

    CarteRoyaume(int id_, std::string nom_, int cost_, int nbCartes_, 
                 int nbActions_, int nbGold_, int nbAchats_, bool attaque_, 
                 bool reaction_, std::string description_);

    /**
     * @brief Active l'effet de la carte dans le contexte du jeu.
     * 
     * @param jeu Référence à l'objet Jeu pour appliquer les effets.
     */
    void trigger(Jeu& jeu);

    void afficherDetail() const override;

    void afficher() const override;

    int getNbCartes() override;

    int getNbActions() override;

    int getNbGold() override;

    int getNbAchats() override;

    bool getEffet();

    bool getAttaque() const override;

    bool getReaction() const override;

    std::string getDescription() const override;

    int getValue() const override;

    void setRevelee(bool revelee) override;

    bool getRevelee() const override;
};

#endif
