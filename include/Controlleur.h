#ifndef __CONTROLLEUR_H__
#define __CONTROLLEUR_H__

#include "View.h"

/**
 * @class Controlleur
 * @brief Classe responsable de la gestion de la dynamique de jeu et de l'interaction utilisateur.
 */
class Controlleur {
private:
    View vue; ///< Instance de la vue pour interagir avec l'utilisateur.
    Jeu jeu;  ///< Instance du modèle de jeu pour gérer la logique.

public:

    Controlleur(View& vue, Jeu& jeu);

    /**
     * @brief Permet aux joueurs de choisir leurs cartes de départ.
     * 
     * Cette méthode gère l'interaction avec les joueurs pour leur permettre de sélectionner
     * leurs cartes initiales.
     */
    void choisirCartesDepart();

    /**
     * @brief Définit une configuration par défaut pour les cartes de départ.
     * 
     * Utilisée si les joueurs ne choisissent pas manuellement leurs cartes de départ.
     */
    void setDefautCartesDepart();

    void lancerMenu();

    void choixDesJoueurs();

    void lancerTour();

    void demanderTresors();

    void demanderAchat();

    void demanderAction();

    /**
     * @brief Affiche une description détaillée d'une carte.
     * 
     * @param description Référence à une chaîne contenant la nom de la carte dont on veut la description.
     */
    void demanderDescription(std::string& description);

    /**
     * @brief extrait le nom dans help(nom)
     * 
     * @param commande Référence à une chaîne contenant la commande pour laquelle l'aide est demandée.
     */
    void castHelp(std::string& commande);

    /**
     * @brief Vérifie si un index est valide pour un tableau ou une liste.
     * 
     * @param input Référence à une chaîne contenant l'index à valider.
     * @param maxIndex Indice maximum autorisé.
     * @return `true` si l'index est valide, `false` sinon.
     */
    bool isIndexValide(std::string& input, int maxIndex);

    void menuFin();
};

#endif
