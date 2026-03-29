#include <iostream>
#include <utility>
#include "../include/CarteRoyaume.h"
#include "../include/Jeu.h"
#include <iomanip>
#include <limits>

#include "../include/Carte.h"

CarteRoyaume::CarteRoyaume(int id_, std::string nom_,
                     int cost_, int nbCartes_, int nbActions_,
                     int nbGold_, int nbAchats_, bool attaque_, bool reaction_, std::string description_)
    : Carte(id_, std::move(nom_), cost_, Type::Royaume),
      nbCartes(nbCartes_), 
      nbActions(nbActions_), 
      nbGold(nbGold_), 
      nbAchats(nbAchats_),
      attaque(attaque_),
      reaction(reaction_),
      description(description_),
      effet(description.size() >= 22),
      revelee(false)

{
}


// Déclenche les effets d'une carte
void CarteRoyaume::trigger(Jeu& jeu) {

    //On applique les effets de la carte si personne ne doit réagir à une attaque
    if (jeu.getJoueurAttaque() == nullptr) {
        jeu.getQuiJoue().ajouterAchats(nbAchats);
        jeu.getQuiJoue().ajouterActions(nbActions);
        jeu.getQuiJoue().ajouterPieces(nbGold);
        jeu.getQuiJoue().piocher(nbCartes);
    }


    //on gère la défense dans le cas ou une carte attaque est jouée
    if (attaque == true) {
        std::string choix;
        //on attaque chaque joueur un par un
        for (Joueur& joueur : jeu.getJoueurs()) {
            // pas d'auto attaque
            if (joueur.getNom() != jeu.getQuiJoue().getNom()) {
                //initialement aucun joueur n'est protégé
                joueur.setProtege(false);
                //on met à jour le joueur cible de l'attaque
                jeu.setJoueurAttaque(&joueur);
                //on regarde s'il a une carte pour se defendre dans la main
                for (Carte* c : joueur.getHand().getCartes()) {
                    std::string royaume = c->getType() == Royaume ? "oui" : "non";
                    //si la carte est une carte reaction et qu'elle n'a pas déjà été utilisée
                    if (c->getReaction() && c->getType() == Royaume && !(c->getRevelee())) {
                        std::cout << "4" << std::endl;

                        CarteRoyaume* c2 = dynamic_cast<CarteRoyaume*>(c);
                        // on lui propose d'utiliser la carte réaction
                        while ((choix != "oui") and (choix != "non")) {
                            std::cout << "Joueur " << joueur.getNom() << ", voulez vous jouer " << c2->getNom() << " pour vous défendre ? "
                                                                                                                   "(oui ou non ) ? "<<std::endl;
                            std::cin >> choix;
                        }
                        if (choix == "oui") {
                            //on active l'effet de la carte défense'
                            c2->trigger(jeu);
                            break;
                        }
                    }

                }
            }
        }
        jeu.setJoueurAttaque(nullptr);
    }

    if (getNom() == "Atelier") // Elle marche
    {
        std::cout << "Veuillez choisir une carte d'un coût de 4 ou moins : " << std::endl;
        std::string c;
        bool carteValide = false;

        while (!carteValide) {
            std::cin >> c;
            for (int i = 0; i < jeu.getNbDeckRoyaumes(); i++) {

                if (c == jeu.getDecksRoyaume().at(i).getCartes().at(0)->getNom() &&
                    jeu.getDecksRoyaume().at(i).getCartes().at(0)->getCost() <= 4) {

                    jeu.getQuiJoue().getDefausse().ajouterCarte(jeu.getDecksRoyaume().at(i).prendreTopCarte());
                    carteValide = true;
                    break;  // On sort du for
                    }
            }
            if (!carteValide) {
                std::cout << "La carte choisie est trop chère ou n'est plus disponible. Veuillez en choisir une autre : " << std::endl;
            }
        }
    }
    if (getNom() == "Chapelle") // Elle marche
    {
        std::cout<<"Combien de cartes voulez vous obliterer de votre main ?"<<std::endl;
        int n=0;
        std::cin >> n;
        while (std::cin.fail() || n > jeu.getQuiJoue().getHand().getTaille()) { // si entree mauvaise
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrée invalide. Veuillez réessayer." << std::endl;
            std::cin >> n;
        }
        while (n>jeu.getQuiJoue().getHand().getTaille() and n<0)
        {
            std::cout<<"Veuillez entrer un nombre valide : "<<std::endl;
            std::cin>>n;
        }

        std::string choix;
        for (int i=0;i<n;i++)
        {
            bool carteTrouvee = false;
            Carte* c = nullptr;
            while (!carteTrouvee) {
                std::cout<<"Veuillez entrer le nom de la carte à oblitérer :("<< i+1 <<"/" << n<< ")"<<std::endl;
                std::cin>>choix;

                c=jeu.getQuiJoue().getHand().retirerCarte(choix);
                if (c!=nullptr) {
                    carteTrouvee = true;
                    delete c;
                }else {
                    std::cout << "Choix incorrect, réessayez \n";
                }
            }
        }

    }
    if (getNom() == "Festin")// elle marche
    {
        jeu.getQuiJoue().getCartesJouees().retirerCarte(this);
        std::cout<<"Veuillez choisir une carte d'un cout de 5 ou moins : "<<std::endl;
        std::string c;
        std::cin>>c;
        bool carteTrouvee= false;
        for (int i = 0; i < jeu.getNbDeckRoyaumes(); i++) {
            if (jeu.getDecksRoyaume().at(i).getTaille() > 0) {
                if (c == jeu.getDecksRoyaume().at(i).getCartes().at(0)->getNom()  && jeu.getDecksRoyaume().at(i).getCartes().at(0)->getCost() <= 5) {
                    jeu.getQuiJoue().getDefausse().ajouterCarte(jeu.getDecksRoyaume().at(i).prendreTopCarte());
                    carteTrouvee = true;
                    break;
                }
            }
        }
        if (!carteTrouvee) {
            std::cout << "Il n'y a plus de carte Atelier" << std::endl;
        }
    }
    if (getNom() == "Sorciere")
    {
        for (size_t i=0 ; i<jeu.getJoueurs().size() ; i++)
        {
            Joueur& j = jeu.getJoueurs()[i];
            if (j.getNom()!=jeu.getQuiJoue().getNom() && !j.estProtege())
            {
                if (jeu.getCurse().estVide())
                {
                    std::cout<<"il n'y a plus de malédictions"<<std::endl;
                }
                else
                {
                    jeu.getJoueurs().at(i).getDefausse().ajouterCarte(jeu.getPlateau().prendreCarte("Malediction"));
                }

            }
        }
    }
    if (getNom() == "Voleur") // elle marche
    {
        for (size_t  i=0 ; i<jeu.getJoueurs().size() ; i++)
        {
            Joueur& j = jeu.getJoueurs().at(i);
            if (j.getNom()!=jeu.getQuiJoue().getNom() && !(j.estProtege()))
            {
                if (jeu.getJoueurs().at(i).getPioche().estVide())// On met les carte de la defausse dans la pioche si la pioche est vide
                {
                    jeu.getJoueurs().at(i).defausseToPioche();
                }
                Carte* c1 = jeu.getJoueurs().at(i).getPioche().prendreTopCarte();  //on sort les 2 premières cartes de la pioche et on les stock dans des variaables temporaires

                if (jeu.getJoueurs().at(i).getPioche().estVide())
                {
                    jeu.getJoueurs().at(i).defausseToPioche();
                }
                Carte* c2 = jeu.getJoueurs().at(i).getPioche().prendreTopCarte();
                std::string n1 = c1->getNom();
                std::string n2 = c2->getNom();
                std::string reponse;

                if (c1->getType()!=Tresor and c2->getType()!=Tresor) // on vérifie qu'il y a au moins un trésor à voler
                {
                    std::cout<<"Il n'y a pas de trésor à voler"<<std::endl;
                    reponse="skip";
                }
                else
                {
                    std::cout<<"Choisissez une carte trésor à voler à "<< jeu.getJoueurs().at(i).getNom() << "parmi  ["<<n1<<"] et ["<<n2<<"] ou écrivez skip :"<<std::endl;
                    std::cin>>reponse;
                }

                while ((reponse !=n1 and reponse !=n2 and reponse !="skip") or (reponse==n1 and c1->getType()!=Tresor)or (reponse==n2 and c2->getType()!=Tresor)) // on vérifie que la reponse est cohérente
                {
                    std::cout<<"Veuillez rentrer une reponse valide"<<std::endl;
                    std::cin>>reponse;
                }

                if (reponse=="skip")
                {
                    jeu.getJoueurs().at(i).getDefausse().ajouterCarte(c1); // On défausse les 2 cartes si le joueur n'en vole pas
                    jeu.getJoueurs().at(i).getDefausse().ajouterCarte(c2);
                }
                if (reponse==n1)
                {
                    jeu.getJoueurs().at(i).getDefausse().ajouterCarte(c2); // on remet dans la defausse du joueur la carte qui n'a pas été choisie
                    jeu.getQuiJoue().getDefausse().ajouterCarte(c1);       // on met dans la defausse du joueur qui joue la carte volée
                }
                else if (reponse==n2)
                {
                    jeu.getJoueurs().at(i).getDefausse().ajouterCarte(c1);
                    jeu.getQuiJoue().getDefausse().ajouterCarte(c2);
                }

            }
        }
    }
    if (getNom() == "Cave")// elle marche
    {
        std::cout<<"Choisissez combien de carte vous souhaitez défausser"<<std::endl;
        int x;
        while (true) {    // On vérifie que la valeur est bien un entier
            std::cin >> x;
            if (std::cin.fail() or x>jeu.getQuiJoue().getHand().getTaille()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Entrée invalide. Veuillez entrer un entier : ";
            } else {
                break;
            }
        }
        for (int i=0;i<x;i++)
        {
            std::cout<<"Quelle carte voulez vous défausser ?"<<std::endl;
            bool carteTrouvee =false;
            std::string reponse;
            while (!carteTrouvee) {
                std::cin >> reponse;

                for (int j=0; j < jeu.getQuiJoue().getHand().getTaille();j++) {
                    if (jeu.getQuiJoue().getHand().getCartes().at(j)->getNom()==reponse)
                        {
                        jeu.getQuiJoue().getDefausse().ajouterCarte(jeu.getQuiJoue().getHand().retirerCarte(jeu.getQuiJoue().getHand().getCartes().at(j)));
                        carteTrouvee =true;
                        break;
                    }
                }if (!carteTrouvee)
                    {
                    std::cout << "Aucune carte avec ce nom trouvée. Veuillez entrer un nom valide de carte à défausser : " << std::endl;
                }
            }
        }
        jeu.getQuiJoue().piocher(x);
    }
    if (getNom() == "Harbinger")// elle marche
    {
        if (jeu.getQuiJoue().getDefausse().estVide())
        {
            std::cout<<"\033[36m\033[1m1Votre défausse est vide"<<std::endl;
        }
        else
        {
            jeu.getQuiJoue().getDefausse().afficher2("Défausse","\033[34m",true);
            int choix;
            while (true) { // On verifie que l'utilisateur rentre bien un entier valide
                std::cout << "\033[36m\033[1m1Veuillez entrer l'indice d'une carte de votre défausse que vous désirez placer au dessus de votre deck : ";
                if (std::cin >> choix) {
                    if (choix >= 0 && choix < jeu.getQuiJoue().getDefausse().getTaille() ) {
                        break;
                    } else {
                        std::cout << "\033[36m\033[1m1Entree invalide, veuillez ressayer." << std::endl;
                    }
                } else {
                    std::cout << "\033[36m\033[1m1Ce n'est pas un entier valide. Essayez à nouveau." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            jeu.getQuiJoue().getPioche().ajouterCarte(jeu.getQuiJoue().getDefausse().retirerCarte(choix));
        }
    }
    if (getNom() == "Marchand")
    {
        jeu.getQuiJoue().setMarchand(true);
    }
    if (getNom() == "Vassal")// elle marche
    {
        if (jeu.getQuiJoue().getPioche().estVide())
        {
            std::cout<<"Votre pioche est vide"<<std::endl;
        }
        else
        {
            std::string nomTopCarte;
            nomTopCarte=jeu.getQuiJoue().getPioche().getCartes().at(jeu.getQuiJoue().getPioche().getTaille()-1)->getNom();
            std::cout<<"Votre carte en haut du deck est un "<<nomTopCarte<<std::endl;

            if (jeu.getQuiJoue().getPioche().getCartes().at(jeu.getQuiJoue().getPioche().getTaille()-1)->getType()==Royaume) // si la top carte est une crate royaume on demande au joueur s'il veut la jouer
            {
                std::cout<<"Voulez vous jouer cette carte actions?\n Taper 'Oui' ou 'Non' :"<<std::endl;
                std::string reponse;
                std::cin>>reponse;
                if (reponse=="Oui")
                {
                    Carte* c1 = jeu.getQuiJoue().getPioche().getCartes().at(jeu.getQuiJoue().getPioche().getTaille()-1);
                    CarteRoyaume* carteRoyaume0 = dynamic_cast<CarteRoyaume*>(c1);
                    jeu.getQuiJoue().piocher(1);   //il pioche et joue la carte
                    jeu.getQuiJoue().jouerCarte(nomTopCarte);
                    jeu.getQuiJoue().ajouterActions(1);
                    carteRoyaume0->trigger(jeu);
                }
                else
                {
                    std::cout<<"Vous avez choisi de ne pas jouer la carte"<<std::endl;
                }
            }
        }

    }
    if (getNom()=="Bureaucrate") // marche mais comme on pioche aun debut du tour pas tres utile
    {
        jeu.getQuiJoue().getHand().ajouterCarte(jeu.getSilver().prendreTopCarte());
        for (size_t i=0;i<jeu.getJoueurs().size();i++) // Appliquer l'effet a tous les autres joueurs
        {
            Joueur& j = jeu.getJoueurs()[i];
            if (j.getNom()!=jeu.getQuiJoue().getNom() && !j.estProtege())
            {
                if(jeu.getJoueurs().at(i).hasVictoire()) // verifier que le joueur a une carte victoire dans la main
                {
                    for (int ii=0;ii<jeu.getJoueurs().at(i).getHand().getTaille(); ii++) // Parcourir la main
                    {
                        if (jeu.getJoueurs().at(i).getHand().getCartes().at(ii)->getType()==Victoire) // chercher la premiere carte victoire dans la main
                        {
                           jeu.getJoueurs().at(i).getPioche().ajouterCarte(jeu.getJoueurs().at(i).getHand().retirerCarte(ii));  // retirer la carte de la main et la mettre au dessus de la pioche
                        }
                    }
                }
                else
                {
                    std::string x = "Main du joueur "+jeu.getJoueurs().at(i).getNom();
                    jeu.getJoueurs().at(i).getHand().afficher2(x,"\033[36m\033[1m");
                }
            }
        }
    }
    if (getNom()=="Milice")
    {
        for (size_t i=0;i<jeu.getJoueurs().size();i++)
        {
            Joueur& j = jeu.getJoueurs()[i];
            if (j.getNom()!=jeu.getQuiJoue().getNom() && !j.estProtege())
            {
                while (jeu.getJoueurs().at(i).getHand().getTaille()>3)
                {
                    jeu.getJoueurs().at(i).getHand().afficher2("Votre main","\033[36m\033[1m");
                    std::cout<<"\033[36m\033[1m"<<jeu.getJoueurs().at(i).getNom()<<"Quelle carte voulez vous défausser ?"<<std::endl;
                    bool carteTrouvee =false;
                    std::string reponse;
                    while (!carteTrouvee) {
                        std::cin >> reponse;

                        for (int j=0; j < jeu.getJoueurs().at(i).getHand().getTaille();j++) {
                            if (jeu.getJoueurs().at(i).getHand().getCartes().at(j)->getNom()==reponse)
                            {
                                jeu.getJoueurs().at(i).getDefausse().ajouterCarte(jeu.getJoueurs().at(i).getHand().retirerCarte(jeu.getJoueurs().at(i).getHand().getCartes().at(j)));
                                carteTrouvee =true;
                                break;
                            }
                        }if (!carteTrouvee)
                        {
                            std::cout << "Aucune carte avec ce nom trouvée. Veuillez entrer un nom valide de carte à défausser : " << std::endl;
                        }
                    }
                }
            }
        }
    }
    if (nom == "Douve") {
        //utilisée pour la défense
        if (jeu.getJoueurAttaque()!=nullptr) {
            jeu.getJoueurAttaque()->setProtege(true);
            revelee = true;
        }
    }
    if (nom == "Preteur") {
        if (jeu.getQuiJoue().getHand().getCarte("Cuivre",Tresor)) {
            std::string choix;
            std::cout << "Voulez vous defausser un cuivre pour 3 pièces d'or (oui ou non) ? ";
            std::cin >> choix;
            if (choix=="oui") {
                jeu.getQuiJoue().getDefausse().ajouterCarte(jeu.getQuiJoue().getHand().retirerCarte("Cuivre"));
                jeu.getQuiJoue().ajouterPieces(3);
            }
        }
    }
    if (nom == "Braconnier") {
        int n = jeu.getPlateau().getNbVide();
        bool choixValide = false;
        std::string choix;
        if (n>5) {
            n=5;
        }
        for (int i = 0; i < n; i++) {
            choixValide = false;
            while (!choixValide) {
                std::cout << std::endl;
                jeu.getQuiJoue().getHand().afficher2("votre main","\033[36m\033[1m");
                std::cout << "Choisissez une carte à défausser ("<< i+1<<"/" << n<<") : " << std::endl;

                std::cin >> choix;

                Carte* c = jeu.getQuiJoue().getHand().retirerCarte(choix);
                if (c!=nullptr) {
                    jeu.getQuiJoue().getDefausse().ajouterCarte(c);
                    choixValide = true;
                }else {
                    std::cout << std::endl<< "Carte introuvable, réessayez : ";
                }
            }
        }
    }
    if (nom == "Renovation"){ // elle marche

        std::string choix;
        bool carteTrouvee = false;
        Carte* c = nullptr;
        while (!carteTrouvee) {
            std::cout<<"Choisissez une carte que vous voulez obliterer puis vous pourrez choisir une carte d'un coût de 2 de plus"<<std::endl;
            std::cin>>choix;

            c=jeu.getQuiJoue().getHand().retirerCarte(choix);
            if (c!=nullptr) {
                carteTrouvee = true;
                delete c;
            }else {
                std::cout << "Choix incorrect, réessayez \n";
            }
        }
        bool cartePrise=false;
        std::string choix2;
        while (!cartePrise)
        {
            std::cout<<"Choisissez une carte qui vaut maximum "<<c->getCost()+2<<" €"<<std::endl;
            std::cin>>choix2;
            if (jeu.getPlateau().isCardOnBoard(choix2) and (c->getCost()+2 >= jeu.getPlateau().getCarte(choix2)->getCost())) // on verifie que la carte existe sur le plateau et son cout est de maximum 2 de plus que la carte obliteree
            {
                jeu.getQuiJoue().getDefausse().ajouterCarte(jeu.getPlateau().prendreCarte(choix2)); //On prend la carte et la met dans la défausse du joueur
                cartePrise=true;
            }
            else
            {
                std::cout<<"la carte n'existe pas ou est trop chere"<<std::endl;
            }
        }
    }
    if (nom == "Salle_trone"){ // elle marche
        std::string choix;
        bool carteTrouvee = false;
        Carte* c = nullptr;
        while (!carteTrouvee) {
            std::cout<<"Choisissez une carte action que vous voulez jouer 2 fois"<<std::endl;
            std::cin>>choix;

            c=jeu.getQuiJoue().getHand().retirerCarte(choix);
            jeu.getQuiJoue().getCartesJouees().ajouterCarte(c);
            CarteRoyaume* carteRoyaume = dynamic_cast<CarteRoyaume*>(c);
            carteRoyaume->trigger(jeu);
            carteRoyaume->trigger(jeu);
            if (c!=nullptr) {
                carteTrouvee = true;
            }else {
                std::cout << "Choix incorrect, réessayez \n";
            }
        }
    }
    if (nom == "Bandit"){// marche
        jeu.getQuiJoue().getDefausse().ajouterCarte(jeu.getPlateau().getGold().prendreTopCarte()); // Donne un or au joueur


        for (size_t  i=0 ; i<jeu.getJoueurs().size() ; i++)
            {
                Joueur& j = jeu.getJoueurs().at(i);
                if (j.getNom()!=jeu.getQuiJoue().getNom() && !(j.estProtege()))
                {
                    if (jeu.getJoueurs().at(i).getPioche().estVide())// On met les carte de la defausse dans la pioche si la pioche est vide
                    {
                        jeu.getJoueurs().at(i).defausseToPioche();
                    }
                    Carte* c1 = jeu.getJoueurs().at(i).getPioche().prendreTopCarte();  //on sort les 2 premières cartes de la pioche et on les stock dans des variaables temporaires

                    if (jeu.getJoueurs().at(i).getPioche().estVide())
                    {
                        jeu.getJoueurs().at(i).defausseToPioche();
                    }
                    Carte* c2 = jeu.getJoueurs().at(i).getPioche().prendreTopCarte();
                    std::string n1 = c1->getNom();
                    std::string n2 = c2->getNom();

                    std::cout<<"le joueur "<<jeu.getJoueurs().at(i).getNom()<<" a les cartes "<<n1<<" et "<<n2<<std::endl;
                    if ((n1=="Or" or n1=="Argent") and (n2=="Or" or n2=="Argent") ) // Cas ou il y a deux trésor obliterable
                    {

                        std::srand(std::time(0));
                        bool randomBool = std::rand() % 2;
                        if(randomBool)
                        {
                            std::cout<<"La carte oblitére est "<<n1<<std::endl;
                            jeu.getJoueurs().at(i).getDefausse().ajouterCarte(c2);
                            delete c1;
                        }
                        else
                        {
                            std::cout<<"La carte oblitére est "<<n2<<std::endl;
                            jeu.getJoueurs().at(i).getDefausse().ajouterCarte(c1);
                            delete c2;
                        }
                    }
                    else if ((n1=="Or" or n1=="Argent"))
                    {
                        std::cout<<"La carte oblitére est "<<n1<<std::endl;
                        jeu.getJoueurs().at(i).getDefausse().ajouterCarte(c2);
                        delete c1;
                    }
                    else if ((n2=="Or" or n2=="Argent"))
                    {
                        std::cout<<"La carte oblitére est "<<n2<<std::endl;
                        jeu.getJoueurs().at(i).getDefausse().ajouterCarte(c1);
                        delete c2;
                    }
                    else
                    {
                        std::cout<<"Aucune carte oblitere"<<std::endl;
                    }




                }
            }
    }
    if (nom == "Salle_Conseil")
    {
        for (size_t  i=0 ; i<jeu.getJoueurs().size() ; i++)
        {
            if (jeu.getJoueurs().at(i).getNom()!=jeu.getQuiJoue().getNom())
            {
                jeu.getJoueurs().at(i).piocher(1);
            }
        }
    }
    if (nom == "Bibliotheque")
    {
        while(jeu.getQuiJoue().getHand().getTaille()<7)
        {
            if (jeu.getQuiJoue().getPioche().estVide())// On met les carte de la defausse dans la pioche si la pioche est vide
            {
                jeu.getQuiJoue().defausseToPioche();
            }
            Carte* c1=jeu.getQuiJoue().getPioche().prendreTopCarte();
            if (c1->getType()==Royaume) // si le joueur pioche une carte royaume, il peut la defausser
            {
                std::string choix;
                while(choix!="1" && choix!="2")
                {
                    std::cout<<"Vous avez pioché la carte "<<c1->getNom()<<", voulez vous la défausser ou la garder?\n1-Defausser\n2-Garder\nChoix :"<<std::endl;
                    std::cin>>choix;
                }
                if(choix=="1")
                {
                    jeu.getQuiJoue().getDefausse().ajouterCarte(c1);
                }
                else
                {
                    jeu.getQuiJoue().getHand().ajouterCarte(c1);
                }

            }
            else{jeu.getQuiJoue().getHand().ajouterCarte(c1);}
        }
    }
    if (nom == "Mine")
    {
        if (!jeu.getQuiJoue().hasTresor())
        {

        }
        else
        {
            Carte* c = nullptr;
            std::string choix;
            while (c == nullptr)
            {

                std::cout<<"Quel trésor voulez vous ameliorer?"<<std::endl;
                std::cin>>choix;

                c = jeu.getQuiJoue().getHand().getCarte(choix);
                if (c==nullptr)
                {
                    std::cout<<"carte non trouvée"<<std::endl;
                }
                else
                {
                    delete jeu.getQuiJoue().getHand().retirerCarte(choix);
                    if (c->getNom()=="Cuivre")
                    {
                        jeu.getQuiJoue().getHand().ajouterCarte(jeu.getPlateau().getSilver().prendreTopCarte());
                    }
                    if (c->getNom()=="Argent")
                    {
                        jeu.getQuiJoue().getHand().ajouterCarte(jeu.getPlateau().getGold().prendreTopCarte());
                    }
                    if (c->getNom()=="Or")
                    {
                        jeu.getQuiJoue().getHand().ajouterCarte(jeu.getPlateau().getGold().prendreTopCarte());
                    }
                }
            }
        }
    }
    if (nom == "Sentinelle")
    {
        if (jeu.getQuiJoue().getPioche().estVide())// On met les carte de la defausse dans la pioche si la pioche est vide
        {
            jeu.getQuiJoue().defausseToPioche();
        }
        Carte* c1 = jeu.getQuiJoue().getPioche().prendreTopCarte();// Récupérer les 2 premières cartes du deck du joueur
        if (jeu.getQuiJoue().getPioche().estVide())// On met les carte de la defausse dans la pioche si la pioche est vide
        {
            jeu.getQuiJoue().defausseToPioche();
        }
        Carte* c2 = jeu.getQuiJoue().getPioche().prendreTopCarte();


        std::cout<<"Les deux premières cartes de votre deck sont :\n";
        std::cout<<"1: "<<c1->getNom()<<"\n";
        std::cout<<"2: "<<c2->getNom()<<"\n";

        std::string choix1, choix2;
        bool choixValide1 = false, choixValide2 = false;

        // Demander au joueur s'il veut défausser ou trash chaque carte
        while (!choixValide1) {
            std::cout << "Voulez-vous défausser, Obliterer ou garder la carte " << c1->getNom() << " ? \n[1]-Défausser\n[2]-Obliterer \n[3]Garder\nChoix :";
            std::cin >> choix1;
            if (choix1 == "1") {
                jeu.getQuiJoue().getDefausse().ajouterCarte(c1);
                choixValide1 = true;
            } else if (choix1 == "2") {
                delete c1;
                choixValide1 = true;
            } else if (choix1 == "3") {
                choixValide1 = true;
            } else {
                std::cout << "Choix invalide. Réessayez.\n";
            }
        }

        while (!choixValide2) {
            std::cout << "Voulez-vous défausser, Obliterer ou garder la carte " << c2->getNom() << " ? \n[1]-Défausser\n[2]-Obliterer \n[3]Garder\nChoix :";
            std::cin >> choix2;
            if (choix2 == "1") {
                jeu.getQuiJoue().getDefausse().ajouterCarte(c2);
                choixValide2 = true;
            } else if (choix2 == "2") {
                delete c2;
                choixValide2 = true;
            } else if (choix2 == "3") {
                choixValide2 = true;
            } else {
                std::cout << "Choix invalide. Réessayez.\n";
            }
        }
        if(choix1=="3" and choix2=="3" )
        {
            bool choixvalide=false;
            std::string choix;
            while(!choixvalide)
            {
                std::cout<<"Quelle carte voulez vous avoir en haut de la pioche ?\n [1]-"<<c1->getNom()<<"\n-[2]"<<c2->getNom()<<"\nchoix :"<<std::endl;
                std::cin>>choix;
                if (choix=="1")
                {
                    jeu.getQuiJoue().getPioche().ajouterCarte(c2);
                    jeu.getQuiJoue().getPioche().ajouterCarte(c1);
                    choixvalide=true;
                }
                else if (choix=="2")
                {
                    jeu.getQuiJoue().getPioche().ajouterCarte(c1);
                    jeu.getQuiJoue().getPioche().ajouterCarte(c2);
                    choixvalide=true;
                }
                else {std::cout<<"Choix invalide, veuillez ressayer"<<std::endl;}
            }
        }
        else if (choix1=="3")
        {
            jeu.getQuiJoue().getPioche().ajouterCarte(c1);
        }
        else if (choix2=="3")
        {
            jeu.getQuiJoue().getPioche().ajouterCarte(c2);
        }
    }
        if (nom == "Artisan") // marche
        {
            std::string choix;
            bool choixValide=false;
            while (!choixValide) {
                std::cout << "Choisissez une carte sur le plateau d'un coup de 5 ou moins ou ecrivez skip\nChoix :"<<std::endl;
                std::cin >> choix;
                if (jeu.getPlateau().isCardOnBoard(choix))
                {
                    if(jeu.getPlateau().getCarte(choix)->getCost()<=5)
                    {
                        jeu.getQuiJoue().getDefausse().ajouterCarte(jeu.getPlateau().prendreCarte(choix)); // retire la carte du plateau et l'ajoute à la main
                        choixValide=true;
                    }

                }
                else if (choix=="skip")
                {
                    choixValide=true;
                }
                else{std::cout<<"carte introuvable ou trop chere"<<std::endl;}

            }
            bool reponseValide=false;
            std::string choix2;
            while (!reponseValide)
            {
                std::cout<<"choisissez une carte de votre main à mettre dans votre deck"<<std::endl;
                std::cin>>choix2;
                for (int i=0; i<jeu.getQuiJoue().getHand().getTaille();i++)
                {
                    if(jeu.getQuiJoue().getHand().getCartes().at(i)->getNom()==choix2)
                    {
                        jeu.getQuiJoue().getDefausse().ajouterCarte(jeu.getQuiJoue().getHand().retirerCarte(choix2));
                        reponseValide=true;
                        break;
                    }
                }
                std::cout<<"carte introuvable, veuillez ressayer"<<std::endl;
            }

        }




}

int CarteRoyaume::getNbCartes()
{
    return nbCartes;
}
int CarteRoyaume::getNbGold()
{
    return nbGold;
}
int CarteRoyaume::getNbAchats()
{
    return nbAchats;
}
int CarteRoyaume::getNbActions()
{
    return nbActions;
}
bool CarteRoyaume::getEffet()
{
    return effet;
}
std::string CarteRoyaume::getDescription() const
{
    return description;
}

int CarteRoyaume::getValue() const{
    return 0;
}

void CarteRoyaume::afficherDetail() const {
    std::cout <<std::endl<< "Carte Royaume : ["<<getNom()<< "]"<< std::endl
    <<(nbCartes > 0 ? "Piocher +"+std::to_string(nbCartes) + "\n": "")
    <<(nbActions > 0 ? "Actions +"+std::to_string(nbActions) + "\n": "")
    <<(nbGold > 0 ? "Gold +"+std::to_string(nbGold)+" €" + "\n": "")
    <<(nbAchats > 0 ? "Achats +"+std::to_string(nbAchats) + "\n": "")
    <<"Coût : "<<getCost()<<" € "<<std::endl;

}

void CarteRoyaume::afficher() const {

    std::cout << std::endl << "\033[31m┌----------------┐" << std::endl;
    std::cout << "|    " << std::left << std::setw(11) << getNom() << " |" << std::endl;
    std::cout << "|-----┐----------|" << std::endl;
    std::cout << "| "  << getCost() << " € |          |" << std::endl;
    std::cout << "└-----┘----------┘\033[0m" << std::endl;
}

bool CarteRoyaume::getAttaque() const{
    return attaque;
}

bool CarteRoyaume::getReaction() const{
    return reaction;
}

bool CarteRoyaume::getRevelee() const{
    return revelee;
}

void CarteRoyaume::setRevelee(bool b) {
    revelee=b;
}

