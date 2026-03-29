#ifndef PLATEAU_H
#define PLATEAU_H
#include "Deck.h"
#include "Carte.h"

class Plateau {
private:
  Deck provinces;
  Deck gold;
  Deck silver;
  Deck duchy;
  Deck estate;
  Deck copper;
  Deck curse;
  std::vector<Deck> decksRoyaume;

public:
  Plateau();
  Deck& getProvinces();
  Deck& getGold();
  Deck& getSilver();
  Deck& getDuchy();
  Deck& getEstate();
  Deck& getCopper();
  Deck& getCurse();
  std::vector<Deck>& getDecksRoyaume();

  /**
 * @brief Ajoute un deck de royaume à la liste des decks de royaume du plateau.
 *
 * Cette fonction prend un `Deck` en paramètre et l'ajoute à la collection des decks de royaume
 * qui sont utilisés durant la partie. Ces decks représentent les cartes de royaume disponibles pour les joueurs.
 *
 * @param deck Le deck à ajouter à la liste des decks de royaume. Ce deck contient des cartes de royaume
 *             qui peuvent être utilisées pendant le jeu.
 */
  void addDeckRoyaume(Deck& deck);
  void addGold(Carte* carte);
  void addSilver(Carte* carte);
  void addDuchy(Carte* carte);
  void addCopper(Carte* carte);
  void addCurse(Carte* carte);
  void addProvince(Carte* carte);
  void addEstate(Carte* carte);


    /**
 * @brief Remplace le deck des provinces du plateau par un nouveau deck.
 *
 * Cette fonction prend un `Deck` en paramètre et l'assigne à la variable `provinces` du plateau,
 * remplaçant ainsi le deck des provinces actuel par celui qui est passé en argument.
 *
 * @param deck Le deck de provinces à assigner au plateau. Ce deck contient les cartes de province
 *             utilisées dans le jeu pour les points de victoire.
 */
  void setProvinces(Deck& deck);
  void setGold(Deck& deck);
  void setSilver(Deck& deck);
  void setDuchy(Deck& deck);
  void setEstate(Deck& deck);
  void setCopper(Deck& deck);
  void setCurse(Deck& deck);
  void setDecksRoyaume(std::vector<Deck> decks);

    /**
 * @brief Retourne le nombre de piles vides sur le plateau.
 *
 * Cette fonction parcourt toutes les piles (ou decks) sur le plateau et compte celles qui sont vides.
 * Une pile est considérée vide si elle ne contient aucune carte.
 *
 * @return Le nombre de piles vides sur le plateau.
 */
  int getNbVide();

  std::vector<Deck*> getPlateau();

    /**
 * @brief Vérifie si une carte spécifiée est présente sur le plateau.
 *
 * Cette fonction vérifie si la carte dont le nom est passé en argument se trouve sur le plateau.
 * Elle effectue une recherche dans les différentes piles de cartes (provinces, gold, silver, duchy, estate, copper, curse)
 * ainsi que dans les decks de royaumes. Si la carte est trouvée dans l'une de ces piles, la fonction retourne `true`.
 * Sinon, elle retourne `false`.
 *
 * @param nom Le nom de la carte à vérifier.
 *
 * @return `true` si la carte est présente sur le plateau, `false` sinon.
 */
  bool isCardOnBoard(std::string nom);

    /**
     * @brief Retire la carte spécifiée du plateau et la renvoie sous forme de pointeur.
     *
     * Cette fonction cherche à retirer une carte du plateau dont le nom correspond à celui passé en argument.
     * La carte est retirée de la pile correspondante (par exemple, Province, Or, Argent, etc.) et un pointeur vers cette carte est retourné.
     * Si la carte n'est pas trouvée sur le plateau, la fonction renverra un pointeur nul (`nullptr`).
     *
     * @param nom Le nom de la carte à retirer du plateau.
     *
     * @return Un pointeur vers la carte retirée, ou `nullptr` si la carte n'est pas présente sur le plateau.
     */
  Carte* prendreCarte(std::string nom);

    /**
 * @brief Recherche et retourne le pointeur vers une carte spécifiée par son nom sur le plateau.
 *
 * Cette fonction recherche une carte dont le nom correspond à l'argument `nom` dans les différents decks du plateau (par exemple, les decks Provinces, Or, Argent, etc.).
 * Elle retourne un pointeur vers la première carte correspondante, ou `nullptr` si aucune carte du nom spécifié n'est trouvée.
 *
 * @param nom Le nom de la carte à rechercher sur le plateau.
 *
 * @return Un pointeur vers la carte trouvée, ou `nullptr` si la carte n'existe pas sur le plateau.
 */
  Carte* getCarte(std::string& nom);

  void clear();

};

#endif