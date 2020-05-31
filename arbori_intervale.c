#include "arbori_intervale.h"

void creare_nod(int stanga, int dreapta, Nod* radacina)
{	
//am creat functia pentru a usura crearea arborelui

	radacina->interval = (Interval*)malloc(sizeof(Interval));
	radacina->interval->capat_stanga = stanga;
	radacina->interval->capat_dreapta = dreapta;
	radacina->info = 0;

	 if(stanga < dreapta){
    	
        radacina->copil_stanga = (Nod*)malloc(sizeof(Nod));
        radacina->copil_dreapta = (Nod*)malloc(sizeof(Nod));

        //construiesc copiii
    	int mijloc = (stanga + dreapta) / 2;
    	creare_nod(stanga, mijloc, radacina->copil_stanga);
    	creare_nod(mijloc+1, dreapta, radacina->copil_dreapta);
    }
    
}

ArboreDeIntervale *construieste_arbore(int capat_stanga, int capat_dreapta,
        							int valoare_predifinita_raspuns_copil,
        							void (*f_actualizare)(Nod *nod, int v_actualizare),
       								int (*f_combinare_raspunsuri_copii)(int raspuns_stanga, int raspuns_dreapta)) {
    // TODO implementati functia de constructie a arborelui prezentata in enunt
    // TODO initializati campurile unui ArboreDeIntervale*

    ArboreDeIntervale* arbore = (ArboreDeIntervale*)malloc(sizeof(ArboreDeIntervale));
    arbore->radacina = (Nod*)malloc(sizeof(Nod));
    creare_nod(capat_stanga,capat_dreapta,arbore->radacina);
    arbore->valoare_predifinita_raspuns_copil = valoare_predifinita_raspuns_copil;
    arbore->f_actualizare = f_actualizare;
    arbore->f_combinare_raspunsuri_copii = f_combinare_raspunsuri_copii;
    arbore->dimensiune = 2*capat_dreapta + 1;

    return arbore;
}

void actualizare_interval_pentru_nod(ArboreDeIntervale *arbore, Nod *nod,
                                        Interval *interval, int v_actualizare) {
    // TODO implementati functia de actualizare pentru un nod
    // Hint: pentru a actualiza un nod cand este cazul folositi arbore->f_actualizare(nod, v_actualizare);

	//functia actualizeaza intervalul unui nod dupa modelul pseudocodului
	//din pdf-ul cu explicatii 
	if(interval->capat_stanga <= nod->interval->capat_stanga 
						&& interval->capat_dreapta >= nod->interval->capat_dreapta){
		arbore->f_actualizare(nod,v_actualizare);
	}else{
		
		int mijloc = (nod->interval->capat_stanga + nod->interval->capat_dreapta) / 2;
		
		if(interval->capat_stanga <= mijloc)
			actualizare_interval_pentru_nod(arbore,nod->copil_stanga,interval,v_actualizare);
		
		if(mijloc < interval->capat_dreapta)
			actualizare_interval_pentru_nod(arbore,nod->copil_dreapta,interval,v_actualizare);

		arbore->f_actualizare(nod,v_actualizare);

	}
}


// Functia este deja implementata, se cheama functia de mai sus cu radacina arborelui
void actualizare_interval_in_arbore(ArboreDeIntervale *arbore, 
                                        Interval *interval, int v_actualizare) {
    actualizare_interval_pentru_nod(arbore, arbore->radacina, interval, v_actualizare);
}


int interogare_interval_pentru_nod(ArboreDeIntervale *arbore, Nod *nod, Interval *interval) {
    // TODO implementati functia de interogare pentru un nod prezentata in enunt
    // Hint: cand vreti sa calculati combinarea raspunsurilor folositi
    // arbore->f_combinare_raspunsuri_copii(raspuns_copil_stanga, raspuns_copil_drepta)
    
    
	//functia interogheaza intervalul pentru un nod dupa modelul pseudocodului
	//din pdf-ul cu explicatii 
    if(interval->capat_stanga <= nod->interval->capat_stanga &&
    							nod->interval->capat_dreapta <= interval->capat_dreapta){
    	return nod->info;

    }else{

    	int mijloc = (nod->interval->capat_stanga + nod->interval->capat_dreapta) / 2;
    	int raspuns_copil_stanga = 0;
    	int raspuns_copil_dreapta = 0;

    	if(interval->capat_stanga <= mijloc){
    		raspuns_copil_stanga = interogare_interval_pentru_nod(arbore,nod->copil_stanga,interval);
    	}
    	
    	if(mijloc < interval->capat_dreapta){
    		raspuns_copil_dreapta = interogare_interval_pentru_nod(arbore,nod->copil_dreapta,interval);
    	}
    
    	return arbore->f_combinare_raspunsuri_copii(raspuns_copil_stanga, raspuns_copil_dreapta);
    }
}


// Functia este deja implementata, se cheama functia de mai sus cu radacina arborelui
int interogare_interval_in_arbore(ArboreDeIntervale *arbore, Interval *interval) {
    return interogare_interval_pentru_nod(arbore, arbore->radacina, interval);
}


// ----- DOAR pentru bonus si DOAR daca considerati ca e necesara ----- //
void seteaza_info_in_nod_la_valoare_capat_dreapta(Nod* nod) {
    // TODO cred ca e destul de clar ce vrea sa faca functia asta
}


void seteaza_info_in_arbore_la_valoare_capat_dreapta(ArboreDeIntervale* arbore) {
    seteaza_info_in_nod_la_valoare_capat_dreapta(arbore->radacina);
}
