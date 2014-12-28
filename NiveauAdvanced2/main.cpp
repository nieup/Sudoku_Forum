/**********************************************************
*
*	File : main.cpp
*	Author : Cédric HUMBERT
*
*	Description : Projet Sudoku
*	Version de Avance Solution par PROPAGATION
*       Pour chaque nombre fait un mapinng des
*       cases suceptible d'avoir un ce nombre.
*       Si il n'y a qu'une seule case par ligne ou
*       Carre elle est choisie.
*	Date : 24 Decembre 2014
*
*************************************************************/

#include <iostream>
#include <fstream>

using namespace std;

    /// TO DO : ////// Envoyer sur le GitHub //////////////////
    /**
     *
     * Algo Carrés ??!! marche sans !
     * Error ???
     */
    /// Adresse des FICHIERS !!

    /// DONE :
    /**
     * Fonctionne avec tout les sudoku teste !!
     * IHM
     *
     */



class Bloc{
    int datB[9];
public:

    Bloc(){for(int a = 0 ; a < 9 ; a++){datB[a] = 0;}}

    void setCase(int a, int val){datB[a] = val;}

    bool isInBloc(int val){
        for (int i = 0 ; i < 9 ; i++){
            if (datB[i]==val){return true;}
        }
        return false;
    }
};


class Grille{
    int dataG[9][9];
    bool isPoss[9][9];
    Bloc ligV[9];
    Bloc ligH[9];
    Bloc Carre[9];
public:
    Grille(){
        // Acquisition des Données
        ifstream fluxData("C:/Users/Cédric/Documents/EMSE/Illu-Mines/Sudoku/NiveauAdvanced2/dataLigneInput.txt");
        for (int i = 0 ; i < 9; i++){
            for (int j = 0 ; j < 9 ; j++){
                fluxData >> dataG[i][j];
                ligH[i].setCase(j, dataG[i][j]);
                ligV[j].setCase(i, dataG[i][j]);
                Carre[retCar(i, j)].setCase(retNumCar(i,j), dataG[i][j]);
                if (dataG[i][j] == 0){isPoss[i][j] = true;}
                else {isPoss[i][j]=false;}
            }
        }
    }

    void afficheGrille(){
        cout << "Affichage Grille : " << endl;
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

    void afficheGrillePoss(){
        cout << "Affichage Grille Poss : " << endl;
        for (int i = 0; i < 9 ; i++){
            for (int j = 0 ; j < 9 ; j++){
                if (isPoss[i][j]){cout << "-" ;}
                else {cout << "X";}
                if (j%3 == 2){cout <<".";}
                else {cout << "/";}
            }
            cout << endl;
            if (i%3 == 2){cout <<".................." << endl;}
        }
    }

    void affiche(){
        afficheGrille();
        afficheGrillePoss();
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

    void resetIsPoss(){
        //cout << "Poss Reset ! " << endl;
        for(int i = 0 ; i < 9 ; i++){
            for(int j = 0 ; j < 9 ; j++){
                if (dataG[i][j] == 0){isPoss[i][j] = true;}
                else {isPoss[i][j] = false;}
            }
        }
    }

    void solveProp(){
        bool goOn = true;
        while (goOn){
            goOn = false;
            for(int a = 1 ; a < 10 ; a++){
                //cout << a << endl;
                resetIsPoss();
                reMapIsPoss(a);
                if (setNew(a)){goOn = true;}
                //affiche();
                //cin >> goOn;
            }
            if (filledGrille()){goOn = false; }
            //afficheGrille();
            //cin >> goOn;
        }
    }

    // Attention heavy faire des passages par bloc
    void reMapIsPoss(int val){
        //cout << "ReMap avec : " << val << endl;
        for(int i = 0 ; i < 9 ;  i++){
            for(int j = 0 ; j < 9 ; j++){
                if (isPoss[i][j]){
                    if (ligH[i].isInBloc(val)){isPoss[i][j] = false;}
                    else if (ligV[j].isInBloc(val)){isPoss[i][j] = false;}
                    else if (Carre[retCar(i, j)].isInBloc(val)){isPoss[i][j] = false;}
                }
            }
        }
    }

    bool setNew(int val){
        bool retVal = false;
        for(int i = 0 ; i < 9 ; i++){
            for (int j = 0 ; j < 9 ; j++){
                if (isPoss[i][j]){
                    if(isAlone(i, j)){
                        dataG[i][j] = val;
                        ligV[j].setCase(i, val);
                        ligH[i].setCase(j, val);
                        Carre[retCar(i,j)].setCase(retNumCar(i, j), val);
                        retVal = true;
                        //cout << "Entre : " << dataG[i][j] << " en (" << i << "," << j << ") test : " << (dataG[i][j] != 0) << endl;
                    }
                }
            }
        }
        if(retVal){return true;}
        else{return false;}
    }

    bool isAlone(int L, int C){
        int onlyOne = 0;
        //* Sur la ligne Horizontale :
        for(int a = 0 ; a < 9 ; a++){if(isPoss[L][a]){onlyOne++;}}
        if(onlyOne == 1){return true;}

        // Sur la ligne Verticale  :
        onlyOne = 0;
        for(int a = 0 ; a < 9 ; a++){if(isPoss[a][C]){onlyOne++;}}
        if(onlyOne == 1){return true;}
        //*/

        //* Sur le Carre : " en securite "
        onlyOne = 0;
        int carId = retCar(L,C);
        for (int i = 0 ; i < 9 ; i++){
            for(int j = 0 ; j < 9 ; j++){
                if (retCar(i,j == carId)){
                    if(isPoss[i][j]){onlyOne++;}
                }
            }
        }
        // cout << "Ligne " << L << " Colonne " << C << " Carre " << carId <<  endl; // " couple ("<<i<<","<<j<<")"<<
        if(onlyOne == 1){return true;}
        //*/
        return false;

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

    static int retC(int carId){
        if(carId == 0 || carId == 3 || carId == 6){return 0;}
        else if(carId == 1 || carId == 4 || carId == 7){return 3;}
        else if(carId == 2 || carId == 5 || carId == 8){return 6;}
    }

    static int retL(int carId){
        if(carId == 0 || carId == 1 || carId == 2){return 0;}
        else if(carId >= 3 && carId <= 5 ){return 3;}
        else if(carId > 5){return 6;}
    }
    static int retNumCar(int L, int C){return (L%3)*3 + C%3;}

};



void afficheMenu(){

    cout << "Version Avance2" << endl;
    cout << "Pour utiliser le programme entrer le nombre correspondant : " << endl;
    cout << "\t 1) Lire la grille en Memoire et l'afficher " << endl;
    cout << "\t 2) Resoudre le Sudoku " << endl;
    cout << "\t 3) Auto RUN" << endl;
    cout << "\t 4) Quitter" << endl;
    cout << "Entrer votre choix : ";
}

void executeSudoku(int choix, Grille curGr){
    switch (choix){
        case 1:{
            curGr = Grille();
            curGr.affiche();
            break;
        }
        case 2:{
            curGr = Grille();
            curGr.affiche();
            curGr.solveProp();
            curGr.afficheGrille();
            break;
        }
        case 3:{
            curGr = Grille();
            curGr.solveProp();
            curGr.afficheGrille();
            break;
        }
    }
}



int main(){
    Grille gr = Grille();
    int goOn = 9;
    while (goOn != 4){
        afficheMenu();
        cin >> goOn;
        executeSudoku(goOn, gr);
        cout << "\n \n" << endl;
    }
    cout << "\t Merci de votre Visite au revoir !! "<< endl;
    cout << "\t \t Par Cedric HUMBERT pour Illu-Mines" << endl;
    cin >> goOn;


    return 0;
}

void mainTest(){

    Grille curGr;
    //curGr.solveProp();

    curGr.solveProp();

    cout << "\n FIN AUCUN TRAITEMENT \n " << endl;
    curGr.resetIsPoss();
    //curGr.affiche();
    curGr.afficheGrille();

    /*TEST CARRE isAlone :
    Grille curGr;
    curGr.resetIsPoss();
    curGr.reMapIsPoss(4);
    curGr.afficheGrillePoss();
    cout << " (0,3) : " << curGr.isAlone(0,3)<< endl;
    cout << " (2,5) : " << curGr.isAlone(2, 5)<< endl;
    cout << " (8,8) : " << curGr.isAlone(8, 8)<< endl;

    curGr.solveProp();
    curGr.affiche();
    //*/

    /// TRUE MAIN :
    Grille gr = Grille();
    int goOn = 9;
    while (goOn != 4){
        afficheMenu();
        cin >> goOn;
        executeSudoku(goOn, gr);
        cout << "\n \n" << endl;
    }
    cout << "\t Merci de votre Visite au revoir !! "<< endl;
    cout << "\t \t Par Cedric HUMBERT pour Illu-Mines" << endl;
    cin >> goOn;

}
