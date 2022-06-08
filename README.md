# Projet de majeur
__Projet de génération d'arbres en 3D.__

## Lancement du programme
Dans le dossier racine :  
```console
mkdir build
cd build
cmake ..
cd ..
make -C && build/pgm
```
(Exécuter seulement la dernière ligne pour la suite du programme)  

## Déplacement dans l'espace 3D

- __Clic gauche + déplacement__ : rotation de la caméra  
- __Clic droit + déplacement__ : zoom avant/arrière de la caméra  
- __MAJ + Clic gauche + déplacement__ : translation de la caméra  

## Choix du modèle

Dans le dossier __./src/external/projet/caractere.cpp__ se trouve plusieurs modèle.
Choisir un des vecteurs et le décommenter.
