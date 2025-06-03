#ifndef Tuile_H
#define Tuile_H
#include <string>
#include <iostream>
#include "Image.h"

using namespace std;

class Tuile
{
    int _x;
    int _y;
    string _nomTuile;
    string _propriete;
public:
    Tuile();
    Tuile(int x, int y,const string& nomTuile,const string& propriete);
    void afficher() const;
    string getNom() const;
    string getPropriete() const;
    int getX() const;
    int getY() const;
};

#endif // Tuile_H

