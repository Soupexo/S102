#include <iostream>
#include <fstream>
#include "Image.h"
#include "../include/dictionnaire.h"
#include "../include/tuile.h"
#include "../include/objet.h"
#include "../include/niveau.h"
#include <string>
#include <SDL.h>

using namespace std;
///Constructeurs

// Constructeur par d�faut
Niveau::Niveau(){

}
// Constructeur avec param�tres
Niveau::Niveau(Image& img,const string& nomFichier,const Dictionnaire& dico){
    ifstream entree;
    string nom;
    int x,y;
    _nbBonus=0;
    //Ouverture du flux qui va lire le fichier
    entree.open(nomFichier);
    int nbInt;
    if (!entree.eof())
        entree >> nbInt;
        //Le nombre de ligne est variabiliser dans l'entier nbInt
    for (int i = 0; i < nbInt && !entree.eof(); i++) {
        int val=1;
        //Tant que nous n'avons pas m�moriser dans des variables les trois caract�ristiques
        while (val<=3){
            if (val == 1){
                entree >> nom;
            }
            else if (val==2){
                entree >> x;
            }
            else{
                entree >> y;
            }
            val+=1;
    }
    //Instanciation de l'objet correspondant
    Objet obj(img,nom,dico,x,y);
    _objets.push_back(obj);
    //Si ce dernier est de propriete bonus alors
    if (obj.getPropriete() == "bonus"){
        //incr�mentation de nbBonus
        _nbBonus+=1;
        }
    }
    //Post traitement, fermeture du flux "entree"
    entree.close();
}
//Fonction qui permet de dessiner les objets du niveau non cacher
void Niveau::dessiner() const
{
    int longueur = _objets.size();
    for (int i = 0; i<longueur; i++){
        if (_objets[i].getPropriete() != "cache"){
            _objets[i].dessiner();
        }
    }
}
//Fonction qui permet d'afficher les objets du niveau
void Niveau::afficher() const
{
    int longueur = _objets.size();
    for (int i = 0; i<longueur; i++){
        _objets[i].afficher();
    }
}
//Fonction qui v�rifie si les objets solides ne sont pas travers�s
bool Niveau::caseEstLibre(int x, int y) const
{
    for (int i = 0; i < _objets.size(); i++){
        //Si l'objet est de propriete solide et est aux coordonn�es du joueur alors
        if (_objets[i].getPropriete() == "solide" && _objets[i].getX() == x && _objets[i].getY() == y){
            return false;
        }
    }
    return true;
}
//Fonction qui permet d'afficher le nombre d'objet typ� bonus
int Niveau::getNbBonus() const
{
    return _nbBonus;
}
//Fonction qui permet de prendre un bonus (pi�ces)
void Niveau::testerBonusEtPrendre(int x, int y)
{
    for (int i = 0; i <_objets.size(); i++){
        //Si l'objet est de propriete bonus et est aux coordonn�es donn�es alors
        if (_objets[i].getPropriete() == "bonus" && _objets[i].getX() == x && _objets[i].getY() == y){
          //Les objets (pi�ces en l'occurrence) sont cach�s
           _objets[i].cache();
          //D�crementation de nbBonus en cons�quence
           _nbBonus -= 1;
        }
    }

}
//Fonction de victoire
bool Niveau::gagne() const
{
    return (_nbBonus == 0);
}


