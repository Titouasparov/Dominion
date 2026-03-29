CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -I./include

OBJ_DIR = obj


# Crée le dossier obj s'il n'existe pas déjà
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile les fichiers .cpp en fichiers .o dans le dossier obj
$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

OBJECTS = $(OBJ_DIR)/Carte.o  \
			$(OBJ_DIR)/main.o \
			$(OBJ_DIR)/CarteRoyaume.o\
			 $(OBJ_DIR)/CarteTresor.o \
			 $(OBJ_DIR)/CarteVictoire.o \
			 $(OBJ_DIR)/Deck.o \
			 $(OBJ_DIR)/Joueur.o \
			 $(OBJ_DIR)/Jeu.o \
			 $(OBJ_DIR)/View.o\
			 $(OBJ_DIR)/Controlleur.o\
			 $(OBJ_DIR)/Plateau.o\
			 $(OBJ_DIR)/Util.o\
			 $(OBJ_DIR)/Save.o



Dominion: $(OBJECTS)
	$(CXX) $^ -o $@

.PHONY: run clean

run: Dominion
	./$^

clean:
	rm -f *.o *~ *.core
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/*~ $(OBJ_DIR)/*.core
