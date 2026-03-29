#ifndef __Carte_h__
#define __Carte_h__
#include <string>

/**
 * @enum Type
 * @brief Représente les différents types de cartes dans le jeu.
 */
enum Type {
    Tresor,  ///< Carte de type Trésor, génère des ressources.
    Victoire, ///< Carte de type Victoire, utilisée pour compter les points.
    Royaume   ///< Carte de type Royaume, fournit des effets variés.
};

/**
 * @class Carte
 * @brief Classe abstraite.
 * 
 * La classe Carte est une classe de base abstraite qui définit les propriétés
 * et comportements de toutes les cartes du jeu. Elle est destinée à être
 * dérivée par des classes spécifiques pour chaque type de carte.
 */
class Carte {
protected:
    int id;              ///< Identifiant de chaque carte.
    std::string nom;     ///< Nom de la carte.
    int cost;            ///< Coût en pièces de la carte.
    Type type;           ///< Type de la carte (Trésor, Victoire ou Royaume).

public:
    /**
     * @brief Constructeur de la classe Carte.
     * 
     * @param id Identifiant unique de la carte.
     * @param nom Nom de la carte.
     * @param cost Coût de la carte.
     * @param type Type de la carte.
     */
    Carte(int id, std::string nom, int cost, Type type);

    virtual bool operator==(const Carte& other) const;

    const std::string& getNom() const;


    int getCost() const;

    Type getType() const;

    int getId() const;

    void setNom(const std::string& nom);

    void setId(int id);

    /**
     * @brief Affiche un résumé de la carte.
     */
    virtual void afficher() const;

    /**
     * @brief Affiche les détails spécifiques de la carte.
     */
    virtual void afficherDetail() const = 0;

    /**
     * @brief Retourne le nombre de cartes supplémentaires offertes pour les cartes actions.
     * 
     * @return Nombre de cartes supplémentaires.
     */
    virtual int getNbCartes() = 0;

    /**
     * @brief Retourne le nombre d'actions supplémentaires offertes pour les cartes actions.
     * 
     * @return Nombre d'actions supplémentaires.
     */
    virtual int getNbActions() = 0;

    /**
     * @brief Retourne le nombre de pièces supplémentaires offertes pour les cartes actions.
     * 
     * @return Nombre de pièces supplémentaires.
     */
    virtual int getNbGold() = 0;

    /**
     * @brief Retourne le nombre d'achats supplémentaires offerts pour les cartes actions.
     * 
     * @return Nombre d'achats supplémentaires.
     */
    virtual int getNbAchats() = 0;

    /**
     * @brief Retourne la valeur de la carte.
     * 
     * @return Valeur de la carte.
     */
    virtual int getValue() const = 0;

    /**
     * @brief Indique si la carte est une carte d'attaque.
     * 
     * @return `true` si la carte est une carte d'attaque, `false` sinon.
     */
    virtual bool getAttaque() const;

    /**
     * @brief Indique si la carte est une carte de réaction.
     * 
     * @return `true` si la carte est une carte de réaction, `false` sinon.
     */
    virtual bool getReaction() const;

    /**
     * @brief Indique si la carte réaction a été révélée lors du tour.
     * 
     * @return `true` si la carte est révélée, `false` sinon.
     */
    virtual bool getRevelee() const;

    /**
     * @brief Définit si la carte réaction a été révélée lors d'un tour.
     * 
     * @param revelee État de révélation de la carte.
     */
    virtual void setRevelee(bool revelee);

    /**
     * @brief Retourne la description de la carte.
     * 
     * @return Description de la carte.
     */
    virtual std::string getDescription() const;

    /**
     * @brief Destructeur virtuel de la classe Carte.
     */
    virtual ~Carte() = default;
};

#endif
