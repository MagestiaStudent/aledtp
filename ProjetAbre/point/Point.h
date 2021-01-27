#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// ÉVITER LES INCLUSIONS INFINI

#ifndef point_included
#define point_included

// DÉFINITION D'UNE STRUCTURE DE POINT

struct point{
	int x;
	int	y;
	int z;
};

// FICHIER DE PROTOTYPES

double carre(double val);

double dist(struct point p1, struct point p2 );




#endif