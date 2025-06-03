#include <iostream>
#include "Image.h"
#include "../include/dictionnaire.h"
#include "../include/tuile.h"
#include "../include/objet.h"
#include <string>
#include <SDL.h>

///Constructeurs

// Constructeur avec paramètres
Objet::Objet(Image& img,const string& nom,const Dictionnaire& dico, int x, int y){
    Tuile t;
    dico.recherche(nom,t);
    _image = img;
    _image.selectionnerRectangle(t.getX(),t.getY(),TAILLE_CASE,TAILLE_CASE);
    _propriete = t.getPropriete();
    _x = x;
    _y = y;
}
//Fonction qui permet de dessiner grâce aux coordonnées mis en attribut de l'objet
void Objet::dessiner() const{
    _image.dessiner(_x*TAILLE_CASE,_y*TAILLE_CASE);
}
//Fonction qui permet de dessiner l'objet
void Objet::afficher() const{
    cout<<"Affichage de l'objet"<<": "<<endl;
    cout<<"Propriete: "<<_propriete<<endl;
    cout<<"Position x "<<_x<<endl;
    cout<<"Position y "<<_y<<endl;

}

//Fonction qui permet d'obtenir la propriété de l'objet
string Objet::getPropriete() const
{
    return _propriete;
}

//Fonction qui permet d'obtenir la coordonnée en abscisse contractuelle
int Objet::getX() const
{
    return _x*TAILLE_CASE;
}

//Fonction qui permet d'obtenir la coordonnée en ordonnee contractuelle
int Objet::getY() const
{
    return _y*TAILLE_CASE;
}
//Fonction qui permet de modifier la propriété de l'objet cible pour le "cacher"
void Objet::cache()
{
    _propriete = "cache";
}


