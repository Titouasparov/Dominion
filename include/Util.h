#ifndef UTIL_H
#define UTIL_H
#include "CarteRoyaume.h"
#include "Carte.h"
#include "Jeu.h"

class Util {
private:
    /**
 * @brief Fonction récursive pour calculer la distance de Levenshtein entre deux chaînes de caractères.
 *
 * Cette fonction est utilisée pour calculer la distance de Levenshtein entre deux chaînes de caractères `a` et `b`.
 * La distance de Levenshtein est une mesure de la différence entre deux chaînes, et elle est définie comme le nombre minimal
 * d'opérations nécessaires pour transformer une chaîne en l'autre, où chaque opération est soit une insertion, une suppression,
 * ou une substitution de caractère.
 *
 * Cette fonction récursive est utilisée en combinaison avec une table (matrice) de résultats (`tab`) pour éviter les recalculs
 * inutiles (mémoïsation), ce qui améliore l'efficacité de l'algorithme.
 *
 * @param i L'index actuel dans la chaîne `a` (1-based).
 * @param j L'index actuel dans la chaîne `b` (1-based).
 * @param a La première chaîne de caractères.
 * @param b La deuxième chaîne de caractères.
 * @param tab La matrice de mémoïsation, qui stocke les résultats intermédiaires pour éviter les recalculs.
 *
 * @return La distance de Levenshtein entre les sous-chaînes `a[0..i-1]` et `b[0..j-1]`.
 */
    static int diffRec(int,int,std::string& a, std::string& b,std::vector<std::vector<int>>& tab);
public :
    /**
 * @brief Transforme une ligne de texte en un objet Carte.
 *
 * Cette fonction prend une ligne de texte, généralement sous forme de chaîne de caractères, et la transforme en un objet
 * `Carte` en fonction des informations contenues dans cette ligne. La ligne est supposée être composée de plusieurs champs
 * séparés par des points-virgules (`;`), représentant différents attributs d'une carte (nom, coût, type, etc.).
 *
 * En fonction du type de carte (Royaume, Victoire, ou Trésor), les informations spécifiques sont extraites et un objet
 * correspondant est créé. Si le type de carte est "Royaume", des attributs supplémentaires comme le nombre de cartes,
 * le nombre d'actions, de pièces d'or, et des informations sur l'attaque et la réaction sont également extraits. Pour
 * les cartes de type "Victoire" ou "Trésor", seule la valeur associée à la carte est extraite.
 *
 * @param line La ligne de texte à transformer en carte, avec les informations séparées par des points-virgules.
 *
 * @return Un pointeur vers l'objet `Carte` créé à partir des données de la ligne de texte. Le type de carte retourné
 *         peut être un objet de type `CarteRoyaume`, `CarteVictoire` ou `CarteTresor` selon les informations présentes.
 */
    static Carte* strToCarte(std::string&);

    /**
     * @brief Convertit un objet Carte en une chaîne de caractères.
     *
     * Cette fonction prend un objet `Carte` et génère une chaîne de caractères qui représente les propriétés de cette carte.
     * La chaîne de caractères retournée est structurée avec des informations séparées par des points-virgules (`;`), permettant
     * de recréer l'objet carte à partir de cette chaîne.
     *
     * Selon le type de la carte, les informations spécifiques sont extraites et ajoutées à la chaîne :
     * - Pour une carte de type "Royaume", des informations supplémentaires comme la description, le nombre de cartes,
     *   le nombre d'actions, de pièces d'or et d'achats, ainsi que les attributs d'attaque et de réaction sont inclus.
     * - Pour une carte de type "Victoire" ou "Trésor", seule la valeur de la carte est incluse.
     *
     * La chaîne générée peut être utilisée pour la sauvegarde de l'état de la carte ou pour la conversion en un format lisible.
     *
     * @param carte Un pointeur vers l'objet `Carte` à convertir en chaîne de caractères.
     *
     * @return Une chaîne de caractères représentant l'objet `Carte`, avec les informations pertinentes séparées par des points-virgules.
     */
    static std::string carteToStr(Carte* carte);

    /**
 * @brief Convertit les informations d'un joueur en une chaîne de caractères.
 *
 * Cette fonction prend un objet `Joueur` et génère une chaîne de caractères représentant les informations de ce joueur,
 * y compris son nom, le nombre d'actions, de pièces, d'achats et de points de vie, ainsi que des informations sur ses différents
 * decks. Chaque information est séparée par un point-virgule (`;`) pour faciliter la reconstruction des données ou leur
 * sérialisation dans un format lisible.
 *
 * La chaîne générée peut être utilisée pour sauvegarder l'état du joueur, le transmettre via un réseau, ou pour toute autre
 * opération nécessitant une représentation textuelle de l'objet joueur.
 *
 * @param j Un objet `Joueur` dont les informations doivent être converties en chaîne de caractères.
 *
 * @return Une chaîne de caractères représentant les informations du joueur, avec des données séparées par des points-virgules.
 */
    static std::string joueurToStr(const Joueur& j);

    /**
 * @brief Convertit les informations d'un jeu en une chaîne de caractères.
 *
 * Cette fonction prend un objet `Jeu` et génère une chaîne de caractères représentant les informations essentielles
 * de l'état actuel du jeu, telles que le prochain identifiant de carte, le numéro de tour, le joueur actif et la phase
 * du jeu (Action ou Achat). Chaque information est séparée par un point-virgule (`;`) pour faciliter la reconstruction
 * ou la sauvegarde de l'état du jeu dans un format lisible et structuré.
 *
 * La chaîne générée peut être utilisée pour sauvegarder l'état du jeu, pour des transferts de données ou pour toute
 * autre opération nécessitant une représentation textuelle de l'objet jeu.
 *
 * @param j Un objet `Jeu` dont les informations doivent être converties en chaîne de caractères.
 *
 * @return Une chaîne de caractères représentant les informations essentielles du jeu, séparées par des points-virgules.
 */
    static std::string jeuToStr(Jeu&);

   /**
 * @brief Calcule la distance de Levenshtein (ou différence minimale) entre deux chaînes de caractères.
 *
 * La distance de Levenshtein mesure le nombre minimal d'opérations (insertions, suppressions ou substitutions)
 * nécessaires pour transformer une chaîne de caractères en une autre. Cette fonction utilise un algorithme dynamique
 * pour calculer cette distance de manière optimale.
 *
 * Avant le calcul, les deux chaînes de caractères sont converties en minuscules pour rendre la comparaison insensible
 * à la casse.
 *
 * @param a La première chaîne de caractères.
 * @param b La seconde chaîne de caractères.
 *
 * @return La distance de Levenshtein entre les deux chaînes de caractères.
 */
    static int diff(std::string, std::string);

   /**
 * @brief Vérifie si un élément est présent dans un vecteur de chaînes de caractères.
 *
 * Cette fonction parcourt un vecteur de chaînes de caractères et vérifie si une chaîne donnée est présente dans le vecteur.
 * Si l'élément recherché est trouvé, la fonction retourne `true`, sinon elle retourne `false`.
 *
 * @param p L'élément à rechercher, de type `std::string`.
 * @param v Le vecteur dans lequel effectuer la recherche, de type `std::vector<std::string>`.
 *
 * @return `true` si l'élément est trouvé dans le vecteur, sinon `false`.
 */
    static bool isInVector(std::string,std::vector<std::string>);

   /**
 * @brief Trouve l'élément le plus proche d'une chaîne donnée dans une liste, en fonction de la distance de Levenshtein.
 *
 * Cette fonction parcourt une liste de chaînes de caractères et compare chaque élément avec une chaîne de référence
 * donnée, en utilisant la distance de Levenshtein pour déterminer la similarité. Elle retourne l'élément de la liste
 * qui présente la plus petite distance par rapport à la chaîne donnée.
 *
 * @param el La chaîne de caractères de référence, de type `std::string`.
 * @param list La liste d'éléments parmi lesquels trouver le plus proche, de type `std::vector<std::string>`.
 *
 * @return L'élément de la liste ayant la plus petite distance de Levenshtein par rapport à la chaîne de référence.
 */
    static std::string closestEl(const std::string&, const std::vector<std::string>&);
    static std::vector<std::string> getCartesRoyaumesFromCsv();

};

#endif