///Pseudo Code de la Version Advanced par Elimination du Solveur de Sudoku :
    /* Attention cependant cette version permet de résoudre
     * qu'un nombre limité de Sudoku ceux "faciles"
     */
/// Global : On se place dans le cas de l'Auto RUN :
    /* Lecture de la Grille en memoire
     * On regarde quelles nombres peuvent entrer dans chaque case de la grille
     * Si il n'y en a qu'un pour une case il est choisit
     * On recommence ensuite l'opération si on a réussi a ajouter au moins une case
     * sur toute la grille
     * Affichage de la Grille avec toutes les casses résolues
     */
/// Entree dans une case :
    /* TANT QUE (on trouve un nouvel element)
     *      POUR chaque case de la Grille
     *          Tab = {1, 2, 3, 4, 5, 6, 7, 8, 9} // Champ de possibilité
     *          Mettre a zero les nombres pris dans la ligne Horizontale,
     *              la ligne Verticale et le carre
     *          SI (il n'y a plus qu'une valeur non nulle dans le tableau)
     *              Mettre la seule valeur du tableau dans la case
     *              Signifier que l'on a trouve un element
     * FIN
     ******** On espere ainsi remplir la Grille !!! ***********
     */
