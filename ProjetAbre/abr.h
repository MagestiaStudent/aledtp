// Plus d'info sur README.pdf

// ÉVITER LES INCLUSIONS INFINI

#ifndef point_included
#define point_included

#include <stdio.h>
#include <math.h>
#include <stdlib.h>



// DÉFINITION D'UNE STRUCTURE DE NŒUD  ---


// Un Arbre binaire est une structure contenant un champ de données et deux pointeurs vers des noeuds fils.

typedef struct tnode 
{

	//struct point* data; // Les données du nœud.
	signed int data;
	struct tnode *gauche; // nœud gauche.
	struct tnode *droite; // nœud droite.
	

}TreeNode, tnode; //TreeNode , tnode


// PROTOTYPE DE FONCTION  ---

// Pas d'attribut dans les protoypes

TreeNode *insert(TreeNode *,int ); // id:Insertion

TreeNode *search(TreeNode *,int ); // id:Recherche

TreeNode *freefun(TreeNode *);// id:Free


void show(TreeNode *); // id:Affichage

tnode *createNode(int); //id: Initilisation






#endif

