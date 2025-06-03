#include <SDL_image.h>
#include <string>
#include <vector>
#include "../include/niveau.h"
#include "Image.h"
#include "../include/Personnage.h"

///Variables directionnelles
string droite = "droite";
string gauche = "gauche";
string haut = "haut";
string bas = "bas";

///Vecteur directionnelles (utile au d�placement al�atoire (Voir la m�thode avancer))
vector <string> vectDirection = {droite,gauche,haut,bas};

///Constructeurs

// Constructeur par d�faut
Personnage::Personnage()
{
}

// Constructeur avec param�tres
Personnage::Personnage(const Image& image, int x, int y, int skin_x, int skin_y,string& direction,int posAnim,const Niveau& niveau)
{
     Image img=image;
    _image=img;
    _abscisse=x;
    _ordonnee=y;
    _skin_x = skin_x;
    _skin_y = skin_y;
    _posAnim = posAnim;
    _niveau = niveau;
    mettreAJourDirection(direction);
}

/// M�thodes pour obtenir les coordonn�es x et y
int Personnage::getX() const
{
  return _abscisse;
}

int Personnage::getY() const
{
  return _ordonnee;
}

// M�thode pour dessiner le personnage
void Personnage::dessiner() const
{
  _image.dessiner(_abscisse, _ordonnee);
}
///Fonction d'avancement dans les 4 directions, elles suivent la m�me structure : test de collision par l'appel de bordAtteint et si le bord est atteint, la fonction renverra -1 sinon elle renverra 0
int Personnage::allerDroite(){
    bool atteint = bordAtteint(droite);
    if (!atteint){
       _abscisse += TAILLE_CASE;
        mettreAJourDirection(droite);
    }
    else{
        return -1;
    }
    return 0;
}
int Personnage::allerGauche(){
    bool atteint = bordAtteint(gauche);
    if (!atteint){
        _abscisse -= TAILLE_CASE;
        mettreAJourDirection(gauche);
    }
    else{
        return -1;
    }
    return 0;
}
int Personnage::allerHaut(){
    bool atteint = bordAtteint(haut);
    if (!atteint){
        _ordonnee -= TAILLE_CASE;
        mettreAJourDirection(haut);

    }
    else{
        return -1;
    }
    return 0;
}
int Personnage::allerBas(){
    bool atteint = bordAtteint(bas);
    if (!atteint){
        _ordonnee += TAILLE_CASE;
        mettreAJourDirection(bas);
    }
    else{
        return -1;
    }
    return 0;
}
//Fonction qui permet aux ennemis d'avancer al�atoirement dans une direction
void Personnage::avancer(){
    //D�claration de l'entier al�atoire parmis 0,1,2 et 3
    int nombre = rand() % 4;
    int peutAvancer = 0;
    //Direction mise � jour
    _direction = vectDirection[nombre];
    //Jeu de conditions pour chaque cas directionnel
    if (_direction == droite){
        peutAvancer = allerDroite();
        if (peutAvancer == -1){
            //Si le personnage ne peut avancer � droite, inverser la direction et avancer � gauche.
            mettreAJourDirection(gauche);
            peutAvancer = allerGauche();
        }
    }
    else if(_direction == gauche){
        peutAvancer = allerGauche();
        if (peutAvancer == -1){
            //Si le personnage ne peut avancer � gauche, inverser la direction et avancer � droite.
            mettreAJourDirection(droite);
            peutAvancer = allerDroite();
        }
    }
    else if(_direction ==  bas){
        peutAvancer = allerBas();
        if (peutAvancer == -1){
            //Si le personnage ne peut avancer en bas, inverser la direction et avancer en haut.
            mettreAJourDirection(haut);
            peutAvancer = allerHaut();
        }
    }
    else if(_direction == haut){
        peutAvancer = allerHaut();
        if (peutAvancer == -1){
            //Si le personnage ne peut avancer en haut, inverser la direction et avancer en bas.
            mettreAJourDirection(bas);
            peutAvancer = allerBas();
        }
    }
}
//Fonction qui permet de v�rifier si le bord a �t� atteint (true => bord atteint et false => bord non atteint)
bool Personnage::bordAtteint(const string& direc) const{
    //Si le personnage se dirige vers le haut ET que les coordonn�es m�nent � un d�passement des limites du terrain OU que le personnage se dirige vers le haut et que la case n'est pas libre alors
    if ((direc == haut && _ordonnee - TAILLE_CASE < 0) || (direc == haut && !(_niveau.caseEstLibre(_abscisse,_ordonnee-TAILLE_CASE) )))
        return true;
    //Si le personnage se dirige vers le bas ET que les coordonn�es m�nent � un d�passement des limites du terrain OU que le personnage se dirige vers le bas et que la case n'est pas libre alors
    else if ((direc == bas && _ordonnee + TAILLE_CASE >= HAUTEUR_FENETRE) || (direc == bas && !(_niveau.caseEstLibre(_abscisse,_ordonnee+TAILLE_CASE) )))
        return true;
    //Si le personnage se dirige vers la gauche ET que les coordonn�es m�nent � un d�passement des limites du terrain OU que le personnage se dirige vers la gauche et que la case n'est pas libre alors
    else if ((direc == gauche &&  _abscisse - TAILLE_CASE < 0) || (direc == gauche && !(_niveau.caseEstLibre(_abscisse-TAILLE_CASE,_ordonnee))))
        return true;
    //Si le personnage se dirige vers la droite ET que les coordonn�es m�nent � un d�passement des limites du terrain OU que le personnage se dirige vers la droite et que la case n'est pas libre alors
    else if ((direc == droite && _abscisse + TAILLE_CASE >= LARGEUR_FENETRE) || (direc == droite && !(_niveau.caseEstLibre(_abscisse+TAILLE_CASE,_ordonnee))))
        return true;
    return false;
}
//Fonction qui permet de mettre � jour la direction et qui, par le biais de la m�thode selectionnerRectangle, de s�lectionner le bon sprite.
void Personnage::mettreAJourDirection(const string& direc){
    _direction = direc;
    int val=0;
    //Appel et m�morisation de la valeur renvoy� de la m�thode mettreAjourAnimation
    val = mettreAjourAnimation();
    //Actualisation de la valeur de _skin_x (ici uniquement _skin_x doit varier)
    _skin_x += val;
    //Jeu de conditions directionnelles
    if (direc == droite){
        _image.selectionnerRectangle((_skin_x)*TAILLE_CASE,(_skin_y+2)*TAILLE_CASE,TAILLE_CASE,TAILLE_CASE);
    }
    else if (direc== gauche){
        _image.selectionnerRectangle((_skin_x)*TAILLE_CASE,(_skin_y+1)*TAILLE_CASE,TAILLE_CASE,TAILLE_CASE);
    }
    else if (direc == haut){
        _image.selectionnerRectangle((_skin_x)*TAILLE_CASE,(_skin_y+3)*TAILLE_CASE,TAILLE_CASE,TAILLE_CASE);
    }
    else{
        _image.selectionnerRectangle((_skin_x)*TAILLE_CASE,(_skin_y)*TAILLE_CASE,TAILLE_CASE,TAILLE_CASE);
    }
    //_skin_x revient � son �tat ant�rieur apr�s la s�lection de la "bonne" partie de l'image
    _skin_x -= val;
}
//Fonction qui permet de v�rifier l'impact entre le personnage et l'ennemi (true => il y a eu impact et false=> il n'y a pas eu d'impact)
 bool Personnage::touche(const Personnage& P){
    if (_abscisse == P.getX() && _ordonnee == P.getY()){
        return true;
    }
    return false;
 }

//Fonction qui permet d'animer en enchainant, selon l'�tat de l'attribut _posAnim, les diff�rents sprites pour �muler un mouvement de marche. val_x est ici la valeur � ajouter � _skin_x pour obtenir le bon sprite (on suppose _skin_x correspondant � l'�tat immobile)
 int Personnage::mettreAjourAnimation(){
    int val_x=0;
    //Si _posAnim est divisible par 4 (Sprite dont la jambe droite est � l'avant)
    if (_posAnim % 4 == 0){
        _posAnim += 1;
        val_x = -1;
    }
    //Si _posAnim est congru � 1 modulo 4 (Sprite immobile)
    else if (_posAnim % 4 == 1 || _posAnim % 4 ==3 ){
        _posAnim += 1;
         val_x = 0;
    }
    //Si _posAnim est congru � 2 modulo 4 (Sprite dont la jambe gauche est � l'avant)
    else if (_posAnim % 4 == 2){
        _posAnim += 1;
         val_x = 1;
    }
    return val_x;

 }

