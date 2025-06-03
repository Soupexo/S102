#ifndef Dictionnaire_H
#define Dictionnaire_H
#include <string>
#include <vector>
#include <iostream>
#include "Tuile.h"

using namespace std;

class Dictionnaire
{
    vector<Tuile> _tuiles;
    string _nomFichier;
    public:
    Dictionnaire();
    Dictionnaire(const string& nomfichier);
    void afficher() const;
    bool recherche(const string& nom, Tuile& tuile) const;
};

#endif // DICTIONNAIRE_H

