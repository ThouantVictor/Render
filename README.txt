
Prérequis:

	-libxml library
	-SDL library
	-SDL_ttf library
	
 Veillez à Modifier la variable INCLUDE dans le Makefile en fonction du
 repertoire de sauvegarde des librairies de votre OS.

Compilation:

	make

Utilisation:

	./render fic.osm
	
Avec fic.osm le fichier osm à lire.

Description:

Rendeur de carte de fichier xml .osm
Le programme s'arrète losque l'on appui sur une touche.

Ne vous attendez pas à quelque chose de beau surtout pas!!

Le coeur du projet réside dans les fichiers render_engine.c et drawer.c et Parser.c .

Pour l'observation du déroulement de l'affichage, je vous conseil de décommenter
la ligne 177 dans render.c

Vous pouvez, pour plus de detail que ce trés faible rendu graphique, afficher
par exemple les structure de données générées en décommentant par exemple la ligne 41 de render.c.



