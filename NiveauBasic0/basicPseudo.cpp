///Pseudo Code de la Version Basique du Solveur de Sudoku :
    /* Attention cependant cette version permet de résoudre
     * qu'un nombre limité de Sudoku
     */
/// Global : On se place dans le cas de l'Auto RUN (entre 4) :
    /* Lecture de la Grille en memoire
     * Dans chaque Carre on ajoute les nombres manquants au Carre dans les cases vides
     * On détecte ensuite les erreurs sur chaque Ligne
     * Affichage de la Grille avec les erreurs
     */
/// Ajout des nombres manquants dans un Carre :
    /* Tab = {1, 2, 3, 4, 5, 6, 7, 8, 9}
     * POUR chaque case définie du Carre
     *      Mettre a 0 la case de Tab correspondant à la valeur dans la case du Carre
     * POUR chaque case vide du Carre
     *      Mettre la premiere valeur non nul de Tab dans cette case
     *      Mettre a zero la case de Tab passee
     * FIN
     ******** Le carre est maintenant REMPLI !!! ***********
     */
