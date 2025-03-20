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

knot *knot_create(knot *c_l,knot *x_l,knot *c_r,knot *x_r)
{
  knot *k=malloc(sizeof(knot));
  k-> cut_l=c_l;
  k-> cross_l=x_l;
  k-> cut_r=c_r;
  k-> cross_r=x_r;

  return k;
}

int main()
{

return 0;
}
