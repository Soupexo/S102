#include <vector>
#include <string>
#include "Moteur.h"
#include "Image.h"
#include "../include/Personnage.h"
#include "../include/dictionnaire.h"
#include "../include/tuile.h"
#include "../include/objet.h"
#include "../include/niveau.h"

using namespace std;

int main(int, char**) // Version special du main, ne pas modifier
{
    // Initialisation du jeu
    Moteur moteur("Mon super jeu vidéo");
    Image image;
    Image coffre_ferme;
    Image coffre_ouvert;
    Image coffre;
    Image perso;
    Image gameOver;
    Image objets;
    Image bravo;

    try
    {
        //Tentative d'instanciations d'image
        image = Image(moteur, "assets/fond.png");
        perso= Image(moteur, "assets/personnages.png");
        gameOver= Image(moteur,"assets/gameover.png");
        objets = Image(moteur,"assets/objets.png");
        bravo = Image(moteur,"assets/bravo.png");
    }
    //Rattrapage des exceptions "runtime_error"
    catch(const std::runtime_error& e)
    {
        cout<<"erreur"<<endl;
    }
    //Déclaration de quelques variables
    int x_perso=TAILLE_CASE;
    int y_perso=TAILLE_CASE*2;
    //personnage en coordonnee (1,2)
    int x_ennemi1=5*TAILLE_CASE;
    int y_ennemi1=TAILLE_CASE;
    //ennemi1 en coordonnee (5,1)
    int x_ennemi2=TAILLE_CASE;
    int y_ennemi2=5*TAILLE_CASE;
    //ennemi2 en coordonnee (1,5)
    bool avance;
    bool quitter = false;
    string droite = "droite";
    string gauche = "gauche";
    string haut = "haut";
    string bas = "bas";

    //Instanciation du personnage, ennemis, dictionnaire et du niveau.
    Dictionnaire dico("assets/dictionnaire.txt");
    Niveau niveau_1(objets,"assets/niveau1.txt",dico);
    Personnage personnage(perso,x_perso,y_perso,4,0,bas,1,niveau_1);
    Personnage ennemi1(perso,x_ennemi1,y_ennemi1,10,4,droite,1,niveau_1);
    Personnage ennemi2(perso,x_ennemi2,y_ennemi2,1,4,bas,1,niveau_1);

    //Tests de la méthode recherche
    Tuile t;
    bool resultat;
    resultat = dico.recherche("Chemin_brique_horitonzal",t);
    if (!resultat){
        cout<<"Erreur: Le booléen résultat est égal à"<<" "<<resultat<<" "<<"resultat attendu : 1"<<endl;
    }
    else{
        cout<<"Test numero 1 réussi"<<endl;
    }
    cout<<"--------------------------------------------------------------------------------------------------------"<<endl;

    resultat = dico.recherche("chaine",t);
    if (resultat){
        cout<<"Erreur: Le booléen résultat est égal à"<<" "<<resultat<<" "<<"resultat attendu : 0"<<endl;
    }
    else{
        cout<<"Test numero 2 réussi"<<endl;
    }
    // Boucle de jeu, appelee a chaque fois que l'ecran doit etre mis a jour
    // (en general, 60 fois par seconde)
    while (!quitter)
    {
        avance = moteur.animationsAmettreAjour();
        //Verification de la collision entre le personnage et les ennemis
        if (avance)
        {
            ennemi1.avancer();
            ennemi2.avancer();
            quitter = (personnage.touche(ennemi1) || personnage.touche(ennemi2));
        }
        //Victoire du joueur
        if (niveau_1.gagne()){
            quitter = true;
        }
        //Laps de temps en cas de fin de partie
        if (quitter){
            moteur.attendre(1);
        }

        // I. Gestion des evenements
        Evenement evenement = moteur.evenementRecu();
        while (evenement != AUCUN)
        {
            switch (evenement)
            {
            // QUITTER = croix de la fenetre ou Echap
            case QUITTER_APPUYE:
                quitter = true;
                break;
            // TODO: gerer les autres evenements
            case GAUCHE_APPUYE:
                personnage.allerGauche();
                niveau_1.testerBonusEtPrendre(personnage.getX(),personnage.getY());
                break;
            case DROITE_APPUYE:
                personnage.allerDroite();
                niveau_1.testerBonusEtPrendre(personnage.getX(),personnage.getY());
                break;
            case HAUT_APPUYE:
                personnage.allerHaut();
                niveau_1.testerBonusEtPrendre(personnage.getX(),personnage.getY());
                break;
            case BAS_APPUYE:
                personnage.allerBas();
                niveau_1.testerBonusEtPrendre(personnage.getX(),personnage.getY());
                break;
            default:
                break;
            }
            evenement = moteur.evenementRecu();
        }
        // II. Mise à jour de l'état du jeu

        // TODO: faire bouger vos personnages, etc.

        // III. Generation de l'image à afficher

        moteur.initialiserRendu(); // efface ce qui avait ete affiche precedemment et reinitalise en ecran noir
        // TODO: afficher vos personnages, objets, etc.

        image.dessiner(0,0);
        niveau_1.dessiner();
        personnage.dessiner();
        ennemi1.dessiner();
        ennemi2.dessiner();
        //Affichage des écrans de victoire et de défaite sous certaines conditions
        if (quitter && niveau_1.gagne()){
            bravo.dessiner(LARGEUR_FENETRE/5,HAUTEUR_FENETRE/4);
        }
        else if (quitter && !(niveau_1.gagne())){
            gameOver.dessiner(LARGEUR_FENETRE/5,HAUTEUR_FENETRE/3);
        }


        /*
          Affiche l'image en se cadencant sur la frequence de
          rafraichissement de l'ecran (donc va en general mettre le
          programme en pause jusqu'a ce que l'ecran soit rafraichi). En
          general, 60 images fois par seconde, mais ca peut dependre du
          materiel
        */

        moteur.finaliserRendu();
    }

    return 0;
}

