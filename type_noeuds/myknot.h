#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

// définition d'une corde, d'un nœud.
// "**_p" (previous) et "**_n" (next) se basent sur la lecture selon le sens trigonométrique du nœud.
struct rope
{
  struct rope *cut_p;  // addresse de la corde précendente
  struct rope *x_p;    // addresse de la corde de coupure précédente
  struct rope *cut_n;  // addresse de la corde suivante
  struct rope *x_n;    // addresse de la corde de coupure suivante
};

typedef  struct rope rope;
typedef  struct rope knot;


// constructeurs
knot* knot_create();

   // figures
knot* trivial_knot_create();
knot* clover_knot_create();
knot* star_knot_create();
knot* infinity_knot_create();

// transformateurs
void knot_tie(knot* kp, knot* kn, knot* k_up);

// accesseurs
int knot_count_cross(knot* k);
int knot_count_rope(knot* k);
bool is_a_node(knot* k);
int knot_tab_i(knot* k,knot** tab,int n);
void knot_print(knot* k);
