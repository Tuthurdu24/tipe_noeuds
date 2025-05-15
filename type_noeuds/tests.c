#include "myknot.h"




void test1()
{
  printf("--------------------- TEST 1 ---------------------\n");
  knot* clover = clover_knot_create();
  int n = knot_count_cross(clover);

  printf("Nombre de croissements pour le noeud trèfle: %d\n", n); 
  knot_self_cross(&clover);

  printf("Nombre de croissements pour le noeud trèfle: %d\n", n);
  knot_self_cross(&clover);

  printf("\n");

  knot* simple = trivial_knot_create();
  int nt = knot_count_cross(simple);
  printf("Nombre de croisements pour le noeud simple: %d\n", nt);
  knot_self_cross(&simple);
  printf("\n");

  knot* star = star_knot_create();
  int ns = knot_count_cross(star);
  printf("Nombre de croisements pour le noeud étoile: %d\n", ns);
  knot_self_cross(&star);
  printf("\n");


  knot* b = braid_knot_create();
  int nb = knot_count_cross(b);
  printf("Nombre de croisements pour la tresse de 5: %d\n", nb);
  
  knot_self_cross(&b);

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
  printf("\n--------------------- TEST 2 ---------------------\n");
  knot* clover = clover_knot_create();
  knot_print(clover);

  knot* simple = trivial_knot_create();
  knot_print(simple);

  knot* star = star_knot_create();
  knot_print(star);

  knot* b = braid_knot_create();
  knot_print(b);

  printf("nbr tricoloriage clover:%d\n",knot_nbr_tricolor(clover));
  printf("nbr tricoloriage star:%d\n",knot_nbr_tricolor(star));


  knot_free(&b);
  knot_free(&star);
  knot_free(&clover);
  knot_free(&simple);

  return;
}

void test3()
{
  printf("\n--------------------- TEST 3 ---------------------\n");
  int clo[6] = {1, 2, 3, 1, 2, 3};
  
  knot* clover = knot_of_tab(clo, 6);

  int n = knot_count_cross(clover);
  printf("Nombre de croisements: %d\n", n);

  int eig[8] = {1, 3, 2, 4, 3, 1, 4, 2};

  knot* eight = knot_of_tab(eig, 8);

  n = knot_count_cross(eight);
  printf("Nombre de croisements : %d\n", n);
   
  int sev[14] = {1, 5, 2, 6, 3, 7, 4, 1, 5, 2, 6, 3, 7, 4};

  knot* star_sev = knot_of_tab(sev, 14);
  
  n = knot_count_cross(star_sev);
  printf("Nombre de croisement : %d\n", n);

  knot_free(&star_sev);
  knot_free(&clover);
  knot_free(&eight);
  return;
}


int main()
{
  test1();
  test2();
  test3();

  return 0;
}
