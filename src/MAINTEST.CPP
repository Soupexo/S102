#include <vector>
#include <string>
#include "Moteur.h"
#include "Image.h"
#include "../include/Personnage.h"
#include "../include/dictionnaire.h"
#include "../include/tuile.h"

using namespace std;

int main (int, char**)
{
    Tuile t;
    bool resultat;
    Dictionnaire dico("assets/dictionnaire.txt");
    resultat = dico.recherche("Chemin_brique_horitonzal",t);
    if (!resultat){
        cout<<"Erreur: Le booléen résultat est égal à"<<" "<<resultat<<" "<<"resultat attendu : 1"<<endl;
    }
    cout<<"--------------------------------------------------------------------------------------------------------"<<endl;

    resultat = dico.recherche("chaine",t);
    if (resultat){
        cout<<"Erreur: Le booléen résultat est égal à"<<" "<<resultat<<" "<<"resultat attendu : 0"<<endl;
    }
return 0;

}

