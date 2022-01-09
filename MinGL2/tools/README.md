# Outils minGL 2
Ce répertoire contient des outils relatif a certaines fonctionnalitées minGL 2.

## Script de conversion .si2
MinGL 2 supporte le chargement d'images sous le format ``.si2``, qui est un format d'image non-compressé, type bitmap avec support de la transparence.  
Un script Python 3 permettant de transformer n'importe quelle image en ``.si2`` (et inversement) vous est fourni ici, nommé ``img2si.py``.

Le spécifications de ce format de fichier vous sont écrites dans ce même script Python, en commentaire.

Ce script Python est dépendant de la biliothèque Pillow, que vous pouvez installer via pip:
```sh
python3 -m pip install --upgrade pip
python3 -m pip install --upgrade Pillow
```
