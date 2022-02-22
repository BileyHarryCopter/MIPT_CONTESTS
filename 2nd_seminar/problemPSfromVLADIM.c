#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// зачем нужна стрктура
// что делаетс калок
// почему pn неэффективно и недостаточно


struct sieve_t {
  unsigned size;    // размер решета
  unsigned char *sieve;    //   указатель на память
};

// создаем структуру, в которой есть структура
// по адресу sieve вызываем память калоком
//

struct sieve_t init_sieve (unsigned n) {
    struct sieve_t res;
    int i, j;
    unsigned char *sieve;
    assert (n > 2);
    sieve = calloc (n, sizeof (unsigned char));
    res.size = n;
    res.sieve = sieve;
    assert ((n > 1) && (sieve != NULL));
    unsigned r = (unsigned)sqrt(n) + 1;

    // TODO: your code here
    // initially sieves have all zeros
    // set one for all composite numbers

    for (i = 2; i < r; i++) {
        if (is_prime(res, j))
            for (j = i*i; j < n; j++) {
                set_composite (res, j);
            }
    }
    return res;
}

void free_sieve (struct sieve_t *s) {
    free (s->sieve);
    s->sieve = 0;
    s->size = 0;
}

int is_prime(struct sieve_t s, unsigned n) {
    assert(n < s.size);
    return (s.sieve[n] == 1) ? 0 : 1;
}

int main() {
    int res, size, nqueries, i;
    res = scanf("%d%d", &size, &nqueries);
    if (res != 2 || size <= 2 || nqueries <= 0) {
        printf("%s\n", "Wrong size or nqueries");
        abort();
  }

    struct sieve_t s = init_sieve(size);

    for (i = 0; i < nqueries; ++i) {
        int num, pr;
        res = scanf("%d", &num);
        if (res != 1 || num >= size || num < 2) {
            printf("%s\n", "Wrong query");
            abort();
        }
        pr = is_prime(s, num);
        printf("%d ", pr);
    }
    printf("\n");

    free_sieve(&s);
}
