#include <pthread.h>
#include <stdio.h>
int proc_fav,
proc1wantIn,
proc2wantIn,
error,
salida;
float saldo = 1000.0; // se da un saldo inicial

void *proc_deposito(void *saldo_ptr) {
    float deposito;
    do {
        proc1wantIn = 1;
        proc_fav = 2;
        while (proc2wantIn && proc_fav == 2);
        printf("¿Cuanto desea depositar?\n");
        scanf("%f", &deposito);
        saldo = saldo + deposito;   
        printf("Saldo actualizado: %f \n", saldo);
        fflush(stdin);
        proc1wantIn = 0;
        int r = rand() % 3;
        sleep(r); // random entre 1 y 3
    } while (deposito != 0.0);
    pthread_exit(NULL);
}
void *proc_retiro(void *saldo_ptr) {
    float retiro;
    do {
        proc2wantIn = 1;
        proc_fav = 1;
        while (proc1wantIn && proc_fav == 1);
        printf("¿Cuanto desea retirar?\n");
        scanf("%f", &retiro);
        if(saldo - retiro >= 0){
            saldo = saldo - retiro;   
            printf("Saldo actualizado: %f \n", saldo);
            fflush(stdin);
        }else{
            printf("No es posible realizar el retiro, cuenta con: %f \n", saldo);
            fflush(stdin);
        }
        proc2wantIn = 0;
        int r = rand() % 3;
        sleep(r); // random entre 1 y 3
    } while (retiro != 0.0);
    pthread_exit(NULL);
}
int main() {
    pthread_t hilo_dep, hilo_ret;
    error = pthread_create( &hilo_dep, NULL, proc_deposito, NULL); // &x
    error = pthread_create(&hilo_ret, NULL, proc_retiro, NULL);
    error = pthread_join(hilo_dep, (void **)&salida); //hilo0, (void **)&salida
    error = pthread_join(hilo_ret, (void **)&salida);
    printf("Saldo final %f \n" , saldo);
    return 0;
}