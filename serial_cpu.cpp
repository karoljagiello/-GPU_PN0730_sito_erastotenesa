#include <iostream>
#include <cmath>
#include <getopt.h>
#include <vector>
#include <time.h>

using namespace std;

vector<int> eratostenes_sieve(int n) {
    int sqrt_n = (int) sqrt(n);
    bool* sieve = new bool[n]();
    vector<int> primes = {};

    for (int i = 2; i <= sqrt_n; i++) {
        if (sieve[i] == false) {
            primes.push_back(i);

            for (int p = i*i; p <= n; p+=i) {
                sieve[p] = true;
            }
        }
    }

    for (int i = sqrt_n + 1; i < n; i++) {
        if (sieve[i] == false) {
            primes.push_back(i);
        }
    }

    delete[] sieve;
    return primes;
}

int main(int argc, char** argv) {
    int n;
    int should_print = true;

    char next_option;
    if( (next_option = getopt(argc, argv, "n:")) == -1 || next_option == 63) {
        printf("Nie podano granicy wyznaczania liczb pierwszych. Podaj te wartosc jako flage '-n'\n");
        return 0;
    }
    else {
        n = atoi(optarg);
    }
    if (next_option = getopt(argc, argv, "silent:") != -1){
        should_print = false;
    }

    clock_t begin = clock();
    vector<int> primes = eratostenes_sieve(n);
    clock_t end = clock();
    if(should_print){
        for (int i: primes) {
            printf("%d ", i);
        }
    }
    printf("\n");
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Czas ekzegucji algorytmu w wersji sekwencyjnej na CPU: %lfs\n", time_spent);

    return 0;
}
