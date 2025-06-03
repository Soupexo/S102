#ifndef Personnage_H
#define Personnage_H
#include <iostream>
#include <string>
#include <SDL.h>
#include "niveau.h"
#include "Image.h"

using namespace std;


class Personnage
{
    Image _image;
    int _abscisse;
    int _ordonnee;
    int _skin_x;
    int _skin_y;
    int _posAnim;
    string _direction;
    Niveau _niveau;
public:
    Personnage();
    Personnage(const Image& image, int x, int y, int skin_x, int skin_y, string& direction, int posAnim,const Niveau& niveau);
    int getX() const;
    int getY() const;
    void dessiner() const;
    int  allerDroite();
    int  allerGauche();
    int  allerHaut();
    int  allerBas();
    bool bordAtteint(const string& direction) const;
    void mettreAJourDirection(const string& direction);
    void avancer();
    bool touche(const Personnage& P);
    int mettreAjourAnimation();

};



#endif // Personnage_H
