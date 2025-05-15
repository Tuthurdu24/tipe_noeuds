#include "myknot.h"    // définition du type et des primitives

int max_tab(int* tab, int n)
{
  assert(tab != NULL);
  int i;
  int max = tab[0];
  
  for (i = 0; i<n; i=i+1)
    {
      if (tab[i] > max)
	max = tab[i];
    }
  return max;
}


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



knot* knot_of_tab(int* tab, int n)
{
  assert(tab != NULL);
  
  knot* new_k;
  rope* curr_r;
  
  int i;
  int max = max_tab(tab, n);
  rope** rope_tab = malloc(max*sizeof(rope*));
  
  rope* rope_start;
  rope* rope_end;

  for(i=0; i< max; i=i+1)
    rope_tab[i] = NULL;
  
  for(i=0; i< n; i=i+1)
    if(rope_tab[tab[i] - 1] == NULL)
      rope_tab[tab[i] - 1] = knot_create();
  
  new_k = rope_tab[tab[0] - 1];
  
  for(i=0; i < n; i = i+2)
    {
      curr_r = rope_tab[tab[i] - 1];
      
      if (i != 0)
	{
	  curr_r->cut_p = rope_tab[tab[i-2] - 1];
	  curr_r->x_p = rope_tab[tab[i-1] - 1];
	}
      if (i < n-2)
	{
	  curr_r->x_n = rope_tab[tab[i+1] - 1];
	  curr_r->cut_n = rope_tab[tab[i+2] - 1];
	}
    }

  rope_start = rope_tab[tab[0] - 1];
  rope_end = curr_r;

  rope_start->x_p = rope_tab[tab[n-1] - 1];
  rope_start->cut_p = rope_end;

  rope_end->cut_n = rope_start;
  rope_end->x_n = rope_tab[tab[n-1] - 1];

  free(rope_tab);
  
  return new_k; 
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

void knot_self_cross(knot** addr_k)                            // remplace une boucle par une corde simple (lorsque une corde se croise elle même, elle est équivalente à une corde simple)
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

int knot_count_cross(knot* k)
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

int aux_tricolor(knot *k,int i,int nc,char *tab_c,knot **tab_k)
{
  int nbr_tric=0;
  int j;

  if(i==nc)
    {
      char c_prev;
      char c_next;
      char c_cut; //color cut
      for(j=0;j<nc;j+=1)
        {
          //k=tab_k[j];

          c_prev=tab_c[j];

          if(j==nc-1)
            c_next=tab_c[0];
          else
            c_next=tab_c[j+1];


          c_cut=tab_c[knot_tab_i(k->x_n,tab_k,nc)];

          if(c_prev==c_next)
            {
              if(c_cut!=c_prev)
               {
                 //printf("1,i:%d %s\n %c %c %c \n\n",j,tab_c,c_prev,c_next,c_cut);
                 return 0;
               }
            }
          else
            {
              if(c_cut==c_prev || c_cut==c_next)
                {
                  //printf("2,i:%d %s\n %c %c %c \n\n",j,tab_c,c_prev,c_next,c_cut);
                  return 0;
                }
            }
          k=k->cut_n;
        }
      //printf("3:%s\n",tab_c);
      return 1;
    }
  else
    {
      tab_c[i]='b';
      nbr_tric+=aux_tricolor(k,i+1,nc,tab_c,tab_k);

      tab_c[i]='r';
      nbr_tric+=aux_tricolor(k,i+1,nc,tab_c,tab_k);

      tab_c[i]='g';
      nbr_tric+=aux_tricolor(k,i+1,nc,tab_c,tab_k);
    }
  return nbr_tric;
}


int knot_nbr_tricolor(knot* k)
{
  int nbr_tric=0;
  int nc=knot_count_rope(k);
  char* tab_c=malloc(sizeof(char)*(nc+1));
  tab_c[nc] = '\0';
  knot **tab_k=malloc(sizeof(knot*)*nc);
  int i;
  for(i=0;i<nc;i+=1)
    {
      assert(k != NULL);
      tab_k[i]=k;
      k=k->cut_n;
    }

  tab_c[0]='b';
  nbr_tric+=aux_tricolor(k,1,nc,tab_c,tab_k);

  tab_c[0]='r';
  nbr_tric+=aux_tricolor(k,1,nc,tab_c,tab_k);

  tab_c[0]='g';
  nbr_tric+=aux_tricolor(k,1,nc,tab_c,tab_k);

  free(tab_c);
  free(tab_k);

  return nbr_tric;
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

