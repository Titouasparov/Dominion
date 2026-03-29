#include "../include/Save.h"
#include <filesystem>
#include <fstream>
#include "../include/Deck.h"
#include "../include/Util.h"
#include "../include/Jeu.h"

Save::Save(Jeu& j,std::string n) : nom(n) ,jeu(j){
}


//prend un chemin et un deck et enregistre le l'état du decj au chemin indiqué au format csv
void Save::saveDeck (const std::string& chemin,Deck& deck){
  std::ofstream outFile;
  outFile.open(chemin);
  if(outFile.is_open()){
    for (Carte* c : deck.getCartes()){
      //on convertit parse la carte en string
      outFile<<Util::carteToStr(c)<<'\n';
    }
  }
}

//charge le deck contenu au chemin dans deck
void Save::loadDeck ( std::string chemin,Deck& deck){
  deck.reset();
  std::string line;
  std::ifstream file;
  file.open(chemin);
  if(file.is_open()){
    while(std::getline(file,line)){
      Carte* c = Util::strToCarte(line);
      deck.ajouterCarte(c);
    }
  }
}

//retourne le Joueur stocké dans le fichier csv du chemin
Joueur Save::loadJoueur(std::string chemin){

  Joueur joueur= Joueur();

  std::filesystem::path path = chemin;

  std::string nom;
  int nbActions=0;
  int nbPieces=0;
  int nbAchats=0;
  int pv=0;

  //on crée les decks
  Deck hand;
  Deck defausse;
  Deck pioche;
  Deck cartesJouees;
  Deck cartesAchetees;

  std::ifstream file;
  std::string line;
  //on ouvre le fichier et on charge les infos du joueurs dans des variables
  file.open(path/path.filename());
  if(file.is_open()){
    std::getline(file,line);
  }else{}

  std::istringstream lineStream(line);
  std::string word;

  std::getline(lineStream,nom,';');

  std::getline(lineStream,word,';');
  nbActions = std::stoi(word);

  std::getline(lineStream,word,';');
  nbPieces = std::stoi(word);

  std::getline(lineStream,word,';');
  nbAchats = std::stoi(word);

  std::getline(lineStream,word,';');
  pv = std::stoi(word);

  std::getline(lineStream,word,';');
  loadDeck((path/word).string(),hand);

  std::getline(lineStream,word,';');
  loadDeck((path/word).string(),defausse);

  std::getline(lineStream,word,';');
  loadDeck((path/word).string(),pioche);

  std::getline(lineStream,word,';');
  loadDeck((path/word).string(),cartesJouees);

  std::getline(lineStream,word,';');
  loadDeck((path/word).string(),cartesAchetees);
	//on initialise le joueur
  joueur.setNom(nom);
  joueur.setNbActions(nbActions);
  joueur.setNbPieces(nbPieces);
  joueur.setNbAchats(nbAchats);
  joueur.setNbPV(pv);

  joueur.setHand(hand);
  joueur.setDefausse(defausse);
  joueur.setPioche(pioche);
  joueur.setCartesJouees(cartesJouees);
  joueur.setCartesAchetes(cartesAchetees);

  return joueur;
};

//enregistre le joueur joueur au chemin indiqué en csv
void Save::saveJoueur(const std::string& chemin,Joueur& joueur){

  std::filesystem::path SavePath = std::filesystem::path(chemin);
  std::filesystem::path JoueurPath = SavePath / joueur.getNom();

  if (!std::filesystem::exists(JoueurPath)){
    std::filesystem::create_directory(JoueurPath);
  }

  std::ofstream outFile;
  outFile.open(JoueurPath/joueur.getNom());
  if(outFile.is_open()){
    //on parse le joueur en string
    outFile << Util::joueurToStr(joueur)<<'\n';
  }

  std::string hand = "/hand_" + joueur.getNom();
  saveDeck(JoueurPath.string()+hand,joueur.getHand());

  std::string defausse = "/defausse_" + joueur.getNom();
  saveDeck(JoueurPath.string()+defausse,joueur.getDefausse());

  std::string cartesAchetees = "/cartesAchetees_" + joueur.getNom();
  saveDeck(JoueurPath.string()+cartesAchetees,joueur.getCartesAchetes());

  std::string cartesJouees = "/cartesJouees_" + joueur.getNom();
  saveDeck(JoueurPath.string()+cartesJouees,joueur.getCartesJouees());

  std::string pioche = "/pioche_" + joueur.getNom();
  saveDeck(JoueurPath.string()+pioche,joueur.getPioche());

}

//enregistre l'état de chaque joueur dans des fichiers csv du nom des joueurs au path savePath
void Save::saveJoueurs(const std::string& savePath, std::vector<Joueur>& joueurs){

  std::filesystem::path SavePath = std::filesystem::path(savePath);
  std::filesystem::path JoueursPath = SavePath / "Joueurs";

  if (!std::filesystem::exists(JoueursPath)){
    std::filesystem::create_directory(JoueursPath);
  }
	//on parcourt tous les joueurs
  for (Joueur& joueur : joueurs){
    //on l'enregistre dans le sous répertoire Joueurs
    saveJoueur(savePath+"/Joueurs",joueur);
  }
}
//enregistre l'état de la partie
void Save::saveJeu(){
  std::filesystem::path SavePath = std::filesystem::current_path()/nom;

//si le dossier de save existe pas
  if (std::filesystem::exists(SavePath)){
    std::filesystem::remove_all(SavePath);
  }
  std::filesystem::create_directory(SavePath);

  std::ofstream outFile;
  outFile.open(SavePath/"Jeu");
  if(outFile.is_open()){
    //on parse l'état du jeu en csv
    outFile << Util::jeuToStr(jeu)<<'\n';
  }

  saveJoueurs(SavePath.string(),jeu.getJoueurs());
  savePlateau(SavePath.string());
}

//enregistre état du plateau sous forme de decks
void Save::savePlateau(const std::string& chemin){
  std::filesystem::path SavePath = std::filesystem::path(chemin)/"Plateau";
  if (!std::filesystem::exists(SavePath)){
    std::filesystem::create_directory(SavePath);
  }

  Deck& provinces = jeu.getPlateau().getProvinces();
  Deck& gold = jeu.getPlateau().getGold();
  Deck& silver = jeu.getPlateau().getSilver();
  Deck& Duchy = jeu.getPlateau().getDuchy();
  Deck& Estate = jeu.getPlateau().getEstate();
  Deck& Copper = jeu.getPlateau().getCopper();
  Deck& Curse = jeu.getPlateau().getCurse();

  saveDeck((SavePath/"Provinces").string(),provinces);
  saveDeck((SavePath/"Gold").string(),gold);
  saveDeck((SavePath/"Silver").string(),silver);
  saveDeck((SavePath/"Duchy").string(),Duchy);
  saveDeck((SavePath/"Estate").string(),Estate);
  saveDeck((SavePath/"Copper").string(),Copper);
  saveDeck((SavePath/"Curse").string(),Curse);

  for (Deck d : jeu.getPlateau().getDecksRoyaume()){
    if (!d.estVide()){
      saveDeck((SavePath/d.getCartes().at(0)->getNom()).string(),d);
    }
  }
}

//charge les joueurs dans le vecteur joueur
void Save::loadJoueurs(std::vector<Joueur>& joueurs){
  std::filesystem::path chemin = std::filesystem::current_path()/nom/"Joueurs";
  for (const auto& entry : std::filesystem::directory_iterator(chemin)){
     if (std::filesystem::is_directory(entry)){
       joueurs.push_back(loadJoueur(entry.path().string()));
     }
  }
}


//charge le jeu depuis le dossier save
void Save::loadJeu(){

  std::filesystem::path plateauPath = std::filesystem::current_path()/nom/"Plateau";
  std::filesystem::path jeuPath = std::filesystem::current_path()/nom/"Jeu";

  //on récupère les joueurs
  std::vector<Joueur> joueurs;
  loadJoueurs(joueurs);


  //chargement du jeu
  std::ifstream inFile;
  std::string line;
  int id=0;
  int numTours = 0;
  Phase p;
  std::string quiJoue;

  inFile.open(jeuPath);
  if (inFile.is_open()){
    std::string word;

    getline(inFile, line);

    std::istringstream ss(line);

    getline(ss,word,';');
    id = std::stoi(word);

    getline(ss, word,';');
    numTours = std::stoi(word);

    getline(ss, word,';');
    p = (word=="Action") ? Action : Achat;

    getline(ss, quiJoue,';');
  }

	//initialisation du jeu
  jeu.setJoueurs(joueurs);
  jeu.setNumTour(numTours);
  Jeu::setNextId(id);
  jeu.setPhase(p);
	//recup du joueur actuel
  for (Joueur& joueur : jeu.getJoueurs()){
    if (joueur.getNom() == quiJoue){
      jeu.setQuiJoue(joueur);
    }
  }
//initialisation du jeu
  jeu.init(true);

  //creation plateau

  Deck& provinces = jeu.getPlateau().getProvinces();
  Deck& gold = jeu.getPlateau().getGold();
  Deck& silver = jeu.getPlateau().getSilver();
  Deck& Duchy = jeu.getPlateau().getDuchy();
  Deck& Estate = jeu.getPlateau().getEstate();
  Deck& Copper = jeu.getPlateau().getCopper();
  Deck& Curse = jeu.getPlateau().getCurse();
  std::vector<Deck>& decksRoyaume = jeu.getPlateau().getDecksRoyaume();

  for (int i=0; i<jeu.getNbDeckRoyaumes(); i++){
    decksRoyaume.push_back(Deck());
  }


  std::string nomDeck;
  int numDernierDeckRoyaumeAjouté = 0;
	//on récupère les différents decks du plateau
  for (auto entry : std::filesystem::directory_iterator(plateauPath)){
    if (std::filesystem::is_regular_file(entry)){
      if (entry.path().filename() == "Provinces"){
        loadDeck(entry.path().string(),provinces);
      }
      else if (entry.path().filename() == "Gold"){
        loadDeck(entry.path().string(),gold);
      }
      else if (entry.path().filename() == "Silver"){
        loadDeck(entry.path().string(),silver);
      }
      else if (entry.path().filename() == "Duchy"){
        loadDeck(entry.path().string(),Duchy);
      }
      else if (entry.path().filename() == "Estate"){
        loadDeck(entry.path().string(),Estate);
      }
      else if (entry.path().filename() == "Copper"){
        loadDeck(entry.path().string(),Copper);
      }
      else if (entry.path().filename() == "Curse"){
        loadDeck(entry.path().string(),Curse);
      }
      //si on charge un deck royaume
      else{
        //nom du deck royaume
        nomDeck = entry.path().string();
        //on charge le deck numero "numDernierDeckRoyaumeAjouté"
        loadDeck(entry.path().string(),decksRoyaume.at(numDernierDeckRoyaumeAjouté));
        //on incremente le numero
        numDernierDeckRoyaumeAjouté++;
      }
    }
  }
}

//renvoie true si un dossier de sauvegarde nommé nom existe
bool Save::exists(){
  std::filesystem::path p = std::filesystem::current_path()/nom;
  if (std::filesystem::exists(p)){
    return true;
  }
  return false;
}