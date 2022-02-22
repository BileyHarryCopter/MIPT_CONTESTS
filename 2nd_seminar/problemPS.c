#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


struct sieve_t {
    unsigned int size;
    unsigned char * sieve_adress;
};

int Is_Prime (int n) { // возвращаемые значения для выполнения условия
    if ((n == 2) || (n == 3)) {
        return 1;  //1
    }
    if ((n < 2) || ((n % 2) == 0) || ((n % 3) == 0)) {
        return 0;  //0
    }
    for (int i = 5; i*i <= n; i = i + 6) {
        if ( (n % i == 0) || (n % (i + 2) == 0) ) {
            return 0;
        }
    }
    return 1;
}

// создаю структуру типа решето с входным потоком из числа N
// в ней на адрес решета выделаяю память
// этот адрес присваиваю новой структуре, которое будет результирующим, +asserts
// ввожу новую переменную, значение которой будет равно числу итераций цикла
// заполнения решета

struct sieve_t init_sieve (unsigned int N) { // это функция, карл
    assert(N > 2);
    //  объявление новой структуры
    struct sieve_t result;
    result.sieve_adress =  calloc (N, sizeof (unsigned char));;
    result.size = (unsigned)sqrt(N) + 1; // приводим к типу

    assert(result.sieve_adress != NULL);

    //  заполнение новой структуры
    result.sieve_adress[0] = 1;


    for (int i = 1; i < result.size; i++) {
        i += 1;
        if (Is_Prime(i)) {  // число получается простым => все кратные ему из N заменяем на 1
            for (int j = i*i; j <= N; j += i) { // проход по всем составным, кратным данному простому, с последующей из заменой на 1
                result.sieve_adress[j - 1] = 1;
            }
        }
        i -= 1;
    } // предполагаем, что все числа до N образуют решето Эратосфена

   return result; // возвращает структуру решета
};

void free_sieve (struct sieve_t *s) {
    free (s->sieve_adress);
    s->sieve_adress = 0;
    s->size = 0;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
                     // нахождение n-го простого числа
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int nth_prime (struct sieve_t *sv, int N) {
    int sum =0;
    int i = 0;
    while (sum != N) {
        if (sv->sieve_adress[i] == 0) {
            sum ++;
        }
        i++;
    }
    return i;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int main() {

    int N = 0;
    int numb = 0;
    scanf ("%d", &N);

    struct sieve_t RECETO = init_sieve (N);

    for (int i = 0; i < N; i++) {

        if ( i % 10 == 0) {
            printf("\n");
        }
        printf("%3d", RECETO.sieve_adress[i]);
    }

    printf("\n\n");

    printf("%d\n", (RECETO.sieve_adress[N-1] == 0)? 1 : 0);
////
    printf ("Введите номер простого числа:\n");
    scanf ("%d", &numb);

    printf("%d-е простое число: %d\n", numb, nth_prime(&RECETO, numb));

    return 0;
}
