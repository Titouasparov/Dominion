#include "../include/View.h"

#include <CarteTresor.h>
#include <CarteVictoire.h>

#include "CarteRoyaume.h"
#include <iomanip>

#include "../include/Jeu.h"

View::View(Controlleur* controlleur_){
  controlleur = controlleur_;
}

void View::setControlleur(Controlleur* controlleur_) {
  controlleur = controlleur_;
}


void View::afficherJeu (Jeu& jeu) {
  std::cout<< std::endl << "\033[35m─────────────────────────────────────────────────────────────────────────────\033[1m\033[4mDominion\033[0m\033[35m─────────────────────────────────────────────────────────────────────────────\033[0m"<<std::endl;

      for (size_t i=0; i<jeu.getJoueurs().size();i++)
      {
        if (jeu.getJoueurs().at(i).getNom()!=jeu.getQuiJoue().getNom())
        {
          std::cout<<"\033[38;5;69m\033[4m\033[1m\nJoueur "<<jeu.getJoueurs().at(i).getNom()<<" :\033[0m"<<std::endl;
          std::cout<<"\033[38;5;69m\033[1mNombre de PV : "<<jeu.getJoueurs().at(i).getPv()<<std::endl;
          std::cout<<"Nombre de cartes : "<<jeu.getJoueurs().at(i).getHand().getTaille()<<std::endl;
        }
      }


  afficherTerrain(jeu);
  jeu.getQuiJoue().getCartesJouees().afficher2("Cartes Jouées","\033[31m");
  jeu.getQuiJoue().getCartesAchetes().afficher2("Cartes achetées","\033[32m");
  jeu.getQuiJoue().getDefausse().afficher2("Défausse","\033[34m");
  jeu.getQuiJoue().getPioche().afficher2("Pioche","\033[38;5;208m");

  std::cout<<"\033[4m\033[38;5;208m\033[1m\nJoueur "<<jeu.getQuiJoue().getNom()<<"\033[0m\033[38;5;208m\033[1m, a vous de jouer."<<std::endl;
  std::cout<<"\033[1m\033[38;5;208mVous avez "<<jeu.getQuiJoue().getPv()<<" PV."<<std::endl;
  std::cout<<"Vous avez "<<jeu.getQuiJoue().getNbPieces()<<" €."<<std::endl;
  std::cout<<"Il vous reste "<<jeu.getQuiJoue().getNbActions()<<" Actions."<<std::endl;
  std::cout<<"Il vous reste "<<jeu.getQuiJoue().getNbAchats()<<" Achats.\033[0m"<<std::endl;


  std::cout<<"\033[0;34m\033[1m─────────────────────────────────────────────────────────────  Votre main ──────────────────────────────────────────────────────────────────────────────────────────"<<std::endl;
  jeu.getQuiJoue().getHand().afficher(jeu);
  std::cout << std::endl;
}
void View::afficherTerrain (Jeu& jeu)
{
  CarteRoyaume* carteFantôme = new CarteRoyaume(1, "    ", 0, 0, 0, 0, 0, false, false, "");
  CarteRoyaume* carteRoyaume0=carteFantôme;
  CarteRoyaume* carteRoyaume1=carteFantôme;
  CarteRoyaume* carteRoyaume2=carteFantôme;
  CarteRoyaume* carteRoyaume3=carteFantôme;
  CarteRoyaume* carteRoyaume4=carteFantôme;
  CarteRoyaume* carteRoyaume5=carteFantôme;
  CarteRoyaume* carteRoyaume6=carteFantôme;
  CarteRoyaume* carteRoyaume7=carteFantôme;
  CarteRoyaume* carteRoyaume8=carteFantôme;
  CarteRoyaume* carteRoyaume9=carteFantôme;

  std::vector<Deck>& decksRoyaumes = jeu.getDecksRoyaume();


  if (jeu.getDecksRoyaume()[0].getTaille()!=0)
  {
    carteRoyaume0 = dynamic_cast<CarteRoyaume*>(decksRoyaumes[0].getCartes()[0]);
  }
  if (jeu.getDecksRoyaume()[1].getTaille()!=0)
  {
    carteRoyaume1 = dynamic_cast<CarteRoyaume*>(decksRoyaumes[1].getCartes()[0]);
  }
  if (jeu.getDecksRoyaume()[2].getTaille()!=0)
  {
    carteRoyaume2 = dynamic_cast<CarteRoyaume*>(decksRoyaumes[2].getCartes()[0]);
  }
  if (jeu.getDecksRoyaume()[3].getTaille()!=0)
  {
    carteRoyaume3 = dynamic_cast<CarteRoyaume*>(decksRoyaumes[3].getCartes()[0]);
  }
  if (jeu.getDecksRoyaume()[4].getTaille()!=0)
  {
    carteRoyaume4 = dynamic_cast<CarteRoyaume*>(decksRoyaumes[4].getCartes()[0]);
  }
  if (jeu.getDecksRoyaume()[5].getTaille()!=0)
  {
    carteRoyaume5 = dynamic_cast<CarteRoyaume*>(decksRoyaumes[5].getCartes()[0]);
  }
  if (jeu.getDecksRoyaume()[6].getTaille()!=0)
  {
    carteRoyaume6 = dynamic_cast<CarteRoyaume*>(decksRoyaumes[6].getCartes()[0]);
  }
  if (jeu.getDecksRoyaume()[7].getTaille()!=0)
  {
    carteRoyaume7 = dynamic_cast<CarteRoyaume*>(decksRoyaumes[7].getCartes()[0]);
  }
  if (jeu.getDecksRoyaume()[8].getTaille()!=0)
  {
    carteRoyaume8 = dynamic_cast<CarteRoyaume*>(decksRoyaumes[8].getCartes()[0]);
  }
  if (jeu.getDecksRoyaume()[9].getTaille()!=0)
  {
    carteRoyaume9 = dynamic_cast<CarteRoyaume*>(decksRoyaumes[9].getCartes()[0]);
  }




std::cout << std::endl << "\033[32m\033[1m┌───────────────┐" << "\033[33m┌───────────────┐" << "\033[31m                  ┌────────────────┐ ┌────────────────┐ ┌────────────────┐ ┌────────────────┐ ┌────────────────┐" <<std::endl;
  std::cout << "\033[32m\033[1m│    Province   │" << "\033[33m\033[1m│       Or      │" ; std::cout<< "\033[31m"; std::cout<< "                  │   "<< std::left << std::setw(13)<<carteRoyaume0->getNom()<<"│ │   "<< std::left << std::setw(13)<<carteRoyaume1->getNom()<<"│ │   "<< std::left << std::setw(13)<<carteRoyaume2->getNom()<<"│ │  "<< std::left << std::setw(13)<<carteRoyaume3->getNom()<<" │ │   "<< std::left << std::setw(13)<<carteRoyaume4->getNom()<<"│"<<std::endl;
  std::cout << "\033[32m│────┐─────┌────│" << "\033[33m│────┐─────┌────│" << "\033[31m                  │───────┐┌───────│ │───────┐┌───────│ │───────┐┌───────│ │───────┐┌───────│ │───────┐┌───────│" <<std::endl;
  std::cout << "\033[32m│ 8€ │     │ " << std::setw(3)<<jeu.getProvinces().getTaille()<<"│" <<"\033[33m│ 6€ │     │ " << std::setw(3)<<jeu.getGold().getTaille()<<"│"<<"\033[31m                  │ "<<carteRoyaume0->getNbCartes()<<" Crt ││ "<<carteRoyaume0->getNbActions()<<" Act │ "<<"│ "<<carteRoyaume1->getNbCartes()<<" Crt ││ "<<carteRoyaume1->getNbActions()<<" Act │ "<<"│ "<<carteRoyaume2->getNbCartes()<<" Crt ││ "<<carteRoyaume2->getNbActions()<<" Act │ "<<"│ "<<carteRoyaume3->getNbCartes()<<" Crt ││ "<<carteRoyaume3->getNbActions()<<" Act │ "<<"│ "<<carteRoyaume4->getNbCartes()<<" Crt ││ "<<carteRoyaume4->getNbActions()<<" Act │ "<<std::endl;
  std::cout << "\033[32m└────┘─────└────┘" << "\033[33m└────┘─────└────┘\033[0m"<< "\033[31m                  │───────││───────│ │───────││───────│ │───────││───────│ │───────││───────│ │───────││───────│";
  std::cout << std::endl << "\033[32m┌───────────────┐" << "\033[33m┌───────────────┐" <<"\033[31m\033[1m                  │ "<<carteRoyaume0->getNbGold()<<" €   ││ "<<carteRoyaume0->getNbAchats()<<" Buy │ "<<"│ "<<carteRoyaume1->getNbGold()<<" €   ││ "<<carteRoyaume1->getNbAchats()<<" Buy │ "<<"│ "<<carteRoyaume2->getNbGold()<<" €   ││ "<<carteRoyaume2->getNbAchats()<<" Buy │ "<<"│ "<<carteRoyaume3->getNbGold()<<" €   ││ "<<carteRoyaume3->getNbAchats()<<" Buy │ "<<"│ "<<carteRoyaume4->getNbGold()<<" €   ││ "<<carteRoyaume4->getNbAchats()<<" Buy │ "<<std::endl;
  std::cout << "\033[32m\033[1m│     Duche     │" << "\033[33m\033[1m│    Argent     │"<< "\033[31m                  │────┐──┘└──┌────│ │────┐──┘└──┌────│ │────┐──┘└──┌────│ │────┐──┘└──┌────│ │────┐──┘└──┌────│"<<std::endl;
  std::cout << "\033[32m│────┐─────┌────│" << "\033[33m│────┐─────┌────│"<< "\033[31m                  "  << (carteRoyaume0->getEffet()? "│ "+std::to_string(carteRoyaume0->getCost())+"€ │ Effet│": "│ "+std::to_string(carteRoyaume0->getCost())+"€ │      │")<<" "<<std::setw(2)<<jeu.getDecksRoyaume().at(0).getTaille()<<" │ "<< (carteRoyaume1->getEffet()? "│ "+std::to_string(carteRoyaume1->getCost())+"€ │ Effet│": "│ "+std::to_string(carteRoyaume1->getCost())+"€ │      │")<<" "<<std::setw(2)<<jeu.getDecksRoyaume().at(1).getTaille()<<" │ "<< (carteRoyaume2->getEffet()? "│ "+std::to_string(carteRoyaume2->getCost())+"€ │ Effet│": "│ "+std::to_string(carteRoyaume2->getCost())+"€ │      │")<<" "<<std::setw(2)<<jeu.getDecksRoyaume().at(2).getTaille()<<" │ "<< (carteRoyaume3->getEffet()? "│ "+std::to_string(carteRoyaume3->getCost())+"€ │ Effet│": "│ "+std::to_string(carteRoyaume3->getCost())+"€ │      │")<<" "<<std::setw(2)<<jeu.getDecksRoyaume().at(3).getTaille()<<" │ "<< (carteRoyaume4->getEffet()? "│ "+std::to_string(carteRoyaume4->getCost())+"€ │ Effet│": "│ "+std::to_string(carteRoyaume4->getCost())+"€ │      │")<<" "<<std::setw(2)<<jeu.getDecksRoyaume().at(4).getTaille()<<" │"<<std::endl;
  std::cout << "\033[32m\033[1m│ 5€ │     │ " << std::setw(3)<<jeu.getDuchy().getTaille()<<"│"<<"\033[33m│ 3€ │     │ " << std::setw(3)<<jeu.getSilver().getTaille()<<"│"<< "\033[31m                  └────┘──────└────┘ └────┘──────└────┘ └────┘──────└────┘ └────┘──────└────┘ └────┘──────└────┘" <<std::endl;
  std::cout << "\033[32m└────┘─────└────┘" << "\033[33m└────┘─────└────┘\033[0m" << "\033[31m                  ┌────────────────┐ ┌────────────────┐ ┌────────────────┐ ┌────────────────┐ ┌────────────────┐" <<std::endl;
  std::cout <<  "\033[32m┌───────────────┐" << "\033[33m┌───────────────┐";std::cout<< "\033[31m"; std::cout<< "\033[1m                  │   "<< std::left << std::setw(13)<<carteRoyaume5->getNom()<<"│ │   "<< std::left << std::setw(13)<<carteRoyaume6->getNom()<<"│ │   "<< std::left << std::setw(13)<<carteRoyaume7->getNom()<<"│ │  "<< std::left << std::setw(13)<<carteRoyaume8->getNom()<<" │ │   "<< std::left << std::setw(13)<<carteRoyaume9->getNom()<<"│"<<std::endl;
  std::cout << "\033[32m\033[1m│    Domaine    │" << "\033[33m│     Cuivre    │" << "\033[31m                  │───────┐┌───────│ │───────┐┌───────│ │───────┐┌───────│ │───────┐┌───────│ │───────┐┌───────│" <<std::endl;
  std::cout << "\033[32m│────┐─────┌────│" << "\033[33m│────┐─────┌────│" <<"\033[31m                  │ "<<carteRoyaume5->getNbCartes()<<" Crt ││ "<<carteRoyaume5->getNbActions()<<" Act │ "<<"│ "<<carteRoyaume6->getNbCartes()<<" Crt ││ "<<carteRoyaume6->getNbActions()<<" Act │ "<<"│ "<<carteRoyaume7->getNbCartes()<<" Crt ││ "<<carteRoyaume7->getNbActions()<<" Act │ "<<"│ "<<carteRoyaume8->getNbCartes()<<" Crt ││ "<<carteRoyaume8->getNbActions()<<" Act │ "<<"│ "<<carteRoyaume9->getNbCartes()<<" Crt ││ "<<carteRoyaume9->getNbActions()<<" Act │ "<<std::endl;
  std::cout << "\033[32m\033[1m│ 2€ │     │ " << std::setw(3)<<jeu.getEstate().getTaille()<<"│" <<"\033[33m\033[1m│ 0€ │     │ " << std::setw(3)<<jeu.getCopper().getTaille()<<"│"<< "\033[31m                  │───────││───────│ │───────││───────│ │───────││───────│ │───────││───────│ │───────││───────│"<<std::endl;
  std::cout << "\033[32m└────┘─────└────┘" << "\033[33m└────┘─────└────┘\033[0m" <<"\033[31m\033[1m                  │ "<<carteRoyaume5->getNbGold()<<" €   ││ "<<carteRoyaume5->getNbAchats()<<" Buy │ "<<"│ "<<carteRoyaume6->getNbGold()<<" €   ││ "<<carteRoyaume6->getNbAchats()<<" Buy │ "<<"│ "<<carteRoyaume7->getNbGold()<<" €   ││ "<<carteRoyaume7->getNbAchats()<<" Buy │ "<<"│ "<<carteRoyaume8->getNbGold()<<" €   ││ "<<carteRoyaume8->getNbAchats()<<" Buy │ "<<"│ "<<carteRoyaume9->getNbGold()<<" €   ││ "<<carteRoyaume9->getNbAchats()<<" Buy │ "<<std::endl;
  std::cout <<  "\033[32m┌───────────────┐" << "\033[31m                                   │────┐──┘└──┌────│ │────┐──┘└──┌────│ │────┐──┘└──┌────│ │────┐──┘└──┌────│ │────┐──┘└──┌────│" <<std::endl;
  std::cout <<"\033[32m\033[1m│  Malediction  │"<< "\033[31m\033[1m                                   "  << (carteRoyaume5->getEffet()? "│ "+std::to_string(carteRoyaume5->getCost())+"€ │ Effet│": "│ "+std::to_string(carteRoyaume5->getCost())+"€ │      │")<<" "<<std::setw(2)<<jeu.getDecksRoyaume().at(5).getTaille()<<" │ "<< (carteRoyaume6->getEffet()? "│ "+std::to_string(carteRoyaume6->getCost())+"€ │ Effet│": "│ "+std::to_string(carteRoyaume6->getCost())+"€ │      │")<<" "<<std::setw(2)<<jeu.getDecksRoyaume().at(6).getTaille()<<" │ "<< (carteRoyaume7->getEffet()? "│ "+std::to_string(carteRoyaume7->getCost())+"€ │ Effet│": "│ "+std::to_string(carteRoyaume7->getCost())+"€ │      │")<<" "<<std::setw(2)<<jeu.getDecksRoyaume().at(7).getTaille()<<" │ "<< (carteRoyaume8->getEffet()? "│ "+std::to_string(carteRoyaume8->getCost())+"€ │ Effet│": "│ "+std::to_string(carteRoyaume8->getCost())+"€ │      │")<<" "<<std::setw(2)<<jeu.getDecksRoyaume().at(8).getTaille()<<" │ "<< (carteRoyaume9->getEffet()? "│ "+std::to_string(carteRoyaume9->getCost())+"€ │ Effet│": "│ "+std::to_string(carteRoyaume9->getCost())+"€ │      │")<<" "<<std::setw(2)<<jeu.getDecksRoyaume().at(9).getTaille()<<" │"<<std::endl;
  std::cout<<"\033[32m│────┐─────┌────│"<< "\033[31m                                   └────┘──────└────┘ └────┘──────└────┘ └────┘──────└────┘ └────┘──────└────┘ └────┘──────└────┘" <<std::endl;
  std::cout << "\033[32m\033[1m│ 0€ │     │ " << std::setw(3)<<jeu.getCurse().getTaille()<<"│"<<std::endl;
  std::cout << "\033[32m└────┘─────└────┘\033[0m"<<std::endl;
}

void View::afficherMenuChoixCartes(std::vector<std::string> &cartes) {
  std::cout << "==============================\n";
  std::cout << "\033[1m   Choisissez une carte à ajouter   \n";
  std::cout << "==============================\n";
  std::cout << "\033[1m\nListe des cartes disponibles :\n";
  std::cout << "------------------------------\n";

  for (size_t i = 0; i < cartes.size(); i++) {
    std::cout << "[" << i << "] : " << cartes[i] << "\n";
  }

  std::cout << "\033[36m\n\033[1mVeuillez taper le numéro de la carte à ajouter au jeu : ";
}


void View::afficherMenu() {
  std::cout << "\033[36m\033[1m1 - Jouer" << std::endl << "2 - choix des cartes" << std::endl <<"3- Reprendre une partie"<<std::endl<< " Entrez votre choix : ";
}

void View::afficherChoixJoueurs(int i) {
  std::cout << "\033[36m\033[1mJoueur " << i << " Entrez votre nom : ";
}

void View::afficherDemandeTresor() {
  std::cout <<std::endl<< "\033[36m\033[1mEntrez :" << std::endl << "- le nom du trésor à jouer" << std::endl << "- * pour jouer tous vos trésors"<< std::endl <<
    "\033[1m- skip pour ne pas jouer de carte" <<
    std::endl << "\033[1mVotre choix : ";
}


void View::afficherDemandeAchat() {
  std::cout << "\033[36m\033[1mQuelle carte voulez vous acheter : ";
}

void View::carteIntrouvable() {
  std::cout << "\033[36m\033[1mCarte introuvable" << std::endl;
}


void View::fondsInsuffisants() {
  std::cout << "\033[36m\033[1mFonds insuffisants" << std::endl;
}

void View::afficherDemandeDescription() {
  std::cout << std::endl << "\033[36m\033[1mPour avoir la description d'une carte entrez help(nom de la carte)" << std::endl;
}

void View::afficherDescription(CarteRoyaume* c) {
  if (c!=nullptr) {
    std::cout <<"\033[36m\033[1m"<< std::endl << c->getNom() << " : " << c->getDescription() << std::endl << std::endl;
  }else {
    carteIntrouvable();
  }
}

void View::afficherDemandeDefausse(Deck d) {

  d.afficher2("\033[36m\033[1mCartes à défausser","\033[31m",true);

  std::cout << "\033[36m\033[1mPour défausser des cartes : "<< std::endl <<"- Entrez les numéros associés dans l'ordre de défausse souhaité"
                                                            << std::endl<<"-Tapez * pour défausser automatiquement" << std::endl <<
                                                              "Votre choix :";
}

void View::afficherDemandeAction()
{
  std::cout << "\033[36m\033[1mChoisissez les cartes actions que vous voulez jouer : "<< std::endl;
}

void View::afficherFin(Jeu& jeu)
{
  std::cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
  std::cout<< std::endl << "\033[35m─────────────────────────────────────────────────────────────────────────────\033[1m\033[4mDominion\033[0m\033[35m─────────────────────────────────────────────────────────────────────────────\033[0m"<<std::endl;
  std::cout<<"\n\n\033[36m\033[1mPartie termine, joueur "<<jeu.getJoueurGagnant().getNom()<< " gagnant avec "<<jeu.getJoueurGagnant().getPv()<<" PV"<<std::endl;
  std::vector<Deck> deck;
  for(size_t i=0; i<jeu.getJoueurs().size();i++)
  {
    jeu.getJoueurs().at(i).defausser();
    jeu.getJoueurs().at(i).defausser(jeu.getJoueurs().at(i).getPioche());
    jeu.getJoueurs().at(i).getDefausse().trier();
    std::cout<<"\n\n";
    std::string Deck = "Deck de joueur " + jeu.getJoueurs().at(i).getNom() + " qui a eu " + std::to_string(jeu.getJoueurs().at(i).getPv())+ " PV";
    jeu.getJoueurs().at(i).getDefausse().afficher2(Deck,"\033[36m\033[1m",false);

  }
  std::cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\033[36m\033[1mQue voulez vous faire?"<<std::endl;
  std::cout<<"-[1]Recommencer"<<std::endl;
  std::cout<<"-[2]Retour ecran d'accueuil"<<std::endl;
  std::cout<<"-[3]Quitter"<<std::endl;
  std::cout<<"-Choix :"<<std::endl;
}