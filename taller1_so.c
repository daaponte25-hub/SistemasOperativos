#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Recurso compartido
int variable_compartida = 0;

// Mutex para Exclusión Mutua en la variable compartida
pthread_mutex_t mutex_variable;

// Semáforos POSIX para Sincronización de secuencia
sem_t semA_C; // Notifica a C que A escribió Cifra 1
sem_t semC_B; // Notifica a B que C leyó y limpió la variable
sem_t semB_C; // Notifica a C que B escribió Cifra 2

// --- INTEGRANTE 1: Hilo A ---
void* HiloA(void* arg) {
    int variable_compartida = 15;
    
    // TO-DO Proteger escritura con Mutex e inicializar variable compartida
    
    
    // TO-DO Notificar a Hilo C
    return NULL;
}

// --- INTEGRANTE 2: Hilo B ---
void* HiloB(void* arg) {
    int cifra_b = 25;
    
    // TO-DO Esperar a que Hilo C haya leído Cifra 1 y limpiado la variable
    
    // TO-DO Proteger escritura con Mutex y actualizar variable compartida
   
    
    // TO-DO Notificar a Hilo C
	
    return NULL;
}

// --- INTEGRANTE 3, Simon Yajure: Hilo C ---
void* HiloC(void* arg) {
    int cifra1 = 0, cifra2 = 0, total = 0;

    sem_wait(&semA_C);

    pthread_mutex_lock(&mutex_variable);
    cifra1 = variable_compartida;
    variable_compartida =0;
    pthread_mutex_unlock(&mutex_variable);

    sem_post(&semC_B);


    sem_wait(&semB_C);

    pthread_mutex_lock(&mutex_variable);
    cifra2 = variable_compartida;
    total = cifra1 + cifra2;
    pthread_mutex_unlock(&mutex_variable);

    // Renderizado final
    printf("\n================ RENDERIZADO DE RESULTADOS ================\n");
    printf("-> Cifra enviada por Hilo A: %d\n", cifra1);
    printf("-> Cifra enviada por Hilo B: %d\n", cifra2);
    printf("-> SUMA TOTAL CALCULADA POR HILO C: %d\n", total);
    printf("===========================================================\n");

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t hA, hB, hC;
    pthread_mutex_init(&mutex_variable, NULL);
    sem_init(&semA_C, 0, 0);
    sem_init(&semC_B, 0, 0);
    sem_init(&semB_C, 0, 0);

    printf("=== INICIO DE LA PRUEBA DE FUEGO ===\n\n");

    pthread_create(&hA, NULL, HiloA, NULL);
    pthread_create(&hB, NULL, HiloB, NULL);
    pthread_create(&hC, NULL, HiloC, NULL);

    pthread_join(hA, NULL);
    pthread_join(hB, NULL);
    pthread_join(hC, NULL);

    pthread_mutex_destroy(&mutex_variable);
    sem_destroy(&semA_C);
    sem_destroy(&semC_B);
    sem_destroy(&semB_C);

    printf("\n=== FIN DE LA EJECUCION ===\n");
    return 0;
}