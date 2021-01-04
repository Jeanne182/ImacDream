ImacDream

Conditions préalables à la compilation : 

Il faut s’assurer d’avoir téléchargé les librairies Assimp, OpenGL, SDL2, SDL_Mixer ainsi que Freetype.	

Commandes linux pour installer les librairies nécessaires à l'exécution : 

sudo apt-get install libassimp-dev assimp-utils
sudo apt-get install libglut3-dev
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-mixer-dev
sudo apt install libfreetype6

Commandes pour créer le dossier de jeu :

Placez-vous dans le dossier IMACDream, au même niveau que Game :
Puis tapez ces commandes dans un terminal :
 	mkdir Game-build
	cd Game-build
	cmake ../Game
	make 

Pour exécuter le programme: 

En s’assurant que vous êtes toujours placé dans Game-build, tapez :
./IMACDream

Bonne expérience dans Dragon's Dusk !
