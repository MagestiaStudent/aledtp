// FICHIER D'IMPLÉMENTATION DES FONCTION DE POINT.H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Point.h"

// FONCTION CARRÉ

double carre(double val){
	return val*val;
}

// FONCTION DISTANCE SUR UN PLAN X,Y,Z

double dist( struct point p1, struct point p2 ) {

    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int dz = p2.z - p2.z;
 
    return sqrt( carre(dx) + carre(dy) + carre(dz) );
}