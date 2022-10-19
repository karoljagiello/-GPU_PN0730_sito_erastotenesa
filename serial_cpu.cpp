#include <iostream>
#include <cmath>
#include <getopt.h>
#include <vector>
#include <time.h>

using namespace std;

vector<int> eratostenes_siege(int n) {
    int sqrt_n = (int) sqrt(n);
    int* siege = new int[n];
    int p;
    vector<int> primes = {};

    for (int i = 2; i <= sqrt_n; i++) {
        if (siege[i] == 0) {
            primes.push_back(i);
            p = i * i;
            while (p <= n) {
                siege[p] = 1;
                p += i;
            }
        }
    }

    for (int i = sqrt_n + 1; i < n; i++) {
        if (siege[i] == 0) {
            primes.push_back(i);
        }
    }

    delete siege;

    return primes;
}

int main(int argc, char** argv) {
    clock_t begin = clock();
    int n;

    char next_option;
    if( (next_option = getopt(argc, argv, "n:")) == -1 || next_option == 63) {
        printf("Nie podano granicy wyznaczania liczb pierwszych. Podaj tą wartosc jako flage '-n'\n");
        return 0;
    }
    else {
        n = atoi(optarg);
    }

    vector<int> primes = eratostenes_siege(n);
    for (int i: primes) {
        printf("%d ", i);
    }
    printf("\n");
        clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Czas ekzegucji algorytmu w wersji sekwencyjnej na CPU: %lfs\n", time_spent);

    return 0;
}
