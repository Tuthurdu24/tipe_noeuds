#include "myknot.h"    // définition du type et des primitives

// constructeurs

knot *knot_create()
{
  knot *k=malloc(sizeof(knot));

  k-> cut_p = NULL;
  k-> x_p = NULL;
  k-> cut_n= NULL;
  k-> x_n= NULL;
  
  return k;
}

//         figures
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


// transformateurs

void knot_tie(knot* kp, knot* kn, knot* k_up)       // "attache" les cordes kp (knot_previous) et kn (knot_next) et fait passer la corde k_up au dessus de l'intersection.
{
  assert(kp != NULL && kn != NULL);

  kp->cut_n = kn;
  kn->cut_p = kp;

  kp->x_n = k_up;
  kn->x_p = k_up;
  
  
  return;
}


// accesseurs

int count_cross(knot* k)         // PAS ENCORE OK: si une corde se croise elle meme, est ce qu'on le croisement???????????????????? 
{
  assert(k != NULL);
  rope* curr_r = k->cut_n;
  rope* stop = k;
  int n_cross = 0;

  if(k != k->cut_n)
    {
      n_cross = 1;
      while(curr_r != stop)
	{
	  
	  if(curr_r->x_n != NULL)
	    n_cross = n_cross + 1;
	  
	  curr_r = curr_r->cut_n;
	}
    }
  
  return n_cross;
}

// destructeurs

void knot_free(knot** addr_k)
{
  assert(addr_k != NULL && *addr_k != NULL);
  rope* curr_r = (*addr_k)->cut_n;
  rope* tmp;
  
  while(curr_r != *addr_k)
    {
      tmp = curr_r;
      curr_r = curr_r->cut_n;
      free(tmp);
    }

  free(*addr_k);
  *addr_k = NULL;
  
  return;
}


int main()
{
  knot* clover = clover_knot_create();
  int n = count_cross(clover);
  printf("Nombre de croissements pour le noeud trèfle: %d\n", n); 

  knot* simple = trivial_knot_create();
  int nt = count_cross(simple);
  printf("Nombre de croisements pour le noeud simple: %d\n", nt);

  knot* star = star_knot_create();
  int ns = count_cross(star);
  printf("Nombre de croisements pour le noeud étoile: %d\n", ns);

  knot_free(&star);
  knot_free(&clover);
  knot_free(&simple);
  return 0;
}
