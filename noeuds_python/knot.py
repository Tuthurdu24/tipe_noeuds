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






#opérations élémentaires

def delete_self_cross(knot):
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




def print_knot(knot):
    for rope in knot:
        print(rope)
    return


clo = [[3, 2, 1, 1],
       [0, 1, 3, 2],
       [1, 3, 0, 3],
       [2, 0, 2, 0]]

delete_self_cross(clo)



print_knot(clo)


