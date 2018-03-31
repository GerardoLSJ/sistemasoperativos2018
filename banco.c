/*
Autores: Lopez Santibañez Jimenez Luis Gerardo

Descripcion del programa:

Un hilo principal crea dos secundarios los cuales accederan a variables compartidas
por lo que se debe garantizar la exclusion mutua cuando se lea o escribe sobre estas variables
esto lo llevamos a cabo utilizando la implementacion de Peterson para operaciones en regiones 
criticas.

Un hilo se encargara de realizar depositos a una varibale compartida saldo
El otro hilo retirara de ls misma variable siempre y cuando existan al menos 
la cantidad que se desea retirar

*/

#include <pthread.h>
#include <stdio.h>
int proc_fav,
proc1wantIn,
proc2wantIn,
error,
salida;
//Definicion de las variables globales
float saldo = 1000.0; // se da un saldo inicial

//Funcion que se le asignara al hilo de deposito
void *proc_deposito(void *saldo_ptr) {
    float deposito;
    do {
        proc1wantIn = 1;
        proc_fav = 2;
        while (proc2wantIn && proc_fav == 2); //primitiva de entrada
        printf("¿Cuanto desea depositar?\n");
        scanf("%f", &deposito);
        saldo = saldo + deposito;               // actualizacion
        printf("Saldo actualizado: %f \n", saldo);
        fflush(stdin);
        proc1wantIn = 0;                       //primitiva de salida
        int r = rand() % 3;
        sleep(r); // random entre 1 y 3
    } while (deposito != 0.0);
    pthread_exit(NULL);
}
//Funcion que se le asignara al hilo de retiro
void *proc_retiro(void *saldo_ptr) {
    float retiro;
    do {
        proc2wantIn = 1;
        proc_fav = 1;
        while (proc1wantIn && proc_fav == 1);  //primitiva de entrada
        printf("¿Cuanto desea retirar?\n");
        scanf("%f", &retiro);
        if(saldo - retiro >= 0){              // retiro de saldo si hay mas de lo que se desea retirar
            saldo = saldo - retiro;           // actualizacion
            printf("Saldo actualizado: %f \n", saldo);
            fflush(stdin);
        }else{
            printf("No es posible realizar el retiro, cuenta con: %f \n", saldo);
            fflush(stdin);
        }
        proc2wantIn = 0;                        //primitiva de salida
        int r = rand() % 3;
        sleep(r); // random entre 1 y 3
    } while (retiro != 0.0);
    pthread_exit(NULL);
}
int main() {
    pthread_t hilo_dep, hilo_ret;
    error = pthread_create( &hilo_dep, NULL, proc_deposito, NULL); // creacion de hilo
    error = pthread_create(&hilo_ret, NULL, proc_retiro, NULL);
    error = pthread_join(hilo_dep, (void **)&salida);              // join de hilo 
    error = pthread_join(hilo_ret, (void **)&salida);              // hilo, variable de salida
    printf("Saldo final %f \n" , saldo);
    return 0;
}

/*
Conclusiones:
El programa nos permite implementar la exclusion mutua, la hambruna de proesos y el bloqueo por muerte accidental
de los recursos compartidos de una manera muy sencilla pero efectiva y eficiente utilizando las minimas comparaciones
psibles para acceder a los recursos compartidos.
*/