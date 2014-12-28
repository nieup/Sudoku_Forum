/**********************************************************
*
*	File : main.cpp
*	Author : Cédric HUMBERT
*
*	Description : Projet Sudoku
*	Version de Avance Solution par ELIMINATION
*       Regarde chaque case et détermine ce qui
*       peut aller pour cette case en fonction
*       du carre et des lignes dans laquelle elle
*       se trouve.
*	Date : 23 Decembre 2014
*
*************************************************************/

#include <iostream>
#include <fstream>


using namespace std;

    /// TO DO : ////// Envoyer sur le GitHub //////////////////
    /**
     *
     *
     */
    /// Adresse des FICHIERS !!

    /// DONE :
    /**
     * Marche pour le NIVEAU FACILE Uniquement
     */



class Bloc{
    int datB[9];
public:
    Bloc(){for(int a = 0 ; a < 9 ; a++){datB[a] = 0;}}

    void setCase(int a, int val){datB[a] = val;}

    void freeInBloc(int freeCase[9]){
        int *all;
        all = freeCase;
        // Quelles nombres restent-ils à trouver dans le carre ?
        for(int i = 0 ; i < 9 ; i++){
            if (datB[i] != 0){all[datB[i]-1] = 0;}
        }
    }
};


class Grille{
    int dataG[9][9];
    Bloc ligV[9];
    Bloc ligH[9];
    Bloc Carre[9];
public:
    Grille(){

        // Acquisition des Données
        ifstream fluxData("C:/Users/Cédric/Documents/EMSE/Illu-Mines/Sudoku/NiveauAdvanced/dataLigneInput.txt");
        for (int i = 0 ; i < 9; i++){
            for (int j = 0 ; j < 9 ; j++){
                fluxData >> dataG[i][j];
                ligH[i].setCase(j, dataG[i][j]);
                ligV[j].setCase(i, dataG[i][j]);
                Carre[retCar(i, j)].setCase(retNumCar(i,j), dataG[i][j]);
            }
        }
    }

    void afficheGrille(){
        for (int i = 0; i < 9 ; i++){
            for (int j = 0 ; j < 9 ; j++){
                cout << dataG[i][j];
                if (j%3 == 2){cout <<".";}
                else {cout << "/";}
            }
            cout << endl;
            if (i%3 == 2){cout <<".................." << endl;}
        }
    }

    void solve(){
        int all[9];
        int valid;
        int val;
        int found = 0;
        bool goOn = true;
        while (goOn){
            // On boucle tant que l'on trouve de nouveau elements
            goOn = false;

            // On regarde toutes les cases
            for(int i = 0 ; i < 9 ;  i++){
                //cout << " Ligne : " << i << endl;
                for(int j = 0 ; j < 9 ; j++){
                    if (dataG[i][j] == 0){
                        //cout << " Colone : " << j << endl;
                        // Remet toutes les possibilités
                        for(int a = 0 ; a < 9 ; a++){all[a] = a+1;}
                        valid = 0;
                        val = 0;

                        // Recherche des nombres possbibles
                        ligV[j].freeInBloc(all);
                        ligH[i].freeInBloc(all);
                        Carre[retCar(i, j)].freeInBloc(all);
                        for(int a = 0 ; a < 9 ; a++){
                            if(all[a] != 0){
                                valid++;
                                val = all[a];
                            }
                        }
                        if (valid == 1){
                            dataG[i][j] = val;
                            ligH[i].setCase(j, dataG[i][j]);
                            ligV[j].setCase(i, dataG[i][j]);
                            Carre[retCar(i, j)].setCase(retNumCar(i,j), dataG[i][j]);
                            goOn = true;
                            found++;
                            //cout << dataG[i][j] << " et (" << i << "," << j << ")"<< endl;
                        }
                    }
                }
            }
            //cout << goOn << endl;
        }
        cout << "Lors de cette iteration : " << endl;
        cout << "Trouve : " << found << " Case(s)" << endl;
    }

    // Retourne Vrai si la Grille est remplie
    bool filledGrille(){
        bool fini = true;
        for(int i = 0 ; i < 9 ;  i++){
            for(int j = 0 ; j < 9 ; j++){
                if (dataG[i][j] == 0){fini = false;}
            }
        }
        if (fini){return true;}
        else{return false;}
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

};


int main()
{
    char wait;
    cout << "Lancement de l'acquisition de Données : " << endl;
    // Test Acquisition Donnee :
    Grille curGr = Grille();
    curGr.afficheGrille();
    cout << "\n \n" << endl;
    curGr.solve();
    cout << "Resultats du Solveur : ";
    if (curGr.filledGrille()){cout << "Success !! \n" << endl;}
    else {cout << "Fail :( \n" << endl;}
    curGr.afficheGrille();
    cin >> wait;
    return 0;
}

void mainTest(){
    /** Test Acquisition Donnee : GOOD
    Grille curGr = Grille();
    curGr.afficheGrille();
    */
    /** Test Solveur : GOOD
    cout << "\n \n" << endl;
    curGr.solve();
    curGr.afficheGrille();
    */
}
