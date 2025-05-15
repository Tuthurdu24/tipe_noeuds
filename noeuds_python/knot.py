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
    
