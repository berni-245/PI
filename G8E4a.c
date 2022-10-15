void
generarMazo(cartas mazo){
    int i, j;
    char * palos[] = {"corazon","trebol","pica","diamante"};
    enum posNumeros numeroActual;
    numeroActual = AZ-1;
    
    for(i=0, j=0; i<CARTAS_MAZO; i++,j++){
        if(i%CANT_PALOS){
            numeroActual++;
            j=0;
        }

        mazo[i].numero = numeroActual;
        strcpy(mazo[i].palo, palos[j]);
                
    }
    //4 cartas del número 1 pero distinto palo
    //las siguietes 4 sean del numero 2 pero de distinto palo
}
