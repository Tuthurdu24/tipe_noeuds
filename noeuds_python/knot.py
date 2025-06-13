from typing import List
from itertools import permutations
import copy

#figures

def clover_knot_create():
    tab=[[2,1,2,1],
         [0,2,0,2],
         [1,0,1,0]]
    return tab

def star_knot_create():
    tab=[[3,4,1,2],
         [4,0,2,3],
         [0,1,3,4],
         [1,2,4,0],
         [2,3,0,1]]
    return tab

def braid_knot_create():
    tab=[[1,0,1,2],
         [0,0,2,3],
         [0,1,3,3],
         [1,2,3,2]]
    return tab

def eight_knot_create():
    tab=[[3,2,3,1],
         [0,3,0,2],
         [1,0,1,3],
         [2,1,2,0]]
    return tab


#accesseurs

def aux_knot_nbr_tricolor(knot,i,nk,tab_c):
    nbr_trico=0

    if(i==nk):
        for j in range(nk):
            c_prev=tab_c[knot[j][0]]
            c_next=tab_c[knot[j][3]]
            c_act=tab_c[j]

            if c_prev==c_next:
                if c_act!=c_prev:
                    return 0
            else:
                if c_act==c_prev or c_act==c_next:
                    return 0

        return 1

    else:
        tab_c[i]='b'
        nbr_trico+=aux_knot_nbr_tricolor(knot,i+1,nk,tab_c)

        tab_c[i]='r'
        nbr_trico+=aux_knot_nbr_tricolor(knot,i+1,nk,tab_c)

        tab_c[i]='g'
        nbr_trico+=aux_knot_nbr_tricolor(knot,i+1,nk,tab_c)

    return nbr_trico

def knot_nbr_tricolor(knot):
    nbr_trico=0
    nk = len(knot) #nombre de cordes
    tab_c= [0 for _ in range(nk)]

    nbr_trico = aux_knot_nbr_tricolor(knot,0,nk,tab_c)

    return nbr_trico


#opérations élémentaires

def move_1(knot):     # mouvement de Reidemeister de type I
    i=0    
    while i < len(knot):
        if (knot[i][1] == i):       # Le paramètre x_p de la corde est égale à l'indice de la corde: autrement dit, la corde se coupe elle même à son extrémité antérieure
            print("move I")

            rope_p = knot[i][0]
            new_rope_p = knot[rope_p][0]
            new_cut_p = knot[rope_p][1]

            knot[new_rope_p][3] = i
            knot[i][0] = new_rope_p
            knot[i][1] = new_cut_p

            suppr_rope(knot, rope_p)

        if (i < len(knot) and knot[i][2] == i):
            print("move I")

            rope_n = knot[i][3]
            new_rope_n = knot[rope_n][3]
            new_cut_n = knot[rope_n][2]

            knot[new_rope_n][0] = i
            knot[i][3] = new_rope_n
            knot[i][2] = new_cut_n

            suppr_rope(knot, rope_n)

        i = i + 1
    return


def suppr_rope(knot : List[List[int]], k: int):
    n = len(knot)
    if(k>=len(knot)):
        return knot
    knot.pop(k)
    for rope in knot:
      for j in range(4):
          if (rope[j] > k):
              rope[j] = rope[j] - 1
    return

def move_2(knot):     # mouvement de Reidemeister de type II. coût: theta(n²)
    i = 0
    while i < len(knot):

        i_prev = knot[i][0]
        i_next = knot[i][3]

        if (knot[i][1] == knot[i][2]):    # cas d'utilisation du mouvement de type II: Une corde indicée i est coupée à gauche et à droite par la même corde
                                          # -> on doit dans ce cas supprimée la corde i et raccorder ses cordes adjacentes entre elles (on les "merge")

            is_cutting = False            # booléen déterminant si i coupe d'autres cordes.
            for j in range(len(knot)):     
                for k in range(1, 3):
                    if k == i:
                        is_cutting = True
                        
            if not is_cutting:            # on doit vérifier que la corde i ne coupe pas d'autres cordes, dans quel cas supprimer i mènerait à une incohérence.
                print("move II")

                for k in range(len(knot)):
                    for p in range(4):
                        if knot[k][p] == i_next:
                            knot[k][p] = i_prev
                                
                knot[i_prev][2] = knot[i_next][2]
                knot[i_prev][3] = knot[i_next][3]
                    
                suppr_rope(knot, i_next)

                if (i_next < i):
                    suppr_rope(knot, i-1)
                else:
                    suppr_rope(knot, i)
        i = i + 1
    return

def move_3(knot : List[List[int]], i: int):     # mouvement de Reidemeister de type III
    print("move III")


    inext = knot[i][3]
    iprev = knot[i][0]

    cut_next = knot[i][2]
    cut_prev = knot[i][1]

    """    
    if(len(set([inext,iprev,cut_prev,cut_next,i]))<5):
        return 
    """

    print("on fait vraiment un III")
    
    knot[iprev][2] = cut_next
    knot[inext][1] = cut_prev
    knot[i][1] = cut_next
    knot[i][2] = cut_prev
    
    return


def knot_is_valid(knot: List[List[int]]):
    i = 0
    rope = 0
    rope_next = 0
    cut_next = 0
    while i < len(knot):
        cut_next = knot[rope][2]
        rope_next = knot[rope][3]
        
        if (knot[rope_next][0] != rope or knot[rope_next][1] != cut_next):
            return False
        
        rope = rope_next
        i = i+1
    return True

def knot_to_prime(knot, from_3 = False, k = 0):
    
    print("k = ", k)

    knot_start = copy.deepcopy(knot)

    move_1(knot)
    move_2(knot)
    
    if((knot_start == knot) and (from_3 == True)):
        print("1er if")
        return knot

    elif (knot_start != knot):
        print("1er elif")
        return knot_to_prime(knot, False, k+1)

    else:
        print("on fait des 3")
        k_better = copy.deepcopy(knot_start)
        
        for i in range(len(knot)):

            print("i = ", i, "\n")
            cut_d = knot[i][2]
            cut_g = knot[i][1]
            if ((knot[cut_d][1] == cut_g or knot[cut_d][2] == cut_g) ^ (knot[cut_g][1] == cut_d or knot[cut_g][2] == cut_d)):
                move_3(knot, i)
                knot_new = knot_to_prime(knot, True, k+1)
                if len(knot_new) < len(k_better):
                    k_better = copy.deepcopy(knot_new)
                knot = copy.deepcopy(knot_start)
                
        return k_better
    return [[-1]]



def knot_to_prime_v2(knot, k = 0, save_tab = []):
    
    print("k = ", k)
    
    
    knot_start = copy.deepcopy(knot)

    move_1(knot)
    move_2(knot)
    
    if (knot_start != knot):
        print("1er elif")
        return knot_to_prime_v2(knot, k+1)

    else:
        print("on fait des 3")
        k_better = copy.deepcopy(knot_start)
        
        for i in range(len(knot)):

            print("i = ", i, "\n")
            cut_d = knot[i][2]
            cut_g = knot[i][1]
            if ((knot[cut_d][1] == cut_g or knot[cut_d][2] == cut_g) ^ (knot[cut_g][1] == cut_d or knot[cut_g][2] == cut_d)):
                move_3(knot, i)
                
                if not (knot in save_tab):
                    
                    save_tab.append( copy.deepcopy(knot) )
                    knot_new = knot_to_prime_v2(knot, k+1, save_tab)
                    
                    if len(knot_new) < len(k_better):
                        k_better = copy.deepcopy(knot_new)
                knot = copy.deepcopy(knot_start)
                
        return k_better
    return [[-1]]



def knot_same_index(knot1,knot2):
    n = len(knot1)
    if n != len(knot2):
        return False
    perm = permutations(range(0,n))
    tab = [list(p) for p in perm]
    for s_tab in tab:    #permet de tester si il existe une permuatations envoyant un noeud sur un autre dans le sens "classique"
        same=True
        for i in range(n):
            for j in range(4):
                if knot1[i][j]!=s_tab[knot2[s_tab[i]][j]]:
                    same=False
        if same==True:
            return True
        
    for s_tab in tab:            #dans le sens inverse
        same=True
        for i in range(n):
            for j in range(4):
                if knot1[n-i-1][3-j]!=s_tab[knot2[s_tab[i]][j]]:
                    same=False
        if same==True:
            return True
    
    return False

def print_knot(knot):
    if len(knot) == 0:
        print("[]")
    for i in range(len(knot)):
        print(knot[i])
    print("\n")
    
    
def knot_is_similar(knot1,knot2):
    if knot_nbr_tricolor(knot1)!=knot_nbr_tricolor(knot2):
        return False
    knot1=knot_to_prime(knot1)
    knot2=knot_to_prime(knot2)
    knot1_save=knot1
    if knot_is_same(knot1,knot2):
        return True
    for i in range(len(knot1)):
        knot1=knot1_save
        cut_d=knot1[i][2]
        cut_g=knot1[i][1]
        if ((knot1[cut_d][1]==cut_g or knot1[cut_d][2]==cut_g) ^ (knot1[cut_g][1]==cut_d or knot1[cut_g][2]==cut_d)):
            move_3(knot1,i)
        if knot_is_same(knot1,knot2):
                return True
    return False



"""
print(knot_is_similar([[2,1,2,1],[0,2,0,2],[1,0,1,0]],
                      [[1,2,1,2],[2,0,2,0],[0,1,0,1]]))
             
print(knot_is_same([[2,1,2,1],[0,2,0,2],[1,0,1,0]],
                   [[1,2,1,2],[2,0,2,0],[1,0,0,1]]))



hard_unknot = [[8,6,5,1],
             [0,5,6,2],
             [1,6,5,3],
             [2,5,0,4],
             [3,0,7,5],
             [4,7,2,6],
             [5,2,5,7],
             [6,5,6,8],
             [7,6,6,0]]

print("Noeud trivial emmelé:")
print_knot(hard_unknot)

hard_unknot = knot_to_prime_v2(hard_unknot)

print("Noeud simplifié:")
print_knot(hard_unknot)

"""

hard_hard_knot = [[15, 4, 13, 1],
                  [0, 13, 8, 2],
                  [1, 8, 11, 3],
                  [2, 11, 10, 4],
                  [3, 10, 15, 5],
                  [4, 15, 9, 6],
                  [5, 9, 13, 7],
                  [6, 13, 1, 8],
                  [7, 1, 12, 9],
                  [8, 12, 0, 10],
                  [9, 0, 3, 11],
                  [10, 3, 9, 12],
                  [11, 9, 8, 13],
                  [12, 8, 10, 14],
                  [13, 10, 0, 15],
                  [14, 0, 4, 0]]

print("Noeud trivial emmelé:")
print_knot(hard_hard_knot)

hard_hard_knot = knot_to_prime_v2(hard_hard_knot, 0)

print("Noeud simplifié:")
print_knot(hard_hard_knot)


"""
mauvais_huit = [[1, 6, 3, 6],  
                [2, 0, 5, 0],
                [3, 1, 4, 1],  
                [4, 2, 6, 2],  
                [5, 3, 1, 3],  
                [6, 4, 2, 4],  
                [0, 5, 0, 5]]

if (not knot_is_valid(mauvais_huit)):
    print("Noeud invalide !\n")


def print_knot(knot):
    for rope in knot:
        print(rope)
    print("\n")
    return


clo_non_opti = [[3, 2, 1, 1],
                [0, 1, 3, 2],
                [1, 3, 0, 3],
                [2, 0, 2, 0]]

move_1(clo_non_opti)

if (not knot_is_valid(clo_non_opti)):
    print("Noeud invalide !\n")
else:
    print("VALIDE")


print_knot(clo_non_opti)

print("\n");

non_opti = [[3, 0, 1, 1],
            [0, 1, 2, 2],
            [1, 2, 3, 3],
            [2, 3, 0, 0]]

move_1(non_opti)
print_knot(non_opti)

print("\n")

braid = braid_knot_create()
move_1(braid)

print_knot(braid)

print("\n")

weirdo = [[1, 1, 1, 1],
          [0, 1, 1, 0]]



move_2(weirdo)

print_knot(weirdo)

def test():
    print("attendu:\n")
    print_knot(clover_knot_create())
    print("resultat:\n")
    print_knot(knot_to_prime(clover_knot_create(),[],[]))
    print("\n")
    
    print("attendu:\n")
    print_knot(star_knot_create())
    print("resultat:\n")
    print_knot(knot_to_prime(star_knot_create(),[],[]))
    print("\n")
    
    print("attendu:\n")
    print_knot(eight_knot_create())
    print("resultat:\n")
    print_knot(knot_to_prime(eight_knot_create(),[],[])   )
    print("\n")
    
    print("attendu:\n")
    print_knot([])
    print("resultat:\n")
    print_knot(knot_to_prime(braid_knot_create(),[],[]))
    print("\n")
    return    
    
 """   
    
    
