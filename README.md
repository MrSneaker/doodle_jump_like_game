# Projet LIFAP4

Projet lifap4 de Foodle jump, MUNOZ Matéo et RIGAUT Cyril.
Note obtenu : 16.8/20 - 8ème sur 165 (note individuel, Matéo)

## Nom du projet
Foodle jump

## Description
Ce projet avait pour but de reproduire le jeu mobile Doodle Jump, sortie en 2009. Doodle jump est un jeu infinie ou l'on ne gagne jamais, et ou il faut aller le plus loin possible. Foodle jump suit donc le même principe. Il faut donc sauter sur les plateformes sans tomber tout en évitant les monstres et les pièges. Le jeu dévleloppé a une interface graphique, et du son. Tout est développé en C++. Notez aussi que cette application est développée pour linux uniquement.

L'archive est organisée de la manière suivante : dans bin on retrouve tous les exécutables, dans data toutes les données nécessaire pour le jeu, dans doc toute la documentation du code et du projet, dans obj sont stockés tous les fichier objet, et enfin dans src se trouve l'intégralité du code. Le Makefile est à la racine.

## Installation
Pour compiler et exécuter le jeu, il suffit de ce placer à la racine et d'executer le Makefile avec la commande "make". ensuite, vous obtiendrez deux executable : bin/test permettant d'executer les tests de régression, et bin/affichageModeGRAPHIQUE qui executera le menu du jeu.

Dans ce Menu vous avez 3 boutons sur lesquels vous pouvez faire un clique gauche à la souris : JOUER SDL, JOUER TXT et QUITTER. JOUER SDL va lancer le jeu en SDL, JOUER TXT fera la même chose avec la version texte, et QUITTER quittera le programme.

## Commande du jeu, règles et principe
Si vous lancer la version SDL, vous bougez grâce aux flèches droite et gauche du clavier (droite pour aller à droite et gauche pour aller à gauche). Vous pouvez aussi tirer un projectile avec la touche espace. 

Avec la version texte, vous devez appuyer sur entrer à chaque fois que vous vouler faire un input pour qu'il soit pris en compte (si vous faites plusieurs input à la suite et que vous appuyez sur entrer, ils seront executés les uns à la suite des autres). Les touches en versions textes sont D pour aller à gauche, G pour aller à droite et R pour tirer.

Les règles du jeu sont simples, vous apparaissez en sautant dans un écran rempli de plateformes toutes générées aléatoirement à chaque partie. Votre personnage saute automatiquement sur les plateformes qu'ils rencontrent, il faut alors le diriger pour qu'il aille le plus haut possible. Vous perdez si vous mourrez, et il y a trois façon de mourir : si vous touchez un monstre, si vous tomber dans le vide, si vous rencontrer un trou noir. Vous devez donc éviter ses situations. Pour cela, plusieurs façons : pour les monstres, vous pouvez simplement les éviter, mais aussi les tuers en leur sautant dessus ou alors en leurs tirant un projectile dessus. Pour les trou noir il faut simplement les éviter, il n'y a pas d'autre moyen. Et pour le vide, ne tombez pas !

Votre score sera affiché (dans la version SDL uniquement) en haut à gauche. Plus votre score augmente plus la difficulté sera grande (nombre de monstre plus grand, nombre de plateformes plus faible, plateformes sur lesquels on ne peut sauter qu'une fois plus grand (apparaissant en blanc).. mais aussi plus de bonus, ce qui semble sympathique, mais cela augmente aussi le nombre de trou noir). 

Si vous perdez une partie, vous reviendrez sur le menu. Vous pourrez alors relancer une partie en faisant un double clique gauche sur "JOUER SDL" ou "JOUER TXT", ou quitter en double cliquant sur "QUITTER".


