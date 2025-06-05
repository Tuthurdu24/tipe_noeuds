from typing import List

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

    nbr_trico=aux_knot_nbr_tricolor(knot,0,nk,tab_c)

    return nbr_trico


#opérations élémentaires

def move_1(knot):     # mouvement de Reidemeister de type I
    i=0
    
    while i < len(knot):
        if (knot[i][1] == i):       # Le paramètre x_p de la corde est égale à l'indice de la corde: autrement dit, la corde se coupe elle même à son extrémité antérieure

            rope_p = knot[i][0]
            new_rope_p = knot[rope_p][0]
            new_cut_p = knot[rope_p][1]

            knot[new_rope_p][3] = i
            knot[i][0] = new_rope_p
            knot[i][1] = new_cut_p

            suppr_rope(knot, rope_p)

        if (knot[i][2] == i):

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
    knot.pop(k)
    for rope in knot:
        for j in range(4):
            if (rope[j] > k):
                rope[j] = rope[j] - 1
    return

def move_2(knot):     # mouvement de Reidemeister de type II
    i = 0

    while i < len(knot):
        if (knot[i][1] == knot[i][2]):
            i_prev = knot[i][0]
            i_next = knot[i][3]

            knot[i_prev][2] = knot[i_next][2]
            knot[i_prev][3] = knot[i_next][3]

            suppr_rope(knot, i)

            if (i_next > i):
                suppr_rope(knot, i_next-1)
            else:
                suppr_rope(knot, i_next)
        i =i + 1
    return

def move_3(knot : List[List[int]], i: int):     # mouvement de Reidemeister de type III
    inext = knot[i][3]
    iprev = knot[i][0]
    cut_next = knot[i][2]
    cut_prev = knot[i][1]

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
