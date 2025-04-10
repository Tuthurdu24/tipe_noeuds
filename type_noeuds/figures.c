#include "myknot.h"

//figures

knot *trivial_knot_create()
{
  knot *k = malloc(sizeof(knot));

  knot_tie(k, k, NULL);

  return k;
}

knot* clover_knot_create()
{
  knot *k1=malloc(sizeof(knot));
  knot *k2=malloc(sizeof(knot));
  knot *k3=malloc(sizeof(knot));

  knot_tie(k1, k2, k3);
  knot_tie(k2, k3, k1);;
  knot_tie(k3, k1, k2);

  return k1;
}

knot* star_knot_create()
{
  knot *k1=malloc(sizeof(knot));
  knot *k2=malloc(sizeof(knot));
  knot *k3=malloc(sizeof(knot));
  knot *k4=malloc(sizeof(knot));
  knot *k5=malloc(sizeof(knot));

  knot_tie(k1, k2, k4);
  knot_tie(k2, k3, k5);
  knot_tie(k3, k4, k1);
  knot_tie(k4, k5, k2);
  knot_tie(k5, k1, k3);

  return k1;
}

knot* braid_knot_create()
{
  knot* k1=malloc(sizeof(knot));
  knot* k2=malloc(sizeof(knot));
  knot* k3=malloc(sizeof(knot));
  knot* k4=malloc(sizeof(knot));
  knot* k5=malloc(sizeof(knot));

  knot_tie(k1, k2, k1);
  knot_tie(k2, k4, k3);
  knot_tie(k4, k5, k5);
  knot_tie(k5, k3, k4);
  knot_tie(k3, k1, k2);

  return k1;
}
