#include "abr.h"


// Signature et body des fonction

// Initialisation d'un abre


static tnode *createNode(int data){

	tnode* node=malloc(sizeof(tnode)); //Allocation mémoire

	if(!node)
	{return NULL;} // S'il n'existe pas deja de

	node->data=data; // Inclure la valeur de la cellule
	node->gauche=NULL; // node gauche et droite null
	node->droite=NULL;

	return node;// On retourne notre arbre.
	}


// Free De-allocation ::

// Hyp : on ne peut desallouer la cellule de tete avant celle des autres node;
// On va desallouer par partie, d'un cote les abres de gauche puis les abres de droite puis la racine de l'abre


TreeNode *freefun(TreeNode *abr) {

	// condition du cas particulier : l'abre existe.
	if (abr){ 

		// On libére les nodes de gauche qui remonterons pour liberer ceux de droite

		// 	

		abr->gauche =freefun(abr->gauche);
		abr->gauche =freefun(abr->droite);

		free(abr); // libere la celulle courante

	}
	return NULL; // l'arbre est nul
}


// INSERT ::

TreeNode *insert(TreeNode *abr,int data){

	TreeNode *prec; // Pointeur precendent
	TreeNode *head; // pointeur de tete debut de ABR


	//Cas l'abre est null

	if(!abr) // if(!bt)
	{
		return createNode(data); // crée un node pour data
	}

	while(abr){
		prec = abr; // valeur temporaire pour ne pas perdre la valeur de la tete
		//condition d'insertion gauche ou droite, taille + droite

		if(data < abr<-data){// pour les données numeric, si generique utilise un type void

			abr = abr-> gauche;
		}else{
			abr = abr-> droite;
		}
	}
	//Nouvelle condition , abr sera null, mais precedent atoujour la valeur nitiale

	//
	if(data < prec <-data) // prec car abr est null
	{
		prec-> gauche =createNode(data);

	}
	else
	{
		prec-> droite =createNode(data);
	}

	return head;// premiere cellule de notre abre binaire

}

// RECHERCHE ::

TreeNode *search(TreeNode *abr,int data){

	//parcourir abr

	while(abr)
	{
		if(data < abr-> data)//inferieur
		{
			abr = abr -> gauche;
		}else{
			
				if(data > abr-> data)// superieur
				{
					abr = abr -> droite;
				}
				else{//égal
					return abr;
				}
			
			}
	}

	return NULL;
}

// AFFICHAGE ::

//afficher recusrivement les données car c'est un arbre, la fonction s'appele par elle meme;

void show(TreeNode * abr ){

// Cas particulier : si l'abre existe (affichage gauche droite)

	if(abr)
	{

		show(abr->gauche);//descend vers la gauche jusqua qu'il n'y ait plus de node a gauche
		printf("%ls\n", abr-> data);
		show(abr->droite);//affiche node de droite
	}
}




