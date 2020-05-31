#include "pozitie_libera.h"


DateIntrare* citeste_fisier_in(char *nume_fisier_intrare) {
    // TODO citeste datele din fisier si populeaza pointerul la structura
    

    FILE *file = fopen(nume_fisier_intrare,"r");
    if(file == NULL)
        return NULL;


    DateIntrare* date = (DateIntrare*)malloc(sizeof(DateIntrare));

    fscanf(file,"%d",&date->numarul_maxim_din_intrari);
    fscanf(file,"%d",&date->numar_intrari);

    date->intrari = (int*)malloc(date->numar_intrari*sizeof(int));

  
    int i;
    for(i = 0; i < date->numar_intrari; i++){
    	fscanf(file,"%d",&date->intrari[i]);
    }

    fclose(file);
    return date;
}


int* calculeaza_vector_raspuns(DateIntrare *date_intrare) {
    // TODO creeaza vectorul raspuns folosind arbori de intervale
    
    int* raspuns = malloc((date_intrare->numarul_maxim_din_intrari+1)*sizeof(int));

    //am alocat memorie si am returnat "raspuns" pentru ca altfel primeam segfault
    //si nu puteam vedea rezultatele
    return raspuns;
}


int* calculeaza_vector_raspuns_trivial(DateIntrare *date_intrare) {
    // TODO creeaza vectorul raspuns folosind 2 for-uri

    int* raspuns = malloc((date_intrare->numarul_maxim_din_intrari+1)*sizeof(int));

    int i,j;
    //initializez vectorul raspuns cu valoarea -1 pentru a putea face comparatiile
    for(i = 0; i < date_intrare->numarul_maxim_din_intrari + 1; i++){
    	raspuns[i] = -1;
    }

    //parcurg lista cu numerele initiale si conform cerintei se construieste 
    //vectorul raspuns
    for(i = 0; i < date_intrare->numar_intrari; i++){
    	if(raspuns[date_intrare->intrari[i]] == -1){
    		raspuns[date_intrare->intrari[i]] = date_intrare->intrari[i];
    	
    	}else{

    		for(j = date_intrare->intrari[i] - 1; j >= 0; j--){
    			if(raspuns[j] == -1){
    				raspuns[j] = date_intrare->intrari[i];
    				break;
    			}
    		}
    	}
    }

    return raspuns;
}