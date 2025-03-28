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

knot* braid5_create()
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

void self_cross(knot** addr_k)                            // remplace une boucle par une corde simple (lorsque une corde se croise elle même, elle est équivalente à une corde simple)
{
  assert(addr_k != NULL);
  assert(*addr_k != NULL);
  rope* tmp;
  rope* stop = *addr_k;
  rope* curr_r = *addr_k;
  bool check = true;
  bool free_r = false;
  int n_self_cross = 0;

  while( (curr_r != stop || check) && curr_r != curr_r->cut_n)
    {
      check = false;

      if (curr_r->x_n == curr_r)
	{
	  tmp = curr_r;
	  curr_r->cut_p->cut_n = curr_r->cut_n;
	  curr_r->cut_n->cut_p = curr_r->cut_p;
	  curr_r->cut_n->x_p = curr_r->cut_p->x_n;

	  n_self_cross = n_self_cross + 1;

	  free_r = true;
	}
      if (curr_r->x_p == curr_r)
	{
	  tmp = curr_r;
	  curr_r->cut_p->cut_n = curr_r->cut_n;
	  curr_r->cut_n->cut_p = curr_r->cut_p;
	  curr_r->cut_p->x_n = curr_r->cut_n->x_p;

	  n_self_cross = n_self_cross + 1;

	  free_r = true;
	}
      curr_r = curr_r->cut_n;
      if(free_r)
	{
	  free(tmp);
	}
      free_r = false;
    }
  if(curr_r->cut_n == curr_r && curr_r->x_n != NULL)    // cas de base: noeud trivial, pas de croisements
    {
      curr_r->x_n = NULL;
      curr_r->x_p = NULL;
      n_self_cross = n_self_cross + 1;
    }
  
  if (n_self_cross == 0)
    printf("noeud déjà optimal!\n");
  else
    {
      *addr_k = curr_r;               // pour ne pas que k pointe sur une corde qui a été free.
      printf("%d croisements optimisés!\n", n_self_cross);
    }
  return;
}

// accesseurs

int knot_count_cross(knot* k)         // PAS ENCORE OK: si une corde se croise elle meme, est ce qu'on compte le croisement???????????????????? 
{
  assert(k != NULL);
  rope* curr_r = k;
  rope* stop = k;
  int n_cross = 0;
  bool check = true;

  while(curr_r != stop || check)
    {
      check = false;
      if(curr_r->x_n != NULL)
	n_cross = n_cross + 1;

      curr_r = curr_r->cut_n;
    }

  return n_cross;
}

int knot_count_rope(knot* k)
{
  assert(k != NULL);
  rope* curr_r = k;
  rope* stop = k;
  int n_cross = 0;
  bool check = true;

  while(curr_r != stop || check)
    {
      check = false;
      n_cross = n_cross + 1;

      curr_r = curr_r->cut_n;
    }

  return n_cross;
}

int knot_tab_i(knot* k,knot** tab,int n)
{
  int i;
  for(i=0;i<n;i+=1)
    {
      if(tab[i]==k)
        return i;
      }
  return -2;
}

void knot_print(knot* k)
{
  int n=knot_count_rope(k);

  knot **tab_k=malloc(sizeof(knot*)*n);
  int i;
  int i_k;
  for(i=0;i<n;i+=1)
    {
      assert(k != NULL);
      tab_k[i]=k;
      k=k->cut_n;
    }

  for(i=0;i<n;i+=1)
    {
      i_k=knot_tab_i(k,tab_k,n)+1;
      printf("(Corde %d / ",i_k);

      i_k=knot_tab_i(k->cut_p,tab_k,n)+1;
      printf("lien gauche: %d / ",i_k);
      if(k->x_p!=NULL)
        {
          i_k=knot_tab_i(k->x_p,tab_k,n)+1;
          printf("croisement gauche: %d / ",i_k);
        }
      else
        printf("croisement gauche: vide / ");
      i_k=knot_tab_i(k->cut_n,tab_k,n)+1;
      printf("lien droite: %d / ",i_k);
      if(k->x_p!=NULL)
        {
          i_k=knot_tab_i(k->x_n,tab_k,n)+1;
          printf("croisement droite: %d)\n",i_k);
        }
      else
        printf("croisement droite: vide)\n ");
          k=k->cut_n;
    }
  printf("\n");
  free(tab_k);
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

void test1()
{
  knot* clover = clover_knot_create();
  int n = knot_count_cross(clover);
  printf("Nombre de croissements pour le noeud trèfle: %d\n", n);
  self_cross(&clover);
  printf("\n");

  knot* simple = trivial_knot_create();
  int nt = knot_count_cross(simple);
  printf("Nombre de croisements pour le noeud simple: %d\n", nt);
  self_cross(&simple);
  printf("\n");

  knot* star = star_knot_create();
  int ns = knot_count_cross(star);
  printf("Nombre de croisements pour le noeud étoile: %d\n", ns);
  self_cross(&star);
  printf("\n");

  knot* b = braid5_create();
  int nb = knot_count_cross(b);
  printf("Nombre de croisements pour la tresse de 5: %d\n", nb);

  self_cross(&b);
  nb = knot_count_cross(b);
  printf("Nombre de croisement pour la tresse de 5 après optimisation: %d\n", nb);

  knot_free(&b);
  knot_free(&star);
  knot_free(&clover);
  knot_free(&simple);


  return;
}

void test2()
{
  knot* clover = clover_knot_create();
  knot_print(clover);

  knot* simple = trivial_knot_create();
  knot_print(simple);

  knot* star = star_knot_create();
  knot_print(star);

  knot* b = braid5_create();
  knot_print(b);



  knot_free(&b);
  knot_free(&star);
  knot_free(&clover);
  knot_free(&simple);

  return;
}

int main()
{

  return 0;
}
