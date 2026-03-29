#include "../include/Controlleur.h"
#include "../include/Carte.h"
#include <fstream>
#include <random>
#include<algorithm>
#include "../include/Util.h"
#include "../include/Save.h"
#include <climits>


Controlleur::Controlleur(View& vue_, Jeu& jeu_) : vue(vue_), jeu(jeu_) {
}

void Controlleur::demanderAchat() {
  bool premierAffichage = true; // Indique si c'est la première entrée dans la boucle

  // On demande les actions tant que le joueur a des achats disponibles
  while (jeu.getQuiJoue().getNbAchats() > 0) {
    // Afficher le jeu la première fois
    if (premierAffichage) {
      vue.afficherJeu(jeu);
      premierAffichage = false;
    }

    // Afficher les options disponibles
    vue.afficherDemandeAchat();
    vue.afficherDemandeDescription();

    std::string choix;
    std::cin >> choix;

    // Gestion de la commande "skip" pour passer le tour
    if (choix == "skip") {
      return;
    }

    // Gestion de la commande "help" à tout moment
    if (choix.find("help") == 0) {
      castHelp(choix);
      std::string meilleurMatch = Util::closestEl(choix, jeu.getNomCartesJeu());

      if (Util::diff(meilleurMatch, choix) < 3) {
        choix = meilleurMatch;
      } else {
        std::cout << "Suggestion : Essayez \"" << meilleurMatch << "\"" << std::endl;
      }

      demanderDescription(choix);
      continue; // Retour au début de la boucle principale
    }

    // Trouver la carte correspondante au choix
    std::string meilleurMatch = Util::closestEl(choix, jeu.getNomCartesJeu());
    if (meilleurMatch != choix) {
      std::cout << "Suggestion : Essayez \"" << meilleurMatch << "\"" << std::endl;
      vue.afficherDemandeAchat();
      vue.afficherDemandeDescription();
      std::cin >> choix;

      if (choix == "skip") {
        return;
      }
    }

    // Vérifier si la carte est sur le plateau
    if (!jeu.getPlateau().isCardOnBoard(choix)) {
      vue.carteIntrouvable();
      continue; // Retour au début de la boucle principale
    }

    // Tenter l'achat de la carte
    if (jeu.acheterCarte(choix)) {
      // Afficher le jeu uniquement lorsqu'une carte est achetée
      vue.afficherJeu(jeu);
      jeu.updatePV();
    } else {
      vue.fondsInsuffisants();
    }
  }
}



void Controlleur::demanderAction()
{
  while (jeu.getQuiJoue().hasActions() && jeu.getQuiJoue().getNbActions()>0)
  {
    vue.afficherJeu(jeu);
    vue.afficherDemandeAction();

    std::string choix;
    std::cin >> choix;

    if (choix =="skip") {
      return;
    }
    else
    {

      bool match = false;

      while (!match) {
        //On tente de marcher la saisie
        std::string meilleurMatch = Util::closestEl(choix,jeu.getQuiJoue().getHand().getNomCartes());

        if (meilleurMatch == choix) {
          choix = meilleurMatch; // Attribuer le meilleur match
          match = true;
        } else {
          std::cout << "Suggestion : Essayez \"" << meilleurMatch <<  std::endl;
          vue.afficherDemandeAction();
          std::cin >> choix;
        }
      }
      //La carte existe alors dans le jeu

      //Si le joueur a dans sa main l'action demandée
      //On va récupérer la carte
      CarteRoyaume* carte_royaume0=nullptr;
      Carte* carteDemandee = nullptr;

      while (carteDemandee == nullptr) {
        //on parcourt la main du joueur à sa recherche
        carteDemandee = jeu.getQuiJoue().getHand().getCarte(choix,Royaume);
        //si la carte a été trouvée
        if (carteDemandee != nullptr) {
          //on cast en carte royaume
          carte_royaume0 = dynamic_cast<CarteRoyaume*>(carteDemandee);
          //le joueur joue la carte

          jeu.getQuiJoue().jouerCarte(choix);
          //on applique les effets de la carte royaume

          carte_royaume0->trigger(jeu);

          //on met à jour les pv
          jeu.updatePV();
        } else {
          std::cout << "Vous n'avez pas la carte, réessayez :" <<  std::endl;
        }
      }
    }
  }
}

void Controlleur::demanderTresors() {
  std::string choix;

  while (jeu.getQuiJoue().hasTresor()) {
    // Afficher uniquement une fois le jeu au début du tour
    vue.afficherJeu(jeu);
    bool afficherJeu = false; // Contrôle si le jeu doit être réaffiché

    while (true) {
      vue.afficherDemandeTresor();
      std::cin >> choix;

      if (choix == "*") {
        // Jouer tous les trésors disponibles
        jeu.getQuiJoue().jouerTresor();
        afficherJeu = true;
        break; // Quitte la boucle interne pour réafficher le jeu
      }
      else if (choix == "skip") {
        // Quitter la phase des trésors
        return;
      }
      else if (!jeu.getQuiJoue().hasTresor(choix)) {
        // Carte introuvable, afficher un message d'erreur
        vue.carteIntrouvable();
      }
      else {
        // Jouer la carte spécifique
        jeu.getQuiJoue().jouerCarte(choix);
        afficherJeu = true;
        break; // Quitte la boucle interne pour réafficher le jeu
      }
    }

    // Réafficher le jeu uniquement si une action valide a été effectuée
    if (afficherJeu) {
      vue.afficherJeu(jeu);
    }
  }
}




void Controlleur::choisirCartesDepart(){

  std::vector<std::string> toutesLesCartes = Util::getCartesRoyaumesFromCsv();

  for (int i = 0; i < jeu.getNbDeckRoyaumes(); i++) {
    int choix;
    Deck deck = Deck();
    vue.afficherMenuChoixCartes(toutesLesCartes);
    std::cin >> choix;
    Carte* c = Util::strToCarte(toutesLesCartes.at(choix));
    auto* carte_royaume = dynamic_cast<CarteRoyaume*>(c);

    toutesLesCartes.erase(toutesLesCartes.begin()+choix);


    for  (int i = 0; i < jeu.getNbCartesRoyaumes(); i++) {
      deck.ajouterCarte(c);
      c = new CarteRoyaume(*carte_royaume);
    }
    jeu.ajouterDeckRoyaume(deck);
  }
}

//Initialise un palteau par defaut depuis un fichier
void Controlleur::setDefautCartesDepart(){

  std::vector<std::string> toutesLesCartes = Util::getCartesRoyaumesFromCsv();
  //Pour le nombres de decks royaume du plateau
  for (int i = 0; i < jeu.getNbDeckRoyaumes(); i++) {
    Deck deck = Deck();

    int max=toutesLesCartes.size()-1;
    std::random_device rd;  // Obtient une source d'entropie pour la graine
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, max);
    int random_number = distrib(gen);
    //On crée une carte depuis une ligne d'attributs
    Carte* c = Util::strToCarte(toutesLesCartes.at(random_number));
    CarteRoyaume* carte_royaume = dynamic_cast<CarteRoyaume*>(c);
    //La carte est choisie donc on la retire du vector
    toutesLesCartes.erase(toutesLesCartes.begin()+random_number);

    //On  crée et on ajoute le nombre d'exemplaires identiques souhaité dans une pile du plateau
    for  (int i = 0; i < jeu.getNbCartesRoyaumes(); i++) {
      deck.ajouterCarte(c);
      c = new CarteRoyaume(*carte_royaume);
    }

    jeu.ajouterDeckRoyaume(deck);

  }
}


void Controlleur::lancerMenu() {
  //On crée un objet sauvegarde pour restaurer une partie si besoin
  Save save = Save(jeu,"Save");
  std::string choix;
  vue.afficherMenu();
  std::cin >> choix;
  Save rsave = Save(jeu,"resetSave");


  int choix_;
  //tant que le choix est incorrect
  while (true) {
    try {
      choix_=std::stoi(choix);
      break;
    }catch(const std::invalid_argument&) {
      vue.afficherMenu();
      std::cin >> choix;
    }
  }
  switch (choix_) {
    case 1:
      // Vérifie si les joueurs sont déjà choisis, sinon lance la méthode pour choisir les joueurs
        if (jeu.getJoueurs().empty()) {
          choixDesJoueurs();
        }
        // Vérifie si les decks du royaume sont vides, sinon initialise les cartes par défaut
        if (jeu.getDecksRoyaume().empty()) {
          jeu.init();
          setDefautCartesDepart();
        }
        //On crée une sauvegarde du jeu si les joueurs veulent rejouer
        rsave.saveJeu();
        break;
    case 2:
      // Vérifie si les joueurs sont déjà choisis, sinon lance la méthode pour choisir les joueurs
        if (jeu.getJoueurs().empty()) {
          choixDesJoueurs();
        }
      jeu.init();
      choisirCartesDepart();
      lancerMenu();
      break;
    case 3:
      if (save.exists()) {
        save.loadJeu();
      }
    else {
      std::cout<<"Sauvegarde introuvable" << std::endl;
      lancerMenu();
    }
      break;
    default:
      std::cout << "Choix invalide, essayez à nouveau.\n";
      lancerMenu();
      break;
    }
  lancerTour();
}

//On lance le jeu
void Controlleur::lancerTour() {
  Save save = Save(jeu,"Save");
  jeu.initNomCartes();
  while (!jeu.fin()) {
    save.saveJeu();
    jeu.lancerTour();
    demanderAction();
    jeu.nextPhase();
    demanderTresors();
    jeu.nextPhase();
    demanderAchat();
    jeu.nextPhase();
  }
  vue.afficherFin(jeu);
  menuFin();
}


void Controlleur::choixDesJoueurs() {
  int nbJoueurs;
  bool saisieIsValide = false;
  std::cout << "Combien de joueurs souhaitez-vous créer ? ";
  while(!saisieIsValide) {
    if (std::cin >> nbJoueurs) {
      saisieIsValide = true;
    }
    if (!saisieIsValide) {
      std::cout << std::endl <<"Saisie invalide, réessayez :";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  while (nbJoueurs < 2) {
    std::cout << "Il faut au moins 2 joueurs pour jouer. Réessayez : ";
    std::cin >> nbJoueurs;
  }

  std::vector<std::string> nomsJoueurs;
  for (int i = 1; i <= nbJoueurs; ++i) {
    std::string choix;
    vue.afficherChoixJoueurs(i);

    while (true) {
      std::cin >> choix;
      // Vérification si le nom est déjà pris
      if (std::find(nomsJoueurs.begin(), nomsJoueurs.end(), choix) != nomsJoueurs.end()) {
        std::cout << std::endl << "Nom déjà pris, réessayez : ";
      } else {
        nomsJoueurs.push_back(choix);
        Joueur joueur = Joueur(choix);
        jeu.ajouterJoueur(joueur);
        break;
      }
    }
  }

  std::cout << "Tous les joueurs ont été ajoutés !" << std::endl;
}


//renvoie nom si s est de la forme help(nom)
void Controlleur::castHelp(std::string &s) {
  std::string result;

  if (s.substr(0, 5) == "help(") {
    size_t startPos = s.find('(');

    size_t endPos = s.find(')', startPos);

    if (startPos != std::string::npos && endPos != std::string::npos && endPos > startPos) {
      result = s.substr(startPos + 1, endPos - startPos - 1);
    }
  }
  s=result;
}

//renvoie la description de la carte nommée nom
void Controlleur::demanderDescription(std::string & nom) {
  Carte* c = jeu.getPlateau().getCarte(nom);
  CarteRoyaume* c1 = nullptr;
  if (c!=nullptr) {
    c1 = dynamic_cast<CarteRoyaume*> (jeu.getPlateau().getCarte(nom));
  }
  vue.afficherDescription(c1);
}


void Controlleur::menuFin() {
  Save rSave = Save(jeu,"resetSave");
  int choix;
  while (!(std::cin >> choix)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Entrée invalide, réessayez : " << std::endl;
  }  switch (choix) {
    case 1:
      jeu.reset();
    rSave.loadJeu();
    for (Joueur& j : jeu.getJoueurs()) {
      j.getPioche().shuffle();
    }
    lancerTour();
    break;
    case 2:
      jeu.reset();
      lancerMenu();
      break;
    default:
      break;
  }
}