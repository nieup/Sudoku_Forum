
/**********************************************************
*
*	File : main.cpp
*	Author : Cédric HUMBERT
*
*	Description : Projet Sudoku
*	Version de base avec generation de carré aléatoire
*
*
*
*
*	Date : 19 Decembre 2014
*
*************************************************************/
#include <iostream>
#include <fstream>


using namespace std;


    /// TO DO :
    /**
    ERREUR !
    Envoyer sur le GitHub
    */

class Ligne{
public:
    Ligne(){
        for (int i = 0; i < 9 ; i++){
            dataL[i] = 0;
        }
    }

    void afficheLigne(){
        for(int i = 0 ; i < 9 ; i++){
            cout << dataL[i] << "/";
            if (i == 2 || i == 5){cout << ".";}
        }
        cout << endl;
    }

    void getData(int Ln){
        int L1, place, iDLigne;
        ifstream fluxData("C:/Users/Cédric/Documents/EMSE/Illu-Mines/Sudoku/NiveauBasic0/dataLigneInput.txt");
        for (iDLigne = 0 ; iDLigne < Ln; iDLigne++){
            for (place = 0 ; place < 9 ; place++){
                fluxData >> L1;
            }
        }
        for (place = 0; place < 9 ; place++){
            fluxData >> L1;
            dataL[place] = L1;
        }
    }

    void fillLigne(int i, int val){
        dataL[i] = val;
    }

    int getDataL(int i){
        return dataL[i];
    }

private:
    int dataL[9];
};


class Carre{
    /// TO DO :
    /**
    */

public:
    Carre(){
        for (int i = 0; i < 9 ; i++){
            data[i] = 0;
        }
    }
    void affiche(){
        for(int i = 0 ; i < 3 ; i++){
            for(int j = 0 ; j < 3 ; j++){
                cout << data[3 * i+j] << "/";
            }
            cout << endl;
        }
    }
    void fillCarre(int a, int val){
        data[a] = val;
    }
    void getData(){
        int L1, L2, L3, place;
        ifstream fluxData("C:/Users/Cédric/Documents/EMSE/Illu-Mines/Sudoku/NiveauBasic0/dataInput.txt");
        for (place = 0; place < 3 ; place++){
            fluxData >> L1 >> L2 >> L3;
            fillCarre(3 * place, L1);
            fillCarre(3 * place + 1, L2);
            fillCarre(3 * place + 2, L3);
        }
    }

    int getDataG(int a){
        return data[a];
    }
    // THE FONCTION !! Penser à faire de la récurence  dedans ou pas loin...
    void solve(){
        int all[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        // Quelles nombres restent-ils à trouver dans le carre ?
        for(int i = 0 ; i < 9 ; i++){
            if (data[i] != 0){all[data[i]-1] = 0;}
        }

        // Pour chaque zero mettre un de ces nombres
        for(int i = 0 ; i < 9 ; i++){
            if (data[i] == 0){
                for(int j = 0 ; j < 9 ; j++){
                    if (all[j] != 0){
                        data[i] = all[j];
                        all[j] = 0;
                        j = 10;
                    }
                }
            }
        }
    }

private:
    int data[9];
};

class Grille{
    /// TO DO :
    /**
    ERREUR En cours
    Lignes Verticales
    */

public:
    Grille (){
        for (int i = 0; i < 9 ; i++){
            gridCar[i] = Carre();
            ligCar[i] = Ligne();
        }
    }

    void afficheGrille(){
        for (int i = 0; i < 9 ; i++){
            gridCar[i].affiche();
            cout << i << endl;
        }
    }

    void afficheLigne(){
        for (int i = 0; i < 9 ; i++){
            ligCar[i].afficheLigne();
            if (i == 2 || i == 5 ){cout << "...................."<< endl;}
        }
    }

    void fillGrilleWCarre(){
        for (int i = 0; i < 9 ; i++){
            gridCar[i].getData();
        }
    }

    void fillGrilleWLigne(){
        for (int i = 0; i < 9 ; i++){
            ligCar[i].getData(i);
        }
    }

    void solveGrille(){
        for (int i = 0; i < 9 ; i++){
            gridCar[i].solve();
        }
    }

    void correspondLiWiGril(){
        for (int i = 0 ; i < 9 ; i++){
            for(int j = 0; j < 9 ; j++){
                gridCar[retCar(i, j)].fillCarre(retNumCar(i, j),ligCar[i].getDataL(j));
            }
        }
    }


    void correspondGrilWiLi(){
        for (int i = 0; i < 9 ; i++){
            for (int j = 0; j < 9 ; j++){
                ligCar[i].fillLigne(j, gridCar[retCar(i,j)].getDataG(retNumCar(i,j)));
            }
        }
    }

    static int retCar(int L, int C){
        if (L < 3){
            return (int)C/3;
        }
        else if(L < 6){
            return 3 + (int)C/3;
        }
        else if(L < 9){
            return 6 + (int)C/3;
        }
        else {return 0; }
    }

    static int retNumCar(int L, int C){
        return (L%3)*3 + C%3;
    }

    void errorCheck(){

    }

    void errorDisplay(){


    }

private: // Eventuellement faire des pointeurs sur un tableau unique :/
    Carre gridCar[9];
    Ligne ligCar[9]; // Lignes Horizontales Seulement

};


int main()
{
    /** Test Carré OK :
    Carre carIn = Carre();
    carIn.getData();
    carIn.affiche();
    cout << endl;
    carIn.solve();
    carIn.affiche();
    */

    /** Test Grille : SUCCESS Partie 1
    Grille gr1 = Grille();
    gr1.fillGrilleWCarre();
    gr1.afficheGrille();
    cout << endl;
    cout << endl;
    gr1.solveGrille();
    gr1.afficheGrille();
    */

    /** Test Ligne : OK
    Ligne Lg = Ligne();
    Lg.getData(5);
    Lg.fillLigne(2, 88);
    Lg.afficheLigne();
    */

    /** Test Grille Partie 2 : En Cours
    Grille gr = Grille();
    gr.fillGrilleWLigne();
    gr.afficheLigne();
    gr.correspondLiWiGril();
    gr.solveGrille();
    gr.afficheGrille();
    gr.correspondGrilWiLi();
    gr.afficheLigne();
    */

    //Test Grille Erreur :
    Grille gr = Grille();
    gr.fillGrilleWLigne();
    gr.correspondLiWiGril();
    gr.solveGrille();
    gr.correspondGrilWiLi();
    gr.errorCheckH();
    gr.errorDisplay();

    return 0;
}
