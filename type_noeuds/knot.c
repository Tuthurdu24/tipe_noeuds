#include "myknot.h"    // définition du type et des primitives

//constructeur

knot *knot_create()
{
  knot *k=malloc(sizeof(knot));

  k-> cut_p = NULL;
  k-> x_p = NULL;
  k-> cut_n= NULL;
  k-> x_n= NULL;
  
  return k;
}

knot *trivial_knot_create()
{
  knot *k=malloc(sizeof(knot));

  k-> cut_p=k;
  k-> x_p=NULL;
  k-> cut_n=k;
  k-> x_n=NULL;

  return k;
}

knot *clover_knot_create()
{
  knot *k1=malloc(sizeof(knot));
  knot *k2=malloc(sizeof(knot));
  knot *k3=malloc(sizeof(knot));
  
  k1-> cut_p=k3;
  k1-> x_p=k2;
  k1-> cut_n=k2;
  k1-> x_n=k3;

  k2-> cut_p=k1;
  k2-> x_p=k3;
  k2-> cut_n=k3;
  k2-> x_n=k1;

  k3-> cut_p=k2;
  k3-> x_p=k1;
  k3-> cut_n=k1;
  k3-> x_n=k2

  return k1;
}

knot* clover_knot_create_rapide()
{
  knot *k1=malloc(sizeof(knot));
  knot *k2=malloc(sizeof(knot));
  knot *k3=malloc(sizeof(knot));
  
  knot_tie(k1, k2, k3);
  knot_tie(k2, k3, k1);
  knot_tie(k3, k1, k2);
}

void knot_tie(knot* kp, knot* kn, knot* k_up)       // "attache" les cordes kp (knot_previous) et kn (knot_next) et fait passer la corde k_up au dessus de l'intersection.
{
  assert(kp != NULL && kn != NULL && k_up != NULL);

  kp->cut_n = kn;
  kn->cut_p = kp;

  kp->x_n = k_up;
  kn->x_p = k_up;
  
  
  return;
}


int main()
{

return 0;
}
