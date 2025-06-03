#include <string>
#include <vector>
#include <iostream>
#include "tuile.h"

///Constructeurs

// Constructeur par d�faut
Tuile::Tuile(){

}
// Constructeur avec param�tres
Tuile::Tuile(int x, int y,const string& nomTuile,const string& propriete)
{
    _x= x;
    _y= y;
    _nomTuile = nomTuile;
    _propriete = propriete;

}

//Fonction d'affichage de la tuile
void Tuile::afficher() const
{
    cout<<"Affichage de la tuile"<<endl;
    cout<<"Nom"<<": "<<_nomTuile<<endl;
    cout<<"Propriete"<<": "<<_propriete<<endl;
    cout<<"Position x"<<": "<<this->getX()<<endl;
    cout<<"Position y"<<": "<<this->getY()<<endl;
}

//Fonction qui permet d'obtenir le nom de la tuile
string Tuile::getNom() const
{
  return _nomTuile;
}

//Fonction qui permet d'obtenir la propri�t� de la tuile
string Tuile::getPropriete() const
{
    return _propriete;
}

//Fonction qui permet d'obtenir la coordonn�e en abscisse "contractuelle" dans la feuille
int Tuile::getX() const
{
    return _x*TAILLE_CASE;
}

//Fonction qui permet d'obtenir la coordonn�e en ordonn�e "contractuelle" dans la feuille
int Tuile::getY() const
{
    return _y*TAILLE_CASE;
}
