#ifndef Objet_H
#define Objet_H
#include <iostream>
#include <string>
#include <SDL.h>
#include "Image.h"
#include "dictionnaire.h"


using namespace std;

class Objet
{
    Image _image;
    int _x;
    int _y;
    string _propriete;
public:
    Objet(Image& img,const string& nom,const Dictionnaire& dico, int x, int y);
    void dessiner() const;
    void afficher() const;
    string getPropriete() const;
    int getX() const;
    int getY() const;
    void cache();

};

#endif // Objet_H
