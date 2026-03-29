#include "include/CarteTresor.h"
#include "include/View.h"
#include "include/Controlleur.h"
#include "include/Util.h"
#include "include/CarteVictoire.h"
#include "include/Save.h"
#include <filesystem>
int main(){

    Jeu jeu = Jeu();
    View vue = View(nullptr);
    Controlleur* controlleur = new Controlleur(vue,jeu);
    vue.setControlleur(controlleur);

    controlleur->lancerMenu();

  /*CarteRoyaume* c1= new CarteRoyaume(232,"bucheron",5,1,2,3,4,true,false,"Valentin le bg");
  std::string s1 = Util::carteToStr(c1);
  c1->afficher();
  std::cout << s1 << std::endl;
  Carte* c2 = Util::strToCarte(s1);
  c2->afficher();
  CarteRoyaume* c2= new CarteRoyaume(235,"atelier",5,1,2,3,4,true,false,"Valentin le bg");
  CarteRoyaume* c3= new CarteRoyaume(236,"laboratoire",5,1,2,3,4,true,false,"Valentin le bg");
  j.getQuiJoue().getHand().ajouterCarte(c1);
  j.getQuiJoue().getHand().ajouterCarte(c2);
  j.getQuiJoue().getHand().ajouterCarte(c3);
  j.getQuiJoue().getCartesJouees().ajouterCarte(c1);
  j.getQuiJoue().getCartesJouees().ajouterCarte(c2);
  j.getQuiJoue().getCartesJouees().ajouterCarte(c3);
  vue.afficherJeu(controlleur->getJeu());
  controlleur->demanderTresors();*/


  return 0;
}



/* Deck d = Deck({c,c2},2);
c.afficher();
*/