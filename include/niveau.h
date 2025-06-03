#ifndef niveau_H
#define niveau_H
#include <string>
#include <vector>
#include <SDL.h>
#include <iostream>
#include "dictionnaire.h"
#include "objet.h"

using namespace std;

class Niveau
{
    vector<Objet> _objets;
    int _nbBonus;
public:

    Niveau(Image& img,const string& nom,const Dictionnaire& dico);
    Niveau();
    void dessiner() const;
    void afficher() const;
    bool caseEstLibre(int x, int y) const;
    int getNbBonus() const;
    void testerBonusEtPrendre(int x, int y);
    bool gagne() const;

};

#endif // Niveau_H
