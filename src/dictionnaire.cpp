#include "Dictionnaire.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Tuile.h"


///Constructeurs
// Constructeur par d�faut
Dictionnaire::Dictionnaire()
{

}
// Constructeur avec param�tres
Dictionnaire::Dictionnaire(const string& nomFichier){
    ifstream entree;
    string nom;
    int x,y;
    string propriete;
    //Ouverture du flux qui va lire le fichier
    entree.open(nomFichier);
    int nbInt;
    if (!entree.eof())
        //Le nombre de ligne est variabiliser dans l'entier nbInt
        entree >> nbInt;
    for (int i = 0; i < nbInt && !entree.eof(); i++) {
        int val=1;
        //Tant que nous n'avons pas m�moriser dans des variables les trois caract�ristiques
        while (val<=4){
            if (val == 1){
                entree >> nom;
            }
            else if (val == 2){
                entree >> x;
            }
            else if (val==3){
                entree >> y;
            }
            else{
                entree >> propriete;
            }
            val+=1;
    }
    //Instanciation de la tuile correspondante
    _tuiles.push_back(Tuile(x,y,nom,propriete));
    }
    //Post traitement, fermeture du flux "entree"
    entree.close();
}
//Fonction qui permet l'affichage du dictionnaire (soit techniquement de toutes les tuiles le constituant)
void Dictionnaire::afficher() const{
    int longueur = _tuiles.size();
    for (int i = 0; i<longueur; i++){
        _tuiles[i].afficher();
    }
}
//Etant donn� son efficacit� et sa complexit� temporelle, l'algorithme de recherche choisi est dichotomique.
bool Dictionnaire::recherche(const string& nom, Tuile& tuile) const{
    //D�claration des variables locales utiles
    bool res= false;
    int debut=0;
    int fin= _tuiles.size() -1;
    int mil;
    //Boucle
    while(!res && debut<=fin){
        //Calcul du pivot (indice m�dian)
        mil = (debut + fin)/2;
        //Egalite entre le nom de la tuile m�diane et le nom, enregistrer dans "res"
        res = (_tuiles[mil].getNom() == nom);
        //Si �galit� il y a
        if (res){
            //La tuile donn�e en r�f�rence est remplac� par la tuile correspondante
            tuile = _tuiles[mil];
        }
        else{
            //Si le nom de la tuile m�diane est plac� avant alphab�tiquement alors
            if (_tuiles[mil].getNom() < nom){
                //Etant tri�, nous nous int�ressons donc � la seconde moiti� du vecteur
                debut = mil+1;
            }
            else{
                //Etant tri�, nous nous int�ressons donc � la premi�re moiti� du vecteur
                fin = fin-1;
            }

        }
    }
    return res;
}





