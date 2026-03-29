#ifndef VIEW_H
#define VIEW_H
#include "Jeu.h"

class Controlleur;

class View {
private:
    Controlleur* controlleur;
public :
    View(Controlleur*);
    void setControlleur(Controlleur*);

    /**
 * @brief Affiche l'état actuel du jeu et des informations sur les joueurs.
 *
 * Cette fonction affiche l'état du jeu, y compris les informations sur les joueurs, les cartes en jeu,
 * et les ressources disponibles pour le joueur actuel. Elle présente les informations de manière claire et stylisée
 * à l'aide de séquences d'échappement ANSI pour la couleur et le formatage du texte.
 * Elle inclut :
 * - Les informations sur les autres joueurs (points de victoire et nombre de cartes en main),
 * - Les informations sur le joueur actif, telles que le nombre de pièces, les actions restantes, et les cartes en main,
 * - La présentation du terrain de jeu, des cartes jouées, achetées, de la défausse et de la pioche du joueur actuel.
 *
 * @param jeu L'objet `Jeu` représentant l'état du jeu, de type `Jeu&`.
 */
    void afficherJeu(Jeu& jeu);

    /**
     * @brief Affiche le menu permettant au joueur de choisir une carte à ajouter au jeu.
     *
     * Cette fonction affiche un menu interactif qui présente une liste de cartes disponibles, permettant au joueur
     * de sélectionner une carte en fonction de son numéro d'index. Le joueur peut ensuite ajouter la carte sélectionnée
     * au jeu. Le menu est affiché avec un formatage coloré pour améliorer la lisibilité et l'interaction avec le joueur.
     *
     * @param cartes La liste des cartes disponibles, de type `std::vector<std::string>`, qui seront affichées
     *               et parmi lesquelles le joueur pourra faire un choix.
     */
    void afficherMenuChoixCartes(std::vector<std::string>& cartes);


    void afficherMenu();
    void afficherChoixJoueurs(int i);

    /**
 * @brief Affiche l'état actuel du terrain de jeu, y compris les cartes des royaumes et les ressources disponibles.
 *
 * Cette fonction affiche le terrain de jeu, avec des informations détaillées sur les cartes des royaumes, les provinces,
 * l'or, le duché, l'argent, et d'autres éléments liés au jeu. Chaque carte des royaumes est affichée avec des informations
 * sur le nombre de cartes, d'actions, de pièces d'or, et d'achats disponibles. Le tout est présenté dans un tableau formaté,
 * avec des effets visuels pour améliorer la lisibilité et l'interaction avec le joueur.
 *
 * @param jeu L'objet `Jeu` représentant l'état actuel du jeu, qui contient les informations sur les decks des royaumes,
 *            les provinces, l'or, les cartes et d'autres éléments nécessaires à l'affichage du terrain.
 */
    void afficherTerrain(Jeu& jeu);
    void afficherDemandeTresor();
    void afficherDemandeAchat();

    void carteIntrouvable();
    void fondsInsuffisants();
    void afficherDemandeDescription();

    void afficherDescription(CarteRoyaume*);
    void afficherDemandeDefausse(Deck d);
    void afficherDemandeAction();

    /**
     * @brief Affiche l'état actuel du terrain de jeu, y compris les cartes des royaumes et les ressources disponibles.
     *
     * Cette fonction affiche le terrain de jeu, avec des informations détaillées sur les cartes des royaumes, les provinces,
     * l'or, le duché, l'argent, et d'autres éléments liés au jeu. Chaque carte des royaumes est affichée avec des informations
     * sur le nombre de cartes, d'actions, de pièces d'or, et d'achats disponibles. Le tout est présenté dans un tableau formaté,
     * avec des effets visuels pour améliorer la lisibilité et l'interaction avec le joueur.
     *
     * @param jeu L'objet `Jeu` représentant l'état actuel du jeu, qui contient les informations sur les decks des royaumes,
     *            les provinces, l'or, les cartes et d'autres éléments nécessaires à l'affichage du terrain.
     */
    void afficherFin(Jeu& jeu);

};



#endif //VIEW_H
