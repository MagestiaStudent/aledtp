#include <stdio.h>
#include <stdlib.h>
#include "abr.h"

// ID de Function 

//id: Initilisation (createNode)

//id:Insertion (insert)

// id:Recherche (search)

// id:Free (freefun)

// id:Affichage (show)


int main(void){

 // Cas initilisation :  L'arbre est vide.

	TreeNode *abr= NULL;

 // Stockage des mes notes sur u12 ( 10 est le 0 )
	//: (-8) -2.5 / 0 / 2.250 / 2.500 / 4 / 6 / 10

	// Head : 0 (10) ; Min : -8 (2 ) ; Max : 10 (20)

	// Insertion de valeurs :

	abr = insert(abr,0);
	abr = insert(abr,-8);
	abr = insert(abr,-3);
	abr = insert(abr,2);
	abr = insert(abr,3);
	abr = insert(abr,4);
	abr = insert(abr,6);
	abr = insert(abr,10);

   //Afficher l'arbre :

	show(abr);
	printf("-> %ls\n", search(abr,6)-> data);

	// Liberer l'arbre :

	abr=freefun(abr);









}