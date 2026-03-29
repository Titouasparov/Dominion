#ifndef __Jeu_h__
#define __Jeu_h__
#include <vector>
#include "Joueur.h"
#include "Deck.h"
#include "CarteRoyaume.h"
#include "Plateau.h"

enum Phase
{
  Action,
  Achat,
    Treasure
};


class Jeu {

private:
    static int nextIdCarte;
    int nbDeckRoyaumes{};
    int nbCartesRoyaumes{};
    int numTour;
    Phase phase;
    std::vector<Joueur> joueurs;
    Joueur* quiJoue{};
    Plateau plateau;
    std::vector<std::string> nomCartesJeu;
    Joueur* joueurAttaque;
    Joueur* joueurGagnant;


public:
    Jeu();
    static void setNextId(int n);

    /**
 * @brief Initialise le jeu en fonction du nombre de joueurs et restaure une sauvegarde si nécessaire.
 *
 * Si une sauvegarde est en cours de restauration, cette fonction ne fait rien. Sinon, elle initialise les cartes sur le plateau et les mains des joueurs.
 * Elle configure également les quantités de cartes de type "Province", "Duchy", "Estate", "Curse", "Gold", "Silver", et "Copper" selon le nombre de joueurs.
 *
 * @param restoringSave Indique si le jeu est en train de restaurer une sauvegarde (`true`) ou s'il doit être initialisé à partir de zéro (`false`).
 */
    void init(bool restoringSave = false);

    /**
 * @brief Crée une liste de tous les noms de cartes du jeu.
 *
 * Cette fonction parcourt les decks de tous les joueurs ainsi que le plateau pour ajouter les noms des cartes dans le vecteur `nomCartesJeu`,
 * en évitant les doublons.
 *
 * @return Aucun retour, la fonction modifie directement le vecteur `nomCartesJeu` en y ajoutant les noms des cartes.
 */
    void initNomCartes();
    void afficher() const;
    Phase getPhase() const;
    std::vector<Joueur>& getJoueurs();
    int getNumTour() const;
    Joueur& getQuiJoue();
    int getNbDeckRoyaumes() const;
    int getNbCartesRoyaumes() const;
    const std::vector<std::string>& getNomCartesJeu() const;

    /**
     * @brief Permet au joueur d'acheter une carte s'il a suffisamment de pièces et d'achats disponibles.
     *
     * Si le joueur a assez de pièces pour acheter la carte et qu'il lui reste des achats disponibles, la carte est déplacée du plateau
     * vers la main du joueur, et les ressources du joueur (pièces et achats) sont mises à jour. La fonction renvoie `true` si l'achat
     * a réussi, sinon elle renvoie `false`.
     *
     * @param nom Le nom de la carte à acheter.
     *
     * @return `true` si l'achat a réussi, `false` sinon.
     */
    bool acheterCarte(std::string&);

    void ajouterDeckRoyaume(Deck&);
    void ajouterJoueur(Joueur&);
    static void addNextIdCarte();

    void setNumTour(int);
    void setJoueur(Joueur&);
    void setPhase(Phase);
    void setJoueurs(std::vector<Joueur>&);
    void setQuiJoue(Joueur&);

    /**
 * @brief Met à jour les points de victoire pour tous les joueurs.
 *
 * La fonction appelle la méthode `updatePV()` de chaque joueur pour recalculer leurs points de victoire en fonction de leurs cartes.
 *
 * @return Aucun retour, la fonction modifie les points de victoire des joueurs dans le jeu.
 */
    void updatePV();

   /**
 * @brief Vérifie les conditions de fin de jeu.
 *
 * La fonction vérifie si les provinces sont toutes épuisées ou si trois piles de cartes sont vides.
 * Si l'une de ces conditions est remplie, le jeu se termine.
 *
 * @return `true` si le jeu est terminé, `false` sinon.
 */
    bool fin();

    void setJoueurAttaque(Joueur*);
    Joueur* getJoueurAttaque();

   /**
 * @brief Détermine le joueur gagnant en fonction des points de victoire.
 *
 * La fonction parcourt la liste des joueurs et compare leurs points de victoire.
 * Le joueur avec le plus grand nombre de points de victoire est déclaré gagnant.
 * En cas d'égalité, le joueur apparaissant en premier dans la liste est choisi.
 *
 * @return Le joueur ayant le plus grand nombre de points de victoire.
 */
    Joueur getJoueurGagnant();

   /**
    * @brief Lance un nouveau tour de jeu.
    *
    * La fonction effectue plusieurs actions à chaque tour :
    * 1. Augmente le numéro du tour.
    * 2. Réinitialise la phase de jeu (Action par défaut) et les actions, achats, etc., des joueurs.
    * 3. Passe la main au joueur suivant.
    * 4. Si c'est le premier tour, chaque joueur pioche 5 cartes. Sinon, le joueur actuel passe son tour et c'est au suivant de jouer.
    * 5. Remplit les mains des joueurs et met à jour leurs points de victoire.
    */
    void lancerTour();

    /**
 * @brief Passe à la phase suivante du jeu.
 *
 * La fonction modifie la phase de jeu en suivant cet ordre cyclique :
 * 1. Si la phase actuelle est "Achat", elle passe à "Action".
 * 2. Si la phase actuelle est "Action", elle passe à "Trésor".
 * 3. Si la phase actuelle est "Trésor", elle revient à "Achat".
 */
    void nextPhase();

    Deck& getProvinces();
    Deck& getGold();
    Deck& getSilver();
    Deck& getDuchy();
    Deck& getEstate();
    Deck& getCopper();
    Deck& getCurse();
    static int getNextIdCarte();
    std::vector<Deck>& getDecksRoyaume();
    Plateau& getPlateau();

   /**
 * @brief Détermine et passe au prochain joueur à jouer.
 *
 * La fonction parcourt la liste des joueurs et met à jour le pointeur `quiJoue` pour désigner le joueur suivant dans l'ordre de la liste.
 * Si le joueur actuel est le dernier de la liste, le pointeur est réinitialisé au premier joueur.
 */

    void nextPlayer();

    void reset();
 };

#endif