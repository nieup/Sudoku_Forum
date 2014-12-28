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

    /// TO DO : ////// Envoyer sur le GitHub //////////////////
    /**
     * FINI !
     */
    /// Adresse des FICHIERS !!


class ErrorCheck{
public:
    ErrorCheck(){
        for (int a = 0 ; a < 9 ; a++){error[a] = false;}
    }

    void errorCh1(int inAr[9]){
        int all[9];
        // Init de all à zero
        for (int a = 0 ; a < 9 ; a++){all[a] = 0;}

        // Lecture des données
        for (int a = 0 ; a < 9 ; a++){
            all[inAr[a]-1]++;
        }

        for (int a = 0 ; a < 9 ; a++){
            if(all[a] >= 2){
                for(int i = 0 ; i < 9 ; i++){
                    if (inAr[i] == a+1){
                        error[i] = true;
                    }
                }
            }
        }
    }

    void errorReset(){
        for (int a = 0 ; a < 9 ; a++){error[a] = false;}
    }

    bool getError(int a){return error[a];}

    void setError(int a){error[a] = true; }

    void errorDisplay(){
        for (int a = 0 ; a < 9 ; a++){
            if (error[a]){cout << "E" << " ";}
            else {cout << "J" << " ";}
            if (a%3 == 2){{cout <<"/";}}
        }
        cout << endl;
    }

private:
    bool error[9];
};

void errorCorrespond(ErrorCheck errorH[9], ErrorCheck errorV[9]){
    for (int i = 0 ; i < 9 ; i++){
        for (int j = 0 ; j < 9 ; j++){
            if (errorV[j].getError(i)){
                errorH[i].setError(j);
            }
        }
    }
}


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
        ifstream fluxData("dataLigneInput.txt");
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
        // C:/Users/Cédric/Documents/EMSE/Illu-Mines/Sudoku/NiveauBasic0/
        ifstream fluxData("dataInput.txt");
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
    // THE FONCTION !!
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
    ERREUR En cours : Lignes Verticales
    User Interface ?? CLI
    */

public:
    Grille (){
        for (int i = 0; i < 9 ; i++){
            gridCar[i] = Carre();
            ligCar[i] = Ligne();
            ligCarV[i] = Ligne();
            error[i] = ErrorCheck();
            errorV[i] = ErrorCheck();
        }
    }

    void afficheGrille(){
        for (int i = 0; i < 9 ; i++){
            gridCar[i].affiche();
            cout << i << endl;
        }
    }

    void afficheLigne(){
        cout << "La grille de Sudoku : " << endl;
        for (int i = 0; i < 9 ; i++){
            ligCar[i].afficheLigne();
            if (i == 2 || i == 5 ){cout << "...................."<< endl;}
        }
        cout << endl;
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
        cout << "Sudoku Resolu !! " << endl;
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
                ligCarV[j].fillLigne(i, ligCar[i].getDataL(j));
            }
        }
    }

    void afficheVerLig(int i){
        cout << endl;
        ligCarV[i].afficheLigne();
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

    void errorCheckH(){
        cout << endl << "Detection des erreurs : " << endl;
        for (int a = 0 ; a < 9 ; a++){
            // Lignes Verticales
            error[a].errorReset();
            error[a].errorCh1(ligCar[a].dataL);
            errorV[a].errorReset();
            errorV[a].errorCh1(ligCarV[a].dataL);
        }
        // Ajout des erreurs Verticales
        errorCorrespond(error, errorV);
        cout << "Erreurs trouvées" << endl;
    }
    void errorDisplay(){
        cout << "Affichage des Erreurs" << endl;
        for (int i = 0 ; i < 9 ; i++){
            for (int j = 0 ; j < 9 ; j++){
                if(error[i].getError(j)){cout << "(" << ligCar[i].dataL[j] << ")";}
                else {cout << " " << ligCar[i].dataL[j] << " ";}
                if (j%3 == 2){cout <<"/";}
            }
            cout << endl;
            if (i%3 == 2){{cout <<"............................." << endl;}}
        }
    }



private: // Eventuellement faire des pointeurs sur un tableau unique :/
    ErrorCheck error[9];
    ErrorCheck errorV[9];
    Carre gridCar[9];
    Ligne ligCar[9]; // Lignes Horizontales
    Ligne ligCarV[9]; // Lignes Verticales

};

// Fonctions Locales :
void afficheMenu();
void executeSudoku(int choix, Grille curGr);

int main()
{
    Grille gr = Grille();
    int goOn = 9;
    while (goOn != 5){
        afficheMenu();
        cin >> goOn;
        executeSudoku(goOn, gr);
    }
    cout << "\t Merci de votre Visite au revoir !! "<< endl;
    cout << "\t \t Par Cedric HUMBERT pour Illu-Mines" << endl;

    return 0;
}

void afficheMenu(){
    cout << endl << endl;
    cout << "Version Basique" << endl;
    cout << "Pour utiliser le programme entrer le nombre correspondant : " << endl;
    cout << "\t 1) Lire la grille en Memoire " << endl;
    cout << "\t 2) Resoudre le Sudoku " << endl;
    cout << "\t 3) Afficher les erreurs " << endl;
    cout << "\t 4) Auto RUN" << endl;
    cout << "\t 5) Quitter" << endl;
    cout << "Entrer votre choix : ";
}

void executeSudoku(int choix, Grille curGr){
    switch (choix){
        case 1:{
            curGr.fillGrilleWLigne();
            curGr.afficheLigne();
            break;
        }
        case 2:{
            curGr.correspondLiWiGril();
            curGr.solveGrille();
            curGr.correspondGrilWiLi();
            curGr.afficheLigne();
            break;
        }
        case 3:{
            curGr.fillGrilleWLigne();
            curGr.correspondLiWiGril();
            curGr.solveGrille();
            curGr.correspondGrilWiLi();
            curGr.errorCheckH();
            curGr.errorDisplay();
            break;
        }
        case 4:{
            curGr.fillGrilleWLigne();
            curGr.afficheLigne();
            curGr.correspondLiWiGril();
            curGr.solveGrille();
            curGr.correspondGrilWiLi();
            curGr.afficheLigne();
            curGr.errorCheckH();
            curGr.errorDisplay();
            break;
        }
    }



}



void mainTest(){

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

    /**Test Grille Erreur : Works sur les lignes Horizontales
    Grille gr = Grille();
    gr.fillGrilleWLigne();
    gr.correspondLiWiGril();
    gr.solveGrille();
    gr.correspondGrilWiLi();
    gr.errorCheckH();
    */

    /** Pour la démo :
    Grille gr = Grille();
    gr.fillGrilleWLigne();
    // Affichage la grille lue :
    gr.afficheLigne();
    //cin >> goOn;

    // Resolution du Sudoku :
    gr.correspondLiWiGril();
    gr.solveGrille();
    gr.correspondGrilWiLi();
    gr.afficheLigne();
    //cin >> goOn;

    // Gestion des erreurs :
    gr.errorCheckH();
    gr.errorDisplay();

    */
}
