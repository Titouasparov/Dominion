#ifndef __Deck_h__
#define __Deck_h__

#include <CarteRoyaume.h>
#include <vector>
#include "Carte.h"

class Jeu;

/**
 * @class Deck
 * @brief Représente un ensemble de cartes et fournit des opérations pour leur gestion.
 */
class Deck {
private:
    std::vector<Carte*> cartes; ///< Liste des cartes dans le deck.
    int nbCartes; ///< Nombre de cartes dans le deck.

public:
    Deck(std::vector<Carte*> cartes);

    Deck();

    ~Deck();

    Deck(const Deck& other);

    Deck& operator=(const Deck& other);

    Deck(Deck&& other) noexcept;

    Deck& operator=(Deck&& other) noexcept;

    /**
     * @brief Retire et retourne la carte du dessus du deck.
     * @return Pointeur vers la carte retirée.
     */
    Carte* prendreTopCarte();

    /**
     * @brief Réinitialise le deck à son état vide.
     */
    void reset();

    int getTaille() const;

    /**
    * @brief Mélange les cartes du deck de manière aléatoire.
    *
    * @param Aucun paramètre n'est pris par cette fonction.
    *
    * @return Aucun retour, la fonction modifie le deck en place en mélangeant les cartes.
    */
    void shuffle();

     /**
    * @brief Affiche le contenu du deck avec des couleurs et des informations spécifiques en fonction de la phase du jeu.
    *
    * @param jeu Une référence constante à un objet de type `Jeu`, utilisé pour déterminer la phase du jeu et ajuster l'affichage en conséquence.
    *
    */
    void afficher(const Jeu& jeu);

    /**
    * @brief Vérifie si le deck est vide.
    *
    * @return `true` si le deck est vide, `false` sinon.
    */
    bool estVide() const;

    /**
     * @brief Ajoute une carte au deck.
     * @param carte_ Pointeur vers la carte à ajouter.
     */
    void ajouterCarte(Carte* carte_);

    /**
     * @brief ajoute les pointeurs du deck other a ce deck.
     * @param other Référence vers le deck à ajouter.
     */
    void ajouterDeck(Deck& other);

    /**
     * @brief Retourne les noms des cartes dans le deck.
     * @return Vecteur de chaînes contenant les noms des cartes.
     */
    std::vector<std::string> getNomCartes();

    /**
     * @brief Retire une carte spécifique du deck.
     * @param carte_ Pointeur vers la carte à retirer.
     * @return Pointeur vers la carte retirée.
     */
    Carte* retirerCarte(Carte* carte_);

    /**
     * @brief Retire une carte spécifique du deck par son nom.
     * @param nom Nom de la carte à retirer.
     * @return Pointeur vers la carte retirée.
     */
    Carte* retirerCarte(std::string nom);

    /**
     * @brief Retire une carte à l'index spécifié.
     * @param index Position de la carte dans le deck.
     * @return Pointeur vers la carte retirée.
     */
    Carte* retirerCarte(int index);

    /**
     * @brief Retire toutes les cartes de type Trésor du deck.
     * @return Vecteur de pointeurs vers les cartes retirées.
     */
    std::vector<Carte*> retirerTresors();

    /**
     * @brief Recherche une carte par son nom et son type.
     * @param nom Nom de la carte à rechercher.
     * @param type Type de la carte à rechercher.
     * @return Pointeur vers la carte trouvée ou `nullptr` si inexistante.
     */
    Carte* getCarte(std::string nom, Type type);

    /**
     * @brief Recherche une carte par son nom.
     * @param nom Nom de la carte à rechercher.
     * @return Pointeur vers la carte trouvée ou `nullptr` si inexistante.
     */
    Carte* getCarte(std::string nom);

    /**
     * @brief Remplace les cartes du deck.
     * @param cartes Vecteur de pointeurs vers les nouvelles cartes.
     */
    void setCartes(const std::vector<Carte*>& cartes);

    /**
     * @brief Retourne les cartes du deck.
     * @return Vecteur constant des pointeurs de cartes.
     */
    const std::vector<Carte*>& getCartes() const;

    /**
    * @brief Vide le deck, mais ne met pas les cartes à nullptr.
    *
    */
    void vider();

    /**
    * @brief Trie le deck en utilisant une fonction de comparaison définie par `comparerParType`.
    *
    */
    void trier();

    /**
    * @brief Affiche le contenu du deck dans un format visuel, avec des bordures et des indices optionnels.
    *
    * @param nom Le nom à afficher en haut du deck.
    * @param color La couleur à utiliser pour le texte, ou `nullptr` pour ne pas spécifier de couleur.
    * @param afficherIndex Booléen pour indiquer si l'index des cartes doit être affiché au milieu de chaque carte.
    */
    void afficher2(std::string filtre = "", const char* style = nullptr, bool afficherIndex = false) const;
};

#endif
