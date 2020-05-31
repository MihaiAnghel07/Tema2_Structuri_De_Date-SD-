#include "intersectii.h"


// functie ajutatoare
void afiseaza_lista_intervale(ListaIntervale2D *lista) {
    int i;
    for (i = 0; i < lista->dimensiune; i++) {
        Interval2D *interv = lista->intervale[i];
        printf("{punct stanga x: %d, punct stanga y: %d, punct dreapta x: %d, punct dreapta y: %d}\n",
                    interv->punct_stanga->x, interv->punct_stanga->y,
                    interv->punct_dreapta->x, interv->punct_dreapta->y);
    }
}


ListaIntervale2D* citeste_intrare(char *nume_fisier_intrare) {
    // TODO citeste intervalele din fisierul dat ca parametru
    // si le salveaza in lista de intervale

    FILE *file = fopen(nume_fisier_intrare,"r");
    if(file == NULL)
        return NULL;

    //se aloca memorie pentru lista si se citeste numarul de intervale
    ListaIntervale2D* lista = (ListaIntervale2D*)malloc(sizeof(ListaIntervale2D));
    fscanf(file,"%d",&lista->dimensiune);
    lista->intervale = (Interval2D**)malloc((lista->dimensiune)*sizeof(Interval2D*));

    int i;
    //se aloca memorie si se citesc punctele pentru fiecare interval
    for(i = 0; i < lista->dimensiune; i++){
        lista->intervale[i] = (Interval2D*)malloc(sizeof(Interval2D));
        lista->intervale[i]->punct_stanga = (Punct2D*)malloc(sizeof(Punct2D));
        lista->intervale[i]->punct_dreapta = (Punct2D*)malloc(sizeof(Punct2D));
        fscanf(file,"%d",&lista->intervale[i]->punct_stanga->x); 
        fscanf(file,"%d",&lista->intervale[i]->punct_stanga->y);
        fscanf(file,"%d",&lista->intervale[i]->punct_dreapta->x);
        fscanf(file,"%d",&lista->intervale[i]->punct_dreapta->y);
    }

    fclose(file);

    return lista;
}

// ! Functie pentru actualizarea in arbore
// ! O veti da ca parametru cand initializati arborele
void actualizare_cu_delta(Nod *nod, int v2) {
    nod->info += v2;
}

// ! Functie pentru combinarea raspunsurilor in arbore
// ! O veti da ca parametru cand initializati arborele
int suma_raspunsurilor(int r1, int r2) {
    return r1 + r2;
}

void sortare(ListaIntervale2D *lista){

    int inv = 1,i,aux;

    do{
        inv = 1;
        for(i = 0; i < lista->dimensiune - 1; i++){
            if(lista->intervale[i]->punct_stanga->x > lista->intervale[i + 1]->punct_stanga->x){
                aux = lista->intervale[i]->punct_stanga->x;
                lista->intervale[i]->punct_stanga->x = lista->intervale[i + 1]->punct_stanga->x;
                lista->intervale[i + 1]->punct_stanga->x = aux;

                aux = lista->intervale[i]->punct_stanga->y;
                lista->intervale[i]->punct_stanga->y = lista->intervale[i + 1]->punct_stanga->y;
                lista->intervale[i + 1]->punct_stanga->y = aux;

                inv = 0;
            }
        }
    }while(inv == 1);
}

int calculeaza_numar_intersectii(ListaIntervale2D *lista) {
    // TODO calculati numarul de intersectii folosind arbori de intervale conform enuntului
    // Hint: initializarea arborelui: 
    // ArboreDeIntervale *arbore = construieste_arbore(0, y_max, 0, actualizare_cu_delta, suma_raspunsurilor);
    
    int i,y_max;
    //calculez y maxim
    if(lista->intervale[0]->punct_stanga->y > lista->intervale[0]->punct_dreapta->y)
        y_max = lista->intervale[0]->punct_stanga->y;
    else
        y_max = lista->intervale[0]->punct_dreapta->y;

    for(i = 1; i < lista->dimensiune; i++){
        if(lista->intervale[i]->punct_stanga->y >= lista->intervale[i]->punct_dreapta->y
            && y_max < lista->intervale[i]->punct_stanga->y)
            y_max = lista->intervale[i]->punct_stanga->y;
        else
            if(lista->intervale[i]->punct_dreapta->y > y_max)
                y_max = lista->intervale[i]->punct_dreapta->y; 
    }

    ArboreDeIntervale *arbore = construieste_arbore(0, y_max, 0, actualizare_cu_delta, suma_raspunsurilor);
    //sortare(lista);


    return 0;
}


int calculeaza_numar_intersectii_trivial(ListaIntervale2D *lista) {
    // TODO: solutia triviala, verific fiecare segment cu fiecare segment daca se intersecteaza 
    
    int i,j,numar_intersectii = 0;

    //in mod trivial, se parcurge lista si se calculeaza numarul de intersectii
    for(i = 0; i < lista->dimensiune - 1; i++){
        for(j = i+1; j < lista->dimensiune; j++){
            if(((lista->intervale[i]->punct_stanga->x <= lista->intervale[j]->punct_stanga->x)
                && (lista->intervale[i]->punct_stanga->y >= lista->intervale[j]->punct_stanga->y)) 
                && ((lista->intervale[i]->punct_dreapta->x >= lista->intervale[j]->punct_dreapta->x)
                && (lista->intervale[i]->punct_dreapta->y <= lista->intervale[j]->punct_dreapta->y)))
                
                numar_intersectii++;
            
            if(((lista->intervale[i]->punct_stanga->x >= lista->intervale[j]->punct_stanga->x)
                && (lista->intervale[i]->punct_stanga->y <= lista->intervale[j]->punct_stanga->y)) 
                && ((lista->intervale[i]->punct_dreapta->x <= lista->intervale[j]->punct_dreapta->x)
                && (lista->intervale[i]->punct_dreapta->y >= lista->intervale[j]->punct_dreapta->y)))
                
                numar_intersectii++;
        }
    }

    return numar_intersectii;
}
