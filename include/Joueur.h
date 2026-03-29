#ifndef __Joueur_h__
#define __Joueur_h__
#include "Deck.h"


class Joueur {
private:
    std::string nom;
    int nbActions;
    int nbPieces;
    int nbAchats;
    int pv{};
    Deck hand;
    Deck defausse;
    Deck pioche;
    Deck cartesJouees;
    Deck cartesAchetees;
    bool marchand;
    bool protege;



  public:
    Joueur(std::string nom_);
    Joueur();
    std::string getNom() const;
    int getPv() const;
    int getNbAchats() const;
    int getNbPieces() const;
    int getNbActions() const;

    /**
     * @brief Joue une carte spécifique de la main et l'ajoute aux cartes jouées.
     *
     * La fonction joue une carte du joueur en vérifiant si la carte est un trésor. Si c'est le cas, elle ajoute sa valeur aux pièces du joueur.
     * Si la carte jouée est "Argent" et que le joueur est un marchand, le joueur gagne une pièce supplémentaire et perd son statut de marchand.
     * La carte est ensuite déplacée de la main vers la liste des cartes jouées du joueur.
     *
     * @param carte La carte à jouer.
     */
    void jouerCarte(Carte&);

    /**
 * @brief Joue une carte spécifiée par son nom à partir de la main du joueur.
 *
 * La fonction retire la carte de la main du joueur et, si la carte est un trésor, elle ajoute sa valeur aux pièces du joueur.
 * Si la carte est "Argent" et que le joueur a le statut de marchand, il gagne une pièce supplémentaire et perd ce statut.
 * Si la carte n'est pas un trésor, le nombre d'actions du joueur est diminué de 1.
 * La carte est ensuite déplacée vers les cartes jouées du joueur.
 *
 * @param nom Le nom de la carte à jouer.
 */
    void jouerCarte(std::string nom);

    /**
 * @brief Joue toutes les cartes trésor présentes dans la main du joueur.
 *
 * La fonction retire toutes les cartes de type "Trésor" de la main du joueur et les joue une par une.
 * Chaque carte est traitée en utilisant la fonction `jouerCarte`, qui gère l'ajout de la valeur des trésors aux pièces du joueur.
 */
    void jouerTresor();

    /**
 * @brief Achète une carte et l'ajoute aux cartes achetées du joueur.
 *
 * La fonction ajoute la carte spécifiée à la collection des cartes achetées du joueur.
 *
 * @param c La carte à acheter et à ajouter aux cartes achetées du joueur.
 */
    void acheterCarte(Carte&);
    void setMarchand(bool);

    void ajouterActions(int);
    void ajouterPieces(int);
    void ajouterAchats(int);
    void ajouterPV(int);

    Deck& getCartesJouees() ;
    Deck& getHand();
    Deck& getPioche();
    Deck& getDefausse();
    Deck& getCartesAchetes();
    Deck getCartesAdefausser();
    bool getMarchand();
    bool estProtege();


    void setCartesJouees(Deck&);
    void setHand(Deck&);
    void setPioche(Deck&);
    void setDefausse(Deck&);
    void setCartesAchetes(Deck&);
    void setProtege(bool);

    void setNom(std::string nom);
    void setNbActions(int n);
    void setNbPieces(int n);
    void setNbAchats(int n);
    void setNbPV(int n);



   /**
    * @brief Défausse toutes les cartes de la main, des cartes achetées et des cartes jouées dans la défausse.
    *
    * La fonction ajoute toutes les cartes de la main, des cartes achetées et des cartes jouées du joueur à la défausse,
    * puis vide ces différents ensembles de cartes du joueur.
    *
    * @param Aucun paramètre n'est pris par cette fonction.
    *
    * @return Aucun retour, la fonction ne retourne rien. Elle effectue une modification interne du joueur.
    */
    void defausser();

    /**
     * @brief Défausse les cartes d'un deck spécifique dans la défausse.
     *
     * La fonction ajoute toutes les cartes du deck spécifié à la défausse,
     * puis remplace le contenu de la défausse par celui du deck.
     *
     * @param d Le deck à défausser.
     *
     * @return Aucun retour, la fonction ne retourne rien. Elle effectue une modification interne du deck et de la défausse.
     */
    void defausser(Deck&);

    /**
 * @brief Pioche un nombre donné de cartes et les ajoute à la main.
 *
 * La fonction pioche les cartes du dessus de la pioche et les ajoute à la main du joueur.
 * Si la pioche est vide, elle est rechargée à partir de la défausse et mélangée avant de continuer à piocher.
 * Si la pioche est toujours vide après un rechargement, aucune carte n'est piochée.
 * Après avoir pioché les cartes, la main du joueur est triée.
 *
 * @param nombre Le nombre de cartes à piocher.
 *
 * @return Aucun retour, la fonction ne retourne rien. Elle modifie la main du joueur et la pioche.
 */
    void piocher(int);

    /**
     * @brief Retire une carte de la main du joueur et la supprime de la mémoire.
     *
     * Cette fonction retire la carte spécifiée de la main du joueur et libère la mémoire associée à la carte en appelant `delete` dessus.
     * Cela permet de supprimer définitivement l'objet carte du système, libérant ainsi la mémoire qu'il occupait.
     *
     * @param carte La carte à retirer et supprimer.
     *
     * @return Aucun retour, la carte est simplement retirée de la main et supprimée.
     */
    void oblitererCarte(Carte&);

    /**
 * @brief Réinitialise l'état du joueur pour le prochain tour.
 *
 * Cette fonction réinitialise les attributs du joueur nécessaires pour le début du prochain tour. Cela inclut la remise à zéro du nombre
 * d'achats, d'actions, et de pièces. Le statut de marchand est également réinitialisé. Toutes les cartes révélées sont réinitialisées et
 * la main du joueur est remplie en piochant cinq nouvelles cartes.
 *
 * De plus, toutes les cartes actuellement dans la main, les cartes achetées et les cartes jouées sont défaussées avant le début du tour suivant.
 *
 * @see piocher() pour le processus de pioche des nouvelles cartes.
 * @see defausser() pour la gestion de la défausse des cartes.
 */
    void nextTour();

    /**
 * @brief Vérifie si le joueur possède un trésor spécifié par son nom.
 *
 * Cette fonction parcourt les cartes de la main du joueur et vérifie si l'une d'entre elles est un trésor avec le nom spécifié.
 * Si un trésor correspondant est trouvé, la fonction renvoie `true`, sinon elle renvoie `false`.
 *
 * @param nom Le nom du trésor à rechercher dans la main du joueur.
 *
 * @return `true` si le joueur possède un trésor avec le nom donné, `false` sinon.
 */
    bool hasTresor(std::string);

   /**
 * @brief Vérifie si le joueur possède au moins un trésor.
 *
 * Cette fonction parcourt les cartes de la main du joueur et vérifie si l'une d'entre elles est de type trésor.
 * Si un trésor est trouvé, la fonction renvoie `true`, sinon elle renvoie `false`.
 *
 * @return `true` si le joueur possède au moins un trésor, `false` sinon.
 */
    bool hasTresor();

    /**
     * @brief Vérifie si le joueur possède au moins une carte d'action.
     *
     * Cette fonction parcourt les cartes de la main du joueur et vérifie si l'une d'entre elles est de type "Royaume",
     * qui représente une carte d'action. Si une carte d'action est trouvée, la fonction renvoie `true`, sinon elle renvoie `false`.
     *
     * @return `true` si le joueur possède au moins une carte d'action, `false` sinon.
     */
    bool hasActions();

    /**
     * @brief Vérifie si le joueur possède au moins une carte de victoire.
     *
     * Cette fonction parcourt les cartes de la main du joueur et vérifie si l'une d'entre elles est de type "Victoire",
     * qui représente une carte de victoire. Si une carte de victoire est trouvée, la fonction renvoie `true`, sinon elle renvoie `false`.
     *
     * @return `true` si le joueur possède au moins une carte de victoire, `false` sinon.
     */
    bool hasVictoire();

    /**
     * @brief Vérifie si le joueur possède une action spécifique par son nom.
     *
     * Cette fonction parcourt les cartes de la main du joueur et vérifie si l'une d'entre elles est une carte de type "Royaume"
     * et correspond au nom spécifié. Si une telle carte est trouvée, la fonction renvoie `true`, sinon elle renvoie `false`.
     *
     * @param nom Le nom de la carte d'action à vérifier.
     *
     * @return `true` si le joueur possède une carte d'action avec le nom spécifié, `false` sinon.
     */
    bool hasActions(std::string);

    /**
     * @brief Permet au joueur de décider s'il souhaite utiliser la carte "Douve" pour se défendre.
     *
     * Cette fonction vérifie si le joueur possède la carte "Douve" (de type Royaume) dans sa main. Si le joueur possède la carte,
     * un prompt est affiché lui demandant s'il souhaite la jouer. Le joueur peut répondre par "oui" ou "non". Si la réponse est
     * "oui", la fonction retourne `true`, sinon elle retourne `false`.
     *
     * @return `true` si le joueur choisit de jouer la carte "Douve", `false` sinon.
     */
    bool seDefend();


    /**
     * @brief Met à jour les points de victoire du joueur en fonction des cartes de victoire dans son deck.
     *
     * Cette fonction parcourt tous les decks du joueur, et pour chaque carte de type "Victoire", elle ajoute sa valeur aux points de victoire du joueur.
     * En plus des cartes de victoire classiques, la carte "Jardin" rapporte des points de victoire supplémentaires en fonction du nombre total de cartes dans le deck.
     *
     * - Les cartes de type "Victoire" ajoutent leur valeur au total des points de victoire du joueur.
     * - La carte "Jardin" rapporte des points de victoire égaux à `nbCartes / 10`, où `nbCartes` est le nombre total de cartes du joueur.
     *
     * @see Carte
     * @see Deck
     */
    void updatePV();

    /**
 * @brief Retourne le nombre total de cartes que possède le joueur.
 *
 * Le nombre total de cartes est la somme des tailles de ces différentes collections de cartes.
 *
 * @return Le nombre total de cartes que possède le joueur.
 */
    int getNbCartes();

    /**
 * @brief Recharge la pioche à partir de la défausse et vide cette dernière.
 *
 * Cette fonction prend toutes les cartes présentes dans la défausse (`defausse`) et les place dans la pioche (`pioche`).
 * Après cela, la défausse est vidée.
 *
 * Cette opération est effectuée lorsqu'il n'y a plus de cartes dans la pioche, afin de la recharger avec les cartes déjà jouées, permettant ainsi de continuer à jouer.
 */
    void defausseToPioche();


    /**
 * @brief Retourne tous les decks associés au joueur.
 *
 * @return Un vecteur de pointeurs vers les decks du joueur.
 */
    std::vector<Deck*> getDeck();

    /**
 * @brief Réinitialise complètement le joueur, y compris ses decks et attributs.
 *
 */
    void reset();

};

#endif