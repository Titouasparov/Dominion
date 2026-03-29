#ifndef SAVE_H
#define SAVE_H
#include <iostream>
#include "../include/Jeu.h"


class Save{
private:
  std::string nom;
  Jeu& jeu;

public:
  Save(Jeu&, std::string nom);
  Save();


  /**
   * @brief Sauvegarde l'état d'un deck dans un fichier CSV.
   *
   * Cette fonction prend un deck et un chemin de fichier en argument et enregistre l'état du deck dans le fichier spécifié, au format CSV.
   * Chaque carte du deck est convertie en chaîne de caractères à l'aide de la fonction `Util::carteToStr` et est enregistrée dans le fichier ligne par ligne.
   *
   * @param chemin Le chemin du fichier où sauvegarder l'état du deck. Le fichier sera créé s'il n'existe pas, ou remplacé s'il existe déjà.
   * @param deck Le deck dont l'état doit être sauvegardé dans le fichier.
   */
  void saveDeck (const std::string& nom,Deck& deck);

    /**
 * @brief Sauvegarde l'état d'un joueur dans un fichier CSV.
 *
 * Cette fonction enregistre les informations liées à un joueur (y compris son état général et ses différents decks) dans un fichier CSV.
 * Le fichier sera créé dans un répertoire spécifique au joueur.
 * Elle enregistre d'abord les informations générales du joueur, puis les decks associés (main, défausse, cartes achetées, cartes jouées, pioche).
 *
 * @param chemin Le chemin du dossier où le joueur sera sauvegardé. Ce dossier sera créé si nécessaire.
 * @param joueur Le joueur dont l'état doit être sauvegardé.
 */
  void saveJoueur(const std::string&,Joueur& joueur);

    /**
     * @brief Sauvegarde l'état de chaque joueur dans des fichiers CSV.
     *
     * Cette fonction enregistre l'état de tous les joueurs dans des fichiers CSV, chacun portant le nom du joueur.
     * Les informations des joueurs sont sauvegardées dans un sous-dossier "Joueurs" situé dans le répertoire spécifié par le chemin `savePath`.
     * Pour chaque joueur, un fichier distinct est créé, contenant son état général et ses différents decks (main, défausse, cartes achetées, cartes jouées, pioche).
     *
     * @param savePath Le chemin du dossier principal où les fichiers de sauvegarde seront enregistrés.
     * @param joueurs Le vecteur des joueurs à sauvegarder.
     */
  void saveJoueurs(const std::string&, std::vector<Joueur>& joueurs);

    /**
 * @brief Sauvegarde l'état du plateau sous forme de decks.
 *
 * Cette fonction enregistre l'état actuel du plateau de jeu dans des fichiers CSV pour chaque deck du plateau.
 * Les decks sont enregistrés dans un dossier "Plateau", situé dans le répertoire spécifié par `chemin`.
 * Chaque deck du plateau (Provinces, Or, Argent, Duché, Domaine, Cuivre, Malédiction) est sauvegardé dans un fichier distinct,
 * ainsi que tous les decks de royaume qui ne sont pas vides.
 *
 * @param chemin Le chemin du dossier principal où l'état du plateau sera sauvegardé.
 */
  void savePlateau(const std::string&);

    /**
 * @brief Enregistre l'état de la partie dans un dossier dédié.
 *
 * Cette fonction enregistre l'état actuel du jeu (y compris les informations sur les joueurs et le plateau) dans un répertoire
 * spécifique, situé dans le répertoire courant de l'application. Si ce répertoire existe déjà, il sera d'abord supprimé
 * avant d'être recréé pour garantir que l'état du jeu est sauvegardé proprement à chaque appel.
 *
 * L'état du jeu est sauvegardé dans des fichiers CSV, avec les informations des joueurs et du plateau enregistrées dans des sous-dossiers.
 *
 * @param nom Le nom du fichier de sauvegarde, utilisé pour créer un répertoire de sauvegarde et nommer les fichiers.
 */
  void saveJeu();

    /**
 * @brief Charge un deck de cartes depuis un fichier.
 *
 * Cette fonction charge un deck de cartes à partir d'un fichier texte. Chaque ligne du fichier doit contenir des informations
 * sur une carte, qui sont ensuite converties en objets de type `Carte` et ajoutées à l'objet `Deck` spécifié.
 * Si le fichier n'existe pas ou est vide, aucun changement n'est effectué sur le deck.
 *
 * @param chemin Le chemin du fichier à partir duquel le deck sera chargé.
 * @param deck L'objet `Deck` dans lequel les cartes seront ajoutées.
 */
  void loadDeck (std::string nom, Deck&);

    /**
 * @brief Charge un joueur depuis un fichier CSV.
 *
 * Cette fonction charge l'état d'un joueur à partir d'un fichier CSV spécifié par le chemin. Le fichier doit contenir les
 * informations du joueur (nom, nombre d'actions, nombre de pièces, nombre d'achats, points de vie) ainsi que des chemins
 * vers plusieurs decks de cartes (main, défausse, pioche, cartes jouées, cartes achetées). Les informations sont extraites
 * du fichier et utilisées pour initialiser un objet `Joueur`, qui est ensuite retourné.
 *
 * Si le fichier n'est pas accessible ou est mal formé, la fonction ne fait aucune modification et retourne un joueur
 * avec des valeurs par défaut.
 *
 * @param chemin Le chemin vers le dossier contenant le fichier CSV du joueur. Le fichier CSV doit être nommé de manière
 *               appropriée (le nom du fichier est utilisé pour localiser les decks).
 *
 * @return Un objet `Joueur` initialisé avec les informations lues depuis le fichier CSV, incluant les decks associés.
 */
  Joueur loadJoueur (std::string nom);

    /**
 * @brief Charge tous les joueurs depuis un répertoire de fichiers.
 *
 * Cette fonction charge l'état de tous les joueurs présents dans un répertoire spécifique. Le répertoire doit contenir un
 * sous-dossier pour chaque joueur, et chaque sous-dossier doit contenir un fichier CSV contenant les informations du joueur,
 * ainsi que les chemins vers les decks associés. Chaque joueur est chargé à l'aide de la fonction `loadJoueur`, et les objets
 * `Joueur` ainsi créés sont ajoutés à un vecteur de joueurs.
 *
 * Si des sous-dossiers n'incluent pas de fichiers valides ou sont mal formés, ces joueurs ne seront pas chargés.
 *
 * @param joueurs Un vecteur de type `Joueur` dans lequel les joueurs chargés seront ajoutés. Ce vecteur est modifié directement
 *                par la fonction, qui y ajoute un objet `Joueur` pour chaque sous-dossier trouvé dans le répertoire des joueurs.
 */
  void loadJoueurs(std::vector<Joueur>&);

    /**
 * @brief Charge l'état du jeu depuis un répertoire de sauvegarde.
 *
 * Cette fonction charge l'état complet du jeu depuis un répertoire de sauvegarde spécifique. Le répertoire doit contenir des
 * fichiers et sous-dossiers organisés pour stocker les informations des joueurs, du plateau, et de l'état du jeu. Les
 * joueurs sont chargés depuis le répertoire "Joueurs", tandis que le plateau et les decks associés sont chargés depuis
 * le répertoire "Plateau". L'état global du jeu (numéro de tour, phase du jeu, joueur actuel, etc.) est également chargé.
 *
 * La fonction procède à l'initialisation du jeu, à la configuration du plateau avec les différents decks (provinces,
 * gold, silver, duchy, estate, copper, curse), et enfin à la mise en place des decks des royaumes. Une fois l'état du jeu
 * complètement chargé, la partie est prête à être reprise.
 */
  void loadJeu();

    /**
 * @brief Vérifie si un dossier de sauvegarde existe.
 *
 * Cette fonction vérifie si un dossier de sauvegarde, spécifié par le nom de la sauvegarde, existe dans le répertoire courant
 * de l'application. Le dossier de sauvegarde est identifié par le nom donné à l'objet `Save`. Si le dossier existe, la
 * fonction retourne `true`, sinon elle retourne `false`.
 *
 * @return `true` si le dossier de sauvegarde existe, `false` sinon.
 */
  bool exists();


};

#endif