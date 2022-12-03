#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void eratostenes_sieve_parallel(int argc, char **argv) {
    int n; // granica wyznaczanych liczb pierwszych
    int sqrt_n; // pierwiastek granicy wyznaczanych liczb pierwszych
    int *list1; // lista liczb mniejszych lub równych od pierwiastka z n
    int *list2; // lista liczb większych od pierwiastka z n, lecz mniejszych od n
    char next_option = ' '; // zmienna pomocnicza wykorzystywana do pobrania argumentów przesłanych z lini komend
    int S = 0; // rozmiar przedziałów dla liczb większych od pierwiastka z n, lecz mniejszych od n
    int R = 0; // reszta wynikająca z niemozliości podziału przedziału (sqrt_n, n) na przedziały o równej długości S
    int L = 0; // najmniejsza liczba w obecnym przedziale
    int H = 0; // największa liczba w obecnym przedziale
    int r = 0; // ranga obecnego procesu
    int p = 0; // liczba procesów
    int c = 0;
    int m = 0;

    // Inicjializacja MPI(bibliotek do multiprocessingu)
    MPI_Init(&argc, &argv);

    // Określenie rangi i ilości procesów
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
   
    // Pobranie z argumentów wartości n
    while((next_option = getopt(argc, argv, "n:")) != -1) {
        switch(next_option) {
            case 'n':
                n = atoi(optarg);
                break;
            case '?':
            default:
                fprintf(stderr, "Usage: %s [-n n]\n", argv[0]);
                exit(-1);
        }
    }

    sqrt_n = (int)sqrt(n);
    S = (n-(sqrt_n+1)) / p;
    R = (n-(sqrt_n+1)) % p;
    L = sqrt_n + r*S + 1;
    H = L+S-1;
    if(r == p-1) {
        H += R;
    }

    list1 = (int*)malloc((sqrt_n+1) * sizeof(int));
    list2 = (int*)malloc((H-L+1) * sizeof(int));

    if(list1 == NULL) {
        exit(-1);
    }
    if(list2 == NULL) {
        exit(-1);
    }

    // Wyzeruj wartości w listach
    for(c = 2; c <= sqrt_n; c++) {
        list1[c] = 0;
    }
    for(c = L; c <= H; c++) {
        list2[c-L] = 0;
    }

    int counter = 0;

    // Sito eratostenesa
    for(c = 2; c <= sqrt_n; c++) {

        // Jeżeli liczba c nie jest skreślona(skreślenie == 1)
        // Potraktuj c jako najmniejszą liczbę pierwszą i rozpocznij skreślanie
        if(list1[c] == 0) {

            // Wykreśl wielokrotności liczby c do pierwiestka z n
            m = c * c;
            while (m <= sqrt_n) {
                list1[m] = 1;
                m += c;
            }

            // Wykreśl wielokrotności w przedziale danego procesu powyżej pierwiestka z n
            m = L;
            while ( m%c != 0 ) {
                m++;
            }
            while (m <= H) {
                list2[m-L] = 1;
                m += c;
            }
        }
    }

    // Jeżeli ranga procesu jest równa zero(proces główny) wyświetl wyniki
    if(r == 0) {
        // Wyświetlanie liczb pierwszych do pierwiastka z n
        for(c = 2; c <= sqrt_n; c++) {
            if(list1[c] == 0) {
                // printf("%d ", c);
                counter++;
            }
        }

        // Wyświetlanie liczb pierwszych dla przedziału powyżej pierwiastka z n
        // przydzielonego dla procesu o randze 0
        for(c = L; c <= H; c++) {
            if(list2[c-L] == 0) {
                // printf("%d ", c);
                counter++;
            }
        }

        // Wyświetl liczby pierwsze obliczone przez pozostałe procesy
        for(r = 1; r <= p-1; r++) {
            
            // Oblicz przedział dla odpowiedniej rangi procesu
            L = sqrt_n + r*S + 1;
            H = L+S-1;
            if(r == p-1) {
                H += R;
            }
            
            // Zapytaj o obliczone liczby pierwsze z przedziału o randze r
            MPI_Recv(list2, H-L+1, MPI_INT, r, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // Wyświetl liczby pierwsze z przedziału przydzielonemu procesowi o randze r
            for(c = L; c <= H; c++) {
                if(list2[c-L] == 0) {
                    // printf("%d ", c);
                    counter++;
                }
            }
        }
        printf("c:%d ", counter);
    }
    // Jeżeli proces nie jest procesem głwonym, zwróć procesowi głównemu listę liczb pierwszych
    // obliczonych dla przedziału przydzielonemu temu procesowi
    else {
        MPI_Send(list2, H-L+1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    free(list2);
    free(list1);

    // Finalizacja MPI
    MPI_Finalize();
}

int main(int argc, char **argv) {
    clock_t begin = clock();

    eratostenes_sieve_parallel(argc, argv);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
    printf("%lf ", time_spent);

    return 0;
}