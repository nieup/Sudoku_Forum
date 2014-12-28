///Pseudo Code de la Version Advanced2 par Propagation du Solveur de Sudoku :
    /* Cette version n'utilise pas completement les cases elle a cependant
     * permit de résoudre tous les Sudoku proposés, même Difficiles
     */
/// Global : On se place dans le cas de l'Auto RUN (entre 3) :
    /* Lecture de la Grille en memoire
     * On choisit un nombre
     * On note quelles cases sont suceptibles de recevoir ce nombre
     * Si il n'y en a qu'une dans une ligne alors on lui affecte ce nombre
     * On recommence ensuite l'opération pour tous les nombres à tour de role
     * Affichage de la Grille avec toutes les casses résolues
     */
/// Entree dans une case : Algorythme abstrait, ce n'est pas réellement 
///   ce qui est fait dans le code mais c'est l'idée 
    /* TANT QUE (on trouve un nouvel element)
     *      POUR chaque case nombre de 1 à 9 
     *          POUR (chaque case) 
	 *				Determiner si elle peut acceuillr ce nombre	// Champ de possibilité
     *          POUR (chaque bloc)
     *              SI (une seule case peut acceuillir le nombre)
     *              	Affecter ce nombre à la case 
     * FIN
     ******** La Grille est REMPLIE !!! ***********
     */
