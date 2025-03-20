#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


struct rope
{
  struct rope *cut_l;
  struct rope *cross_l;
  struct rope *cut_r;
  struct rope *cross_r;
};

typedef  struct rope rope;
typedef  struct rope knot;

//constructeur

knot *knot_create(knot *c_l,knot *x_l,knot *c_r,knot *x_r)
{
  knot *k=malloc(sizeof(knot));

  k-> cut_l=c_l;
  k-> cross_l=x_l;
  k-> cut_r=c_r;
  k-> cross_r=x_r;

  return k;
}

knot *trivial_knot_create()
{
  knot *k=malloc(sizeof(knot));

  k-> cut_l=k;
  k-> cross_l=NULL;
  k-> cut_r=k;
  k-> cross_r=NULL;

  return k;
}

knot *clover_knot_create()
{
  knot *k1=malloc(sizeof(knot));
  knot *k2=malloc(sizeof(knot));
  knot *k3=malloc(sizeof(knot));

  k1-> cut_l=k3;
  k1-> cross_l=k2;
  k1-> cut_r=k2;
  k1-> cross_r=k3;

  k2-> cut_l=k1;
  k2-> cross_l=k3;
  k2-> cut_r=k3;
  k2-> cross_r=k1;

  k3-> cut_l=k2;
  k3-> cross_l=k1;
  k3-> cut_r=k1;
  k3-> cross_r=k2;

  return k1;
}


int main()
{

return 0;
}
