# minGL 2
MinGL 2 est un bibliothèque écrite en C++, évolution de MinGL par Alain Casali, enseignant chercheur au département informatique de l'IUT d'Aix-en-Provence.  
Elle facilite l'affichage de forme primitives et composées, de texte et la réalisation d'animations. Elle permet également de jouer des fichiers audios et de gérer les saisies clavier et souris.

Développé dans un but pédagogique.

## Installation
Les dépendances suivantes sont requises pour utiliser minGL 2: 
* freeglut
* sfml (audio)

Installation sous **Debian et dérivés**:
```
sudo apt-get install freeglut3-dev libsfml-dev
```

Installation sous **Arch Linux et Manjaro**: 
```
sudo pacman -S freeglut sfml
```

Installation sous **macOS** (avec [Homebrew](https://brew.sh) préalablement installé):
```
brew cask install xquartz
brew install freeglut sfml
```
**Important**: Afin de terminer l'installation de XQuartz, macOS doit être redémarré.

Testé sous Debian 10, Ubuntu 20.04, macOS 10.15, Manjaro GNU/Linux (audio non testé)

## Utilisation

### Avec un autre projet qmake
Pour utiliser minGL 2 dans votre projet qmake, il vous suffit de décompresser (ou encore mieux, mettre en sous-module git) cette bibliothèque dans un sous-répertoire du répertoire contenant votre fichier ``.pro``.  
Il vous suffit ensuite de rajouter dans votre ``.pro`` la directive ``include(.../mingl.pri)``, en remplaçant ``...`` par le chemin du répertoire de minGL 2.

Par exemple, si vous avez décompressé minGL 2 dans le sous-répertoire ``minGL2/`` présent dans le même répertoire que votre ``.pro``, alors vous devez écrire dans ce dernier: ``include(minGL2/mingl.pri)``.

### En tant que bibliothèque
Vous pouvez facilement compiler minGL 2 en tant que bibliothèque afin de générer le fichier ``libmingl.a``.  
Il vous suffit simplement d'ouvrir le fichier de projet ``mingl.pro`` et de lancer la compilation, vous trouverez le fichier ``.a`` dans le répertoire de compilation.  
Le répertoire ``include/`` contient tout les fichiers d'en-tête de minGL 2.

### Extras
Si vous avez ``doxygen`` installé sur votre machine, vous pouvez générer, dans le répertoire ``doc/``, une documentation HTML de minGL 2 avec la commande suivante:
```
doxygen Doxyfile
```

Dans le répertoire ``tools/``, vous trouverez des outils relatif a l'utilisation de minGL 2.

## Remerciements
* **Alexandre Sollier et Clément Mathieu--Drif**: Développeurs principaux de minGL 2
* **Alain Casali**: Auteur de la version originale de MinGL
* La promo 2020-2021 de la 2ème année du Département Informatique de l'IUT d'Aix-en-Provence

